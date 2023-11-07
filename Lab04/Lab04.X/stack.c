#include <stdio.h>

//CMPE13 Support Library
#include "BOARD.h"


// User libraries
#include "stack.h"

#define EMPTY -1
#define INDEX_HELP 1

void StackInit(struct Stack *stack) {

    stack->currentItemIndex = EMPTY;
    stack->initialized = TRUE;

}

int StackPop(struct Stack *stack, double *value) {

    if ((stack->initialized != TRUE) || (stack->currentItemIndex == EMPTY)) {
        return STANDARD_ERROR;
    } else {
        *value = stack->stackItems[stack->currentItemIndex];
        stack->currentItemIndex -= INDEX_HELP;
        return SUCCESS;
    }
}

int StackPush(struct Stack *stack, double value) {

    if ((stack->initialized != TRUE) || (stack->currentItemIndex == (STACK_SIZE - INDEX_HELP))) {
        return STANDARD_ERROR;
    } else {
        stack->currentItemIndex += INDEX_HELP;
        stack->stackItems[stack->currentItemIndex] = value;
        return SUCCESS;
    }
}

int StackIsEmpty(const struct Stack *stack) {

    if ((stack->currentItemIndex == EMPTY) && (stack->initialized == TRUE))
        return TRUE;
    else
        return FALSE;
}

int StackIsFull(const struct Stack *stack) {

    if (stack->currentItemIndex == (STACK_SIZE - INDEX_HELP) && (stack->initialized == TRUE))
        return TRUE;
    else
        return FALSE;
}

int StackGetSize(const struct Stack *stack) {
    if (stack->initialized == FALSE)
        return SIZE_ERROR;
    else
        return (stack->currentItemIndex) + INDEX_HELP;
}

