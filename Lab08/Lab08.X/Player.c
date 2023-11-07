// **** Include libraries here ****
// Standard libraries
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//CSE013E Support Library
#include "UNIXBOARD.h"



// User libraries
#include "Player.h"
#include "Game.h"

static int InventorySize = 0;
static uint8_t playerInventory[INVENTORY_SIZE] = {0};

int AddToInventory(uint8_t item) {

	if (InventorySize < INVENTORY_SIZE) {
		playerInventory[InventorySize] = item;
		InventorySize += 1;
		return SUCCESS;
	}

	return STANDARD_ERROR;
}

int FindInInventory(uint8_t item) {
	
	int i;

	for (i = 0; i < INVENTORY_SIZE; i++) {
		if (playerInventory[i] == item) {
			return SUCCESS;
		}
	}

	return STANDARD_ERROR;
}