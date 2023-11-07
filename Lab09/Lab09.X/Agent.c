#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "BOARD.h"

#include <xc.h>
#include <sys/attribs.h>

#include "Buttons.h"
#include "Uart1.h"
#include "Oled.h"

#include "Agent.h"
#include "Field.h"
#include "Negotiation.h"
#include "FieldOled.h"


static Field ownField;
static Field oppField;
static FieldOledTurn turn;
static AgentState state;
static GuessData myGuess, oppGuess;
static int turnCount;

/**
 * The Init() function for an Agent sets up everything necessary for an agent before the game
 * starts.  At a minimum, this requires:
 *   -setting the start state of the Agent SM.
 *   -setting turn counter to 0
 * If you are using any other persistent data in Agent SM, that should be reset as well.
 * 
 * It is not advised to call srand() inside of AgentInit.  
 *  */
void AgentInit(void) {
    ButtonsInit();
    FieldInit(&ownField, &oppField);
    FieldAIPlaceAllBoats(&ownField);
    turn = FIELD_OLED_TURN_NONE;
    state = AGENT_STATE_START;
    turnCount = 0;

}

/**
 * AgentRun evolves the Agent state machine in response to an event.
 * 
 * @param  The most recently detected event
 * @return Message, a Message struct to send to the opponent. 
 * 
 * If the returned Message struct is a valid message
 * (that is, not of type MESSAGE_NONE), then it will be
 * passed to the transmission module and sent via UART.
 * This is handled at the top level! AgentRun is ONLY responsible 
 * for generating the Message struct, not for encoding or sending it.
 */
Message AgentRun(BB_Event event) {
    Message msg;
    msg.type = MESSAGE_NONE;
    NegotiationData a;
    NegotiationData b;
    NegotiationData hash;
    NegotiationOutcome coin;

    if (event.type == BB_EVENT_RESET_BUTTON) {
        AgentInit();
        OledClear(OLED_COLOR_BLACK);
        OledDrawString("\nPress BTN4 to start a new game.\n");
        OledUpdate();
    }

    if (event.type == BB_EVENT_ERROR) {
        OledDrawString("\nAn Error occured...\n");
        OledDrawString("Press BTN4 to start a new game.\n");
        OledUpdate();
    }

    switch (state) {
        case AGENT_STATE_START:
            if (event.type == BB_EVENT_START_BUTTON) {
                a = rand();
                hash = NegotiationHash(a);
                msg.type = MESSAGE_CHA;
                msg.param0 = hash;
                FieldInit(&ownField, &oppField);
                FieldAIPlaceAllBoats(&ownField);
                state = AGENT_STATE_CHALLENGING;
            }
            if (event.type == BB_EVENT_CHA_RECEIVED) {
                b = rand();
                hash = event.param0;
                msg.type = MESSAGE_ACC;
                msg.param0 = b;
                FieldInit(&ownField, &oppField);
                FieldAIPlaceAllBoats(&ownField);
                state = AGENT_STATE_ACCEPTING;
            }
            FieldOledDrawScreen(&ownField, &oppField, turn, turnCount);
            break;
        case AGENT_STATE_CHALLENGING:
            if (event.type == BB_EVENT_ACC_RECEIVED) {
                b = event.param0;
                msg.type = MESSAGE_REV;
                msg.param0 = a;
                coin = NegotiateCoinFlip(a, b);

                if (coin == TAILS) {
                    state = AGENT_STATE_DEFENDING;
                } else if (coin == HEADS) {
                    state = AGENT_STATE_WAITING_TO_SEND;
                }
            }
            FieldOledDrawScreen(&ownField, &oppField, turn, turnCount);
            break;
        case AGENT_STATE_ACCEPTING:
            if (event.type == BB_EVENT_REV_RECEIVED) {
                a = event.param0;
                coin = NegotiateCoinFlip(a, b);
                if (NegotiationVerify(a, hash) == FALSE) {
                    state = AGENT_STATE_END_SCREEN;
                }
                if (coin == HEADS) {
                    state = AGENT_STATE_DEFENDING;
                } else if (coin == TAILS) {
                    myGuess = FieldAIDecideGuess(&oppField);
                    msg.param0 = myGuess.row;
                    msg.param1 = myGuess.col;
                    msg.type = MESSAGE_SHO;
                    state = AGENT_STATE_ATTACKING;
                }
            }
            FieldOledDrawScreen(&ownField, &oppField, turn, turnCount);
            break;
        case AGENT_STATE_ATTACKING:
            if (event.type == BB_EVENT_RES_RECEIVED) {
                oppGuess.row = event.param0;
                oppGuess.col = event.param1;
                oppGuess.result = event.param2;
                FieldUpdateKnowledge(&oppField, &oppGuess);
                if (FieldGetBoatStates(&oppField) == 0) {
                    state = AGENT_STATE_END_SCREEN;
                } else {
                    state = AGENT_STATE_DEFENDING;
                    turn = FIELD_OLED_TURN_THEIRS;
                }
            }
            FieldOledDrawScreen(&ownField, &oppField, turn, turnCount);
            break;
        case AGENT_STATE_DEFENDING:
            if (event.type == BB_EVENT_SHO_RECEIVED) {
                turn = FIELD_OLED_TURN_THEIRS;
                oppGuess.row = event.param0;
                oppGuess.col = event.param2;
                FieldRegisterEnemyAttack(&ownField, &oppGuess);
                msg.param0 = oppGuess.row;
                msg.param1 = oppGuess.col;
                msg.param2 = oppGuess.result;
                msg.type = MESSAGE_RES;
            }
            if (FieldGetBoatStates(&ownField) == 0) {
                state = AGENT_STATE_END_SCREEN;
            } else {
                state = AGENT_STATE_WAITING_TO_SEND;
                turn = FIELD_OLED_TURN_MINE;
            }
            FieldOledDrawScreen(&ownField, &oppField, turn, turnCount);
            break;
        case AGENT_STATE_WAITING_TO_SEND:
            if (event.type == BB_EVENT_MESSAGE_SENT) {
                turnCount += 1;
                myGuess = FieldAIDecideGuess(&oppField);
                msg.param0 = myGuess.row;
                msg.param1 = myGuess.col;
                msg.type = MESSAGE_SHO;
                state = AGENT_STATE_ATTACKING;
            }
            FieldOledDrawScreen(&ownField, &oppField, turn, turnCount);
            break;
        case AGENT_STATE_END_SCREEN:
            OledClear(OLED_COLOR_BLACK);
            OledUpdate();
            if (FieldGetBoatStates(&ownField) == 0) {
                OledDrawString("Alas....\nDefeat. :'(\n");
            } else if (FieldGetBoatStates(&oppField) == 0) {
                OledDrawString("Hooray!\n Victory! :)\n");
            }
            OledUpdate();
            break;
    }
    return msg;
}

/** * 
 * @return Returns the current state that AgentGetState is in.  
 * 
 * This function is very useful for testing AgentRun.
 */
AgentState AgentGetState(void) {

    return state;
}

/** * 
 * @param Force the agent into the state given by AgentState
 * 
 * This function is very useful for testing AgentRun.
 */
void AgentSetState(AgentState newState) {

    state = newState;
}


