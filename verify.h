#ifndef VERIFY_H
#define TOOLBOX_H

/* Boolean definitions */
#define FALSE 0
#define TRUE !FALSE
#define NUM_ARGS 2

int vStartLocation(int* coords);
int vArgs(int* numArgs);
int vCanvasSize(int* usrIns);
int vMove(char* move);
int vFloor(int* usrIns, int* coords, char*** canvas, int checkGoal);
int vWin(int* goalCoords, int* playerCoords);
int vLose(char*** canvas, int* coords, int* usrIns);

#endif