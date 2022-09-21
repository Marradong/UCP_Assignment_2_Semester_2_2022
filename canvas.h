#ifndef CANVAS_H
#define CANVAS_H

#define MAP_SIZE_MINIMUM 5

/* index for parameters specified by the command line user inputs */
#define ROWS 0
#define COLS 1
#define PLAYER_ROW 2
#define PLAYER_COL 3
#define GOAL_ROW 4
#define GOAL_COL 5

/* symbols used for the game canvas */
#define BORDER_SYM '*'
#define SPACE_SYM ' '
#define PLAYER_SYM 'P'
#define GOAL_SYM 'G'
#define FLOOR_SYM 'X'

void initCanvas(int* usrIns, int* playerCoords, char*** canvas);
void printCanvas(int* usrIns, char*** canvas);
void placeSym(int* coords, char*** canvas, char sym);
void freeCanvas(int* usrIns, char*** canvas);

#endif