#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <Windows.h>
#include "MapStruct.h"
#include "Astar.h"

void AstarStruct::Astar(MapStruct *this_) {

	Astar_Init(this_);
	int i, j,loop = 0;//for문용 변수
	int CurrentX = this_->StartX, CurrentY = this_->StartY;
	int Min = 0, MinX, MinY;
	int AddOpen = 0;
	Close[CurrentY][CurrentX] = 1;

	while (this_->map[CurrentY][CurrentX] != 'f') {
		

		for (i = -1; i <= 1; ++i) {
			for (j = -1; j <= 1; ++j) {
				if (CurrentY + i < 0 || CurrentY + i >= this_->col || CurrentX + j < 0 || CurrentX + j >= this_->col) {} // 맵 밖으로 벗어나면 열린목록에 넣지않음.
				else if (this_->map[CurrentY + i][CurrentX + j] < 0) {} // 장애물이면 열린목록에 넣지않음.
				else if (Close[CurrentY + i][CurrentX + j] == 1) {}// 닫힌목록에 있으면 열린목록에 넣지않음.
				//else if (Open[CurrentY + i][CurrentX + j] == 1) {} // 열린목록에 있으면 열린목록에 넣지않음.
				else {
					Open[CurrentY + i][CurrentX + j] = 1;
					ParentsXY[CurrentY + i][CurrentX + j] = CurrentX * 100 + CurrentY;

					G[CurrentY + i][CurrentX + j] = sqrt(pow(this_->StartX - (CurrentX + j), 2) + pow(this_->StartY - (CurrentY + i), 2)) * 100;
					H[CurrentY + i][CurrentX + j] = (abs(this_->FinishX - (CurrentX + j)) + abs(this_->FinishY - (CurrentY + i))) * 100;
					F[CurrentY + i][CurrentX + j] = G[CurrentY + i][CurrentX + j] + H[CurrentY + i][CurrentX + j];
					
					AddOpen++;
				}
			}
		}
		if (AddOpen == 0) {
			for (i = -1; i <= 1; ++i) {
				for (j = -1; j <= 1; ++j) {
					if (CurrentY + i < 0 || CurrentY + i >= this_->col || CurrentX + j < 0 || CurrentX + j >= this_->col) {}
					else if (this_->map[CurrentY + i][CurrentX + j] < 0) {}
					else if (Close[CurrentY + i][CurrentX + j] == 1) {}
					else if (Open[CurrentY + i][CurrentX + j] == 1) {
						if (G[CurrentY + i][CurrentX + j] < G[CurrentY][CurrentX] + sqrt(i*i + j*j)) {
							CurrentX = CurrentX + j;
							CurrentY = CurrentY + i;
							break;
						}
					}
				}
				if (G[CurrentY + i][CurrentX + j] < G[CurrentY][CurrentX] + sqrt(i*i + j*j)) break;
			}
		}


		AddOpen = 0;

		
		for (i = -1; i <= 1; ++i) {
			for (j = -1; j <= 1; ++j) {
				if (CurrentY + i < 0 || CurrentY + i >= this_->col || CurrentX + j < 0 || CurrentX + j >= this_->col) {}
				else if (this_->map[CurrentY + i][CurrentX + j] < 0){}
				else if (Close[CurrentY + i][CurrentX + j] == 1) {}
				else if (i*i + j*j == 0) {}
				else if (F[CurrentY + i][CurrentX + j] == 0) {}
				else if (Min > F[CurrentY + i][CurrentX + j] || Min == 0) {
					Min = F[CurrentY + i][CurrentX + j];
					MinX = CurrentX + j;
					MinY = CurrentY + i;
					
				}
			}
		}
		Min = 0;
		CurrentX = MinX;
		CurrentY = MinY;
		Close[CurrentY][CurrentX] = 1;
		this_->PathMap[CurrentY][CurrentX] = 0;
		/*system("cls");
		for (i = 0; i < 13; ++i) {
			for (j = 0; j < 13; ++j) {
				printf("%d\t", Close[i][j]);
			}printf("\n");
		}printf("\n");
		
		printf("%d %d\n", CurrentX, CurrentY);
		Sleep(800);*/
	}


	this_->PathMap[CurrentY][CurrentX] = 'f';
	

	for (i = 0; i < 13; ++i) {
		for (j = 0; j < 13; ++j) {
			printf("%d\t", Close[i][j]);
		}printf("\n");
	}printf("\n");

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