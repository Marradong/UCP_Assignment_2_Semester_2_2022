#ifndef TOOLBOX_H
#define TOOLBOX_H

/* struct type definition for linked list data */
typedef struct Data
{
	int playerCoords[2];
	int fCoords[2];
} Data;

void charToInt(char** cArr, int* iArr, int* len);
void createData(Data** newData);
void freeData(void* data);

#endif