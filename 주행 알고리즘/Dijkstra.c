#include <stdio.h>
#include <malloc.h>
#include "MapStruct.h"

void Dijkstra(MapStruct *this) {


	int StartX = this->StartX, StartY = this->StartY;
	int CurrentX = StartX, CurrentY = StartY;
	int VisitX = CurrentX, VisitY = CurrentY;
	int FinishX, FinishY;
	int i = 0, j = 0, m = 0, n = 0, roop = 0; // for���� ����


	int **MapWeight = (int**)malloc(sizeof(int*) * this->col);
	for (i = 0; i < this->col; ++i) {
		MapWeight[i] = (int*)malloc(sizeof(int) * this->row);

	}



	for (i = 0; i < this->col; ++i) {
		for (j = 0; j < this->row; ++j) {
			MapWeight[i][j] = this->row * this->col * 10; // �Ϲ������� ���� �湮�������� ���� ����ġ�� ���Ѵ�� �����ϳ�, ���Ѵ�ǥ���� ��Ʊ⿡ ����ġ �ִ밪+1���� �ʱ�ȭ
		}
	}
	MapWeight[StartY][StartX] = 0; // MapWeight �ʱ�ȭ

	char **VisitMap=(char**)malloc(sizeof(char*) * this->col); // 0�� �湮 ��,1�� �湮 ���, 2�� �湮 ��
	for (i = 0; i < this->col; ++i) {
		VisitMap[i] = (char*)malloc(sizeof(char) * this->row);
	}


	for (i = 0; i < this->col; ++i) {
		for (j = 0; j < this->row; ++j) {
			VisitMap[i][j] = 0;
		}
	} // VisitMap �ʱ�ȭ


	int VisitValA = 0;
	int VisitValB = 1;
	int VisitSize = 2 * 4; // (3-1) * 4




	int *CompareSize = (int*)malloc(sizeof(int) * VisitSize + (VisitValA * 8)); // ������ǥ �ֺ��� ����ġ�� ���峷�� ��ǥ���� �湮�ؾ��ϱ⿡ ����ġ���� ��ǥ����
																				//00000(����ġ)00(x��ǥ)00(y��ǥ)

	for (i = 0; i < VisitSize + (VisitValA * 8); ++i) {
		CompareSize[i] = 0;
	}

	VisitMap[CurrentY][CurrentX] = 2;
	for (i = -1; i <= 1; ++i) {
		for (j = -1; j <= 1; ++j) {

			if (this->map[CurrentY + i][CurrentX + j] < 0) {}

			else if (i*i + j*j == 2) {

				if (MapWeight[CurrentY + i][CurrentX + j] == this->row * this->col * 10) {
					MapWeight[CurrentY + i][CurrentX + j] = 14;
				}
				else MapWeight[CurrentY + i][CurrentX + j] += 14;

			}

			else if (i*i + j*j == 1) {

				if (MapWeight[CurrentY + i][CurrentX + j] == this->row * this->col * 10) {
					MapWeight[CurrentY + i][CurrentX + j] = 10;
				}
				else MapWeight[CurrentY + i][CurrentX + j] += 10;
			}
			if (VisitMap[CurrentY + i][CurrentX + j] != 2) {
				VisitMap[CurrentY + i][CurrentX + j] = 1;
				CompareSize[roop] = MapWeight[CurrentY + i][CurrentX + j] * 10000 + (CurrentX + j) * 100 + (CurrentY + i);
				++roop;
			}
		}


	}

	//printf("roop %d\n\n", roop);/////////////Debug
	roop = 0;
	



	int tmp;
	int *Size;
	while (this->map[VisitY][VisitX] != 102) { // 102 = 'f'

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
		//����ġ�� ���������� ����
		/*for (i = 0; i < VisitSize + VisitValA * 8; ++i) {

			printf("%d\t", CompareSize[i]);

		}printf("\n\n");*//////////////////Debug

						//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		Size = (int*)malloc(sizeof(int) * (VisitSize + VisitValB * 8));

		for (i = 0; i < VisitSize + VisitValB * 8; ++i) {
			Size[i] = this->row * this->col * 10 * 10000;
		}



		for (m = 0; m < VisitSize + VisitValA * 8; ++m) {
			if (CompareSize[m] == this->row * this->col * 10 * 10000) {}
			else {
				VisitX = (CompareSize[m] % 10000) / 100; // = x��ǥ
				VisitY = (CompareSize[m] % 10000) % 100; // = y��ǥ
				if (this->map[VisitY][VisitX] == 102) break; // 102 = 'f'

				if (this->map[VisitY][VisitX] == -1) {}
				else {
					for (i = -1; i <= 1; ++i) {
						for (j = -1; j <= 1; ++j) {
							if (VisitY + i >= this->col || VisitX + j >= this->row || VisitX + j < 0 || VisitY + i < 0) {


							}
							else {
								if (this->map[VisitY + i][VisitX + j] == -1) {}
								else if (VisitMap[VisitY + i][VisitX + j] == 1) {}
								else if (i*i + j*j == 2) {

									if (MapWeight[VisitY + i][VisitX + j] == this->row * this->col * 10) {
										MapWeight[VisitY + i][VisitX + j] = MapWeight[VisitY][VisitX] + 14;
									}
									else if (MapWeight[VisitY + i][VisitX + j] < MapWeight[VisitY + i][VisitX + j] + 14) {}
									else {
										MapWeight[VisitY + i][VisitX + j] += 14;
									}

								}

								else if (i*i + j*j == 1) {

									if (MapWeight[VisitY + i][VisitX + j] == this->row * this->col * 10) {
										MapWeight[VisitY + i][VisitX + j] = MapWeight[VisitY][VisitX] + 10;
									}
									else if (MapWeight[VisitY + i][VisitX + j] < MapWeight[VisitY + i][VisitX + j] + 10) {}
									else {
										MapWeight[VisitY + i][VisitX + j] += 10;
									}
								}

								if (VisitMap[VisitY + i][VisitX + j] < 1) {
									VisitMap[VisitY + i][VisitX + j] = 1;
									Size[roop] = MapWeight[VisitY + i][VisitX + j] * 10000 + (VisitX + j) * 100 + (VisitY + i);
									++roop;
								}
							}

						}

					}

					VisitMap[VisitY][VisitX] = 2;
				}
			}
		}
		//printf("roop : %d\n\n", roop);//////////////////////////////////Debug
		roop = 0;

		free(CompareSize);
		if (this->map[VisitY][VisitX] == 102) break; //102 = 'f'

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
			CompareSize[i] = this->row * this->col * 10 * 10000;
		}


		for (m = 0; m < VisitSize + VisitValB * 8; ++m) {
			if (Size[m] == this->row * this->col * 10 * 10000) {}
			else {
				VisitX = (Size[m] % 10000) / 100; // = x��ǥ
				VisitY = (Size[m] % 10000) % 100; // = y��ǥ
				if (this->map[VisitY][VisitX] == 102) break; // 102 = 'f'

				if (this->map[VisitY][VisitX] == -1) {}
				else {
					for (i = -1; i <= 1; ++i) {
						for (j = -1; j <= 1; ++j) {
							if (VisitX + j >= this->row || VisitY + i >= this->col || VisitX + j < 0 || VisitY + i < 0) {
								CompareSize[roop] = this->row * this->col * 10 * 10000;
								++roop;

							}
							else {
								if (this->map[VisitY + i][VisitX + j] == -1) {}
								else if (VisitMap[VisitY + i][VisitX + j] == 1) {}
								else if (i*i + j*j == 2) {

									if (MapWeight[VisitY + i][VisitX + j] == this->row * this->col * 10) {
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
									CompareSize[roop] = MapWeight[VisitY + i][VisitX + j] * 10000 + (VisitX + j) * 100 + (VisitY + i);
									++roop;
								}
								else {
									CompareSize[roop] = this->row * this->col * 10 * 10000;

								}

							}
						}
					}

					VisitMap[VisitY][VisitX] = 2;
				}
			}
		}
		free(Size);

		//printf(" roop : %d\n\n", roop); //////////Debug

		roop = 0;
		if (this->map[VisitY][VisitX] == 102) break; // 102 = 'f'

		VisitValB += 2;

		/*for (i = 0; i < this->col; ++i) {
			for (j = 0; j < this->row; ++j) {

				printf("%d\t", MapWeight[i][j]);

			}
			printf("\n");
		}printf("\n"); *////////////////////////////////////Debug





	}

	roop = 0;
	
	CompareSize = (int*)malloc(sizeof(int) * 8);
	
	FinishX = VisitX; FinishY = VisitY;
	
	while (this->map[VisitY][VisitX] != 115) {
		for (i = -1; i <= 1; ++i) {
			for (j = -1; j <= 1; ++j) {
				if (i == 0 && j == 0) {}
				else if (VisitX + j >= this->row || VisitX + j < 0 || VisitY + i >= this->col || VisitY + i < 0) {
					CompareSize[roop] = this->row * this->col * 10 * 10000;
					++roop;
				}
				else {
					CompareSize[roop] = MapWeight[VisitY + i][VisitX + j] * 10000 + (VisitX + j) * 100 + VisitY + i;
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
		//����ġ�� ���������� ����

		VisitX = (CompareSize[0] % 10000) / 100;
		VisitY = (CompareSize[0] % 10000) % 100;

		this->PathMap[VisitY][VisitX] = 0;
		

	}
	free(CompareSize);

	/*for (i = 0; i < this->col; ++i) {
		for (j = 0; j < this->row; ++j) {

			printf("%d\t", this->PathMap[i][j]);

		}
		printf("\n");
	}printf("\n"); */////////////////////////////////////Debug

	for (i = 0; i < this->row; ++i) {
		free(MapWeight[i]);
		free(VisitMap[i]);
	}
	free(MapWeight);
	free(VisitMap);


	




}


