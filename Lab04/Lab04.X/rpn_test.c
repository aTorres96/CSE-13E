// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//CMPE13 Support Library
#include "BOARD.h"



// User libraries
#include "rpn.h"

int main() {
    BOARD_Init();
    int error;

    printf("\n###### Beginning CRUZID's rpn test harness: ####\n\n");

    //What follows is starter code.  You will need to modify it!

    char test1[] = "1 1 + ";
    char test2[] = "4 5 * ";
    char test3[] = "54 9 / ";
    char test4[] = "43 4 -";
    char test5[] = "1 2 - 5 + 6 * 3 /";
    char test6[] = "5.5 2.5 * ";
    char test7[] = "1 & - ";
    char test8[] = "1 + + ";
    char test9[] = "1 1";
    char test10[] = "5 0 / ";
    char test11[] = "  ";
    char test12[] = "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 ";

    double test1_result = 2;
    double test2_result = 20;
    double test3_result = 6;
    double test4_result = 39;
    double test5_result = 8;
    double test6_result = 13.75;
    double result; 

    printf("Testing RPN_Evaluate simple addition with \"%s\"... \n ", test1);
    error = RPN_Evaluate(test1, &result);
    if ((error == RPN_NO_ERROR) && (result == test1_result)) {
        printf("Success RPN_Evaluate simple addition test passed: %f\n", result);
    } 
    else if (error > RPN_NO_ERROR) {
        printf("RPN_EVALUATE produced error = %d , result = %f\n", error, result);
    }
    
    printf("\nTesting RPN_Evaluate simple multiplication with \"%s\"... \n ", test2);
    error = RPN_Evaluate(test2, &result);
    if ((error == RPN_NO_ERROR) && (result == test2_result)) {
        printf("Success RPN_Evaluate simple multiplication test passed: %f\n", result);
    } 
    else if (error > RPN_NO_ERROR) {
        printf("RPN_EVALUATE produced error = %d , result = %f\n", error, result);
    }
    
    printf("\nTesting RPN_Evaluate simple division with \"%s\"... \n ", test3);
    error = RPN_Evaluate(test3, &result);
    if ((error == RPN_NO_ERROR) && (result == test3_result)) {
        printf("Success RPN_Evaluate simple division test passed: %f\n", result);
    } 
    else if (error > RPN_NO_ERROR) {
        printf("RPN_EVALUATE produced error = %d , result = %f\n", error, result);
    }
    
    printf("\nTesting RPN_Evaluate simple subtraction with \"%s\"... \n ", test4);
    error = RPN_Evaluate(test4, &result);
    if ((error == RPN_NO_ERROR) && (result == test4_result)) {
        printf("Success RPN_Evaluate simple subtraction test passed: %f\n", result);
    } 
    else if (error > RPN_NO_ERROR) {
        printf("RPN_EVALUATE produced error = %d , result = %f\n", error, result);
    }
    
    printf("\nTesting RPN_Evaluate with a long equation\"%s\"... \n ", test5);
    error = RPN_Evaluate(test5, &result);
    if ((error == RPN_NO_ERROR) && (result == test5_result)) {
        printf("Success RPN_Evaluate long equation test passed: %f\n", result);
    } 
    else if (error > RPN_NO_ERROR) {
        printf("RPN_EVALUATE produced error = %d , result = %f\n", error, result);
    }
    
    printf("\nTesting RPN_Evaluate with decimal floats\"%s\"... \n ", test6);
    error = RPN_Evaluate(test6, &result);
    if ((error == RPN_NO_ERROR) && (result == test6_result)) {
        printf("Success RPN_Evaluate decimal floats test passed: %f\n", result);
    } 
    else if (error > RPN_NO_ERROR) {
        printf("RPN_EVALUATE produced error = %d , result = %f\n", error, result);
    }

    printf("\nTesting if RPN_Evaluate catches an invalid token \"%s\"... \n ", test7);
    error = RPN_Evaluate(test7, &result);
    if (error == RPN_ERROR_INVALID_TOKEN){
        printf("Success RPN_Evaluate returned the invalid token error.\n");
    } 
    else if (error != RPN_ERROR_INVALID_TOKEN) {
        printf("RPN_EVALUATE did not catch the invalid token error.\n");
    } 
    
    printf("\nTesting if RPN_Evaluate catches a stack underflow error \"%s\"... \n ", test8);
    error = RPN_Evaluate(test8, &result);
    if (error == RPN_ERROR_STACK_UNDERFLOW){
        printf("Success RPN_Evaluate returned the stack underflow error.\n");
    } 
    else if (error != RPN_ERROR_STACK_UNDERFLOW) {
        printf("RPN_EVALUATE did not catch the stack underflow error.\n");
    }
    
    printf("\nTesting if RPN_Evaluate catches the too many items remain error \"%s\"... \n ", test9);
    error = RPN_Evaluate(test9, &result);
    if (error == RPN_ERROR_TOO_MANY_ITEMS_REMAIN){
        printf("Success RPN_Evaluate returned the too many items remain error.\n");
    } 
    else if (error != RPN_ERROR_TOO_MANY_ITEMS_REMAIN) {
        printf("RPN_EVALUATE did not catch the too many items remain error. \n");
    }
    
    printf("\nTesting if RPN_Evaluate catches the divide by zero error \"%s\"... \n ", test10);
    error = RPN_Evaluate(test10, &result);
    if (error == RPN_ERROR_DIVIDE_BY_ZERO){
        printf("Success RPN_Evaluate returned the divide by zero error.\n");
    } 
    else if (error != RPN_ERROR_DIVIDE_BY_ZERO) {
        printf("RPN_EVALUATE did not catch the divide by zero error.\n");
    }
    
    printf("\nTesting if RPN_Evaluate catches the too few items remaining error \"%s\"... \n", test11);
    error = RPN_Evaluate(test11, &result);
    if (error == RPN_ERROR_TOO_FEW_ITEMS_REMAIN){
        printf("Success RPN_Evaluate returned the too few items remaining error.\n");
    } 
    else if (error != RPN_ERROR_TOO_FEW_ITEMS_REMAIN) {
        printf("RPN_EVALUATE did not catch the too few items remain error.\n");
    }

    printf("\nTesting if RPN_Evaluate catches the stack over flow error \"%s\"... \n", test12);
    error = RPN_Evaluate(test12, &result);
    if (error == RPN_ERROR_STACK_OVERFLOW){
        printf("Success RPN_Evaluate returned the stack overflow error.\n");
    } 
    else if (error != RPN_ERROR_STACK_OVERFLOW) {
        printf("RPN_EVALUATE did not catch the stack overflow error .\n");
    }
    /*printf("Testing ProcessBackspaces:\n");
    char test_pb1[] = "123\b34";
    ProcessBackspaces(test_pb1);
    printf("result    : %s\n", test_pb1);
    printf("should be : 1234\n");*/
    BOARD_End();
    while (1);
}


