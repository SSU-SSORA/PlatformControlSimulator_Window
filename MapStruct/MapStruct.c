﻿#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "MapStruct.h"


void _ShowMap(const MapStruct* this_) {
	for (int i = 0; i < this_->col; ++i) {
		for (int j = 0; j < this_->row; ++j) {
			//if (this_->map[i][j] == 255)
			//	printf("%3d", -1);
			if (this_->map[i][j] == 's' || this_->map[i][j] == 'f')
				printf("%3c", this_->map[i][j]);
			else
				printf("%3d", (int)this_->map[i][j]);
		}
		printf("\n");
	}
}

void _ShowPathMap(const MapStruct* this_) {
	for (int i = 0; i < this_->col; ++i) {
		for (int j = 0; j < this_->row; ++j) {
			//if (this_->map[i][j] == 255)
			//	printf("%3d", -1);
			if (this_->PathMap[i][j] == 's' || this_->PathMap[i][j] == 'f')
				printf("%3c", this_->PathMap[i][j]);
			else
				printf("%3d", (int)this_->PathMap[i][j]);
		}
		printf("\n");
	}
}

void _Init(const char * filename, MapStruct *this_) {
	
	int row, col;

	FILE * in = fopen(filename, "rt");
	fscanf(in, "%d %d", &row, &col);

	//assign memory
	this_->map = (int **)malloc(sizeof(int *) * col);
	assert(this_->map != NULL);
	for (int i = 0; i < col; i++) {
		this_->map[i] = (int *)malloc(sizeof(int) * row);
		assert(this_->map != NULL);
	}

	this_->PathMap = (int **)malloc(sizeof(int *) * col);
	assert(this_->PathMap != NULL);
	for (int i = 0; i < col; i++) {
		this_->PathMap[i] = (int *)malloc(sizeof(int) * row);
		assert(this_->map != NULL);
	}


	int i, j, data;

	
	while (fgetc(in)!= EOF) {
		fscanf(in,"%d %d %d", &i, &j, &data);
		this_->map[i][j] = data;
		this_->PathMap[i][j] = data; 
		if (this_->map[i][j] == 's') { this_->StartX = j; this_->StartY = i; }
	}


	this_->VisitX = (int*)malloc(sizeof(int) * (row * col));
	this_->VisitY = (int*)malloc(sizeof(int) * (row * col));

	for (i = 0; i < row*col; ++i) {
		this_->VisitX[i] = this_->StartX;
		this_->VisitY[i] = this_->StartY;
	}



	this_->Init = _Init;
	this_->ShowMap = _ShowMap;
	this_->ShowPathMap = _ShowPathMap;
	this_->Destroy = _Destroy;
	this_->ShowMapPretty = _ShowMapPretty;
	this_->ShowVisitXY = _ShowVisitXY;
	this_->row = row;
	this_->col = col;
}

void _Destroy(MapStruct *this_) {

	for (int i = 0; i < this_->row; ++i)
		free(this_->map[i]);
	free(this_->map);
	
	for (int i = 0; i < this_->row; ++i)
		free(this_->PathMap[i]);
	free(this_->PathMap);

	free(this_->VisitY);
	free(this_->VisitX);
	

	this_->PathMap = NULL;
	this_->map = NULL;
	this_->col = 0;
	this_->row = 0;
	this_->StartX = 0;
	this_->StartY = 0;
	this_->VisitX = 0;
	this_->VisitY = 0;
}

void _ShowMapPretty(const MapStruct* this_) {
	for (int i = 0; i < this_->col; ++i) {
		for (int j = 0; j < this_->row; ++j) {
			if (this_->map[i][j] == -1)//-1, ��
				printf("%3s", "��");
			else if (this_->map[i][j] == 's' || this_->map[i][j] == 'f')
				printf("%3c", this_->map[i][j]);
			else
				printf("%3s", "��");
		}
		printf("\n");
	}
}

void _ShowVisitXY(const MapStruct* this_) {
	for (int i = 0; i < this_->col * this_->row; ++i) {
		printf("X[%d] : %d\t Y[%d] : %d\n", i, this_->VisitX[i], i, this_->VisitY[i]);
	}
}
