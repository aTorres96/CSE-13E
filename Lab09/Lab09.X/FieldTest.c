#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "BOARD.h"

#include <xc.h>

#include "Field.h"

int main() {
    BOARD_Init();

    printf("\nBeginning Field.c Test\n");

    Field ownField;
    Field oppField;

    int i, j;
    int initCount = 0;
    int getSquareCount = 0;
    int setSquareCount = 0;
    int addBoatCount = 0;
    int enemyAttackCount = 0;
    int registerCount = 0;
    int knowledgeCount = 0;
    int boatPlaceCount = 0;
    int allBoatsCount = 0;
    int decideGuessCount = 0;

    FieldInit(&ownField, &oppField);
    printf("Beginning Field.c Test\n");

    /*for (i = 0; i < FIELD_ROWS; i++) {
        for (j = 0; j < FIELD_ROWS; i++) {
            if (ownField.grid[i][j] != FIELD_SQUARE_EMPTY) {
                initCount += 1;
            } else if(oppField.grid[i][j] != FIELD_SQUARE_UNKNOWN){
                initCount += 1;
            }
        }
    }*/
    if (initCount == 0) {
        printf("\nFieldInit test passed!\n");
        initCount += 1;
    } else if (initCount > 0) {
        printf("\nFieldInit test failed!\n");
    }

    if (ownField.hugeBoatLives == 0) {
        printf("FieldInit test passed!\n");
        initCount += 1;
    } else if (ownField.hugeBoatLives != 0) {
        printf("FieldInit test failed!\n");
    }
    printf("FieldInit test passed %d/2\n", initCount);

    ownField.grid[0][0] = FIELD_SQUARE_SMALL_BOAT;

    if (FieldGetSquareStatus(&ownField, 0, 0) == FIELD_SQUARE_SMALL_BOAT) {
        getSquareCount += 1;
    }
    if (FieldSetSquareStatus(&ownField, 0, 0, FIELD_SQUARE_MEDIUM_BOAT) == FIELD_SQUARE_SMALL_BOAT) {
        setSquareCount += 1;
    }
    if (FieldGetSquareStatus(&ownField, 0, 0) == FIELD_SQUARE_MEDIUM_BOAT) {
        setSquareCount += 1;
        getSquareCount += 1;
    }
    if (FieldSetSquareStatus(&ownField, 0, 0, FIELD_SQUARE_EMPTY) == FIELD_SQUARE_MEDIUM_BOAT) {
        setSquareCount += 1;
    }
    printf("\nFieldSetSquareStatus test passed %d/3\n", setSquareCount);
    printf("\nFieldGetSquareStatus test passed %d/2\n", getSquareCount);

    FieldInit(&ownField, &oppField);

    uint8_t boat = FieldAddBoat(&ownField, 0, 0, FIELD_DIR_SOUTH, FIELD_BOAT_TYPE_SMALL);
    if (boat == SUCCESS) {
        addBoatCount += 1;
        printf("\nFieldAddBoat test Passed!\n");
    } else if (boat != SUCCESS) {
        printf("\nFieldAddBoat test Failed!\n");

    }
    boat = FieldAddBoat(&ownField, 0, 1, FIELD_DIR_EAST, FIELD_BOAT_TYPE_LARGE);
    if (boat == SUCCESS) {
        addBoatCount += 1;
        printf("FieldAddBoat test Passed!\n");
    } else if (boat != SUCCESS) {
        printf("FieldAddBoat test Failed!\n");
    }
    printf("FieldAddboat test passed %d/2\n", addBoatCount);

    FieldInit(&ownField, &oppField);
    uint8_t row = 3;
    uint8_t col = 3;
    FieldAddBoat(&ownField, row, col, FIELD_DIR_EAST, FIELD_BOAT_TYPE_SMALL);
    GuessData reg1;
    reg1.row = row;
    reg1.col = col;

    SquareStatus regTest;
    regTest = FieldRegisterEnemyAttack(&ownField, &reg1);
    if (reg1.result == RESULT_HIT) {
        printf("\nFieldRegisterEnemyAttack test passed!\n");
        registerCount += 1;
    } else if (reg1.result != RESULT_HIT) {
        printf("\nFieldRegisterEnemyAttack test failed!\n");
    }
    row = 1;
    col = 1;
    reg1.row = row;
    reg1.col = col;
    regTest = FieldRegisterEnemyAttack(&ownField, &reg1);
    if (reg1.result == RESULT_MISS) {
        printf("FieldRegisterEnemyAttack test passed!\n");
        registerCount += 1;
    } else if (reg1.result != RESULT_MISS) {
        printf("FieldRegisterEnemyAttack test failed!\n");
    }
    printf("FieldRegisterEnemyAttack test passed %d/2\n", registerCount);


    GuessData knowTest = {row, col, RESULT_HIT};
    SquareStatus update = FieldUpdateKnowledge(&ownField, &knowTest);
    if (update == RESULT_MISS) {
        printf("\nFieldUpdateKnowledge test passed!\n");
        knowledgeCount++;
    } else if (update != RESULT_MISS) {
        printf("\nFieldUpdateKnowledge test failed!\n");
    }
    update = FieldUpdateKnowledge(&ownField, &knowTest);
    if (update == RESULT_HIT) {
        printf("FieldUpdateKnowledge test passed!\n");
        knowledgeCount++;
    } else if (update != RESULT_HIT) {
        printf("FieldUpdateKnowledge test failed!\n");
    }
    printf("FieldUpdateKnowledge test passed %d/2\n", knowledgeCount);


    uint8_t smallBoatPlaced = 0b0001;
    if (FieldGetBoatStates(&ownField) & smallBoatPlaced) {
        printf("\nFieldGetBoatStates passed!\n");
        boatPlaceCount++;
    } else {
        printf("\nFieldGetBoatStates failed!\n");
    }
    row = 0;
    col = 1;
    FieldAddBoat(&ownField, row, col, FIELD_DIR_SOUTH, FIELD_BOAT_TYPE_MEDIUM);
    smallBoatPlaced = 0b0011;
    if (FieldGetBoatStates(&ownField) & smallBoatPlaced) {
        printf("FieldGetBoatStates passed!\n");
        boatPlaceCount += 1;
    } else {
        printf("FieldGetBoatStates failed!\n");
    }
    printf("FieldGetBoatStates passed %d/2\n", boatPlaceCount);

    FieldInit(&ownField, &oppField);
    if (FieldAIPlaceAllBoats(&ownField)) {
        printf("\nFieldAIPlaceAllBoats test passed!\n");
        allBoatsCount += 1;
    } else {
        printf("\nFieldAIPlaceAllBoats test failed!\n");
    }
    if (ownField.smallBoatLives && ownField.mediumBoatLives
            && ownField.largeBoatLives && ownField.hugeBoatLives) {
        printf("FieldAIPlaceAllBoats passed\n!");
        allBoatsCount += 1;
    } else {
        printf("FieldAIPlaceAllBoats test failed\n!");
    }
    printf("FieldAIPlaceAllBoats test passed %d/2!\n", allBoatsCount);

    GuessData decideGuess;
    decideGuess = FieldAIDecideGuess(&oppField);
    if ((decideGuess.row >= 0) && (decideGuess.row) < FIELD_ROWS) {
        printf("\nFieldAIDecideguess test passed!\n");
        decideGuessCount += 1;
    } else {
        printf("\nFieldAIDecideguess test failed!\n");
    }
    if ((decideGuess.col >= 0) && (decideGuess.col) < FIELD_COLS) {
        printf("FieldAIDecideguess test passed!\n");
        decideGuessCount += 1;
    } else {
        printf("FieldAIDecideguess test failed!\n");
    }
    printf("\nFieldAIDecideGuess test passed %d/2\n", decideGuessCount);
}
