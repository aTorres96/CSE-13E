// **** Include libraries here ****
// Standard libraries
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

//CSE013E Support Library
#include "UNIXBOARD.h"



// User libraries
#include "Game.h"
#include "Player.h"

static struct {
    uint8_t north;
    uint8_t south;
    uint8_t east;
    uint8_t west;
    char title[GAME_MAX_ROOM_TITLE_LENGTH + 1];
    char desc[GAME_MAX_ROOM_DESC_LENGTH + 1];
} currentRoom = {};

int LoadRoom(uint16_t roomNumber);

int GameGoNorth(void) {
    if (currentRoom.north) {
        return LoadRoom(currentRoom.north);
    }
    return STANDARD_ERROR;
}

int GameGoEast(void) {
    if (currentRoom.east) {
        return LoadRoom(currentRoom.east);
    }
    return STANDARD_ERROR;
}

int GameGoSouth(void) {
    if (currentRoom.south) {
        return LoadRoom(currentRoom.south);
    }
    return STANDARD_ERROR;
}

int GameGoWest(void) {
    if (currentRoom.west) {
        return LoadRoom(currentRoom.west);
    }
    return STANDARD_ERROR;
}

int GameInit(void) {

    if (LoadRoom(STARTING_ROOM)) {
        return SUCCESS;
    }
    return STANDARD_ERROR;
}

int GameGetCurrentRoomTitle(char *title) {
    strcpy(title, currentRoom.title);
    return strlen(title);
}

int GameGetCurrentRoomDescription(char *desc) {
    strcpy(desc, currentRoom.desc);
    return strlen(desc);
}

uint8_t GameGetCurrentRoomExits(void) {
    uint8_t exits = '\0';
    if (currentRoom.west) {
        exits |= GAME_ROOM_EXIT_WEST_EXISTS;
    }
    if (currentRoom.south) {
        exits |= GAME_ROOM_EXIT_SOUTH_EXISTS;
    }
    if (currentRoom.east) {
        exits |= GAME_ROOM_EXIT_EAST_EXISTS;
    }
    if (currentRoom.north) {
        exits |= GAME_ROOM_EXIT_NORTH_EXISTS;
    }
    return exits;
}

int LoadRoom(uint16_t roomNumber) {

    FILE *room;

    char roomFileName[50];

    sprintf(roomFileName, "RoomFiles/room%d.txt", roomNumber);

    if ((room = fopen(roomFileName, "rb")) == NULL) {
        return STANDARD_ERROR;
    }

    fgetc(room);
    fgetc(room);
    fgetc(room);

    uint8_t titleLength = fgetc(room);
fgets(currentRoom.title, titleLength + 1, room);
    /*if (titleLength == EOF || titleLength == 0 || fgets(currentRoom.title, titleLength + 1, room) == NULL) {
        fclose(room);
        return STANDARD_ERROR;
    }*/

    currentRoom.title[titleLength] = '\0';

    while (1) {
        uint8_t item = fgetc(room);
        uint8_t found = 0;
        int i;
        for (i = 0; i < item; i++) {
            if (FindInInventory(item) == SUCCESS) {
                found += 1;
            }
        }
        if (item == found) {
            uint8_t descLength = fgetc(room);
            fgets(currentRoom.desc, descLength + 1, room);
            currentRoom.desc[descLength] = '\0';
            for (i = 0; i < descLength; i++) {
                if (AddToInventory(item) == STANDARD_ERROR) {
                    return STANDARD_ERROR;
                }
            }


        } else if (item != found) {

            uint8_t descLength2 = fgetc(room);
            fgets(currentRoom.desc, descLength2 + 1, room);
            currentRoom.desc[descLength2] = '\0';
            for (i = 0; i < descLength2; i++) {
                if (AddToInventory(descLength2) == STANDARD_ERROR) {
                    return STANDARD_ERROR;
                }
            }
        }

        currentRoom.north = fgetc(room);
        currentRoom.east = fgetc(room);
        currentRoom.south = fgetc(room);
        currentRoom.west = fgetc(room);
        fclose(room);
        return SUCCESS;
    }
}
