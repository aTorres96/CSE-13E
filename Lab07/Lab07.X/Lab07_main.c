// **** Include libraries here ****
// Standard libraries
#include "Adc.h"
#include "Ascii.h"
#include "BOARD.h"
#include "Buttons.h"
#include "OledDriver.h"
#include "Oled.h"
#include <stdio.h>

//CSE13E Support Library
#include "BOARD.h"
#include "Leds.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>



// **** Set any macros or preprocessor directives here ****



// **** Set any local typedefs here ****

typedef enum {
    BAKE_MODE, TOAST_MODE, BROIL_MODE
} OvenMode;

typedef enum {
    SETUP, SELECTOR_CHANGE_PENDING, COOKING, RESET_PENDING
} OvenState;

typedef enum {
    TIME_INPUT, TEMP_INPUT
} Input;

typedef struct {
    //OvenState state;
    //add more members to this struct
    // add cooktime
    OvenState state;
    Input inputSelector;
    OvenMode cookingMode;
    uint8_t totalCookTime;
    uint16_t cookTimeRemaining;
    int StartTime;
    int buttonTime;
    int temperature;
    // add cooktime remaining 
    //  add temperature variable
    // 
} OvenData;

OvenData ovenData;

#define LONG_PRESS 5
#define elapseTime freeRunningTime - ovenData.buttonTime
#define NUM_MODES 3
#define NUM_LEDS 8
#define MIN_TEMP 300
#define MIN_TIME 0
#define ADC_SHIFT 2
// **** Declare any datatypes here ****

// **** Define any module-level, global, or external variables here ****

static uint16_t freeRunningTime = 0;
static uint8_t TimerTickEvent = FALSE;
static uint8_t buttonsCheck = 0;
static uint8_t theADC = 0;
static uint8_t adcFlag = 0;
static int buttonFlag = 0;
static int TIMER_TICK;


// **** Put any helper functions here ****

/*This function will update your OLED to reflect the state .*/
void updateOvenOLED(OvenData ovenData);
//update OLED here

/*This function will execute your state machine.  
 * It should ONLY run if an event flag has been set.*/
void runOvenSM(void);

void updateLEDs(OvenData ovenData);

int main() {
    BOARD_Init();
    LEDS_INIT();
    OledInit();
    AdcInit();
    ButtonsInit();
    OledOn();

    //initalize timers and timer ISRs:
    // <editor-fold defaultstate="collapsed" desc="TIMER SETUP">

    // Configure Timer 2 using PBCLK as input. We configure it using a 1:16 prescalar, so each timer
    // tick is actually at F_PB / 16 Hz, so setting PR2 to F_PB / 16 / 100 yields a .01s timer.

    T2CON = 0; // everything should be off
    T2CONbits.TCKPS = 0b100; // 1:16 prescaler
    PR2 = BOARD_GetPBClock() / 16 / 100; // interrupt at .5s intervals
    T2CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T2IF = 0; //clear the interrupt flag before configuring
    IPC2bits.T2IP = 4; // priority of  4
    IPC2bits.T2IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T2IE = 1; // turn the interrupt on

    // Configure Timer 3 using PBCLK as input. We configure it using a 1:256 prescaler, so each timer
    // tick is actually at F_PB / 256 Hz, so setting PR3 to F_PB / 256 / 5 yields a .2s timer.

    T3CON = 0; // everything should be off
    T3CONbits.TCKPS = 0b111; // 1:256 prescaler
    PR3 = BOARD_GetPBClock() / 256 / 5; // interrupt at .5s intervals
    T3CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T3IF = 0; //clear the interrupt flag before configuring
    IPC3bits.T3IP = 4; // priority of  4
    IPC3bits.T3IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T3IE = 1; // turn the interrupt on;

    // </editor-fold>

    printf("Welcome to CRUZID's Lab07 (Toaster Oven).  Compiled on %s %s.", __TIME__, __DATE__);

    //initialize state machine (and anything else you need to init) here
    ovenData.state = SETUP;
    ovenData.cookTimeRemaining = 0;
    ovenData.StartTime = 0;
    while (1) {
        if (adcFlag = 1) {
            runOvenSM();
            adcFlag = 0;
        }
        if (buttonsCheck = 1) {
            runOvenSM();
            buttonsCheck = 0;
        }
        if (TimerTickEvent = TRUE) {
            runOvenSM();
            TimerTickEvent = FALSE;
        }
    };
}

/*The 5hz timer is used to update the free-running timer and to generate TIMER_TICK events*/
void __ISR(_TIMER_3_VECTOR, ipl4auto) TimerInterrupt5Hz(void) {
    // Clear the interrupt flag.
    IFS0CLR = 1 << 12;
    freeRunningTime += 1;
    TimerTickEvent = TRUE;
}

/*The 100hz timer is used to check for button and ADC events*/
void __ISR(_TIMER_2_VECTOR, ipl4auto) TimerInterrupt100Hz(void) {
    // Clear the interrupt flag.
    IFS0CLR = 1 << 8;
    buttonsCheck = ButtonsCheckEvents();
    if (AdcChanged()) {
        theADC = AdcRead();
        adcFlag = 1;
    }
}

