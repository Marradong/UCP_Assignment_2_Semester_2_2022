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
 * @param gObj, pointer to Struct containing game variables (GameObj*)
 * @param canvas pointer to the game canvas (char***).
 */
static void collapseFloor(GameObj* gObj, char ***canvas, int *floorCoords)
{
    int check = FALSE;

    /* Randomly generate coordinates until an acceptable location is achieved */
    /* location cannot be equal to the player, goal or any existing collapsed floors */
    while (!check)
    {
        /* Randomly generate row INDEX between 0 and maximum rows-1 (as specified by user input) */
        /* -1 accounts for C indexing starting at 0 */
        floorCoords[ROWS] = random(0, (gObj->canvasSize[ROWS] - 1));
        floorCoords[COLS] = random(0, (gObj->canvasSize[COLS] - 1));
        /* checks location is not equal to the player, goal or any existing collapsed floors */
        check = vFloor(gObj, floorCoords, canvas, TRUE);
    }
    /* place collapsed floor symbol on canvas at generated location */
    placeSym(floorCoords, canvas, FLOOR_SYM);
}

/**
 * @brief changes the player coordinates based off user input key (both with borders and borderless)
 *
 * @param gObj, pointer to Struct containing game variables (GameObj*)
 * @param usrKey, pointer to the keyboard charater associated with the players next move (char*).
 */
static void changeCoords(GameObj* gObj, char *usrKey)
{
    /* change the player coordinates based off user input key */
    switch ((*usrKey))
    {
    case UP_KEY:
        gObj->playerCoords[ROWS] = gObj->playerCoords[ROWS] - 1;
        break;
    case DOWN_KEY:
        gObj->playerCoords[ROWS] = gObj->playerCoords[ROWS] + 1;
        break;
    case LEFT_KEY:
        gObj->playerCoords[COLS] = gObj->playerCoords[COLS] - 1;
        break;
    case RIGHT_KEY:
        gObj->playerCoords[COLS] = gObj->playerCoords[COLS] + 1;
        break;
    default:
        break;
    }

#ifdef BORDERLESS
    /* check if the new player coordinates lie outside the canvas border and adjust the coordinates
    to wrap around to the otherside of the canvas if true*/
    if (gObj->playerCoords[ROWS] > gObj->canvasSize[ROWS] - 1)
    {
        gObj->playerCoords[ROWS] = 0;
    }
    else if (gObj->playerCoords[ROWS] < 0)
    {
        gObj->playerCoords[ROWS] = gObj->canvasSize[ROWS] - 1;
    }
    else if (gObj->playerCoords[COLS] > gObj->canvasSize[COLS] - 1)
    {
        gObj->playerCoords[COLS] = 0;
    }
    else if (gObj->playerCoords[COLS] < 0)
    {
        gObj->playerCoords[COLS] = gObj->canvasSize[COLS] - 1;
    }
#endif
}

/**
 * @brief Places the player and collapsed floor at new coordinates and adds these to the linked list
 *
 * @param canvas, pointer to the game canvas (char***).
 * @param gObj, pointer to Struct containing game variables (GameObj*)
 * @param tCoords, old coordinates of the player on the canvas (int[2]).
 * @param fCoords, current coordinates of the new collapsed on the canvas (int[2]).
 * @param gList, pointer to linked list containing the game data (LList*)
 */
static void pPlayer(char ***canvas, GameObj* gObj, int *tCoord, int *fCoord, LinkedList **gList)
{
    /* create new node for linked list */
    Data* newNodeData = NULL;
    createData(&newNodeData);
    /* Remove player from old location and place player at new location */
    placeSym(tCoord, canvas, SPACE_SYM);
    placeSym(gObj->playerCoords, canvas, PLAYER_SYM);
    /* Generate collapsed floor */
    collapseFloor(gObj, canvas, fCoord);
    /* assign the old location and collapsed floor to the data */
    newNodeData->playerCoords[ROWS] = tCoord[ROWS];
    newNodeData->playerCoords[COLS] = tCoord[COLS];
    newNodeData->fCoords[ROWS] = fCoord[ROWS];
    newNodeData->fCoords[COLS] = fCoord[COLS];
    /* add the node to the linked list */
    insertLast(gList, newNodeData);
    /* reprint canvas after successful move */
    printCanvas(gObj, canvas, gList);
}

