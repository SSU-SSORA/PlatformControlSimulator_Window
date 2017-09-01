#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "MapStruct.h"


void _ShowMap(const MapStruct* this) {
	for (int i = 0; i < this->row; ++i) {
		for (int j = 0; j < this->col; ++j) {
			if (this->map[i][j] == 255)
				printf("%3d", -1);
			else if (this->map[i][j] == 's' || this->map[i][j] == 'f')
				printf("%3c", this->map[i][j]);
			else
				printf("%3d", (int)this->map[i][j]);
		}
		printf("\n");
	}
}


void _Init(const char * filename, MapStruct *this) {
	
	int row, col;

	FILE * in = fopen(filename, "rt");
	fscanf(in, "%d %d", &row, &col);

	//assign memory
	this->map = (unsigned char **)malloc(sizeof(unsigned char *) * row);
	assert(this->map != NULL);
	for (int i = 0; i < col; i++) {
		this->map[i] = (unsigned char *)malloc(sizeof(unsigned char) * col);
		assert(this->map != NULL);
	}

	int i, j, data;
	while (fgetc(in)!= EOF) {
		fscanf(in,"%d %d %d", &i, &j, &data);
		this->map[i][j] = (unsigned char)data;//unsigned char = int, -1 == 255·Î Ä¡È¯µÊ
	}

	this->Init = _Init;
	this->ShowMap = _ShowMap;
	this->Destroy = _Destroy;
	this->ShowMapPretty = _ShowMapPretty;
	this->row = row;
	this->col = col;
}

void _Destroy(MapStruct *this) {
	for (int i = 0; i < this->col; ++i)
		free(this->map[i]);
	free(this->map);

	this->map = NULL;
	this->col = 0;
	this->row = 0;
}


void _ShowMapPretty(const MapStruct* this) {
	for (int i = 0; i < this->row; ++i) {
		for (int j = 0; j < this->col; ++j) {
			if (this->map[i][j] == 255)//-1, º®
				printf("%3s", "¡á");
			else if (this->map[i][j] == 's' || this->map[i][j] == 'f')
				printf("%3c", this->map[i][j]);
			else
				printf("%3s", "¡à");
		}
		printf("\n");
	}
}