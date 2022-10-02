#include <stdio.h>
#include "gameplay.h"
#include "terminal.h"
#include "verify.h"
#include "canvas.h"
#include "random.h"
#include "toolbox.h"
#include "LinkedList.h"

/**************************************************************************************************/
/* Player Movement and Collapsed Floor Generation Methods                   	      		  	  */
/**************************************************************************************************/

/**
 * @brief Reads keyboard input immediately.
 *
 * @param usrKey, pointer to the keyboard charater associated with the players next move (char*).
 */
void readMove(char *usrKey)
{
    /* disables terminal buffer so keyboard input can be read immediately without the return key */
    disableBuffer();

    /* continually requests keyboard input until a verified character move is entered */
    while (!vMove(usrKey))
    {
        scanf(" %c", usrKey);
    }

    enableBuffer();
}

/**
 * @brief Randomly places a collapsed floor character on the canvas.
 *
 * @param canvasSize, array of integers containing the size of the canvas (int[])
 * @param canvas pointer to the game canvas (char***).
 */
void collapseFloor(int *canvasSize, char ***canvas, int *floorCoords)
{
    int check = FALSE;

    /* Randomly generate coordinates until an acceptable location is achieved */
    /* location cannot be equal to the player, goal or any existing collapsed floors */
    while (!check)
    {
        /* Randomly generate row INDEX between 0 and maximum rows-1 (as specified by user input) */
        /* -1 accounts for C indexing starting at 0 */
        floorCoords[ROWS] = random(0, (canvasSize[ROWS] - 1));
        floorCoords[COLS] = random(0, (canvasSize[COLS] - 1));
        /* checks location is not equal to the player, goal or any existing collapsed floors */
        check = vFloor(canvasSize, floorCoords, canvas, TRUE);
    }
    /* place collapsed floor symbol on canvas at generated location */
    placeSym(floorCoords, canvas, FLOOR_SYM);
}

/**
 * @brief Moves player based off user input key (within borders)
 *
 * @param canvas, pointer to the game canvas (char***).
 * @param usrKey, pointer to the keyboard charater associated with the players next move (char*).
 * @param playerCoords, current coordinates of the player on the canvas (int [2]).
 * @param canvasSize, array of integers containing the size of the canvas (int[])
 */
void movePlayer(char ***canvas, char *usrKey, int *playerCoords, int *canvasSize, LinkedList *gameList)
{
    /* Temporarily store player location in case of invalid move */
    int tempCoords[2], floorCoords[2], conditions;
    tempCoords[ROWS] = playerCoords[ROWS];
    tempCoords[COLS] = playerCoords[COLS];

    /* Change the player coordinates in the direction indicated by the user input character */
    switch ((*usrKey))
    {
    case UP_KEY:
    case DOWN_KEY:
    case LEFT_KEY:
    case RIGHT_KEY:
        changeCoords(playerCoords, canvasSize, usrKey);

        conditions = !vFloor(canvasSize, playerCoords, canvas, FALSE);
        #ifndef BORDERLESS
            /* check if the new player coordinates lie outside the canvas border or are equal to a
    collapsed floor */
        /* -1 accounts for C indexing starting at 0 */
            conditions = conditions || (playerCoords[ROWS] > canvasSize[ROWS] - 1) 
            || (playerCoords[ROWS] < 0) || (playerCoords[COLS] > canvasSize[COLS] - 1) 
            || (playerCoords[COLS] < 0);
        #endif
        
        if (conditions)
        {
            /* Invalid move, revert coordinates back to the original position */
            playerCoords[ROWS] = tempCoords[ROWS];
            playerCoords[COLS] = tempCoords[COLS];
        }
        else
        {
            Data* newNodeData = createData();

            /* Valid move, remove player from old location and place player at new location */
            placeSym(tempCoords, canvas, SPACE_SYM);
            placeSym(playerCoords, canvas, PLAYER_SYM);
            /* Generate collapsed floor and reprint canvas after every successful move */
            collapseFloor(canvasSize, canvas, floorCoords);

            newNodeData->playerCoords[ROWS] = tempCoords[ROWS];
            newNodeData->playerCoords[COLS] = tempCoords[COLS];
            newNodeData->floorCoords[ROWS] = floorCoords[ROWS];
            newNodeData->floorCoords[COLS] = floorCoords[COLS];

            addEndNode(gameList, newNodeData);
            printCanvas(canvasSize, canvas, gameList);
        }
        break;
    case UNDO_KEY:
        if (gameList->listLength != 0)
        {
            Data* data = ((Data*)(gameList->end->data));

            playerCoords[ROWS] = (int)data->playerCoords[ROWS];
            playerCoords[COLS] = (int)data->playerCoords[COLS];
            floorCoords[ROWS] = (int)data->floorCoords[ROWS];
            floorCoords[COLS] = (int)data->floorCoords[COLS];

            removeEndNode(gameList, &freeData);

            placeSym(tempCoords, canvas, SPACE_SYM);
            placeSym(playerCoords, canvas, PLAYER_SYM);
            placeSym(floorCoords, canvas, SPACE_SYM);

            printCanvas(canvasSize, canvas, gameList);
        }
        break;
    default:
        break;
    }
    /* Reset user input character to invalid character */
    (*usrKey) = ' ';
}

void changeCoords(int *playerCoords, int* canvasSize, char *usrKey)
{
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

#ifdef BORDERLESS
    /* check if the new player coordinates lie outside the canvas border and adjust the coordinates
    to wrap around to the otherside of the canvas if true*/
    if (playerCoords[ROWS] > canvasSize[ROWS] - 1)
    {
        playerCoords[ROWS] = 0;
    }
    else if (playerCoords[ROWS] < 0)
    {
        playerCoords[ROWS] = canvasSize[ROWS] - 1;
    }
    else if (playerCoords[COLS] > canvasSize[COLS] - 1)
    {
        playerCoords[COLS] = 0;
    }
    else if (playerCoords[COLS] < 0)
    {
        playerCoords[COLS] = canvasSize[COLS] - 1;
    }
#endif
}