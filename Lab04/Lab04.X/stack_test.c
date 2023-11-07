// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CMPE13 Support Library
#include "BOARD.h"


// User libraries
#include "stack.h"

int main()
{
    BOARD_Init();
    int result;

    printf("\n###### Beginning atorre83's stack test harness: ####\n\n");

    //What follows is starter code.  You will need to modify it!
    
    printf("Does StackInit() set the currentItemIndex appropriately?\n");
    struct Stack stack = {};
    StackInit(&stack);
    if (stack.currentItemIndex == -1) {
        printf("StackInit passed\n");
    } else {
        printf("StackInit failed\n");
    }
    printf("\n");
    
    
    printf("Testing StackPush() when the stack is uninitialized.\n");
    stack.initialized = FALSE;    
    result = StackPush(&stack, 4);
    if(result == 0){
        printf("StackPush passed the uninitialize test.\n");
    } else {
        printf("StackPush failed the uninitialize test.\n");
    }
    printf("Testing StackPush() when the stack is full.\n");
    stack.initialized = TRUE;
    stack.currentItemIndex = (STACK_SIZE - 1);
    result = StackPush(&stack, 4);
    if(result == 0){
        printf("StackPush passed the full stack test.\n");
    } else {
        printf("StackPush failed the full stack test.\n");
    }
    printf("Testing StackPush() if the function pushes the value onto the stack.\n");
    stack.initialized = TRUE;
    stack.currentItemIndex = -1;
    result = StackPush(&stack, 3);
    if(stack.currentItemIndex == 0){
        printf("StackPush passed the push onto stack test.\n");
    } else {
        printf("StackPush passed the push onto stack test.\n");
    }    
    printf("\n");

    
    double popped;
    printf("Testing StackPop() when the stack is uninitialized or the stack is empty.\n");
    stack.initialized = FALSE;
    stack.currentItemIndex = -1;
    result = StackPop(&stack, &popped);
    if(result == 0){
        printf("StackPop passed the uninitialized or empty test.\n");
    } else {
        printf("StackPop failed the uninitialized or empty test.\n");
    }
    printf("Testing StackPop() if the function pops the value off the stack.\n");
    stack.initialized = TRUE;
    stack.currentItemIndex = 0;
    result = StackPop(&stack, &popped);
    if(stack.currentItemIndex == -1){
        printf("StackPop passed the pop off of stack test.\n");
    } else {
        printf("StackPop failed the pop off of stack test.\n");
    }
    printf("The number popped off the stack pushed by the previous function: %lf\n", popped);
    printf("\n");
    

    printf("Testing if the StackIsEmpty() function verifies the stack was empty and initialized.\n");
    stack.currentItemIndex = -1;
    stack.initialized = TRUE;
    result = StackIsEmpty(&stack);
    if(result == 1){
        printf("StackIsEmpty verified that the stack was empty and initialized.\n");
    }else{
        printf("StackIsEmpty verified that the stack was not empty and initialized.\n");
    }
    printf("Testing if the StackIsEmpty() function verifies the stack empty and initialized.\n");
    stack.currentItemIndex = 1;
    stack.initialized = FALSE;
    result = StackIsEmpty(&stack);
    if(result == 1){
        printf("StackIsEmpty verified that the stack was empty and initialized.\n");
    }else{
        printf("StackIsEmpty verified that the stack was not empty and initialized.\n");
    }
    printf("\n");

    
    printf("Testing if the StackIsFull() function verifies the stack Full and initialized.\n");
    stack.initialized = TRUE;
    stack.currentItemIndex = (STACK_SIZE-1);
    result = StackIsFull(&stack);
    if(result == 1){
        printf("StackIsFull verified that the stack was full and initialized.\n");
    }else{
        printf("StackIsFull verified that the stack was empty and initialized.\n");
    }
    
    printf("Testing if the StackIsFull() function verifies the stack Full and initialized.\n");
    stack.currentItemIndex = -1;
    stack.initialized = FALSE;
    result = StackIsFull(&stack);
    if(result == 1){
        printf("StackIsFull verified that the stack was full and initialized.\n");
    }else{
        printf("StackIsFull verified that the stack was empty and uninitialized.\n");
    }
    printf("\n");
    
    
    printf("Testing if the StackGetSize() function verifies the stack empty and initialized.\n");
    stack.initialized = FALSE;
    result = StackGetSize(&stack);
    if(result == -1){
        printf("StackGetSize showed that the stack was empty and initialized.\n");
    }else{
        printf("StackGetSize relayed the size of the stack is: %d\n", stack.currentItemIndex);
    }
    
    printf("Testing if the StackGetSize() function verifies the stack empty and initialized.\n");
    stack.initialized = TRUE;
    stack.currentItemIndex = 4;
    result = StackGetSize(&stack);
    if(result == -1){
        printf("StackGetSize showed that the stack was empty and initialized.\n");
    }else{
        printf("StackGetSize relayed the size of the stack is: %d\n", (stack.currentItemIndex + 1));
    }
    
    
    BOARD_End();
    while (1);
    return 0;
}
