// **** Include libraries here ****
// Standard libraries
#include <string.h>
#include <math.h>
#include <stdio.h>

//CSE013E Support Library
#include "UNIXBOARD.h"
#include "Game.h"
#include "Player.h"



// User libraries


// **** Set any macros or preprocessor directives here ****

// **** Declare any data types here ****

// **** Define any global or external variables here ****
// **** Declare any function prototypes here ****

int main() {

    /******************************** Your custom code goes below here ********************************/
    uint8_t check = 0;
    uint8_t roomExits = 0;
    char title[GAME_MAX_ROOM_TITLE_LENGTH + 1];
    char description[GAME_MAX_ROOM_DESC_LENGTH + 1];
    char input;


    printf("Welcome to the Atorre83 RPG.\n");

    if (GameInit() == STANDARD_ERROR) {
        printf("Failed to Load Starting Room.");
        FATAL_ERROR();
    }

    while (TRUE) {

        GameGetCurrentRoomTitle(title);

        GameGetCurrentRoomDescription(description);

        printf("\n\n%s\n\n%s\n\n", title, description);

        printf("Possible exits: ");

        roomExits = GameGetCurrentRoomExits();

        if (roomExits & GAME_ROOM_EXIT_NORTH_EXISTS) {
            printf("North ");
        }
        if (roomExits & GAME_ROOM_EXIT_EAST_EXISTS) {
            printf("East ");
        }
        if (roomExits & GAME_ROOM_EXIT_SOUTH_EXISTS) {
            printf("South ");
        }
        if (roomExits & GAME_ROOM_EXIT_WEST_EXISTS) {
            printf("West ");
        }
        if (roomExits == STANDARD_ERROR) {
            printf("No escape, Press q to quit.");
        }
        printf("\n");

        while (1) {
            printf("\nChoose a direction to press onward. Enter n for north, e for east,"
                    "s for south, w for west, or q to quit: ");
            input = getchar();

            switch (input) {
                case 'n':
                    check = GameGoNorth();
                    if (check == STANDARD_ERROR) {
                        printf("\nCan't go North!\n");
                    }
                    break;
                case 'e':
                    check = GameGoEast();
                    if (check == STANDARD_ERROR) {
                        printf("\nCan't go East!\n");
                    }
                    break;
                case 's':
                    check = GameGoSouth();
                    if (check == STANDARD_ERROR) {
                        printf("\nCan't go South!\n");
                    }
                case 'w':
                    check = GameGoWest();
                    if (check == STANDARD_ERROR) {
                        printf("\nCan't go West!\n");
                    }
                case 'q':
                    printf("\nThanks for playing!\n");
                    exit(0);
                    break;
                default:
                    printf("Please enter n, e, s, w, or q!\n");
                    break;
            }
        }
    }





    /**************************************************************************************************/
}

