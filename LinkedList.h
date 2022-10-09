#ifndef LINKEDLIST_H
#define LINKEDLIST_H

/* type definition for function pointer */
typedef void (*listFunc)(void* data);

/* struct type definition for linked list node */
typedef struct Node
{
	void* data;
	struct Node* next;
	struct Node* previous;
} Node;

/* struct type definition for linkedlist */
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