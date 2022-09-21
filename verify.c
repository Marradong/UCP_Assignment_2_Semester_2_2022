#include <stdio.h>
#include <stdlib.h>
#include "verify.h"
#include "gameplay.h"
#include "canvas.h"
#include "toolbox.h"

/**************************************************************************************************/
/* Game Validation Methods     	                	                                         	  */
/**************************************************************************************************/

/**
 * @brief Verifies that the correct number of command line arguements has been entered.
 * 
 * @param numArgs, pointer to the number of command line arguements entered (int*).
 */
int vArgs(int* numArgs)
{
    int verified = TRUE;
    /* Check correct number of command line arguments has been entered */
    if((*numArgs) != 7)
    {
        verified = FALSE;
        /* Clear terminal and print error message */
        system("clear");
        printf("Invalid number of arguements please enter in the format below\n");
        printf("./escape <row_map> <col_map> <row_player> <col_player> <row_goal> <col_goal>\n");
    }
    /* return true or false based on condition being checked */
    return verified;
}

/**
 * @brief Verifies the size of the canvas specified by the user.
 * 
 * @param usrIns, the command line inputs of the user (int [6]).
 */
int vMapSize(int* usrIns)
{
    int verified = TRUE;
    /* Check if the user specified size of the canvas is greater than the defined minimum */
    if((usrIns[ROWS] < MAP_SIZE_MINIMUM) || (usrIns[COLS] < MAP_SIZE_MINIMUM))
    {
        verified = FALSE;
        /* Clear terminal and print error message */
        system("clear");
        printf("Invalid Map Size! Please ensure map size is greater than or equal to 5\n");
        printf("./escape <row_map> <col_map> <row_player> <col_player> <row_goal> <col_goal>\n");
    }
    /* return true or false based on condition being checked */
    return verified;
}

/**
 * @brief Verifies the starting location of the player and goal specified by the user.
 * 
 * @param usrIns, the command line inputs of the user (int [6]).
 */
int vStartLocation(int* usrIns)
{
    int verified = TRUE;

    /* Check the user specified player location starts in map and not equal to the goal*/
    int playerChecks = (usrIns[PLAYER_ROW] >= usrIns[ROWS]) || (usrIns[PLAYER_ROW] < 0) 
        || (usrIns[PLAYER_COL] >= usrIns[COLS]) || (usrIns[PLAYER_COL] < 0 
        || (usrIns[PLAYER_ROW] == usrIns[GOAL_ROW] && usrIns[PLAYER_COL] == usrIns[GOAL_COL]));

    /* Check the user specified goal location starts in map and not equal to the player*/
    int goalChecks = (usrIns[GOAL_ROW] >= usrIns[ROWS]) || (usrIns[GOAL_ROW] < 0) 
        || (usrIns[GOAL_ROW] >= usrIns[COLS]) || (usrIns[GOAL_ROW] < 0);

    if(playerChecks || goalChecks)
    {
        verified = FALSE;
        /* Clear terminal and print error message */
        system("clear");
        printf("Invalid Location! Ensure locations are not equal and reside within the map\n");
        printf("./escape <row_map> <col_map> <row_player> <col_player> <row_goal> <col_goal>\n");
    }
    /* return true or false based on condition being checked */
    return verified;
}

/**
 * @brief Verifies the move character specified by the user.
 * 
 * @param move, the keyboard character entered by the user to move the player (char*).
 */
int vMove(char* move)
{
    int verified = FALSE;
    /*Check user enters a correct move key*/
    if((*move) == UP_KEY || (*move) == DOWN_KEY || (*move) == LEFT_KEY || (*move) == RIGHT_KEY)
    {
        verified = TRUE;
    }
    /* return true or false based on condition being checked */
    return verified;
}

/**
 * @brief Verifies if there is a collapsed floor character at the specified coordinates.
 * 
 * @param usrIns, the command line inputs of the user (int [6]).
 * @param coords, the coordinates being checked for a collapsed floor character (int [2])
 * @param canvas, pointer to the game canvas (char***).
 * @param checkGoal, integer that confirms if the goal and player symbols should also be checked
 * 0 = false otherwise true (int).
 */
