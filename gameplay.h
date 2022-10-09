#ifndef GAMEPLAY_H
#define GAMEPLAY_H

/* Valid move keys */
#define UP_KEY 'w'
#define DOWN_KEY 's'
#define LEFT_KEY 'a'
#define RIGHT_KEY 'd'
#define UNDO_KEY 'u'

/* include relevate files containing struct type definitions */
#include "LinkedList.h"

/* struct type definition for the game data */
typedef struct GameObj
{
	int canvasSize[2];
    int goalCoords[2];
    int playerCoords[2];
} GameObj;

void readMove(char* usrKey);
void movePlayer(char ***canvas, char *usrKey, GameObj* gObj, LinkedList **gList);

#endif