/**
 * @brief Moves the player to the previous position and removes the newest collapsed floor
 *
 * @param canvas, pointer to the game canvas (char***).
 * @param gObj, pointer to Struct containing game variables (GameObj*)
 * @param tCoords, old coordinates of the player on the canvas (int[2]).
 * @param fCoords, current coordinates of the new collapsed on the canvas (int[2]).
 * @param gList, pointer to linked list containing the game data (LList*)
 */
static void undoMove(char ***canvas, GameObj* gObj, int *tCoord, int *fCoord, LinkedList **gList)
{
    /* get the data from the last node of the linked list */
    Data* data = ((Data*)((*gList)->end->data));
    /* assign the player location and collapsed floor location from the node to the arrays */
    gObj->playerCoords[ROWS] = (int)data->playerCoords[ROWS];
    gObj->playerCoords[COLS] = (int)data->playerCoords[COLS];
    fCoord[ROWS] = (int)data->fCoords[ROWS];
    fCoord[COLS] = (int)data->fCoords[COLS];
    /* remove the node from the linked list */
    removeLast(gList, &freeData);
    /* Remove player from new location and place at old location then remove collapsed floor */
    placeSym(tCoord, canvas, SPACE_SYM);
    placeSym(gObj->playerCoords, canvas, PLAYER_SYM);
    placeSym(fCoord, canvas, SPACE_SYM);
    /* reprint canvas after every successful undo */
    printCanvas(gObj, canvas, gList);
}

/**
 * @brief Moves player based off user input key (both with borders and borderless)
 *
 * @param canvas, pointer to the game canvas (char***).
 * @param usrKey, pointer to the keyboard charater associated with the players next move (char*).
 * @param gObj, pointer to Struct containing game variables (GameObj*)
 * @param gList, pointer to linked list containing the game data (LList*)
 */
void movePlayer(char ***canvas, char *usrKey, GameObj* gObj, LinkedList **gList)
{
    /* Temporarily store player location in case of invalid move */
    int tempCoords[2], floorCoords[2], conditions;
    tempCoords[ROWS] = gObj->playerCoords[ROWS];
    tempCoords[COLS] = gObj->playerCoords[COLS];
    /* move player based on user input */
    switch ((*usrKey))
    {
    case UP_KEY:
    case DOWN_KEY:
    case LEFT_KEY:
    case RIGHT_KEY:
        /* Change the player coordinates in the direction indicated by the user input character */
        changeCoords(gObj, usrKey);

        /* check the players new coordinates arent equal to a collapsed floor */
        conditions = !vFloor(gObj, gObj->playerCoords, canvas, FALSE);
        #ifndef BORDERLESS
            /* check if the new coordinates lie outside the canvas border */
            /* -1 accounts for C indexing starting at 0 */
            conditions = conditions || (gObj->playerCoords[ROWS] > gObj->canvasSize[ROWS] - 1) 
            || (gObj->playerCoords[ROWS] < 0) 
            || (gObj->playerCoords[COLS] > gObj->canvasSize[COLS] - 1) 
            || (gObj->playerCoords[COLS] < 0);
        #endif
        
        if (conditions)
        {
            /* Invalid move, revert coordinates back to the original position */
            gObj->playerCoords[ROWS] = tempCoords[ROWS];
            gObj->playerCoords[COLS] = tempCoords[COLS];
        }
        else
        {
            /* Move the player and add the coordinates to a linked list */
            pPlayer(canvas, gObj, tempCoords, floorCoords, gList);
        }
        break;
    case UNDO_KEY:
        /* check there are moves to undo */
        if ((*gList)->listLength != 0)
        {
           /* Move the player and remove the last node from a linked list */
            undoMove(canvas, gObj, tempCoords, floorCoords, gList);
        }
        break;
    default:
        break;
    }
    /* Reset user input character to invalid character */
    (*usrKey) = ' ';
}