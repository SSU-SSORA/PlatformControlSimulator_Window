#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include "MapStruct.h"
#include "Astar.h"

void AstarStruct::Astar(MapStruct *this_) {

	Astar_Init(this_);
	int i, j;//for문용 변수
	int CurrentX = this_->StartX, CurrentY = this_->StartY;
	int Min = 0, MinX, MinY;

	Close[CurrentY][CurrentX] = 1;

	int V = 0;//VisitXY저장용
	while (this_->map[CurrentY][CurrentX] != 'f') {
		

		for (i = -1; i <= 1; ++i) {
			for (j = -1; j <= 1; ++j) {
				if (CurrentY + i < 0 || CurrentY + i >= this_->col || CurrentX + j < 0 || CurrentX + j >= this_->col) {} // 맵 밖으로 벗어나면 열린목록에 넣지않음.
				else if (this_->map[CurrentY + i][CurrentX + j] < 0) {} // 장애물이면 열린목록에 넣지않음.
				else if (Close[CurrentY + i][CurrentX + j] == 1) {}// 닫힌목록에 있으면 열린목록에 넣지않음.
				else if (Open[CurrentY + i][CurrentX + j] == 1) { // 이미 열린목록에 있었을 때
					Open[CurrentY + i][CurrentX + j] = 2;
				}
				else if (Open[CurrentY + i][CurrentX + j] == 2) {}// 열린목록에 있으면 열린목록에 넣지않음.
				else {
					Open[CurrentY + i][CurrentX + j] = 1;

					ParentsXY[CurrentY + i][CurrentX + j] = CurrentX * 100 + CurrentY;

					G[CurrentY + i][CurrentX + j] = sqrt(pow(this_->StartX - (CurrentX + j), 2) + pow(this_->StartY - (CurrentY + i), 2)) * 100;
					H[CurrentY + i][CurrentX + j] = (abs(this_->FinishX - (CurrentX + j)) + abs(this_->FinishY - (CurrentY + i))) * 100;
					F[CurrentY + i][CurrentX + j] = G[CurrentY + i][CurrentX + j] + H[CurrentY + i][CurrentX + j];
					
				}
			}
		}

		for (i = -1; i <= 1; ++i) {
			for (j = -1; j <= 1; ++j) {
				if (CurrentY + i < 0 || CurrentY + i >= this_->col || CurrentX + j < 0 || CurrentX + j >= this_->col) {}
				else if (this_->map[CurrentY + i][CurrentX + j] < 0) {}
				else if (Close[CurrentY + i][CurrentX + j] == 1) {}
				else if (i*i + j*j == 0) {}
				else if (F[CurrentY + i][CurrentX + j] == 0) {}
				else if (Min > F[CurrentY + i][CurrentX + j] || Min == 0) {
					Min = F[CurrentY + i][CurrentX + j];
					MinX = CurrentX + j;
					MinY = CurrentY + i;
				}
				else if (Min == F[CurrentY + i][CurrentX + j]) {//F값이 같은 곳이 있을 때 
					if (Open[CurrentY + i][CurrentX + j] >= 1) {//이미 열린목록에 있었다면, 그 곳을 먼저 검사한다.
						MinX = CurrentX + j;
						MinY = CurrentY + i;
					}
				}
			}
		}
		Min = 0;

		if (Open[MinY][MinX] == 2) {
			if (G[MinY][MinX] >= G[CurrentY][CurrentX] + sqrt(pow((MinX - CurrentX), 2) + pow((MinY - CurrentY), 2))) {
				ParentsXY[MinY][MinX] = CurrentX * 100 + CurrentY; 
			}
		}

		CurrentX = MinX;
		CurrentY = MinY;
		Close[CurrentY][CurrentX] = 1;
		this_->VisitX[V] = CurrentX;
		this_->VisitY[V] = CurrentY;
		++V;
	}

	Astar_PathXY(this_);
	Astar_VisitXY(this_);
	Astar_Destroy(this_);

}

void AstarStruct::Astar_Init(MapStruct *this_) {

	ParentsXY = (int**)calloc(sizeof(int*), this_->col);

	Open = (int**)calloc(sizeof(int*), this_->col);  // 열린지점    1은 열린지점 0 은 x
	Close = (int**)calloc(sizeof(int*), this_->col); //닫힌지점     1은 닫힌지점 0 은 x    

	for (int i = 0; i < this_->col; ++i) {
		Open[i] = (int*)calloc(sizeof(int*), this_->row);
		Close[i] = (int*)calloc(sizeof(int*), this_->row);
		ParentsXY[i] = (int*)calloc(sizeof(int*), this_->row);
	}

	F = (int**)calloc(sizeof(int*), this_->col); // F = G + H
	G = (int**)calloc(sizeof(int*), this_->col); // 시작점에서 현재점까지의 거리
	H = (int**)calloc(sizeof(int*), this_->col); // 현재점에서 도착점까지의 거리

	for (int i = 0; i < this_->col; ++i) {
		F[i] = (int*)calloc(sizeof(int), this_->row);
		G[i] = (int*)calloc(sizeof(int), this_->row);
		H[i] = (int*)calloc(sizeof(int), this_->row);
	}

}

void AstarStruct::Astar_Destroy(MapStruct *this_) {
	for (int i = 0; i < this_->row; ++i) {
		free(Open[i]);
		free(Close[i]);
		free(ParentsXY[i]);
		free(F[i]);
		free(G[i]);
		free(H[i]);
	}

	free(Open);
	free(Close);
	free(ParentsXY);
	free(F);
	free(G);
	free(H);

	Open = NULL;
	Close = NULL;
	ParentsXY = NULL;
	F = NULL;
	G = NULL;
	H = NULL;
}

void AstarStruct::Astar_PathXY(MapStruct *this_) {
	int X,PathX = this_->FinishX;
	int Y,PathY = this_->FinishY;
	FILE* fp = fopen(PATHMAPFILENAME, "w+");

	while (this_->map[PathY][PathX] != 's') {
		X = ParentsXY[PathY][PathX] / 100;
		Y = ParentsXY[PathY][PathX] % 100;

		PathX = X, PathY = Y;

		if (this_->map[PathY][PathX] != 's') {
			this_->PathMap[PathY][PathX] = 0;
			
			fprintf(fp, "%d %d\n", PathX, PathY);
		}

	}

	fclose(fp);
}

void AstarStruct::Astar_VisitXY(MapStruct *this_) {
	FILE* fp = fopen(VISITXYFILENAME, "w+");
	for (int i = 0; i < this_->row * this_->col; ++i) {
		fprintf(fp, "%d %d\n", this_->VisitX[i], this_->VisitY[i]);
		if (this_->map[this_->VisitY[i]][this_->VisitX[i]] == 'f') break;
	}
	fclose(fp);
}