int vFloor(int* usrIns, int* coords, char*** canvas, int checkGoal)
{
    int i, j;
    int verified = TRUE;
    for (i=0;i<=usrIns[ROWS];i++)
    {
        for(j=0;j<=usrIns[COLS];j++)
        {
            /*Check if there is an collapsed floor at the given coordinates*/
            if((*canvas)[i][j] == FLOOR_SYM && i == (coords[0]+1) && j == (coords[1]+1))
            {
                verified = FALSE;
            }
            /*Check if there is a player or goal at the given coordinates*/
            if(checkGoal && ((*canvas)[i][j] == GOAL_SYM || (*canvas)[i][j] == PLAYER_SYM) 
                && i == (coords[0]+1) && j == (coords[1]+1))
            {
                verified = FALSE;
            }
        }
    }
    /* return true or false based on condition being checked */
    return verified;
}

/**
 * @brief Verifies the win condition.
 * 
 * @param usrIns, the command line inputs of the user (int [6]).
 * @param playerCoords, the coordinates of the current player's position (int [2])
 */
int vWin(int* usrIns, int* playerCoords)
{
    int won = FALSE;
    /*Check if the player coordinates are equal to the goal*/
    if(playerCoords[0] == usrIns[GOAL_ROW] && playerCoords[1] == usrIns[GOAL_COL])
    {
        won = TRUE;
    }
    /* return true or false based on condition being checked */
    return won;
}

/**
 * @brief Verifies if there are collapsed floors surrounding the specified coordinates.
 * 
 * @param canvas, pointer to the game canvas (char***).
 * @param coords, the coordinates being checked for surrounding collapsed floor characters (int [2])
 * @param usrIns, the command line inputs of the user (int [6]).
 */
int vLose(char*** canvas, int* coords, int* usrIns)
{
    int lose = FALSE;
    /* the starting position of the coordinates being checked */
    /* +1 accounts for the canvas border */
    int sRow = coords[0] + 1;
    int sCol = coords[1] + 1;
    int cUp, cDown, cLeft, cRight;
    
    #ifndef BORDERLESS
        /* check left, right, up and down around the coordinates for a collapsed floor or border */
        cUp = ((*canvas)[sRow-1][sCol] == FLOOR_SYM) || ((*canvas)[sRow-1][sCol] == BORDER_SYM);
        cDown = ((*canvas)[sRow+1][sCol] == FLOOR_SYM) || ((*canvas)[sRow+1][sCol] == BORDER_SYM);
        cLeft = ((*canvas)[sRow][sCol-1] == FLOOR_SYM) || ((*canvas)[sRow][sCol-1] == BORDER_SYM);
        cRight = ((*canvas)[sRow][sCol+1] == FLOOR_SYM)|| ((*canvas)[sRow][sCol+1] == BORDER_SYM);
        /* check if the coordinates are completely surrounded by collapsed floors or borders */
        if(cLeft && cRight && cUp && cDown)
        {
            lose = TRUE;
        }
    #else 
        int maxRow = usrIns[ROWS];
        int maxCol = usrIns[COLS]; 
        /* check left, right, up and down around the coordinates for a collapsed floor or border */
        /* check 'across' the canvas if a border character is found */
        cUp = ((*canvas)[sRow-1][sCol] == FLOOR_SYM) 
            || (((*canvas)[sRow-1][sCol] == BORDER_SYM) && ((*canvas)[maxRow][sCol] == FLOOR_SYM));
        cDown = ((*canvas)[sRow+1][sCol] == FLOOR_SYM) 
            || (((*canvas)[sRow+1][sCol] == BORDER_SYM) && ((*canvas)[1][sCol] == FLOOR_SYM));
        cLeft = ((*canvas)[sRow][sCol-1] == FLOOR_SYM) 
            || (((*canvas)[sRow][sCol-1] == BORDER_SYM) && ((*canvas)[sRow][maxCol] == FLOOR_SYM));
        cRight = ((*canvas)[sRow][sCol+1] == FLOOR_SYM) 
            || (((*canvas)[sRow][sCol+1] == BORDER_SYM) && ((*canvas)[sRow][1] == FLOOR_SYM));
        /* check if the coordinates are completely surrounded by collapsed floors */
        if(cLeft && cRight && cUp && cDown)
        {
            lose = TRUE;
        }
    #endif
    /* return true or false based on condition being checked */
    return lose;
}