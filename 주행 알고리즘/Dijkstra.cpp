#pragma warning(disable : 4996)

#include <stdio.h>
#include <malloc.h>
#include <windows.h>
#include "MapStruct.h"
#include "Dijkstra.h"


void DijkstraStruct::Dijkstra(MapStruct *this_) 
{

	int StartX = this_->StartX, StartY = this_->StartY;
	int VisitX = StartX, VisitY = StartY;
	int i = 0, j = 0, m = 0, loop = 0, V = 0; // for문용 변수

	Dijstra_Init(this_);

	int VisitValA = 0;
	int VisitValB = 1;
	const int VisitSize = 2 * 4; // (3-1) * 4

	int *CompareSize = (int*)malloc(sizeof(int) * VisitSize + (VisitValA * VisitSize)); // 현재좌표 주변에 가중치가 가장낮은 좌표부터 방문해야하기에 가중치비교후 좌표저장
																				//00000(가중치)00(x좌표)00(y좌표)

	for (i = 0; i < VisitSize + (VisitValA * VisitSize); ++i) {
		CompareSize[i] = INFINITE * 10000;
	}

	VisitMap[VisitY][VisitX] = VISIT_FINISH;
	this_->VisitX[V] = VisitX;
	this_->VisitY[V] = VisitY;
	++V;
	for (i = -1; i <= 1; ++i) {
		for (j = -1; j <= 1; ++j) {
			if(!(VisitX + j < 0 || VisitX + j >= this_->row || VisitY + i < 0 || VisitY + j >= this_->col))
			{
				int * searchPoint = &MapWeight[VisitY + i][VisitX + j];

				if (this_->map[VisitY + i][VisitX + j] < 0) {}//장애물일때
				else if (i*i + j*j == 2) {
					if (*searchPoint == INFINITE) *searchPoint = 14;
					else *searchPoint += 14;
				}

				else if (i*i + j*j == 1) {
					if (*searchPoint == INFINITE) *searchPoint = 10;
					else *searchPoint += 10;
				}


				if (VisitMap[VisitY + i][VisitX + j] < VISIT_SEARCHING) {
					VisitMap[VisitY + i][VisitX + j] = VISIT_SEARCHING;
					CompareSize[loop] = *searchPoint * 10000 + (VisitX + j) * 100 + (VisitY + i);
					++loop;
				}
			}
		}


	}

	loop = 0;

	int tmp;
	int *Size;

	while (this_->map[VisitY][VisitX] != 'f') { // 102 = 'f'

		for (i = 0; i < VisitSize + VisitValA * VisitSize; ++i) {
			for (j = i + 1; j < VisitSize + (VisitValA * VisitSize); j++) {
				if (CompareSize[j] < CompareSize[i]) {
					tmp = CompareSize[i];
					CompareSize[i] = CompareSize[j];
					CompareSize[j] = tmp;
				}
			}
		}
		//가중치가 작은순으로 나열

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		Size = (int*)malloc(sizeof(int) * (VisitSize + VisitValB * VisitSize));

		for (i = 0; i < VisitSize + VisitValB * VisitSize; ++i) {
			Size[i] = INFINITE * 10000;
		}


		for (m = 0; m < VisitSize + VisitValA * VisitSize; ++m) {
			if (CompareSize[m] == INFINITE * 10000) {}
			else {
				VisitX = (CompareSize[m] % 10000) / 100; // = x좌표
				VisitY = (CompareSize[m] % 10000) % 100; // = y좌표
				if (this_->map[VisitY][VisitX] == 'f') break; // 102 = 'f'

				if (this_->map[VisitY][VisitX] < 0) {}
				else {
					for (i = -1; i <= 1; ++i) {
						for (j = -1; j <= 1; ++j) {
							if (VisitY + i >= this_->col || VisitX + j >= this_->row || VisitX + j < 0 || VisitY + i < 0) {}
							else {
								if (this_->map[VisitY + i][VisitX + j] < 0) {}
								else if (VisitMap[VisitY + i][VisitX + j] == 1) {}
								else if (i*i + j*j == 2) {

									if (MapWeight[VisitY + i][VisitX + j] == INFINITE) {
										MapWeight[VisitY + i][VisitX + j] = MapWeight[VisitY][VisitX] + 14;
									}
									else if (MapWeight[VisitY + i][VisitX + j] < MapWeight[VisitY + i][VisitX + j] + 14) {}
									else {
										MapWeight[VisitY + i][VisitX + j] += 14;
									}

								}

								else if (i*i + j*j == 1) {
									if (MapWeight[VisitY + i][VisitX + j] == INFINITE) {
										MapWeight[VisitY + i][VisitX + j] = MapWeight[VisitY][VisitX] + 10;
									}
									else if (MapWeight[VisitY + i][VisitX + j] < MapWeight[VisitY + i][VisitX + j] + 10) {}
									else {
										MapWeight[VisitY + i][VisitX + j] += 10;
									}
								}

								if (VisitMap[VisitY + i][VisitX + j] < 1) {
									VisitMap[VisitY + i][VisitX + j] = 1;
									Size[loop] = MapWeight[VisitY + i][VisitX + j] * 10000 + (VisitX + j) * 100 + (VisitY + i);
									++loop;
								}
							}

						}

					}
					
					VisitMap[VisitY][VisitX] = 2;
					this_->VisitX[V] = VisitX;
					this_->VisitY[V] = VisitY;
					++V;
					
				}
			}
		}

		loop = 0;

		free(CompareSize);
		if (this_->map[VisitY][VisitX] == 'f') {
			VisitMap[VisitY][VisitX] = 2;
			this_->VisitX[V] = VisitX;
			this_->VisitY[V] = VisitY;
			++V;
			free(Size);
			break; //102 = 'f'
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////
		for (i = 0; i < VisitSize + VisitValB * VisitSize; ++i) {
			for (j = i + 1; j < VisitSize + VisitValB * VisitSize; j++) {
				if (Size[j] < Size[i]) {
					tmp = Size[i];
					Size[i] = Size[j];
					Size[j] = tmp;
				}
			}
		}


		VisitValA += 2;
		CompareSize = (int*)malloc(sizeof(int) * (VisitSize + VisitValA * VisitSize));

		for (i = 0; i < VisitSize + VisitValA * VisitSize; ++i) {
			CompareSize[i] = INFINITE * 10000;
		}


		for (m = 0; m < VisitSize + VisitValB * VisitSize; ++m) {
			if (Size[m] == INFINITE * 10000) {}
			else {
				VisitX = (Size[m] % 10000) / 100; // = x좌표
				VisitY = (Size[m] % 10000) % 100; // = y좌표
				if (this_->map[VisitY][VisitX] == 'f') break;

				if (this_->map[VisitY][VisitX] == -1) {}
				else {
					for (i = -1; i <= 1; ++i) {
						for (j = -1; j <= 1; ++j) {
							if (VisitX + j >= this_->row || VisitY + i >= this_->col || VisitX + j < 0 || VisitY + i < 0) {
								CompareSize[loop] = INFINITE * 10000;
								++loop;

							}
							else {
								if (this_->map[VisitY + i][VisitX + j] == -1) {}
								else if (VisitMap[VisitY + i][VisitX + j] == 1) {}
								else if (i*i + j*j == 2) {

									if (MapWeight[VisitY + i][VisitX + j] == INFINITE) {
										MapWeight[VisitY + i][VisitX + j] = MapWeight[VisitY][VisitX] + 14;
									}
									else if (MapWeight[VisitY + i][VisitX + j] < MapWeight[VisitY + i][VisitX + j] + 14) {}
									else {
										MapWeight[VisitY + i][VisitX + j] += 14;
									}

								}

								else if (i*i + j*j == 1) {

									if (MapWeight[VisitY + i][VisitX + j] == 13 * 13 * 10) {
										MapWeight[VisitY + i][VisitX + j] = MapWeight[VisitY][VisitX] + 10;
									}
									else if (MapWeight[VisitY + i][VisitX + j] < MapWeight[VisitY + i][VisitX + j] + 10) {}
									else {
										MapWeight[VisitY + i][VisitX + j] += 10;
									}
								}

								if (VisitMap[VisitY + i][VisitX + j] < 1) {
									VisitMap[VisitY + i][VisitX + j] = 1;
									CompareSize[loop] = MapWeight[VisitY + i][VisitX + j] * 10000 + (VisitX + j) * 100 + (VisitY + i);
									++loop;
								}
								else {
									CompareSize[loop] = INFINITE * 10000;

								}

							}
						}
					}

					VisitMap[VisitY][VisitX] = 2;
					this_->VisitX[V] = VisitX;
					this_->VisitY[V] = VisitY;
					++V;
				}
			}
		}					

		free(Size);

		loop = 0;
		if (this_->map[VisitY][VisitX] == 'f') {
			VisitMap[VisitY][VisitX] = 2;
			this_->VisitX[V] = VisitX;
			this_->VisitY[V] = VisitY;
			++V;
			free(CompareSize);
			break; 
		}
		VisitValB += 2;

	}
	
	loop = 0;
	this->VisitXYData(this_);
	this->PathXYData(this_);
	this->Destroy(this_);
}

void DijkstraStruct::Dijstra_Init(MapStruct* this_) {
	int i, j;
	


	MapWeight = (int**)malloc(sizeof(int*) * this_->col);
	for (i = 0; i < this_->col; ++i) {
		MapWeight[i] = (int*)malloc(sizeof(int) * this_->row);

	}



	for (i = 0; i < this_->col; ++i) {
		for (j = 0; j < this_->row; ++j) {
			MapWeight[i][j] = INFINITE; // 일반적으로 아직 방문하지않은 곳의 가중치를 무한대로 설정하나, 무한대표현이 어렵기에 가중치 최대값+1으로 초기화
		}
	}
	MapWeight[this_->StartY][this_->StartX] = 0; // MapWeight 초기화

	VisitMap = (char**)calloc(sizeof(char*), this_->col); // 0은 방문 전,1은 방문 대기, 2은 방문 후
	for (i = 0; i < this_->col; ++i) {
		VisitMap[i] = (char*)calloc(sizeof(char), this_->row);
	}

}

void DijkstraStruct::PathXYData (MapStruct* this_) {
	int i, j, tmp;
	int loop = 0;
	int *CompareSize = (int*)malloc(sizeof(int) * 8);
	int VisitX = this_->FinishX;
	int VisitY = this_->FinishY;
	FILE* fp = fopen(PATHMAPFILENAME, "w+");

	while (this_->map[VisitY][VisitX] != 's') {
		for (i = -1; i <= 1; ++i) {
			for (j = -1; j <= 1; ++j) {
				//printf("%d %d %d\n", i, j,loop);	
				if (i == 0 && j == 0) {}
				else if (VisitX + j >= this_->row || VisitX + j < 0 || VisitY + i >= this_->col || VisitY + i < 0) {
					CompareSize[loop] = INFINITE * 10000;
					++loop; 
				}
				else {
					CompareSize[loop] = MapWeight[VisitY + i][VisitX + j] * 10000 + (VisitX + j) * 100 + VisitY + i;
					 ++loop;
				}
			}
		}
		loop = 0;
		

		for (i = 0; i < 8; ++i) {
			for (j = i + 1; j < 8; j++) {
				if (CompareSize[j] < CompareSize[i]) {
					tmp = CompareSize[i];
					CompareSize[i] = CompareSize[j];
					CompareSize[j] = tmp;
				}
			}
		}
		
		//가중치가 작은순으로 나열
		
		VisitX = (CompareSize[0] % 10000) / 100;
		VisitY = (CompareSize[0] % 10000) % 100;
		
		this_->PathMap[VisitY][VisitX] = 0;
		
		if (this_->map[VisitY][VisitX] != 's')
			fprintf(fp,"%d %d\n", VisitX, VisitY);


	}
	this_->PathMap[VisitY][VisitX] = 's';
	fclose(fp);
	free(CompareSize);

}

void DijkstraStruct::Destroy(MapStruct* this_) {
	
	for (int i = 0; i < this_->row; ++i) {
		free(MapWeight[i]);
		free(VisitMap[i]);
	}
	
	free(VisitMap);
	free(MapWeight);

	MapWeight = NULL;
	VisitMap = NULL;

}

void DijkstraStruct::VisitXYData(const MapStruct* this_) {
	FILE* fp = fopen(VISITXYFILENAME, "w+");
	for (int i = 0; i < this_->row * this_->col; ++i) {
		fprintf( fp,"%d %d\n", this_->VisitX[i], this_->VisitY[i]);
		if (this_->map[this_->VisitY[i]][this_->VisitX[i]] == 'f') break;
	}
	fclose(fp);

}
