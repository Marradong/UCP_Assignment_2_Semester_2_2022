#include <stdio.h>
#include <stdlib.h>
#include "canvas.h"
#include "toolbox.h"
#include "verify.h"
#include "gameplay.h"
#include "random.h"

/**************************************************************************************************/
/* Main loop of Game                   	      		                                         	  */
/**************************************************************************************************/

int main(int argc, char *argv[])
{
    /* Check if the correct number of command line arguments was entered */
    if (vArgs(&argc))
    {
        /* initialise integer arrays */
        int usrIns[6], playerCoords[2], goalCoords[2];

        /* convert command line arguments to integers */
        charToInt(argv, usrIns, &argc);

        /* store user starting locations for player and goal in seperate arrays */
        playerCoords[ROWS] = usrIns[PLAYER_ROW];
        playerCoords[COLS] = usrIns[PLAYER_COL];
        goalCoords[ROWS] = usrIns[GOAL_ROW];
        goalCoords[COLS] = usrIns[GOAL_COL];

        /* Check if the command line map size and starting locations are valid */
        if (vMapSize(usrIns) && vStartLocation(usrIns))
        {
            /* initialise game variables */
            int winStatus = FALSE;
            int loseStatus = FALSE;
            char **canvas = NULL;
            char usrKey = ' ';
            pfMove mFunc = NULL;

            /* initialise random generator and game canvas */
            initRandom();
            initCanvas(usrIns, playerCoords, &canvas);

            /* determine player movement function based on borderless definition */
            #ifndef BORDERLESS
                mFunc = &movePlayer;
            #else
                mFunc = &moveBorderless;
            #endif

            /* Game loop - continue asking player for moves until a win or lose condition is met */
            while (!(winStatus || loseStatus))
            {
                /* Read user input for players next move */
                readMove(&usrKey);
                /* Move player */
                (*mFunc)(&canvas, &usrKey, playerCoords, usrIns);
                /* Check if win or lose condition is met after player moves */
                winStatus = vWin(usrIns, playerCoords);
                loseStatus = (vLose(&canvas, playerCoords, usrIns) 
                            || vLose(&canvas, goalCoords, usrIns));
            }
            /* Print end game message based on win or lose */
            if(winStatus)
            {
                printf("You Win!\n");
            }
            else
            {
                printf("You Lose!\n");
            }
            /* Free game canvas memory */
            freeCanvas(usrIns, &canvas);
        }
    }
    return 0;
}