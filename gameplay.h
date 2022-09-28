#ifndef GAMEPLAY_H
#define GAMEPLAY_H

/* Valid move keys */
#define UP_KEY 'w'
#define DOWN_KEY 's'
#define LEFT_KEY 'a'
#define RIGHT_KEY 'd'
#define UNDO_KEY 'u'

#include "LinkedList.h"
/* Definition for pointer to movement function */
typedef void (*pfMove)(char*** canvas, char* usrKey, int* playerCoords, int* canvasSize, LinkedList** list);

void readMove(char* usrKey);
void movePlayer(char*** canvas, char* usrKey, int* playerCoords, int* canvasSize, LinkedList** list);
void collapseFloor(int* canvasSize, char*** canvas, int* floorCoords);
void moveBorderless(char*** canvas, char* usrKey, int* playerCoords, int* canvasSize, LinkedList** list);

#endif