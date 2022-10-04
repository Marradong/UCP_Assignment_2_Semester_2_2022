#ifndef GAMEPLAY_H
#define GAMEPLAY_H

/* Valid move keys */
#define UP_KEY 'w'
#define DOWN_KEY 's'
#define LEFT_KEY 'a'
#define RIGHT_KEY 'd'
#define UNDO_KEY 'u'

#include "LinkedList.h"

void readMove(char* usrKey);
void movePlayer(char*** canvas, char* usrKey, int* playerCoords, int* canvasSize, LList** list);
void collapseFloor(int* canvasSize, char*** canvas, int* floorCoords);

#endif