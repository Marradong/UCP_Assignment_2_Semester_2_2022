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
    newList->end = NULL;

    return newList;
}

void addEndNode(LinkedList* curList, void* nodeData)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = nodeData;
    newNode->next = NULL;

    if (curList->end)
    {
        Node* lastNode = curList->end;
        lastNode->next = newNode;
        newNode->previous = lastNode;
        curList->end = newNode;
        curList->listLength++;
    }
    else
    {
        curList->start = newNode;
        curList->end = newNode;
        newNode->previous = NULL;
        curList->listLength++;
    }
}

void removeEndNode(LinkedList* curList, dataFunction fPtr)
{
    Node* endNode = curList->end;

    if (endNode)
    {
        if (curList->listLength > 1)
        {
            Node* newEndNode = endNode->previous;
            newEndNode->next = NULL;
            curList->end = newEndNode;
        }
        else
        {
            curList->start = NULL;
            curList->end = NULL;
        }
        curList->listLength--;

        endNode->next = NULL;
        endNode->previous = NULL;
        (*fPtr)(endNode->data);
        endNode->data = NULL;

        free(endNode);
    }
}

void freeList(LinkedList* curList, dataFunction fPtr)
{
    Node* curNode = curList->start;
	Node* temp;
	
	while (curNode)
	{
		temp = curNode->next;

		curNode->next = NULL;
        curNode->previous = NULL;
        (*fPtr)(curNode->data);
		curNode->data = NULL;

		free(curNode);
		
		curNode = temp;		
	}	
    curList->listLength = 0;
    curList->end = NULL;
    curList->start = NULL;
	
	free(curList);
}