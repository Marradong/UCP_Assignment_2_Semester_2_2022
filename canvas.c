#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "canvas.h"
#include "LinkedList.h"
#include "toolbox.h"
#include "color.h"
#include "verify.h"
#include "gameplay.h"

/**************************************************************************************************/
/* Canvas Initialisation, Display and Termination Methods                   	      		  	  */
/**************************************************************************************************/

/**
 * @brief Dynamicly allocates memory to a 2D array of characters (the canvas).
 *
 * @param gObj, pointer to Struct containing game variables (GameObj*)
 * @param canvas pointer to a 2d character array or 'game canvas' (char***).
 */
static void createCanvas(GameObj* gObj, char*** canvas)
{
    int i;
    /* Establish number of rows and columns in the array given by the users command line input */
    /* + 2 accounts for the rows and columns that make up the canvas border */
    int rows = gObj->canvasSize[ROWS] + 2;
    int cols = gObj->canvasSize[COLS] + 2;

    /* Dynamicly allocate memory the size of a char* to the rows of the array  */
    (*canvas) = (char**)malloc(rows*sizeof(char*));

    /* For each row dynamicly allocate memory the size of a char to the columns of the array */
    for (i = 0; i < rows; i++)
    {
        (*canvas)[i] = (char*)malloc(cols*sizeof(char));

        if (i == 0 || i == (rows - 1))
        {
            /* if it is the first or last row place a border symbol in every column */
            memset((*canvas)[i], BORDER_SYM, cols);
        }
        else
        {
            /* otherwise place a border symbol in the 1st and last column with spaces in between */
            memset((*canvas)[i], BORDER_SYM, 1);
            memset((*canvas)[i] + 1, SPACE_SYM, cols - 2);
            memset((*canvas)[i] + cols - 1, BORDER_SYM, 1);
        }
    }
}

/**
 * @brief Initialises canvas from input file and prints the canvas along with player and goal.
 *
 * @param f, pointer to pointer of the file entered by the user in the command line (FILE**)
 * @param canvas, pointer to the game canvas (char***).
 * @param argv, pointer to array of characters entered by the user in the command line (char**)
 * @param gObj, pointer to Struct containing game variables (GameObj*)
 * @param gList, pointer to linked list containing the game data (LList*)
 */
int iCanv(FILE** f, char*** canvas, char** argv, GameObj* gObj, LinkedList** gList)
{
    /* create an integer that reflects if a file error occurs or not */
    int fileError = FALSE;
    /* open the file with name specified by the command line args */
    (*f) = fopen(argv[FILE_IDX], "r");
    /* check if the file can be opened */
    if ((*f) == NULL)
    {
        /* Print error message if a file error occurs */
        perror("File Opening Error: Please check file name is correct and the file exist");
        fileError = TRUE;
    }
    else
    {
        int coords[2];
        int numRead = 3;
        char cSymbol;
        /* read the first line of the file in the form of 'number number\n' */
        fscanf((*f), "%d %d", &(gObj->canvasSize[ROWS]), &(gObj->canvasSize[COLS]));
        /* create canvas of size read from file */
        createCanvas(gObj, canvas);
        /* continue reading lines in the form of 'number number char\n' until end is reached */
        while (numRead == 3)
        {
            /* read lines in the form of 'number number char\n' */
            numRead = fscanf((*f), "%d %d %c", &coords[ROWS], &coords[COLS], &cSymbol);
            /* check if char read is a player, goal or floor and ammend coords accordingly  */
            if (cSymbol == PLAYER_SYM)
            {
                placeSym(coords, canvas, PLAYER_SYM);
                gObj->playerCoords[ROWS] = coords[ROWS];
                gObj->playerCoords[COLS] = coords[COLS];
            }
            else if (cSymbol == GOAL_SYM)
            {
                placeSym(coords, canvas, GOAL_SYM);
                gObj->goalCoords[ROWS] = coords[ROWS];
                gObj->goalCoords[COLS] = coords[COLS];
            }
            else if (cSymbol == FLOOR_SYM)
            {
                placeSym(coords, canvas, FLOOR_SYM);
            }
        }
        /* print canvas to terminal */
        printCanvas(gObj, canvas, gList);
        /* check if an error occured while the file is opened */
        if (ferror((*f)))
        {
            /* Print error message if a file error occurs */
            perror("A File Closing Error Occured");
            fileError = TRUE;
        }
        /* close the file */
        fclose((*f));
    }
    return fileError;
}

/**
 * @brief Prints the 2D array of characters (the canvas) to the cleared terminal.
 *
 * @param gObj, pointer to Struct containing game variables (GameObj*)
 * @param canvas pointer to the game canvas (char***).
 * @param gList, pointer to linked list containing the game data (LList*)
 */
void printCanvas(GameObj* gObj, char ***canvas, LinkedList** gList)
{
    /* Establish number of rows and columns in the array given by the users command line input */
    /* + 2 accounts for the rows and columns that make up the canvas border */
    int rows = gObj->canvasSize[ROWS] + 2;
    int cols = gObj->canvasSize[COLS] + 2;
    int i, j;

    /* clears all previous output on the terminal */
    system("clear");

    /* prints each character in the canvas 1 by 1 with a new line character after each row */
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            /* if char is a player set font colour to blue */
            if ((*canvas)[i][j] == PLAYER_SYM)
            {
                setForeground("blue");
                setBackground("reset");
            }
            /* if char is a goal set font colour to green */
            else if ((*canvas)[i][j] == GOAL_SYM)
            {
                setForeground("green");
                setBackground("reset");
            }
            /* if char is the last collapsed floor set background colour to red */
            else if((*gList)->end != NULL && i == (((Data *)((*gList)->end->data))->fCoords[ROWS]+1) 
                    && j == (((Data *)((*gList)->end->data))->fCoords[COLS] + 1))
            {
                setForeground("white");
                setBackground("red");
            }
            /* otherwise reset colours */
            else
            {
                setForeground("reset");
                setBackground("reset");
            }
            printf("%c", (*canvas)[i][j]);
        }
        printf("\n");
    }
    /* prints movement instructions for the user */
    printf("Press w to go up\n");
    printf("Press s to go down\n");
    printf("Press a to go left\n");
    printf("Press d to go up\n");
    printf("Press u to undo\n");
}

/**
 * @brief Places a symbol (player, goal, floor) on the canvas.
 *
 * @param coords the coordinates of the symbol (int [2]).
 * @param canvas pointer to the game canvas (char***).
 * @param sym the symbol to place on the canvas (char).
 */
void placeSym(int *coords, char ***canvas, char sym)
{
    /* Equates the value of the canvas at the given coordinates to the specified a symbol */
    /* + 1 accounts for canvas border */
    (*canvas)[coords[ROWS] + 1][coords[COLS] + 1] = sym;
}

/**
 * @brief Frees the dynamicly allocated memory of a 2D array of characters (the canvas).
 *
 * @param gObj, pointer to Struct containing game variables (GameObj*)
 * @param canvas pointer to the game canvas (char***).
 */
void freeCanvas(GameObj* gObj, char*** canvas)
{
    /* Establish number of rows in the array given by the users command line input */
    /* + 2 accounts for the rows that make up the canvas border */
    int rows = gObj->canvasSize[ROWS] + 2;
    int i;

    for (i = 0; i < rows; i++)
    {
        /* Free and nullify the memory dynamicly allocated to the columns in the array */
        free((*canvas)[i]);
        (*canvas)[i] = NULL;
    }
    /* Free and nullify the memory dynamicly allocated to the rows in the array */
    free((*canvas));
    (*canvas) = NULL;
}