#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "MapStruct.h"


void _ShowMap(const MapStruct* this_) {
	for (int i = 0; i < this_->row; ++i) {
		for (int j = 0; j < this_->col; ++j) {
			if (this_->map[i][j] == 255)
				printf("%3d", -1);
			else if (this_->map[i][j] == 's' || this_->map[i][j] == 'f')
				printf("%3c", this_->map[i][j]);
			else
				printf("%3d", (int)this_->map[i][j]);
		}
		printf("\n");
	}
}

void _Init(const char * filename, MapStruct *this_) {
	
	int row, col;

	FILE * in = fopen(filename, "rt");
	fscanf(in, "%d %d", &row, &col);

	//assign memory
	this_->map = (unsigned char **)malloc(sizeof(unsigned char *) * row);
	assert(this_->map != NULL);
	for (int i = 0; i < col; i++) {
		this_->map[i] = (unsigned char *)malloc(sizeof(unsigned char) * col);
		assert(this_->map != NULL);
	}

	int i, j, data;
	while (fgetc(in)!= EOF) {
		fscanf(in,"%d %d %d", &i, &j, &data);
		this_->map[i][j] = (unsigned char)data;//unsigned char = int, -1 == 255·Î Ä¡È¯µÊ
	}

	this_->Init = _Init;
	this_->ShowMap = _ShowMap;
	this_->Destroy = _Destroy;
	this_->ShowMapPretty = _ShowMapPretty;
	this_->row = row;
	this_->col = col;
}

void _Destroy(MapStruct *this_) {
	for (int i = 0; i < this_->col; ++i)
		free(this_->map[i]);
	free(this_->map);

	this_->map = NULL;
	this_->col = 0;
	this_->row = 0;
}

void _ShowMapPretty(const MapStruct* this_) {
	for (int i = 0; i < this_->row; ++i) {
		for (int j = 0; j < this_->col; ++j) {
			if (this_->map[i][j] == 255)//-1, º®
				printf("%3s", "¡á");
			else if (this_->map[i][j] == 's' || this_->map[i][j] == 'f')
				printf("%3c", this_->map[i][j]);
			else
				printf("%3s", "¡à");
		}
		printf("\n");
	}
}