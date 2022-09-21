#ifndef VERIFY_H
#define TOOLBOX_H

/* Boolean definitions */
#define FALSE 0
#define TRUE !FALSE

int vStartLocation(int* usrIns);
int vArgs(int* numArgs);
int vMapSize(int* usrIns);
int vMove(char* move);
int vFloor(int* usrIns, int* coords, char*** canvas, int checkGoal);
int vWin(int* usrIns, int* playerCoords);
int vLose(char*** canvas, int* coords, int* usrIns);

#endif