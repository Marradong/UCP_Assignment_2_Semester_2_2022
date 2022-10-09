#include <stdio.h>
#include <stdlib.h>
#include "canvas.h"
#include "toolbox.h"

/**************************************************************************************************/
/* Utilities                           	      		                                         	  */
/**************************************************************************************************/

/**
 * @brief Converts an array of characters into an array of integers (skips first character)
 * 
 * @param cArr, pointer to an array of charaters (char**).
 * @param iArr, an array of integers (int*).
 * @param len, pointer to the length of both character and integer arrays (int*).
 */
void charToInt(char** cArr, int* iArr, int* len)
{
    int i;
    /* Starting with the second character in the array
    iterate through each character and convert it to a number */
    for (i=1; i<(*len); i++)
    {
        iArr[i-1] = atoi(cArr[i]);
    }
}

/**
 * @brief Dynamocly allocates memory to a new data struct 
 * 
 * @param newData, doupble pointer to game data
 */
void createData(Data** newData)
{
    (*newData) = (Data*)malloc(sizeof(Data));
}

/**
 * @brief Frees memory of a data struct 
 * 
 * @param data, void pointer to data struct
 */
void freeData(void *data)
{
    /* set data to 0*/
    ((Data*)data)->playerCoords[ROWS] = 0;
    ((Data*)data)->playerCoords[COLS] = 0;
    ((Data*)data)->fCoords[ROWS] = 0;
    ((Data*)data)->fCoords[COLS] = 0;
    /* free data and nullify data */
    free(((Data*)data));
    data = NULL;
}