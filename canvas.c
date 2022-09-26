#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "canvas.h"

/**************************************************************************************************/
/* Canvas Initialisation, Display and Termination Methods                   	      		  	  */
/**************************************************************************************************/

/**
 * @brief Dynamicly allocates memory to a 2D array of characters (the canvas).
 * 
 * @param usrIns the command line inputs of the user (int [6]).
 * @param canvas pointer to the game canvas (char***).
 */
void createCanvas(int* canvasSize, char*** canvas)
{
    int i;
    /* Establish number of rows and columns in the array given by the users command line input */
    /* + 2 accounts for the rows and columns that make up the canvas border */
    int rows = canvasSize[ROWS] + 2;
    int cols = canvasSize[COLS] + 2;
    
    /* Dynamicly allocate memory the size of a char* to the rows of the array  */
    (*canvas) = (char**)malloc(rows * sizeof(char*));

    /* For each row dynamicly allocate memory the size of a char to the columns of the array */
    for (i=0;i<rows;i++)
    {
        (*canvas)[i] = (char*)malloc(cols * sizeof(char));

        if(i == 0 || i == (rows - 1))
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
 * @brief Initialises and prints the canvas along with player and goal.
 * 
 * @param fInput, pointer to pointer of the file entered by the user in the command line (FILE**)
 * @param canvas, pointer to the game canvas (char***).
 * @param argv, pointer to array of characters entered by the user in the command line (char**)
 * @param canvasSize, array of integers containing the size of the canvas (int[])
 * @param goalCoords, array of integers containing the coordinates of the goal (int[])
 * @param playerCoords, array of integers containing the coordinates of the player (int[])
 */
void initCanvas(FILE** fInput, char*** canvas, char** argv, int* canvasSize, int* goalCoords, int* playerCoords)
{
    (*fInput) = fopen(argv[FILE_IDX], "r");

        if(fInput == NULL)
        {
            perror("File Opening Error: Please check file name is correct and the file exist");
        }
        else
        {            
            int coords[2]; 
            int numRead = 3;
            char cSymbol;

            fscanf(fInput, "%d %d", coords[ROWS], coords[COLS]);
            canvasSize[ROWS] = coords[ROWS];
            canvasSize[COLS] = coords[COLS];

            createCanvas(coords, canvas);

            while (numRead != 3)
            {
                numRead = fscanf(fInput, "%d %d %c", coords[ROWS], coords[COLS], &cSymbol);

                if(cSymbol == PLAYER_SYM)
                {
                    placeSym(coords, canvas, PLAYER_SYM);
                    playerCoords[ROWS] = coords[ROWS];
                    playerCoords[COLS] = coords[COLS];
                }
                else if(cSymbol == GOAL_SYM)
                {
                    placeSym(coords, canvas, GOAL_SYM);
                    goalCoords[ROWS] = coords[ROWS];
                    goalCoords[COLS] = coords[COLS];
                }
                else if(cSymbol == FLOOR_SYM)
                {
                    placeSym(coords, canvas, FLOOR_SYM);
                }
            }
            printCanvas(canvasSize, canvas);

            if(ferror(fInput))
            {
                perror("File Reading Error: ");
            }

            fclose(fInput);
        }
}

/**
 * @brief Prints the 2D array of characters (the canvas) to the cleared terminal.
 * 
 * @param usrIns the command line inputs of the user (int [6]).
 * @param canvas pointer to the game canvas (char***).
 */
void printCanvas(int* canvasSize, char*** canvas)
{
    /* Establish number of rows and columns in the array given by the users command line input */
    /* + 2 accounts for the rows and columns that make up the canvas border */
    int rows = canvasSize[ROWS] + 2;
    int cols = canvasSize[COLS] + 2;
    int i, j;

    /* clears all previous output on the terminal */
    system("clear");

    /* prints each character in the canvas 1 by 1 with a new line character after each row */
    for (i=0;i<rows;i++)
    {
        for(j=0;j<cols;j++)
        {
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
void placeSym(int* coords, char*** canvas, char sym)
{
    /* Equates the value of the canvas at the given coordinates to the specified a symbol */
    /* + 1 accounts for canvas border */
    (*canvas)[coords[ROWS] + 1][coords[COLS] + 1] = sym;
}

/**
 * @brief Frees the dynamicly allocated memory of a 2D array of characters (the canvas).
 * 
 * @param usrIns the command line inputs of the user (int [6]).
 * @param canvas pointer to the game canvas (char***).
 */
void freeCanvas(int* usrIns, char*** canvas)
{
    /* Establish number of rows in the array given by the users command line input */
    /* + 2 accounts for the rows that make up the canvas border */
    int rows = usrIns[ROWS] + 2;
    int i;

    for (i=0;i<rows;i++)
    {
        /* Free and nullify the memory dynamicly allocated to the columns in the array */
        free((*canvas)[i]);
        (*canvas)[i] = NULL;
    }
    /* Free and nullify the memory dynamicly allocated to the rows in the array */
    free((*canvas));
    (*canvas) = NULL;
}