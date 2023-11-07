#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <xc.h>
#include <sys/attribs.h>

#include "BOARD.h"
#include "Uart1.h"
#include "Oled.h"

#include "Field.h"

#define NUM_BOATS 4
#define NUM_DIR 4
#define DIR_RAND 1

/**
 * This function is optional, but recommended.   It prints a representation of both
 * fields, similar to the OLED display.
 * @param f The field to initialize.
 * @param p The data to initialize the entire field to, should be a member of enum
 *                     SquareStatus.
 */
void FieldPrint_UART(Field *own_field, Field * opp_field) {
}

void FieldInit(Field *own_field, Field *opp_field) {
    int i, j;

    for (i = 0; i < FIELD_ROWS; i++) {
        for (j = 0; j < FIELD_COLS; j++) {
            own_field->grid[i][j] = FIELD_SQUARE_EMPTY;
            opp_field->grid[i][j] = FIELD_SQUARE_UNKNOWN;
        }
    }
    own_field->smallBoatLives = 0;
    own_field->mediumBoatLives = 0;
    own_field->largeBoatLives = 0;
    own_field->hugeBoatLives = 0;

    opp_field->smallBoatLives = FIELD_BOAT_SIZE_SMALL;
    opp_field->mediumBoatLives = FIELD_BOAT_SIZE_MEDIUM;
    opp_field->largeBoatLives = FIELD_BOAT_SIZE_LARGE;
    opp_field->hugeBoatLives = FIELD_BOAT_SIZE_HUGE;
}

SquareStatus FieldGetSquareStatus(const Field *f, uint8_t row, uint8_t col) {

    if ((row > FIELD_ROWS) || (col > FIELD_COLS)) {
        return FIELD_SQUARE_INVALID;
    }
    else {
        return f->grid[row][col];
    }
}

SquareStatus FieldSetSquareStatus(Field *f, uint8_t row, uint8_t col, SquareStatus p) {

    SquareStatus oldValue = FieldGetSquareStatus(f, row, col);

    if (oldValue != FIELD_SQUARE_INVALID) {
        f->grid[row][col] = p;
    }

    return oldValue;
}

uint8_t FieldAddBoat(Field *own_field, uint8_t row, uint8_t col, BoatDirection dir, BoatType boat_type) {

    if ((row < 0) || (row > FIELD_ROWS - 1) || (col < 0) || (col > FIELD_COLS - 1)) {
        return STANDARD_ERROR;
    }
    BoatSize size;
    SquareStatus boat;
    int i;

    switch (boat_type) {
        case FIELD_BOAT_TYPE_SMALL:
            own_field->smallBoatLives = FIELD_BOAT_SIZE_SMALL;
            size = FIELD_BOAT_SIZE_SMALL;
            boat = FIELD_SQUARE_SMALL_BOAT;
            break;
        case FIELD_BOAT_TYPE_MEDIUM:
            own_field->mediumBoatLives = FIELD_BOAT_SIZE_MEDIUM;
            size = FIELD_BOAT_SIZE_MEDIUM;
            boat = FIELD_SQUARE_MEDIUM_BOAT;
            break;
        case FIELD_BOAT_TYPE_LARGE:
            own_field->largeBoatLives = FIELD_BOAT_SIZE_LARGE;
            size = FIELD_BOAT_SIZE_LARGE;
            boat = FIELD_SQUARE_LARGE_BOAT;
            break;
        case FIELD_BOAT_TYPE_HUGE:
            own_field->hugeBoatLives = FIELD_BOAT_SIZE_HUGE;
            size = FIELD_BOAT_SIZE_HUGE;
            boat = FIELD_SQUARE_HUGE_BOAT;
            break;
    }
    switch (dir) {
        case FIELD_DIR_EAST:
            for (i = 0; i < size; i++) {
                if (FieldGetSquareStatus(own_field, row + 1, col + i) != FIELD_SQUARE_EMPTY) {
                    return STANDARD_ERROR;
                }
            }
            break;
        case FIELD_DIR_SOUTH:
            for (i = 0; i < size; i++) {
                if (FieldGetSquareStatus(own_field, row + i, col + i) != FIELD_SQUARE_EMPTY) {
                    return STANDARD_ERROR;
                }
            }
            break;
    }

    for (i = 0; i < size; i++) {
        if (dir == FIELD_DIR_EAST) {
            own_field->grid[row][col + i] = boat;
        } else if (dir == FIELD_DIR_SOUTH) {
            own_field->grid[row + i][col] = boat;
        }

    }

    return SUCCESS;
}

