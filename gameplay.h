#ifndef GAMEPLAY_H
#define GAMEPLAY_H

/* Valid move keys */
#define UP_KEY 'w'
#define DOWN_KEY 's'
#define LEFT_KEY 'a'
#define RIGHT_KEY 'd'

/* Definition for pointer to movement function */
typedef void (*pfMove)(char***, char*, int*, int*);

void readMove(char* usrKey);
void movePlayer(char*** canvas, char* usrKey, int* playerCoords, int* usrIns);
void collapseFloor(int* usrIns, char*** canvas);
void moveBorderless(char*** canvas, char* usrKey, int* playerCoords, int* usrIns);

#endif