// User libraries
#include "rpn.h"
#include "stack.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "BOARD.h"

int isNum(char *token);

int isNum(char *token) {
    int i, j, decCount;
    j = 0;
    decCount = 0;
    if (token[0] == '-')
        j = 1;
    for (i = j; i < strlen(token); i++) {
        if (token[i] == '.')
            decCount++;
        else if (!isdigit(token[i]))
            return FALSE;
    }
    if (decCount > 1)
        return FALSE;
    else
        return TRUE;
}

int RPN_Evaluate(char * rpn_string, double * result) {

    char *token = strtok(rpn_string, " ");

    double op1, op2, output, divSub1, divSub2, tokenDub; //divSub1 and 2 are to
    //variables in the stack
    // for div and sub.
    struct Stack myStack;
    StackInit(&myStack);

    while (token != NULL) {
        if (*token == '+') {
            if (StackPop(&myStack, &op2) == STANDARD_ERROR)
                return RPN_ERROR_STACK_UNDERFLOW;
            if (StackPop(&myStack, &op1) == STANDARD_ERROR)
                return RPN_ERROR_STACK_UNDERFLOW;
            output = (op2 + op1);
            if (StackPush(&myStack, output) == STANDARD_ERROR)
                return RPN_ERROR_STACK_OVERFLOW;
        } else if (*token == '*') {
            if (StackPop(&myStack, &op1) == STANDARD_ERROR)
                return RPN_ERROR_STACK_UNDERFLOW;
            if (StackPop(&myStack, &op2) == STANDARD_ERROR)
                return RPN_ERROR_STACK_UNDERFLOW;
            output = (op1 * op2);
            if (StackPush(&myStack, output) == STANDARD_ERROR)
                return RPN_ERROR_STACK_OVERFLOW;
        } else if (*token == '-') {
            if (StackPop(&myStack, &divSub2) == STANDARD_ERROR)
                return RPN_ERROR_STACK_UNDERFLOW;
            if (StackPop(&myStack, &divSub1) == STANDARD_ERROR)
                return RPN_ERROR_STACK_UNDERFLOW;
            output = (divSub1 - divSub2);
            if (StackPush(&myStack, output) == STANDARD_ERROR)
                return RPN_ERROR_STACK_OVERFLOW;
        } else if (*token == '/') {
            if (StackPop(&myStack, &divSub2) == STANDARD_ERROR)
                return RPN_ERROR_STACK_UNDERFLOW;
            if (StackPop(&myStack, &divSub1) == STANDARD_ERROR)
                return RPN_ERROR_STACK_UNDERFLOW;
            if (divSub2 != 0.0) {
                output = (divSub1 / divSub2);
                if (StackPush(&myStack, output) == STANDARD_ERROR)
                    return RPN_ERROR_STACK_OVERFLOW;
            } else
                return RPN_ERROR_DIVIDE_BY_ZERO;
        } else if (isNum(token)) {
            tokenDub = atof(token);
           if (StackPush(&myStack, tokenDub) == STANDARD_ERROR)
            return RPN_ERROR_STACK_OVERFLOW;
        } else
            return RPN_ERROR_INVALID_TOKEN;

        token = strtok(NULL, " ");
    }
    if (StackGetSize(&myStack) > 1) {
        return RPN_ERROR_TOO_MANY_ITEMS_REMAIN;
    } else if (StackGetSize(&myStack) < 1) {
        return RPN_ERROR_TOO_FEW_ITEMS_REMAIN;
    } else
        StackPop(&myStack, result);
    return RPN_NO_ERROR;
}