SquareStatus FieldRegisterEnemyAttack(Field *own_field, GuessData *opp_guess) {

    SquareStatus previous = own_field->grid[opp_guess->row][opp_guess->col];
    if (own_field->grid[opp_guess->row][opp_guess->col] == FIELD_SQUARE_EMPTY) {
        own_field->grid[opp_guess->row][opp_guess->col] = FIELD_SQUARE_MISS;
        opp_guess->result = RESULT_MISS;
    } else if (own_field->grid[opp_guess->row][opp_guess->col] == FIELD_SQUARE_SMALL_BOAT) {
        own_field->smallBoatLives--;
        if (own_field->smallBoatLives == 0) {
            opp_guess->result = RESULT_SMALL_BOAT_SUNK;
        } else {
            opp_guess->result = RESULT_HIT;
        }
        own_field->grid[opp_guess->row][opp_guess->col] = FIELD_SQUARE_HIT;
    } else if (own_field->grid[opp_guess->row][opp_guess->col] == FIELD_SQUARE_MEDIUM_BOAT) {
        own_field->mediumBoatLives--;
        if (own_field->mediumBoatLives == 0) {
            opp_guess->result = RESULT_MEDIUM_BOAT_SUNK;
        } else {
            opp_guess->result = RESULT_HIT;
        }
        own_field->grid[opp_guess->row][opp_guess->col] = FIELD_SQUARE_HIT;
    } else if (own_field->grid[opp_guess->row][opp_guess->col] == FIELD_SQUARE_LARGE_BOAT) {
        own_field->largeBoatLives--;
        if (own_field->largeBoatLives == 0) {
            opp_guess->result = RESULT_LARGE_BOAT_SUNK;
        } else {
            opp_guess->result = RESULT_HIT;
        }
        own_field->grid[opp_guess->row][opp_guess->col] = FIELD_SQUARE_HIT;
    } else if (own_field->grid[opp_guess->row][opp_guess->col] == FIELD_SQUARE_HUGE_BOAT) {
        own_field->hugeBoatLives--;
        if (own_field->mediumBoatLives == 0) {
            opp_guess->result = RESULT_HUGE_BOAT_SUNK;
        } else {
            opp_guess->result = RESULT_HIT;
        }
        own_field->grid[opp_guess->row][opp_guess->col] = FIELD_SQUARE_HIT;
    }

    return previous;
}

/**
 * This function updates the FieldState representing the opponent's game board with whether the
 * guess indicated within gData was a hit or not. If it was a hit, then the field is updated with a
 * FIELD_SQUARE_HIT at that position. If it was a miss, display a FIELD_SQUARE_EMPTY instead, as
 * it is now known that there was no boat there. The FieldState struct also contains data on how
 * many lives each ship has. Each hit only reports if it was a hit on any boat or if a specific boat
 * was sunk, this function also clears a boats lives if it detects that the hit was a
 * RESULT_*_BOAT_SUNK.
 * @param f The field to grab data from.
 * @param gData The coordinates that were guessed along with their HitStatus.
 * @return The previous value of that coordinate position in the field before the hit/miss was
 * registered.
 */
SquareStatus FieldUpdateKnowledge(Field *opp_field, const GuessData * own_guess) {
    SquareStatus previous = opp_field->grid[own_guess->row][own_guess->col];
//need to fix
    if (own_guess->result == RESULT_HIT) {
        opp_field->grid[own_guess->row][own_guess->col] = FIELD_SQUARE_HIT;
    } else if (own_guess->result == RESULT_MISS) {
        opp_field->grid[own_guess->row][own_guess->col] = FIELD_SQUARE_MISS;

    } else if (own_guess->result == RESULT_SMALL_BOAT_SUNK) {
        opp_field->smallBoatLives = 0;
        opp_field->grid[own_guess->row][own_guess->col] = FIELD_SQUARE_HIT;

    } else if (own_guess->result == RESULT_MEDIUM_BOAT_SUNK) {
        opp_field->mediumBoatLives = 0;
        opp_field->grid[own_guess->row][own_guess->col] = FIELD_SQUARE_HIT;

    } else if (own_guess->result == RESULT_LARGE_BOAT_SUNK) {
        opp_field->largeBoatLives = 0;
        opp_field->grid[own_guess->row][own_guess->col] = FIELD_SQUARE_HIT;

    } else if (own_guess->result == RESULT_HUGE_BOAT_SUNK) {
        opp_field->hugeBoatLives = 0;
        opp_field->grid[own_guess->row][own_guess->col] = FIELD_SQUARE_HIT;

    }
    return previous;
}