void runOvenSM(void) {
    switch (ovenData.state) {
        case SETUP:
            updateOvenOLED(ovenData);
            if (adcFlag == TRUE) {
                if (ovenData.inputSelector == TIME_INPUT) {
                    ovenData.totalCookTime = theADC >> ADC_SHIFT;
                    printf("Time: %d", (int) ovenData.cookTimeRemaining);
                } else if (ovenData.inputSelector == TEMP_INPUT) {
                    ovenData.temperature = (theADC >> ADC_SHIFT) + MIN_TEMP;
                }
                ovenData.cookTimeRemaining = ovenData.totalCookTime;
                updateOvenOLED(ovenData);
                adcFlag = 0;
            }
            if (buttonsCheck & BUTTON_EVENT_4DOWN) {
                ovenData.buttonTime = freeRunningTime;
                //ovenData.cookTimeRemaining = freeRunningTime; 
                // A tutor told me to do this although it works better without.
                ovenData.state = COOKING;

            } else if (buttonsCheck & BUTTON_EVENT_3DOWN) {
                ovenData.buttonTime = freeRunningTime;
                ovenData.state = SELECTOR_CHANGE_PENDING;
            }
            break;
        case SELECTOR_CHANGE_PENDING:
            if (buttonsCheck & BUTTON_EVENT_3UP) {
                if (elapseTime >= LONG_PRESS) {
                    if (ovenData.inputSelector == TIME_INPUT) {
                        ovenData.inputSelector = TEMP_INPUT;
                    } else if (ovenData.inputSelector == TEMP_INPUT) {
                        ovenData.inputSelector = TIME_INPUT;
                    }
                    updateOvenOLED(ovenData);
                    ovenData.state = SETUP;
                } else if (elapseTime < LONG_PRESS) {
                    ovenData.cookingMode = (ovenData.cookingMode + 1) % NUM_MODES;

                    if (ovenData.cookingMode == TOAST_MODE) {
                        ovenData.inputSelector = TIME_INPUT;
                    }
                    if (ovenData.cookingMode == BROIL_MODE) {
                        ovenData.inputSelector = TIME_INPUT;
                    }
                    updateOvenOLED(ovenData);
                    ovenData.state = SETUP;
                }
            }
            break;
        case COOKING:
            updateOvenOLED(ovenData);
            updateLEDs(ovenData);
            if (freeRunningTime > 1 && ovenData.cookTimeRemaining > 0) {
                ovenData.cookTimeRemaining -= 1;
                ovenData.state = COOKING;
                updateOvenOLED(ovenData);
                updateLEDs(ovenData);
            } else if (ovenData.cookTimeRemaining == 0) {
                ovenData.state = SETUP;
                updateOvenOLED(ovenData);
                updateLEDs(ovenData);
            }
            if (buttonsCheck & BUTTON_EVENT_4DOWN) {
                buttonsCheck = 0;
                ovenData.buttonTime = freeRunningTime;
                ovenData.state = RESET_PENDING;
            }
            break;
        case RESET_PENDING:
            //updateOvenOLED(ovenData);
            if (freeRunningTime > 1 && ovenData.cookTimeRemaining > 0) {
                ovenData.cookTimeRemaining -= 1;
                ovenData.state = RESET_PENDING;
                updateLEDs(ovenData);
                updateOvenOLED(ovenData);
            } else if (elapseTime >= LONG_PRESS) {
                ovenData.state = SETUP;
                updateLEDs(ovenData);
                updateOvenOLED(ovenData);
            }
            if (buttonsCheck & BUTTON_EVENT_4UP) {
                ovenData.state = COOKING;
            }
            break;
        default:
            //print to OLED an error
            //occured and to restart
            //the oven
            //while(1);
            break;
    }
    //write your SM logic here.
}

