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

void addEndNode(LinkedList* currentList, void* nodeData)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = nodeData;
    newNode->next = NULL;

    if (currentList->end)
    {
        Node* lastNode = currentList->end;
        lastNode->next = newNode;
        newNode->previous = lastNode;
        currentList->end = newNode;
        currentList->listLength++;
    }
    else
    {
        currentList->start = newNode;
        currentList->end = newNode;
        newNode->previous = NULL;
        currentList->listLength++;
    }
}

void removeEndNode(LinkedList* currentList)
{
    Node* endNode = currentList->end;

    if (endNode)
    {
        if (currentList->listLength > 1)
        {
            Node* newEndNode = endNode->previous;
            newEndNode->next = NULL;
            currentList->end = newEndNode;
        }
        else
        {
            currentList->start = NULL;
            currentList->end = NULL;
        }
        currentList->listLength--;

        endNode->next = NULL;
        endNode->previous = NULL;
        endNode->data = NULL;
        free(endNode);
    }
}