#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct Data
{
	int* playerCoords;
	int* floorCoords;
} Data;

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
void appendNewNode(LinkedList* currentList, void* nodeData);
void removeEndNode(LinkedList* currentList);

#endif