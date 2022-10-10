#include <stdio.h>
#include <stdlib.h>
#include "canvas.h"
#include "toolbox.h"
#include "verify.h"
#include "gameplay.h"
#include "random.h"
#include "LinkedList.h"

/**************************************************************************************************/
/* Main loop of Game                   	      		                                         	  */
/**************************************************************************************************/

int main(int argc, char *argv[])
{
    /* Check if the correct number of command line arguments was entered */
    if (vArgs(&argc))
    {
        /* initialise game variables */
        GameObj gObj;
        int winStatus = FALSE;
        int loseStatus = FALSE;
        char **canvas = NULL;
        char usrKey = ' ';
        FILE *inputFile = NULL;

        LinkedList *gameList = createLinkedList();

        initRandom();
        if (!iCanv(&inputFile, &canvas, argv, &gObj, &gameList))
        {

            /* Game loop - continue asking player for moves until a win or lose condition is met */
            while (!(winStatus || loseStatus))
            {
                /* Read user input for players next move */
                readMove(&usrKey);
                /* Move player */
                /* determine player movement function based on borderless definition */
                movePlayer(&canvas, &usrKey, &gObj, &gameList);

                /* Check if win or lose condition is met after player moves */
                winStatus = vWin(&gObj);
                loseStatus = (vLose(&canvas, gObj.playerCoords, &gObj) 
                || vLose(&canvas, gObj.goalCoords, &gObj));
            }
            /* Print end game message based on win or lose */
            if (winStatus)
            {
                printf("You Win!\n");
            }
            else
            {
                printf("You Lose!\n");
            }
            /* Free game canvas memory */
            freeCanvas(&gObj, &canvas);
        }
        freeLinkedList(&gameList, &freeData);
    }
    return 0;
}