void updateOvenOLED(OvenData ovenData) {

    char display[100];
    char selector1 = '>';
    char selector2 = ' ';
    char ovenTop[5];
    char ovenBottom[5];
    char *cookMode;
    char *temp;

    OledClear(OLED_COLOR_BLACK);

    sprintf(ovenTop, "%c", 0x01);
    sprintf(ovenBottom, "%c", 0x03);

    if (ovenData.cookingMode == BAKE_MODE) {
        temp = "Temp: ";
        cookMode = "BAKE ";
        if (ovenData.inputSelector == 0) {
            selector1 = '>';
            selector2 = ' ';
        } else if (ovenData.inputSelector == 1) {
            selector1 = ' ';
            selector2 = '>';
        }
    } else if (ovenData.cookingMode == TOAST_MODE) {
        selector1 = ' ';
        selector2 = ' ';
        cookMode = "TOAST ";
    } else if (ovenData.cookingMode == BROIL_MODE) {
        selector1 = ' ';
        selector2 = ' ';
        cookMode = "BROIL ";
        ovenData.temperature = 500;
    }
    if (ovenData.state == COOKING && ovenData.cookingMode == BAKE_MODE) {
        sprintf(display, "%c%c%c%c%c%c%s%s%s\n%s%c%s%d%c%d\n%s%c%s%d%c%c\n%c%c%c%c%c%c%c",
                '|', 0x01, 0x01, 0x01, 0x01, 0x01, "| Mode: ", cookMode, " ",
                "|     | ", selector1, "Time: ", (int) ovenData.cookTimeRemaining / 60, ':', (int) ovenData.cookTimeRemaining % 60,
                "|-----| ", selector2, "Temp: ", ovenData.temperature, 0xF8, 'F',
                '|', 0x03, 0x03, 0x03, 0x03, 0x03, '|');
    } else if (ovenData.state == COOKING && ovenData.cookingMode == TOAST_MODE) {
        sprintf(display, "%c%c%c%c%c%c%s%s%s\n%s%c%s%d%c%d\n%s\n%c%c%c%c%c%c%c",
                '|', 0x02, 0x02, 0x02, 0x02, 0x02, "| Mode: ", cookMode, " ",
                "|     | ", selector1, "Time: ", (int) ovenData.cookTimeRemaining / 60, ':', (int) ovenData.cookTimeRemaining % 60,
                "|-----|             ",
                '|', 0x03, 0x03, 0x03, 0x03, 0x03, '|');
    } else if (ovenData.state == COOKING && ovenData.cookingMode == BROIL_MODE) {
        sprintf(display, "%c%c%c%c%c%c%s%s%s\n%s%c%s%d%c%d\n%s%c%s%d%c%c\n%c%c%c%c%c%c%c",
                '|', 0x01, 0x01, 0x01, 0x01, 0x01, "| Mode: ", cookMode, " ",
                "|     | ", selector1, "Time: ", (int) ovenData.cookTimeRemaining / 60, ':', (int) ovenData.cookTimeRemaining % 60,
                "|-----| ", selector2, "Temp: ", 500, 0xF8, 'F',
                '|', 0x04, 0x04, 0x04, 0x04, 0x04, '|');
    } else if (ovenData.cookingMode == BAKE_MODE) {
        sprintf(display, "%c%c%c%c%c%c%s%s%s\n%s%c%s%d%c%d\n%s%c%s%d%c%c\n%c%c%c%c%c%c%c",
                '|', 0x02, 0x02, 0x02, 0x02, 0x02, "| Mode: ", cookMode, " ",
                "|     | ", selector1, "Time: ", (int) ovenData.cookTimeRemaining / 60, ':', (int) ovenData.cookTimeRemaining % 60,
                "|-----| ", selector2, "Temp: ", ovenData.temperature, 0xF8, 'F',
                '|', 0x04, 0x04, 0x04, 0x04, 0x04, '|');
    } else if (ovenData.cookingMode == TOAST_MODE) {
        sprintf(display, "%c%c%c%c%c%c%s%s%s\n%s%c%s%d%c%d\n%s\n%c%c%c%c%c%c%c",
                '|', 0x02, 0x02, 0x02, 0x02, 0x02, "| Mode: ", cookMode, " ",
                "|     | ", selector1, "Time: ", (int) ovenData.cookTimeRemaining / 60, ':', (int) ovenData.cookTimeRemaining % 60,
                "|-----|             ",
                '|', 0x04, 0x04, 0x04, 0x04, 0x04, '|');
    } else if (ovenData.cookingMode == BROIL_MODE) {
        sprintf(display, "%c%c%c%c%c%c%s%s%s\n%s%c%s%d%c%d\n%s%c%s%d%c%c\n%c%c%c%c%c%c%c",
                '|', 0x02, 0x02, 0x02, 0x02, 0x02, "| Mode: ", cookMode, " ",
                "|     | ", selector1, "Time: ", (int) ovenData.cookTimeRemaining / 60, ':', (int) ovenData.cookTimeRemaining % 60,
                "|-----| ", selector2, "Temp: ", ovenData.temperature, 0xF8, 'F',
                '|', 0x04, 0x04, 0x04, 0x04, 0x04, '|');
    }
    OledDrawString(display);
    OledUpdate();

}

void updateLEDs(OvenData ovenData) {
    int light;
    if (ovenData.state == COOKING | ovenData.state == RESET_PENDING) {
        light = (int) (((NUM_LEDS * ovenData.cookTimeRemaining) / ovenData.totalCookTime));
        if (light == 8) {
            LEDS_SET(0xFF);
        } else if (light == 7) {
            LEDS_SET(0xFE);
        } else if (light == 6) {
            LEDS_SET(0xFC);
        } else if (light == 5) {
            LEDS_SET(0xF8);
        } else if (light == 4) {
            LEDS_SET(0xF0);
        } else if (light == 3) {
            LEDS_SET(0xE0);
        } else if (light == 2) {
            LEDS_SET(0xC0);
        } else if (light == 1) {
            LEDS_SET(0x80);
        } else if (light == 0) {
            LEDS_SET(0x00);
        }
    } else
        LEDS_SET(0);
}
