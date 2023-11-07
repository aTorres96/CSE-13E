
// **** Include libraries here ****
// old bounce
// Standard libraries
#include <stdio.h>
					


//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// **** Declare any datatypes here ****
struct Timer{
    uint8_t event;
    int16_t timeRemaining;
}; 
static struct Timer Timer1 = {FALSE, 0};

// **** Define global, module-level, or external variables here ****
enum{
    LEFT, RIGHT
};	
#define TIME_FRE 30
#define TimerA 2 * TIME_FRE
#define TimerB 3 * TIME_FRE
#define TimerC 5 * TIME_FRE

// **** Declare function prototypes ****
void Moniter_LED(void);

int main(void)
{
    BOARD_Init();

    // Configure Timer 1 using PBCLK as input. This default period will make the LEDs blink at a
    // pretty reasonable rate to start.
    T1CON = 0; // everything should be off
    T1CONbits.TCKPS = 1; // 1:8 prescaler
    PR1 = 0xFFFF; // interrupt at max interval
    T1CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T1IF = 0; //clear the interrupt flag before configuring
    IPC1bits.T1IP = 4; // priority of  4
    IPC1bits.T1IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T1IE = 1; // turn the interrupt on

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    printf("Welcome to CRUZID's lab6 part2 (bounce_switch).  Compiled on %s %s.\n",__TIME__,__DATE__);
    LEDS_INIT();
							 
	while(1){
        if(Timer1.event == TRUE){
            Moniter_LED();
            Timer1.event = FALSE;
        }
        //poll timer events and react if any occur
    }			


    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}


/**
 * This is the interrupt for the Timer1 peripheral. It will trigger at the frequency of the peripheral
 * clock, divided by the timer 1 prescaler and the interrupt interval.
 * 
 * It should not be called, and should communicate with main code only by using module-level variables.
 */
void __ISR(_TIMER_1_VECTOR, ipl4auto) Timer1Handler(void)
{
    // Clear the interrupt flag.
    IFS0bits.T1IF = 0;

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    Timer1.timeRemaining --;
    if(Timer1.timeRemaining < 0){
        Timer1.timeRemaining = SWITCH_STATES()+1;
        Timer1.event = TRUE;
    }
    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/									
	 
}

 void Moniter_LED(void){
     static char dir = RIGHT;
     static uint8_t pattern = 0x80;
     
     if (pattern == 0x80){
         dir = RIGHT;
         pattern >>= 1;
     }
     else if (pattern == 0x01){
         dir = LEFT;
         pattern <<= 1;
     }
     else{
         if (dir == LEFT){
         pattern <<= 1;
         }
         else{
             pattern >>=1;
         }
     }
     LEDS_SET(pattern);           
 }