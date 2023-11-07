#include "LinkedList.h"
#include "BOARD.h"

#include <stdio.h>


ListItem *LinkedListNew(char *data){
    
    return LinkedListCreateAfter(NULL, data);
}

ListItem *LinkedListCreateAfter(ListItem *item, char *data){
    
    ListItem * theItem = malloc(sizeof(ListItem)); 
    
    if (theItem == NULL) return NULL;
    
    theItem->previousItem = item;
    theItem->nextItem = NULL; 
    theItem->data = data;
    
    if (item){
    
        if (item->nextItem){
            theItem ->nextItem = item ->nextItem;
            theItem ->nextItem->previousItem = theItem;
        }
        item ->nextItem = theItem;
    }
    return theItem;
}

char *LinkedListRemove(ListItem *item){
    if (item == NULL) return NULL;
    char *returnData = item->data;
    
    if (item ->previousItem){
        item ->previousItem ->nextItem = item->nextItem;
    }
    
    if (item ->nextItem){
        item ->nextItem ->previousItem = item ->previousItem;     
    }
    
    free (item);
    
    return returnData;
}

int LinkedListSize(ListItem *list){
    
    if(list == NULL) return 0;
    
    int size = 0;
    
    list = LinkedListGetFirst(list);
    
    while (list != NULL){
        size++;
        list = list ->nextItem;
    }
    
    return size;
}

ListItem *LinkedListGetFirst(ListItem *list){
    
    if (list == NULL) return NULL;
        
    while (list->previousItem){
        list  = list->previousItem;
    }
    
    return list;
}

ListItem *LinkedListGetLast(ListItem *list){
    if (list == NULL) return NULL;
    
    while (list ->nextItem){
        list = list->nextItem;
    }
    
    return list;
}

int LinkedListSwapData(ListItem *firstItem, ListItem *secondItem){
    if ((firstItem == NULL) || (secondItem == NULL)) return STANDARD_ERROR;
    
    char *temp;
    
    temp = firstItem ->data;
    firstItem->data = secondItem->data;
    secondItem->data = temp;
    
    return SUCCESS;
}

int LinkedListPrint(ListItem *list){
    if(list == NULL) return STANDARD_ERROR;
    
    list = LinkedListGetFirst(list);
    while (list != NULL){
        printf("%s\n", list->data);
        list = list ->nextItem;
    }
    return SUCCESS; 
}

