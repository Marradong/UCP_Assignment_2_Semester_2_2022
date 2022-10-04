#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

LList* createList()
{
    /* Dynamically allocate memory to LList */
    LList* newList = (LList*)malloc(sizeof(LList));
    /* Nullify list properties */
    newList->listLength = 0;
    newList->start = NULL;
    newList->end = NULL;

    return newList;
}

void addEndNode(LList* curList, void* nodeData)
{
    /* Dynamically allocate memory to LList */
    Node* newNode = (Node*)malloc(sizeof(Node));
    /* point node to data */
    newNode->data = nodeData;
    /* Nullify node properties */
    newNode->next = NULL;
    /* check if an end node exists */
    if (curList->end)
    {
        /* point the end node to the new node */
        curList->end->next = newNode;
        /* point the new node to the end node */
        newNode->previous = curList->end;
        /* point the end of the list to the new node */
        curList->end = newNode;
        
    }
    else
    {
        /* point the start of the list to the new node */
        curList->start = newNode;
        /* point the end of the list to the new node */
        curList->end = newNode;
        /* Nullify node properties */
        newNode->previous = NULL;
    }
    /* increase list length */
    curList->listLength++;
}


void removeEndNode(LList* curList, dataFunction fPtr)
{
    /* get the end node of the list */
    Node* endNode = curList->end;
    /* check if the end node exists */
    if (endNode)
    {
        /* check if there is more than one node in the list */
        if (curList->listLength > 1)
        {
            /* get the second last node of the list */
            Node* newEndNode = endNode->previous;
            /* Nullify second last node properties */
            newEndNode->next = NULL;
            /* point the end of the list to the second last node */
            curList->end = newEndNode;
        }
        else
        {
            /* Nullify list properties */
            curList->start = NULL;
            curList->end = NULL;
        }
        /* decrease list length */
        curList->listLength--;
        /* Nullify and free node properties */
        endNode->next = NULL;
        endNode->previous = NULL;
        (*fPtr)(endNode->data);
        endNode->data = NULL;

        free(endNode);
    }
}

void freeList(LList* curList, dataFunction fPtr)
{
    /* get the starting node of the list and create a temporary variable */
    Node* curNode = curList->start;
	Node* temp;
	/* check curNode exists */
	while (curNode)
	{
        /* get the next node */
		temp = curNode->next;
        /* Nullify and free node properties */
		curNode->next = NULL;
        curNode->previous = NULL;
        (*fPtr)(curNode->data);
		curNode->data = NULL;

		free(curNode);
		/* make the next node the current node */
		curNode = temp;		
	}	
    /* Nullify and free list properties */
    curList->listLength = 0;
    curList->end = NULL;
    curList->start = NULL;
	
	free(curList);
}