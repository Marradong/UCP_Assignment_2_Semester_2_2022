#ifndef CANVAS_H
#define CANVAS_H

#define MAP_SIZE_MINIMUM 5

/* index for parameters specified by the command line user inputs */
#define ROWS 0
#define COLS 1
#define FILE_IDX 2

/* symbols used for the game canvas */
#define BORDER_SYM '*'
#define SPACE_SYM ' '
#define PLAYER_SYM 'P'
#define GOAL_SYM 'G'
#define FLOOR_SYM 'X'

void initCanvasFromFile(FILE** fInput, char*** canvas, char** argv, int* canvasSize, int* goalCoords, int* playerCoords);
void printCanvas(int* usrIns, char*** canvas);
void placeSym(int* coords, char*** canvas, char sym);
void freeCanvas(int* usrIns, char*** canvas);

#endif