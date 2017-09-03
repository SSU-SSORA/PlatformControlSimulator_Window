#include <stdio.h>
#include <malloc.h>
#include "MapStruct.h"
#include "Dijkstra.h"

void Dijkstra(MapStruct *this_,DijkstraStruct *this__) {



	int StartX = this_->StartX, StartY = this_->StartY;
	int CurrentX = StartX, CurrentY = StartY;
	int VisitX = CurrentX, VisitY = CurrentY;
	int FinishX, FinishY;
	int i = 0, j = 0, m = 0, n = 0, roop = 0; // for문용 변수


	this__->MapWeight = (int**)malloc(sizeof(int*) * this_->col);
	for (i = 0; i < this_->col; ++i) {
		this__->MapWeight[i] = (int*)malloc(sizeof(int) * this_->row);

	}



	for (i = 0; i < this_->col; ++i) {
		for (j = 0; j < this_->row; ++j) {
			this__->MapWeight[i][j] = this_->row * this_->col * 10; // 일반적으로 아직 방문하지않은 곳의 가중치를 무한대로 설정하나, 무한대표현이 어렵기에 가중치 최대값+1으로 초기화
		}
	}
	this__->MapWeight[StartY][StartX] = 0; // this__->MapWeight 초기화

	this__->VisitMap=(char**)malloc(sizeof(char*) * this_->col); // 0은 방문 전,1은 방문 대기, 2은 방문 후
	for (i = 0; i < this_->col; ++i) {
		this__->VisitMap[i] = (char*)malloc(sizeof(char) * this_->row);
	}


	for (i = 0; i < this_->col; ++i) {
		for (j = 0; j < this_->row; ++j) {
			this__->VisitMap[i][j] = 0;
		}
	} // this__->VisitMap 초기화


	int VisitValA = 0;
	int VisitValB = 1;
	int VisitSize = 2 * 4; // (3-1) * 4




	int *CompareSize = (int*)malloc(sizeof(int) * VisitSize + (VisitValA * 8)); // 현재좌표 주변에 가중치가 가장낮은 좌표부터 방문해야하기에 가중치비교후 좌표저장
																				//00000(가중치)00(x좌표)00(y좌표)

	for (i = 0; i < VisitSize + (VisitValA * 8); ++i) {
		CompareSize[i] = 0;
	}

	this__->VisitMap[CurrentY][CurrentX] = 2;
	for (i = -1; i <= 1; ++i) {
		for (j = -1; j <= 1; ++j) {

			if (this_->map[CurrentY + i][CurrentX + j] < 0) {}

			else if (i*i + j*j == 2) {

				if (this__->MapWeight[CurrentY + i][CurrentX + j] == this_->row * this_->col * 10) {
					this__->MapWeight[CurrentY + i][CurrentX + j] = 14;
				}
				else this__->MapWeight[CurrentY + i][CurrentX + j] += 14;

			}

			else if (i*i + j*j == 1) {

				if (this__->MapWeight[CurrentY + i][CurrentX + j] == this_->row * this_->col * 10) {
					this__->MapWeight[CurrentY + i][CurrentX + j] = 10;
				}
				else this__->MapWeight[CurrentY + i][CurrentX + j] += 10;
			}
			if (this__->VisitMap[CurrentY + i][CurrentX + j] != 2) {
				this__->VisitMap[CurrentY + i][CurrentX + j] = 1;
				CompareSize[roop] = this__->MapWeight[CurrentY + i][CurrentX + j] * 10000 + (CurrentX + j) * 100 + (CurrentY + i);
				++roop;
			}
		}


	}

	//printf("roop %d\n\n", roop);/////////////Debug
	roop = 0;
	



	int tmp;
	int *Size;
	while (this_->map[VisitY][VisitX] != 102) { // 102 = 'f'

											   ////////////////////////////////////////////

		for (i = 0; i < VisitSize + VisitValA * 8; ++i) {
			for (j = i + 1; j < VisitSize + (VisitValA * 8); j++) {
				if (CompareSize[j] < CompareSize[i]) {
					tmp = CompareSize[i];
					CompareSize[i] = CompareSize[j];
					CompareSize[j] = tmp;
				}
			}
		}
		//가중치가 작은순으로 나열
		/*for (i = 0; i < VisitSize + VisitValA * 8; ++i) {

			printf("%d\t", CompareSize[i]);

		}printf("\n\n");*//////////////////Debug

						//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		Size = (int*)malloc(sizeof(int) * (VisitSize + VisitValB * 8));

		for (i = 0; i < VisitSize + VisitValB * 8; ++i) {
			Size[i] = this_->row * this_->col * 10 * 10000;
		}



		for (m = 0; m < VisitSize + VisitValA * 8; ++m) {
			if (CompareSize[m] == this_->row * this_->col * 10 * 10000) {}
			else {
				VisitX = (CompareSize[m] % 10000) / 100; // = x좌표
				VisitY = (CompareSize[m] % 10000) % 100; // = y좌표
				if (this_->map[VisitY][VisitX] == 102) break; // 102 = 'f'

				if (this_->map[VisitY][VisitX] == -1) {}
				else {
					for (i = -1; i <= 1; ++i) {
						for (j = -1; j <= 1; ++j) {
							if (VisitY + i >= this_->col || VisitX + j >= this_->row || VisitX + j < 0 || VisitY + i < 0) {


							}
							else {
								if (this_->map[VisitY + i][VisitX + j] == -1) {}
								else if (this__->VisitMap[VisitY + i][VisitX + j] == 1) {}
								else if (i*i + j*j == 2) {

									if (this__->MapWeight[VisitY + i][VisitX + j] == this_->row * this_->col * 10) {
										this__->MapWeight[VisitY + i][VisitX + j] = this__->MapWeight[VisitY][VisitX] + 14;
									}
									else if (this__->MapWeight[VisitY + i][VisitX + j] < this__->MapWeight[VisitY + i][VisitX + j] + 14) {}
									else {
										this__->MapWeight[VisitY + i][VisitX + j] += 14;
									}

								}

								else if (i*i + j*j == 1) {

									if (this__->MapWeight[VisitY + i][VisitX + j] == this_->row * this_->col * 10) {
										this__->MapWeight[VisitY + i][VisitX + j] = this__->MapWeight[VisitY][VisitX] + 10;
									}
									else if (this__->MapWeight[VisitY + i][VisitX + j] < this__->MapWeight[VisitY + i][VisitX + j] + 10) {}
									else {
										this__->MapWeight[VisitY + i][VisitX + j] += 10;
									}
								}

								if (this__->VisitMap[VisitY + i][VisitX + j] < 1) {
									this__->VisitMap[VisitY + i][VisitX + j] = 1;
									Size[roop] = this__->MapWeight[VisitY + i][VisitX + j] * 10000 + (VisitX + j) * 100 + (VisitY + i);
									++roop;
								}
							}

						}

					}

					this__->VisitMap[VisitY][VisitX] = 2;
				}
			}
		}
		//printf("roop : %d\n\n", roop);//////////////////////////////////Debug
		roop = 0;

		free(CompareSize);
		if (this_->map[VisitY][VisitX] == 102) break; //102 = 'f'

		/////////////////////////////////////////////////////////////////////////////////////////////////
		for (i = 0; i < VisitSize + VisitValB * 8; ++i) {
			for (j = i + 1; j < VisitSize + VisitValB * 8; j++) {
				if (Size[j] < Size[i]) {
					tmp = Size[i];
					Size[i] = Size[j];
					Size[j] = tmp;
				}
			}
		}
		/*for (i = 0; i < VisitSize + VisitValB * 8; ++i) {

			printf("%d\t", Size[i]);

		}printf("\n\n");*////////////////////////////////////////Debug

		VisitValA += 2;
		CompareSize = (int*)malloc(sizeof(int) * (VisitSize + VisitValA * 8));

		for (i = 0; i < VisitSize + VisitValA * 8; ++i) {
			CompareSize[i] = this_->row * this_->col * 10 * 10000;
		}


		for (m = 0; m < VisitSize + VisitValB * 8; ++m) {
			if (Size[m] == this_->row * this_->col * 10 * 10000) {}
			else {
				VisitX = (Size[m] % 10000) / 100; // = x좌표
				VisitY = (Size[m] % 10000) % 100; // = y좌표
				if (this_->map[VisitY][VisitX] == 102) break; // 102 = 'f'

				if (this_->map[VisitY][VisitX] == -1) {}
				else {
					for (i = -1; i <= 1; ++i) {
						for (j = -1; j <= 1; ++j) {
							if (VisitX + j >= this_->row || VisitY + i >= this_->col || VisitX + j < 0 || VisitY + i < 0) {
								CompareSize[roop] = this_->row * this_->col * 10 * 10000;
								++roop;

							}
							else {
								if (this_->map[VisitY + i][VisitX + j] == -1) {}
								else if (this__->VisitMap[VisitY + i][VisitX + j] == 1) {}
								else if (i*i + j*j == 2) {

									if (this__->MapWeight[VisitY + i][VisitX + j] == this_->row * this_->col * 10) {
										this__->MapWeight[VisitY + i][VisitX + j] = this__->MapWeight[VisitY][VisitX] + 14;
									}
									else if (this__->MapWeight[VisitY + i][VisitX + j] < this__->MapWeight[VisitY + i][VisitX + j] + 14) {}
									else {
										this__->MapWeight[VisitY + i][VisitX + j] += 14;
									}

								}

								else if (i*i + j*j == 1) {

									if (this__->MapWeight[VisitY + i][VisitX + j] == 13 * 13 * 10) {
										this__->MapWeight[VisitY + i][VisitX + j] = this__->MapWeight[VisitY][VisitX] + 10;
									}
									else if (this__->MapWeight[VisitY + i][VisitX + j] < this__->MapWeight[VisitY + i][VisitX + j] + 10) {}
									else {
										this__->MapWeight[VisitY + i][VisitX + j] += 10;
									}
								}

								if (this__->VisitMap[VisitY + i][VisitX + j] < 1) {
									this__->VisitMap[VisitY + i][VisitX + j] = 1;
									CompareSize[roop] = this__->MapWeight[VisitY + i][VisitX + j] * 10000 + (VisitX + j) * 100 + (VisitY + i);
									++roop;
								}
								else {
									CompareSize[roop] = this_->row * this_->col * 10 * 10000;

								}

							}
						}
					}

					this__->VisitMap[VisitY][VisitX] = 2;
				}
			}
		}
		free(Size);

		//printf(" roop : %d\n\n", roop); //////////Debug

		roop = 0;
		if (this_->map[VisitY][VisitX] == 102) break; // 102 = 'f'

		VisitValB += 2;

		/*for (i = 0; i < this_->col; ++i) {
			for (j = 0; j < this_->row; ++j) {

				printf("%d\t", this__->MapWeight[i][j]);

			}
			printf("\n");
		}printf("\n"); *////////////////////////////////////Debug





	}

	roop = 0;
	
	
	FinishX = VisitX; FinishY = VisitY;
	
	DrawPathMap(this_,this__ , FinishX, FinishY);

	for (i = 0; i < this_->row; ++i) {
		free(this__->MapWeight[i]);
		free(this__->VisitMap[i]);
	}
	

	free(this__->MapWeight);
	free(this__->VisitMap);


	




}

