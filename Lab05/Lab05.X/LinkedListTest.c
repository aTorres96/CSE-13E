#include "BOARD.h"
#include "LinkedList.h"

#include <stdio.h>
#include <string.h>


int main(void){
    
    char *word = "dog";
    char *letter = "s";
    int LLNewCount;
    int LLAfterCount;
    int LLSizeCount;
    int LLRemoveCount;
    int LLFirstCount;
    int LLLastCount;
    int LLSwapCount;
    int LLPrintCount;
    
    ListItem *newLL = LinkedListNew(word);
        
    if (newLL ->nextItem == NULL){
        LLNewCount += 1;
    }
    
    if (newLL ->previousItem == NULL){
        LLNewCount += 1;
    }
    
    if (strcmp(newLL->data, word) == 0){
        LLNewCount += 1;
    }
    
    printf("LinkedListNew passed %d/3 tests.\n",LLNewCount);

    
    ListItem* end = newLL;
        
    end = LinkedListCreateAfter(newLL, letter);
    
    if (end->previousItem != NULL){
        LLAfterCount += 1;
        if (strcmp(end->previousItem->data, word) == 0){
            LLAfterCount +=1;
        }
        
        if(end->nextItem == NULL){
            LLAfterCount += 1;
        }
    }
    
    printf("LinkedListCreateAfter passed %d/3 tests.\n",LLAfterCount);
    
    if (LinkedListSize(NULL) == 0){
        LLSizeCount += 1;
    }
    if (LinkedListSize(newLL) == 2){
        LLSizeCount += 1;
    }
    
    printf("LinkedListSize passed %d/2 tests.\n",LLSizeCount);
    
    if (LinkedListRemove(NULL) == NULL){
        LLRemoveCount += 1;
    }
    if (strcmp(LinkedListRemove(end), letter) == 0){
        LLRemoveCount += 1;
    }

    printf("LinkedListRemove passed %d/2 tests.\n", LLRemoveCount);
    
    if (LinkedListGetFirst(NULL) == NULL){
        LLFirstCount +=1;
    }
    
    ListItem *temp = LinkedListGetFirst(end);
    if (strcmp(temp->data, word) == 0){
        LLFirstCount +=1;
    }
    
    printf("LinkedListGetFirst passed %d/2 tests.\n", LLFirstCount);
    
    if (LinkedListGetLast(NULL) == NULL){
        LLLastCount +=1;
    }
    
    ListItem *temp2 = LinkedListGetLast(end);
    if (strcmp(temp2->data, letter) == 0){
        LLLastCount +=1;
    }
    
    printf("LinkedListGetLast passed %d/2 tests.\n", LLLastCount);
    
    if (LinkedListSwapData(NULL, newLL) == 0){
        LLSwapCount += 1;
    }
    
    if (LinkedListSwapData(newLL, end) == 1){
        LLSwapCount += 1;        
    }
    
    printf("LinkedListSwapdata passed %d/2 Tests.\n", LLSwapCount);
   
    if(LinkedListPrint(NULL) == 0){
        LLPrintCount += 1;
    }

    if(LinkedListPrint(newLL) == 1){
        LLPrintCount += 1;
    }
    
    printf("LinkedListPrint printed and passed %d/2 Tests.\n", LLSwapCount);
    
    while(1);
}
