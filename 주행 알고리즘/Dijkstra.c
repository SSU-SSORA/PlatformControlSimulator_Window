#include <stdio.h>
#include "MapStruct.h"

void Dijkstra(MapStruct *this) {


	int StartX = 5, StartY = 7;
	int CurrentX = StartX, CurrentY = StartY;
	int FinishX = 0, FinishY = 12;
	int i = 0, j = 0, roop = 0; // for���� ����


	char MapWeight[13][13];
	for (i = 0; i < 13; ++i) {
		for (j = 0; j < 13; ++j) {
			MapWeight[i][j] = 13 * 13 * 10; // �Ϲ������� ���� �湮�������� ���� ����ġ�� ���Ѵ�� �����ϳ�, ���Ѵ�ǥ���� ��Ʊ⿡ ����ġ �ִ밪+1���� �ʱ�ȭ
		}
	}
	MapWeight[StartY][StartX] = 0; // MapWeight �ʱ�ȭ

	char VisitMap[13][13]; // 0�� �湮 ��, 1�� �湮 ��
	
	for (i = 0; i < 13; ++i) {
		for (j = 0; j < 13; ++j) {
			VisitMap[i][j] = 0;
		}
	} // VisitMap �ʱ�ȭ

	char CompareSize[9][4]; // ������ǥ �ֺ��� ����ġ�� ���峷�� ��ǥ���� �湮�ؾ��ϱ⿡ ����ġ���� ��ǥ����

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