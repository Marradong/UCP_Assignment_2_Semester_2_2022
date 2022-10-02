#ifndef TOOLBOX_H
#define TOOLBOX_H

typedef struct Data
{
	int playerCoords[2];
	int floorCoords[2];
} Data;

void charToInt(char** cArr, int* iArr, int* len);
Data* createData();
void freeData(void* data);

#endif