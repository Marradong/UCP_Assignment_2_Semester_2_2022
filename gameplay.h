#ifndef GAMEPLAY_H
#define GAMEPLAY_H

/* Valid move keys */
#define UP_KEY 'w'
#define DOWN_KEY 's'
#define LEFT_KEY 'a'
#define RIGHT_KEY 'd'
#define UNDO_KEY 'u'

#include "LinkedList.h"

typedef struct Data
{
	int playerCoords[2];
	int floorCoords[2];
} Data;

void readMove(char* usrKey);
void movePlayer(char*** canvas, char* usrKey, int* playerCoords, int* canvasSize, LinkedList* list);
void collapseFloor(int* canvasSize, char*** canvas, int* floorCoords);
void freeData(void* data);
void changeCoords(int* playerCoords, char* usrKey);

#endif