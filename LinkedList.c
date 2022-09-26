#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

LinkedList* createList()
{	
	/* Dynamically allocate memory to LinkedList */
    LinkedList* newList = (LinkedList*)malloc(sizeof(LinkedList));
    /* Nullify list properties */
	newList->listLength = 0;
    newList->start = NULL;

	return newList;	
}

void appendNewNode(LinkedList* currentList, void* nodeData)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = nodeData;
    newNode->next = NULL;

    if(currentList->start)
    {
        Node* lastNode = currentList->start;
        while(lastNode->next)
        {
            lastNode = lastNode->next;
        }

        lastNode->next = newNode;
    }
    else
    {
        currentList->start = newNode;
    }
    
}