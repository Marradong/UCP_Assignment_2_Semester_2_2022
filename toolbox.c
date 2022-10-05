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
 */
void createData(Data** newData)
{
    (*newData) = (Data*)malloc(sizeof(Data));
}

/**
 * @brief Frees memory of a data struct 
 * 
 * @param data, pointer to data struct
 */
void freeData(void *data)
{
    ((Data*)data)->playerCoords[ROWS] = 0;
    ((Data*)data)->playerCoords[COLS] = 0;
    ((Data*)data)->floorCoords[ROWS] = 0;
    ((Data*)data)->floorCoords[COLS] = 0;
    free(((Data*)data));
    data = NULL;
}