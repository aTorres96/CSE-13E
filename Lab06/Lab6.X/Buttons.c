#include <stdio.h>
#include "BOARD.h"
#include "Buttons.h"

#define MASK_BUTTON_1_DOWN 0x1111
#define MASK_BUTTON_2_DOWN 0x2222
#define MASK_BUTTON_3_DOWN 0x4444
#define MASK_BUTTON_4_DOWN 0x8888

#define SHIFT_DEBOUNCE 4

void ButtonsInit(void){
    
    TRISD |= 0x00E0;
    TRISF |= 0x0002;
}

uint8_t ButtonsCheckEvents(void){
    static uint16_t prev_val = 0;
    static uint8_t prevButtonEvent1 = BUTTON_EVENT_NONE;
    static uint8_t prevButtonEvent2 = BUTTON_EVENT_NONE;
    static uint8_t prevButtonEvent3 = BUTTON_EVENT_NONE;
    static uint8_t prevButtonEvent4 = BUTTON_EVENT_NONE;
    uint8_t returnButtonEvent = BUTTON_EVENT_NONE;

    prev_val = (prev_val << SHIFT_DEBOUNCE) | BUTTON_STATES();

    if((prev_val & MASK_BUTTON_1_DOWN) && !(prevButtonEvent1 & BUTTON_EVENT_1DOWN)){
        returnButtonEvent |= BUTTON_EVENT_1DOWN;
        prevButtonEvent1 = BUTTON_EVENT_1DOWN;
    }
    
    if (!(prev_val & MASK_BUTTON_1_DOWN) && (prevButtonEvent1 & BUTTON_EVENT_1DOWN)){
        returnButtonEvent |= BUTTON_EVENT_1UP;
        prevButtonEvent1 = BUTTON_EVENT_1UP;
    }
    
    if((prev_val & MASK_BUTTON_2_DOWN) && !(prevButtonEvent2 & BUTTON_EVENT_2DOWN)){
        returnButtonEvent |= BUTTON_EVENT_2DOWN;
        prevButtonEvent2 = BUTTON_EVENT_2DOWN;
    }
    
    if (!(prev_val & MASK_BUTTON_2_DOWN) && (prevButtonEvent2 & BUTTON_EVENT_2DOWN)){
        returnButtonEvent |= BUTTON_EVENT_2UP;
        prevButtonEvent2 = BUTTON_EVENT_2UP;
    }
    
    if((prev_val & MASK_BUTTON_3_DOWN) && !(prevButtonEvent3 & BUTTON_EVENT_3DOWN)){
        returnButtonEvent |= BUTTON_EVENT_3DOWN;
        prevButtonEvent3 = BUTTON_EVENT_3DOWN;
    }
    
    if (!(prev_val & MASK_BUTTON_3_DOWN) && (prevButtonEvent3 & BUTTON_EVENT_3DOWN)){
        returnButtonEvent |= BUTTON_EVENT_3UP;
        prevButtonEvent3 = BUTTON_EVENT_3UP;
    }
    
    if((prev_val & MASK_BUTTON_4_DOWN) && !(prevButtonEvent4 & BUTTON_EVENT_4DOWN)){
        returnButtonEvent |= BUTTON_EVENT_4DOWN;
        prevButtonEvent4 = BUTTON_EVENT_4DOWN;
    }
    
    if (!(prev_val & MASK_BUTTON_4_DOWN) && (prevButtonEvent4 & BUTTON_EVENT_4DOWN)){
        returnButtonEvent |= BUTTON_EVENT_4UP;
        prevButtonEvent4 = BUTTON_EVENT_4UP;
    }
    
    return returnButtonEvent;
}
