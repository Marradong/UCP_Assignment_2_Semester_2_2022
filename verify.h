#ifndef VERIFY_H
#define VERIFY_H

/* Boolean definitions */
#define FALSE 0
#define TRUE !FALSE
#define NUM_ARGS 2

#include "gameplay.h"

int vStartLocation(int* coords);
int vArgs(int* numArgs);
int vCanvasSize(int* usrIns);
int vMove(char* move);
int vFloor(GameObj* gObj, int *coords, char ***canvas, int checkGoal);
int vWin(GameObj* gObj);
int vLose(char*** canvas, int* coords, GameObj* gObj);

#endif