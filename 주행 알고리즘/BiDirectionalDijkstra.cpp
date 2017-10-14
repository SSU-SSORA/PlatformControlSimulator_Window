#include <stdio.h>
#include <malloc.h>
#include "MapStruct.h"
#include "BiDirectionalDijkstra.h"

void BiDirectionalDijkstraStruct::BiDirectional_Dijkstra(MapStruct *this_) {
	
	BiDijkstra_Init(this_);
	int CurrentSX = this_->StartX, CurrentSY = this_->StartY;
	int CurrentFX = this_->FinishX, CurrentFY = this_->FinishY;

	while (1) {
		if (MeetDiscriminant(this_, &CurrentSX, &CurrentSY, MapWeightF)) break;
		Searching(this_, &CurrentSX, &CurrentSY,MapWeightS,VisitMapS);

		if (MeetDiscriminant(this_, &CurrentFX, &CurrentFY, MapWeightS)) break;
		Searching(this_, &CurrentFX, &CurrentFY, MapWeightF,VisitMapF);
	}
	
	V += 1;
	this_->VisitX[V] = MeetX;
	this_->VisitY[V] = MeetY;

	BiDijkstra_PathXY(this_);
	BiDijkstra_VisitXY(this_);
	BiDijkstra_Destroy(this_);
}

void BiDirectionalDijkstraStruct::BiDijkstra_Init(MapStruct *this_) {
	int i, j;

	MapWeightS = (int**)malloc(sizeof(int*) * this_->col);
	MapWeightF = (int**)malloc(sizeof(int*) * this_->col);
	for (i = 0; i < this_->col; ++i) {
		MapWeightS[i] = (int*)malloc(sizeof(int) * this_->row);
		MapWeightF[i] = (int*)malloc(sizeof(int) * this_->row);
	}

	for (i = 0; i < this_->col; ++i) {
		for (j = 0; j < this_->row; ++j) {
			MapWeightS[i][j] = INFINITE;
			MapWeightF[i][j] = INFINITE;// 일반적으로 아직 방문하지않은 곳의 가중치를 무한대로 설정하나, 무한대표현이 어렵기에 가중치 최대값+1으로 초기화
		}
	}
	MapWeightS[this_->StartY][this_->StartX] = 0; // MapWeight 초기화
	MapWeightF[this_->FinishY][this_->FinishX] = 0;

	VisitMapS = (char**)calloc(sizeof(char*), this_->col);
	VisitMapF = (char**)calloc(sizeof(char*), this_->col);// 0은 방문 전,1은 방문 대기, 2은 방문 후
	for (i = 0; i < this_->col; ++i) {
		VisitMapS[i] = (char*)calloc(sizeof(char), this_->row);
		VisitMapF[i] = (char*)calloc(sizeof(char), this_->row);
	}

}

void BiDirectionalDijkstraStruct::BiDijkstra_Destroy(MapStruct* this_) {

	for (int i = 0; i < this_->row; ++i) {
		free(MapWeightS[i]);
		free(MapWeightF[i]);
		free(VisitMapS[i]);
		free(VisitMapF[i]);
	}

	free(VisitMapS);
	free(VisitMapF);
	free(MapWeightS);
	free(MapWeightF);

	MapWeightS = NULL;
	MapWeightF = NULL;
	VisitMapS = NULL;
	VisitMapF = NULL;

}

