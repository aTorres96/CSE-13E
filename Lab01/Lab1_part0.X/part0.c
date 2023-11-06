/* 
 * File:   part0.c
 * Author: Alexander Torres (atorre83@ucsc.edu)
 *
 * Created on April 5, 2021, 5:06 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "BOARD.h"

/*
 * 
 */
int main(void)
{
    BOARD_Init();
    printf("Hello World\n");
    
    BOARD_End();
    while(1);
}

