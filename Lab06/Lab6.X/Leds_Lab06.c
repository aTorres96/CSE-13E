#include "Leds_Lab06.h"
#include "BOARD.h"

void LEDS_INIT(void){
    
    TRISE = 0x00; //
    LATE = 0x00; // leds set to off
}

void LEDS_SET(char newPattern){
    
    LATE = newPattern;
    
}

char LEDS_GET(void){
    
    char current;
    
    current = LATE;
    
    return current;
}