void BiDirectionalDijkstraStruct::BiDijkstra_PathXY(MapStruct* this_) {
	int i, j;
	int Min = INFINITE;
	int a, b;
	int X = MeetX, Y = MeetY;
	this_->PathMap[Y][X] = 0;

	FILE* fp = fopen(PATHMAPFILENAME, "w+");
	fprintf(fp, "%d %d\n", X, Y);

	while (this_->map[Y][X] != 's') {
		for (i = -1; i <= 1; ++i) {
			for (j = -1; j <= 1; ++j) {
				if (Y + i < 0 || Y + i >= this_->col || X + j < 0 || X + j >= this_->row) {}
				else if (i * i + j * j == 0) {}
				else if (Min > MapWeightS[Y + i][X + j]) {
					Min = MapWeightS[Y + i][X + j];
					a = X + j; 
					b = Y + i; 
				}
			}
		} 
		X = a; Y = b;
		Min = INFINITE;
		if (this_->map[Y][X] == 's') break;
		fprintf(fp, "%d %d\n", X,Y);
		this_->PathMap[Y][X] = 0;
	}
	
	X = MeetX; Y = MeetY;

	while (this_->map[Y][X] != 'f') {
		for (i = -1; i <= 1; ++i) {
			for (j = -1; j <= 1; ++j) {
				if (Y + i < 0 || Y + i >= this_->col || X + j < 0 || X + j >= this_->row){}
				else if (Min > MapWeightF[Y + i][X + j]) {
					Min = MapWeightF[Y + i][X + j]; 
					a = X + j;   
					b = Y + i;
				}
			}
		} 
		X = a; Y = b;
		Min = INFINITE;
		if (this_->map[Y][X] == 'f') break;
		fprintf(fp, "%d %d\n", X, Y);
		this_->PathMap[Y][X] = 0;
	}
	
	fclose(fp);
}

void BiDirectionalDijkstraStruct::BiDijkstra_VisitXY(MapStruct* this_) {
	FILE* fp = fopen(VISITXYFILENAME, "w+");
	
	for (int i = 0; i < this_->row * this_->col; ++i) {
		if (this_->map[this_->VisitY[i]][this_->VisitX[i]] == 's') continue;
		if (this_->map[this_->VisitY[i]][this_->VisitX[i]] == 'f') continue;
		fprintf(fp, "%d %d\n", this_->VisitX[i], this_->VisitY[i]);
	}
	fclose(fp);
}

void BiDirectionalDijkstraStruct::Searching(MapStruct* this_, int *CurrentX, int *CurrentY, int **MapWeight,char **VisitMap) {

	int Min = INFINITE;
	int i, j;
	int X, Y;
	VisitMap[*CurrentY][*CurrentX] = 1;
	this_->VisitX[V] = *CurrentX;
	this_->VisitY[V] = *CurrentY;
	V += 1;
	
	for (i = -1; i <= 1; ++i) {
		for (j = -1; j <= 1; ++j) {
			if (*CurrentX + j < 0 || *CurrentX + j >= this_->row || *CurrentY + i < 0 || *CurrentY + i >= this_->col) {}
			else if (this_->map[*CurrentY + i][*CurrentX + j] < 0) {}
			else {
				if (i*i + j*j == 1)
					if (MapWeight[*CurrentY + i][*CurrentX + j] > MapWeight[*CurrentY][*CurrentX] + 10)
						MapWeight[*CurrentY + i][*CurrentX + j] = MapWeight[*CurrentY][*CurrentX] + 10;
				if (i*i + j*j == 2)
					if (MapWeight[*CurrentY + i][*CurrentX + j] > MapWeight[*CurrentY][*CurrentX] + 14)
						MapWeight[*CurrentY + i][*CurrentX + j] = MapWeight[*CurrentY][*CurrentX] + 14;
				if (i*i + j*j == 0) {}

			}
		}
	}

	for (i = 0; i < this_->col; ++i) {
		for (j = 0; j < this_->row; ++j) {
			if (Min > MapWeight[i][j]) {
				if (VisitMap[i][j] == 0) {
					Min = MapWeight[i][j];
					*CurrentX = j;
					*CurrentY = i;
				}
			}
		}
	}

}

int BiDirectionalDijkstraStruct::MeetDiscriminant(MapStruct* this_, int *CurrentX, int *CurrentY, int **MapWeight) {
	
	int Min = INFINITE;
	int escape = 0;

	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			if (*CurrentX + j < 0 || *CurrentX + j >= this_->row || *CurrentY + i < 0 || *CurrentY + i >= this_->col) {}
			else if (MapWeightS[*CurrentY + i][*CurrentX + j] != INFINITE) {
				if (Min > MapWeight[*CurrentY + i][*CurrentX + j]) {
					Min = MapWeight[*CurrentY + i][*CurrentX + j];
					MeetX = *CurrentX + j; MeetY = *CurrentY + i;
					this_->VisitX[V] = *CurrentX;
					this_->VisitY[V] = *CurrentY;
					escape = 1;
				}
			}
		}
	}
	if (escape) return 1;
	else return 0;
}