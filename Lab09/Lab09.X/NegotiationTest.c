#include <math.h>
#include <stdio.h>
#include <string.h>
#include "BOARD.h"
#include "Negotiation.h"

int main() {
    BOARD_Init();

    NegotiationData hashTest = 0;
    NegotiationData verifyTest = 0;
    NegotiationData coinTest = 0;

    uint16_t hashResult, coinResult, hashCount, verifyCount, coinCount,
            hash, verify1, verify2, coin1, coin2;

    printf("\n Negotiation Test: \n");

    hash = 4;
    hashResult = 16;
    hashTest = NegotiationHash(hash);
    if (hashTest == hashResult) {
        printf("\nThe NegotiationHash test passed!\n");
        hashCount++;
    } else {
        printf("\nThe NegotiationHash test failed!\n");
    }
    hash = 12345;
    hashResult = 43182;
    hashTest = NegotiationHash(hash);
    if (hashTest == hashResult) {
        printf("The NegotiationHash test passed!\n");
        hashCount++;
    } else {
        printf("The NegotiationHash test failed!\n");
    }

    printf("NegotiationHash test passed %d/2.\n", hashCount);
    
    verify1 = 4;
    verify2 = 16;
    verifyTest = NegotiationVerify(verify1, verify2);
    if (verifyTest == TRUE) {
        printf("\nThe NegotiationVerify test passed!\n");
        verifyCount++;
    } else {
        printf("\nThe NegotiationVerify test failed!\n");
    }
    verifyTest = NegotiationVerify(hash, hashResult);
    if (verifyTest == TRUE) {
        printf("The NegotiationVerify test passed!\n");
        verifyCount++;
    } else {
        printf("The NegotiationVerify test failed!\n");
    }

    printf("NegotiationVerify test passed %d/2\n", verifyCount);
    
    coin1 = 5;
    coin2 = 11;
    coinTest = NegotiateCoinFlip(coin1, coin2);
    if (coinTest == HEADS) {
        printf("\nThe NegotiateCoinFlip test passed!\n");
        coinCount++;
    } else {
        printf("\nThe NegotiateCoinFlip test failed!\n");
    }
    coin1 = 123;
    coin2 = 231;
    coinTest = NegotiateCoinFlip(coin1, coin2);
    if (coinTest == TAILS) {
        printf("The NegotiateCoinFlip test passed!\n");
        coinCount++;
    } else {
        printf("The NegotiateCoinFlip test failed!\n");
    }

    printf("NegotiateCoinFlip test passed %d/2\n", coinCount);
    
}