/**
 * This function returns the alive states of all 4 boats as a 4-bit bitfield (stored as a uint8).
 * The boats are ordered from smallest to largest starting at the least-significant bit. So that:
 * 0b00001010 indicates that the small boat and large boat are sunk, while the medium and huge boat
 * are still alive. See the BoatStatus enum for the bit arrangement.
 * @param f The field to grab data from.
 * @return A 4-bit value with each bit corresponding to whether each ship is alive or not.
 */
uint8_t FieldGetBoatStates(const Field * f) {
    uint8_t state = 0;
    if (f->smallBoatLives) {
        state |= FIELD_BOAT_STATUS_SMALL;
    }
    if (f->mediumBoatLives) {
        state |= FIELD_BOAT_STATUS_MEDIUM;
    }
    if (f->largeBoatLives) {
        state |= FIELD_BOAT_STATUS_LARGE;
    }
    if (f->hugeBoatLives) {
        state |= FIELD_BOAT_STATUS_HUGE;
    }
    return state;
}

/**
 * This function is responsible for placing all four of the boats on a field.
 * 
 * @param f         //agent's own field, to be modified in place.
 * @return SUCCESS if all boats could be placed, STANDARD_ERROR otherwise.
 * 
 * This function should never fail when passed a properly initialized field!
 */
uint8_t FieldAIPlaceAllBoats(Field * own_field) {

    int i;
    uint8_t row, col;
    BoatDirection dir;
    int small = FALSE;
    int medium = FALSE;
    int large = FALSE;
    int huge = FALSE;
    int status = FALSE;


    while (i < NUM_BOATS) {

        row = rand() % (FIELD_ROWS - 1);
        col = rand() % (FIELD_COLS - 1);
        dir = rand() & DIR_RAND;

        if (small == FALSE) {
            status = FieldAddBoat(own_field, row, col, dir, FIELD_BOAT_TYPE_SMALL);
            if (status == SUCCESS) {
                i++;
                small = TRUE;
            }
        }
        else if (medium == FALSE) {
            status = FieldAddBoat(own_field, row, col, dir, FIELD_BOAT_TYPE_MEDIUM);
            if (status == SUCCESS) {
                i++;
                medium = TRUE;
            }
        }
        else if (large == FALSE) {
            status = FieldAddBoat(own_field, row, col, dir, FIELD_BOAT_TYPE_LARGE);
            if (status == SUCCESS) {
                i++;
                large = TRUE;
            }
        }
        else if (huge == FALSE) {
            status = FieldAddBoat(own_field, row, col, dir, FIELD_BOAT_TYPE_HUGE);
            if (status == SUCCESS) {
                i++;
                medium = TRUE;
            }
        }
    }
    return SUCCESS;
}

/**
 * Given a field, decide the next guess.
 *
 * This function should not attempt to shoot a square which has already been guessed.
 *
 * You may wish to give this function static variables.  If so, that data should be
 * reset when FieldInit() is called.
 * 
 * @param f an opponent's field.
 * @return a GuessData struct whose row and col parameters are the coordinates of the guess.  The 
 *           result parameter is irrelevant.
 */
GuessData FieldAIDecideGuess(const Field * opp_field) {

    GuessData myGuess;

    do {
        myGuess.row = rand() % (FIELD_ROWS - 1);
        myGuess.col = rand() % (FIELD_COLS - 1);
    } while (FieldGetSquareStatus(opp_field, myGuess.row, myGuess.col) != FIELD_SQUARE_UNKNOWN);

    return myGuess;

}

/** 
 * For Extra Credit:  Make the two "AI" functions above 
 * smart enough to beat our AI in more than 55% of games.
 */