#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct Node
{
	void* data;
	struct Node* next;
} Node;

typedef struct LinkedList
{
	int listLength;
    Node* start;
} LinkedList;

LinkedList* createList();
void appendNewNode(LinkedList* currentList, void* nodeData);

#endif