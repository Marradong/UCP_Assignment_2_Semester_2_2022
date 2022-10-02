#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef void (*dataFunction)(void* data);

typedef struct Node
{
	void* data;
	struct Node* next;
	struct Node* previous;
} Node;

typedef struct LinkedList
{
	int listLength;
    Node* start;
	Node* end;
} LinkedList;

LinkedList* createList();
void addEndNode(LinkedList* currentList, void* nodeData);
void removeEndNode(LinkedList* curList, dataFunction fPtr);
void freeList(LinkedList* curList, dataFunction fPtr);

#endif