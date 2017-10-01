#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "MapStruct.h"


void MapStruct::ShowMap() {
	for (int i = 0; i < this->col; ++i) {
		for (int j = 0; j < this->row; ++j) {
			//if (map[i][j] == 255)
			//	printf("%3d", -1);
			if (this->map[i][j] == 's' || this->map[i][j] == 'f')
				printf("%3c", map[i][j]);
			else
				printf("%3d", (int)this->map[i][j]);
		}
		printf("\n");
	}
}
	 
void MapStruct::ShowPathMap() {
	for (int i = 0; i < col; ++i) {
		for (int j = 0; j < row; ++j) {
			//if (map[i][j] == 255)
			//	printf("%3d", -1);
			if (PathMap[i][j] == 's' || PathMap[i][j] == 'f')
				printf("%3c", PathMap[i][j]);
			else
				printf("%3d", (int)PathMap[i][j]);
		}
		printf("\n");
	}
}

void MapStruct::Init(const char * filename) {
	
	int row, col;

	FILE * in = fopen(filename, "rt");
	fscanf(in, "%d %d", &row, &col);

	//assign memory
	map = (int **)calloc(sizeof(int *), col);
	assert(map != NULL);
	for (int i = 0; i < col; i++) {
		map[i] = (int *)calloc(sizeof(int), row);
		assert(map != NULL);
	}

	PathMap = (int **)calloc(sizeof(int *), col);
	assert(PathMap != NULL);
	for (int i = 0; i < col; i++) {
		PathMap[i] = (int *)calloc(sizeof(int), row);
		assert(map != NULL);
	}


	int i, j, data;

	
	while (fgetc(in)!= EOF) {
		fscanf(in,"%d %d %d", &i, &j, &data);
		map[i][j] = data;
		PathMap[i][j] = data; 
		if (map[i][j] == 's') { StartX = j; StartY = i; }
		if (map[i][j] == 'f') { FinishX = j; FinishY = i; }
	}


	VisitX = (int*)malloc(sizeof(int) * (row * col));
	VisitY = (int*)malloc(sizeof(int) * (row * col));

	for (i = 0; i < row*col; ++i) {
		VisitX[i] = StartX;
		VisitY[i] = StartY;
	}
	this->row = row;
	this->col = col;
}

void MapStruct::Destroy() {

	for (int i = 0; i < row; ++i)
		free(map[i]);
	free(map);
	
	for (int i = 0; i < row; ++i)
		free(PathMap[i]);
	free(PathMap);

	free(VisitY);
	free(VisitX);
	

	PathMap = NULL;
	map = NULL;
	col = 0;
	row = 0;
	StartX = 0;
	StartY = 0;
	FinishX = 0;
	FinishY = 0;
	VisitX = 0;
	VisitY = 0;
}
	 
void MapStruct::ShowMapPretty() {
	for (int i = 0; i < col; ++i) {
		for (int j = 0; j < row; ++j) {
			if (map[i][j] == -1)//-1, ��
				printf("%3s", "��");
			else if (map[i][j] == 's' || map[i][j] == 'f')
				printf("%3c", map[i][j]);
			else
				printf("%3s", "��");
		}
		printf("\n");
	}
}
	 
void MapStruct::ShowVisitXY() {
	for (int i = 0; i < col * row; ++i) {
		printf("X[%d] : %d\t Y[%d] : %d\n", i, VisitX[i], i, VisitY[i]);
	}
}
