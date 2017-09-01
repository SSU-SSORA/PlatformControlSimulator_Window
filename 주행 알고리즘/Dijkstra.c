#include <stdio.h>
#include "MapStruct.h"

void Dijkstra(MapStruct *this) {


	int StartX = 5, StartY = 7;
	int CurrentX = StartX, CurrentY = StartY;
	int FinishX = 0, FinishY = 12;
	int i = 0, j = 0, roop = 0; // for문용 변수


	char MapWeight[13][13];
	for (i = 0; i < 13; ++i) {
		for (j = 0; j < 13; ++j) {
			MapWeight[i][j] = 13 * 13 * 10; // 일반적으로 아직 방문하지않은 곳의 가중치를 무한대로 설정하나, 무한대표현이 어렵기에 가중치 최대값+1으로 초기화
		}
	}
	MapWeight[StartY][StartX] = 0; // MapWeight 초기화

	char VisitMap[13][13]; // 0은 방문 전, 1은 방문 후
	
	for (i = 0; i < 13; ++i) {
		for (j = 0; j < 13; ++j) {
			VisitMap[i][j] = 0;
		}
	} // VisitMap 초기화

	char CompareSize[9][4]; // 현재좌표 주변에 가중치가 가장낮은 좌표부터 방문해야하기에 가중치비교후 좌표저장

	for (i = -1; i <= 1; ++i) {
		for (j = -1; j <= 1; ++j) {
			
			if (this -> map[CurrentY + i][CurrentX + j] < 0) {}
			
			else if (i*i + j*j == 2) {
				
				if (MapWeight[CurrentY + i][CurrentX + j] == 13 * 13 * 10) {
					MapWeight[CurrentY + i][CurrentX + j] = 14;
				}
				else MapWeight[CurrentY + i][CurrentX + j] += 14;
			}
			
			else if (i*i + j*j == 1) {
				
				if (MapWeight[CurrentY + i][CurrentX + j] == 13 * 13 * 10) {
					MapWeight[CurrentY + i][CurrentX + j] = 10;
				}
				else MapWeight[CurrentY + i][CurrentX + j] += 10;
			}
		}
	}
	
	VisitMap[CurrentY][CurrentX] = 1;







	for (i = 0; i < 13; ++i) {
		for (j = 0; j < 13; ++j) {
			if (this->map[i][j] == 255)
				printf("%d\t", -1);
			else 
				printf("%d\t", this -> map[i][j]);

		}
		printf("\n");
	}
}