void DrawPathMap(const MapStruct* this_, const DijkstraStruct* this__, int VisitX, int VisitY) {
	int i, j, tmp;
	int roop = 0;
	int *CompareSize = (int*)malloc(sizeof(int) * 8);

	while (this_->map[VisitY][VisitX] != 115) {
		
		for (i = -1; i <= 1; ++i) {
			for (j = -1; j <= 1; ++j) {
				if (i == 0 && j == 0) {}
				else if (VisitX + j >= this_->row || VisitX + j < 0 || VisitY + i >= this_->col || VisitY + i < 0) {
					CompareSize[roop] = this_->row * this_->col * 10 * 10000;
					++roop;
				}
				else {
					CompareSize[roop] = this__->MapWeight[VisitY + i][VisitX + j] * 10000 + (VisitX + j) * 100 + VisitY + i;
					++roop;
				}
			}
		}
		roop = 0;
		

		for (i = 0; i < 8; ++i) {
			for (j = i + 1; j < 8; j++) {
				if (CompareSize[j] < CompareSize[i]) {
					tmp = CompareSize[i];
					CompareSize[i] = CompareSize[j];
					CompareSize[j] = tmp;
				}
			}
		}
		
		//가중치가 작은순으로 나열ltgjqh

		VisitX = (CompareSize[0] % 10000) / 100;
		VisitY = (CompareSize[0] % 10000) % 100;
		
		this_->PathMap[VisitY][VisitX] = 0;


	}
	free(CompareSize);

	/*for (i = 0; i < this_->col; ++i) {
	for (j = 0; j < this_->row; ++j) {

	printf("%d\t", this_->PathMap[i][j]);

	}
	printf("\n");
	}printf("\n"); */////////////////////////////////////Debug


}

