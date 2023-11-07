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

int main(){
    BOARD_Init();
    AgentInit();
    int setCount = 0;
    int getCount = 0;
    int runCount = 0;
    printf("\nAgent Test:\n");
    
    AgentState agentTest = AgentGetState();
    if (agentTest == AGENT_STATE_START){
        printf("\nAgentInit test passed!\n");
        printf("\nAgentGetState test passed!\n");
        getCount += 1;
    } else {
        printf("\nAgentInit test failed!\n");
    }
    
    AgentSetState(AGENT_STATE_DEFENDING);
    agentTest = AgentGetState();
    if (agentTest == AGENT_STATE_DEFENDING){
        getCount += 1;
        setCount += 1;
        printf("AgentGetState test passed!\n");
    }
    printf("AgentGetState test passed %d/2!\n", getCount);
    if (setCount == 1){
        printf("\nAgentSetState test passed!\n");
    }
    else {
        printf("\nAgentSetState test Failed!\n");
    }
    AgentSetState(AGENT_STATE_WAITING_TO_SEND);
    agentTest = AgentGetState();
    if (agentTest == AGENT_STATE_WAITING_TO_SEND){
        setCount += 1;
        printf("AgentSetState test passed!\n");
    }
    else {
        printf("AgentSetState test failed!\n");
    }
    printf("AgentSetState test passed %d/2.\n", setCount);
    
    AgentInit();
    BB_Event testEvent;
    testEvent.type = BB_EVENT_START_BUTTON;
    Message testMsg = AgentRun(testEvent);
    
    if (testMsg.type == MESSAGE_CHA){
        runCount += 1;
        printf("\nAgentRun test Passed!\n");
    }
    else {
        printf("\nAgentRun test failed!\n");
    }
    testEvent.type = BB_EVENT_ACC_RECEIVED;
    AgentSetState(AGENT_STATE_CHALLENGING);
    testMsg = AgentRun(testEvent);
    if (testMsg.type == MESSAGE_REV){
        runCount += 1;
        printf("AgentRun test Passed!\n");
    }
    else {
        printf("AgentRun test failed!\n");
    }
    printf("AgentRun test passed %d/2!\n", runCount);
    
    
}
