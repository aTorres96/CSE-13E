// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//CMPE13 Support Library
#include "BOARD.h"



// User libraries
#include "rpn.h"


// **** Set macros and preprocessor directives ****
// The lab calls for 60 characters of user input
#define MAX_INPUT_LENGTH 60

int main() {
    BOARD_Init();

    //What follows is starter code.  You will need to modify it!

    char rpn_sentence[MAX_INPUT_LENGTH + 2];
    double result;
    int output_error;

    printf("Welcome to atorre's RPN calculator.  Compiled on %s %s\n", __DATE__, __TIME__);
    while (1) {

        printf("\n");
        printf("Enter floats and + - / * in RPN format:\n");

        strtok(rpn_sentence, "\n");

        fgets(rpn_sentence, sizeof (rpn_sentence), stdin);

        output_error = RPN_Evaluate(rpn_sentence, &result);
        
        switch (output_error) {
            case RPN_NO_ERROR:
                printf("result = %f\n", result);
                break;
            case RPN_ERROR_STACK_OVERFLOW:
                printf("There is a stack overflow error.\n");
                break;
            case RPN_ERROR_STACK_UNDERFLOW:
                printf("There is a stack underflow error.\n");
                break;
            case RPN_ERROR_INVALID_TOKEN:
                printf("Invalid token error.\n");
                break;
            case RPN_ERROR_DIVIDE_BY_ZERO:
                printf("Divide by zero error.\n");
                break;
            case RPN_ERROR_TOO_FEW_ITEMS_REMAIN:
                printf("Too few items remain error.\n");
                break;
            case RPN_ERROR_TOO_MANY_ITEMS_REMAIN:
                printf("Too many items remain error.\n");
                break;
        }
    }
    while (1);
}
