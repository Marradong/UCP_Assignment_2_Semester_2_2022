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
        int canvasSize[2], goalCoords[2], playerCoords[2];
        int winStatus = FALSE;
        int loseStatus = FALSE;
        char **canvas = NULL;
        char usrKey = ' ';
        FILE* inputFile = NULL;

        LinkedList* gameList = createList();

        initRandom();
        initCanvasFromFile(&inputFile, &canvas, argv, canvasSize, goalCoords, playerCoords);

        /* Game loop - continue asking player for moves until a win or lose condition is met */
        while (!(winStatus || loseStatus))
        {
            /* Read user input for players next move */
            readMove(&usrKey);
            /* Move player */
            /* determine player movement function based on borderless definition */
            movePlayer(&canvas, &usrKey, playerCoords, canvasSize, gameList);
        
            /* Check if win or lose condition is met after player moves */
            winStatus = vWin(goalCoords, playerCoords);
            loseStatus = (vLose(&canvas, playerCoords, canvasSize) || vLose(&canvas, goalCoords, canvasSize));
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
        freeCanvas(canvasSize, &canvas);
        freeList(gameList, &freeData);
    }
    return 0;
}