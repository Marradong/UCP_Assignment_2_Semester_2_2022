#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef void (*listFunc)(void* data);

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

LinkedList* createLinkedList();
void insertLast(LinkedList** currentList, void* nodeData);
void removeLast(LinkedList** curList, listFunc fPtr);
void freeLinkedList(LinkedList** curList, listFunc fPtr);

#endif