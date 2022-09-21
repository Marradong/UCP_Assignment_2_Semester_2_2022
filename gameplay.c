#include <stdio.h>
#include "gameplay.h"
#include "terminal.h"
#include "verify.h"
#include "canvas.h"
#include "random.h"
#include "toolbox.h"

/**************************************************************************************************/
/* Player Movement and Collapsed Floor Generation Methods                   	      		  	  */
/**************************************************************************************************/

/**
 * @brief Reads keyboard input immediately.
 * 
 * @param usrKey, pointer to the keyboard charater associated with the players next move (char*).
 */
void readMove(char* usrKey)
{
    /* disables terminal buffer so keyboard input can be read immediately without the return key */
    disableBuffer();

    /* continually requests keyboard input until a verified character move is entered */
    while(!vMove(usrKey))
    {
        scanf(" %c", usrKey);
    }  

    enableBuffer();
}

/**
 * @brief Randomly places a collapsed floor character on the canvas.
 * 
 * @param usrIns the command line inputs of the user (int [6]).
 * @param canvas pointer to the game canvas (char***).
 */
void collapseFloor(int* usrIns, char*** canvas)
{
    int clpseCoords[2];
    int check = FALSE;

    /* Randomly generate coordinates until an acceptable location is achieved */
    /* location cannot be equal to the player, goal or any existing collapsed floors */
    while(!check)
    {
        /* Randomly generate row INDEX between 0 and maximum rows-1 (as specified by user input) */
        /* -1 accounts for C indexing starting at 0 */
        clpseCoords[ROWS] = random(0, (usrIns[ROWS] - 1));
        clpseCoords[COLS] = random(0, (usrIns[COLS] - 1));
        /* checks location is not equal to the player, goal or any existing collapsed floors */
        check = vFloor(usrIns, clpseCoords, canvas, TRUE);
    }
    /* place collapsed floor symbol on canvas at generated location */
    placeSym(clpseCoords, canvas, FLOOR_SYM);
}

/**
 * @brief Moves player based off user input key (within borders)
 * 
 * @param canvas, pointer to the game canvas (char***).
 * @param usrKey, pointer to the keyboard charater associated with the players next move (char*).
 * @param playerCoords, current coordinates of the player on the canvas (int [2]).
 * @param usrIns, the command line inputs of the user (int [6]).
 */
void movePlayer(char*** canvas, char* usrKey, int* playerCoords, int* usrIns)
{
    /* Temporarily store player location in case of invalid move */
    int tempCoords[2];
    tempCoords[ROWS] = playerCoords[ROWS];
    tempCoords[COLS] = playerCoords[COLS];

    /* Change the player coordinates in the direction indicated by the user input character */
    switch ((*usrKey))
    {
    case UP_KEY:
        playerCoords[ROWS] = playerCoords[ROWS] - 1;
        break;
    case DOWN_KEY:
        playerCoords[ROWS] = playerCoords[ROWS] + 1;
        break;
    case LEFT_KEY:
        playerCoords[COLS] = playerCoords[COLS] - 1;
        break;
    case RIGHT_KEY:
        playerCoords[COLS] = playerCoords[COLS] + 1;
        break;
    default:
        break;
    }

    /* check if the new player coordinates lie outside the canvas border or are equal to a 
    collapsed floor */
    /* -1 accounts for C indexing starting at 0 */
    if((playerCoords[ROWS] > usrIns[ROWS] - 1) 
        || (playerCoords[ROWS] < 0) 
        || (playerCoords[COLS] > usrIns[COLS] - 1) 
        || (playerCoords[COLS] < 0) 
        || !vFloor(usrIns, playerCoords, canvas, FALSE)) 
    {
        /* Invalid move, revert coordinates back to the original position */
        playerCoords[ROWS] = tempCoords[ROWS];
        playerCoords[COLS] = tempCoords[COLS];
    }
    else
    {
        /* Valid move, remove player from old location and place player at new location */
        placeSym(tempCoords, canvas, SPACE_SYM);
        placeSym(playerCoords, canvas, PLAYER_SYM);
        /* Generate collapsed floor and reprint canvas after every successful move */
        collapseFloor(usrIns, canvas);
        printCanvas(usrIns, canvas);
    }
    /* Reset user input character to invalid character */
    (*usrKey) = ' ';
}

/**
 * @brief Moves player based off user input key (ignores borders)
 * 
 * @param canvas, pointer to the game canvas (char***).
 * @param usrKey, pointer to the keyboard charater associated with the players next move (char*).
 * @param playerCoords, current coordinates of the player on the canvas (int [2]).
 * @param usrIns, the command line inputs of the user (int [6]).
 */
void moveBorderless(char*** canvas, char* usrKey, int* playerCoords, int* usrIns)
{
    /* Temporarily store player location in case of invalid move */
    int tempCoords[2];
    tempCoords[ROWS] = playerCoords[ROWS];
    tempCoords[COLS] = playerCoords[COLS];

    /* Change the player coordinates in the direction indicated by the user input character */
    switch ((*usrKey))
    {
    case UP_KEY:
        playerCoords[ROWS] = playerCoords[ROWS] - 1;
        break;
    case DOWN_KEY:
        playerCoords[ROWS] = playerCoords[ROWS] + 1;
        break;
    case LEFT_KEY:
        playerCoords[COLS] = playerCoords[COLS] - 1;
        break;
    case RIGHT_KEY:
        playerCoords[COLS] = playerCoords[COLS] + 1;
        break;
    default:
        break;
    }

    /* check if the new player coordinates lie outside the canvas border and adjust the coordinates 
    to wrap around to the otherside of the canvas if true*/
    if(playerCoords[ROWS] > usrIns[ROWS] - 1)
    {
        playerCoords[ROWS] = 0;
    }
    else if(playerCoords[ROWS] < 0)
    {
        playerCoords[ROWS] = usrIns[ROWS] - 1;
    }
    else if(playerCoords[COLS] > usrIns[COLS] - 1)
    {
        playerCoords[COLS] = 0;
    }
    else if(playerCoords[COLS] < 0)
    {
        playerCoords[COLS] = usrIns[COLS] - 1;
    }

    /* check if the new player coordinates are equal to a collapsed floor */
    if(vFloor(usrIns, playerCoords, canvas, FALSE))
    {
        /* Valid move, remove player from old location and place player at new location */
        placeSym(tempCoords, canvas, SPACE_SYM);
        placeSym(playerCoords, canvas, PLAYER_SYM);
        /* Generate collapsed floor and reprint canvas after every successful move */
        collapseFloor(usrIns, canvas);
        printCanvas(usrIns, canvas);
    }
    else
    {
        /* Invalid move, revert coordinates back to the original position */
        playerCoords[ROWS] = tempCoords[ROWS];
        playerCoords[COLS] = tempCoords[COLS];
    }
    /* Reset user input character to invalid character */
    (*usrKey) = ' ';
}