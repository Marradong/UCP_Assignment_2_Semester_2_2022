#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef void (*dataFunction)(void* data);

typedef struct Node
{
	void* data;
	struct Node* next;
	struct Node* previous;
} Node;

typedef struct LList
{
	int listLength;
    Node* start;
	Node* end;
} LList;

LList* createList();
void addEndNode(LList** currentList, void* nodeData);
void removeEndNode(LList** curList, dataFunction fPtr);
void freeList(LList** curList, dataFunction fPtr);

#endif