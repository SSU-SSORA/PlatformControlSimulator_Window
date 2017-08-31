#include <iostream>
#include <fstream>

#define SAMPLE_MAP_SIZE 13
template <typename T, size_t N>
size_t CalcSize(const T(&)[N]) {
	return N;
}

template <typename T, size_t N>
size_t CalcSize(const T*(&)[N]) {
	return N;
}

int main() {
	int ary[SAMPLE_MAP_SIZE][SAMPLE_MAP_SIZE] = { 0 };
	for (size_t i = 0; i < CalcSize(ary); i++) {
		for (size_t j = 0; j < CalcSize(ary[i]); j++)
			ary[i][j] = 1;
	}

	/* Sample_basic.txt */
	ary[5][7] = 's';
	ary[0][12] = 'f';//starting point, finish point
	

	
	/*insert Sample pixel here
	delete comment with ctrl + shift, or use drag and click erase comment(ctrl + c, ctrl + k)
	*/
	
	/* Sample_기억 */
	//ary[2][8] = -1;
	//ary[2][9] = -1;
	//ary[2][10] = -1;
	//ary[2][11] = -1;
	//ary[3][11] = -1;
	//ary[3][11] = -1;
	/* end_Sample_기억*/

	/* Sample_네모*/
	//ary[2][2] = -1;
	//ary[2][3] = -1;
	//ary[2][4] = -1;
	//ary[2][5] = -1;
	//ary[2][6] = -1;
	//ary[2][7] = -1;
	//ary[2][8] = -1;
	//ary[2][9] = -1;
	//ary[2][10] = -1;
	//ary[2][11] = -1;
	//ary[3][2] = -1;
	//ary[4][2] = -1;
	//ary[5][2] = -1;
	//ary[6][2] = -1;
	//ary[7][2] = -1;
	//ary[8][11] = -1;
	//ary[9][5] = -1;
	//ary[9][6] = -1;
	//ary[9][7] = -1;
	//ary[9][8] = -1;
	//ary[9][9] = -1;
	//ary[9][10] = -1;
	//ary[9][11] = -1;
	/* end_Sample_네모*/

	/* Sample_수용돌이*/
	//ary[1][1] = -1;
	//ary[1][2] = -1;
	//ary[1][3] = -1;
	//ary[1][4] = -1;
	//ary[1][5] = -1;
	//ary[1][6] = -1;
	//ary[1][7] = -1;
	//ary[1][8] = -1;
	//ary[1][9] = -1;
	//ary[1][10] = -1;
	//ary[1][11] = -1;
	//ary[1][12] = -1;
	//
	//ary[2][1] = -1;
	//ary[3][1] = -1;
	//ary[4][1] = -1;
	//ary[5][1] = -1;
	//ary[6][1] = -1;
	//ary[7][1] = -1;
	//ary[8][1] = -1;
	//ary[9][1] = -1;
	//ary[10][1] = -1;
	//ary[11][1] = -1;
	//
	//ary[11][2] = -1;
	//ary[11][3] = -1;
	//ary[11][4] = -1;
	//ary[11][5] = -1;
	//ary[11][6] = -1;
	//ary[11][7] = -1;
	//ary[11][8] = -1;
	//ary[11][9] = -1;
	//ary[11][10] = -1;
	//ary[11][11] = -1;
	//
	//ary[10][11] = -1; 
	//ary[9][11] = -1; 
	//ary[8][11] = -1; 
	//ary[7][11] = -1; 
	//ary[6][11] = -1; 
	//ary[5][11] = -1; 
	//ary[4][11] = -1; 
	//
	//ary[4][10] = -1;
	//ary[4][9] = -1;
	//ary[4][8] = -1;
	//ary[4][7] = -1;
	//ary[4][6] = -1;
	//ary[4][5] = -1;
	//ary[4][4] = -1;
	//
	//ary[4][4] = -1;
	//ary[5][4] = -1;
	//ary[6][4] = -1;
	//ary[7][4] = -1;
	//ary[8][4] = -1;
	//ary[9][4] = -1;
	//
	//ary[9][5] = -1;
	//ary[9][6] = -1;
	//ary[9][7] = -1;
	//ary[9][8] = -1;
	//ary[9][9] = -1;
	//
	//ary[8][9] = -1;
	//ary[7][9] = -1;
	//ary[6][9] = -1;
	//ary[5][9] = -1;
	//
	//ary[5][8] = -1;
	//ary[5][7] = -1;
	//ary[5][6] = -1;
	//ary[5][5] = -1;
	//
	//ary[6][5] = -1;
	//ary[7][5] = -1;
	//
	//ary[7][6] = -1;
	//ary[7][7] = -1;
	/* end_Sample_수용돌이*/

	/* Sample_직선*/
	//시작점과 끝점의 좌표가 다르므로 갱신한다
	ary[5][7] = 1;
	ary[0][12] = 1;//starting point, finish point
	
	ary[5][0] = -1;
	ary[5][1] = -1;
	ary[5][2] = -1;
	ary[5][3] = -1;
	ary[5][4] = -1;
	ary[5][5] = -1;
	ary[5][6] = -1;
	ary[5][7] = -1;
	ary[5][8] = -1;
	ary[5][9] = -1;
	ary[5][10] = -1;
	ary[5][11] = -1;
	ary[5][12] = -1;

	ary[6][0] = 's';
	ary[6][12] = 'f';
	
	ary[7][0] = -1;
	ary[7][1] = -1;
	ary[7][2] = -1;
	ary[7][3] = -1;
	ary[7][4] = -1;
	ary[7][5] = -1;
	ary[7][6] = -1;
	ary[7][7] = -1;
	ary[7][8] = -1;
	ary[7][9] = -1;
	ary[7][10] = -1;
	ary[7][11] = -1;
	ary[7][12] = -1;
	/* end_Sample_직선*/

	std::ofstream out("Sample.txt");
	out << CalcSize(ary) << ' ' << CalcSize(ary[0]) << std::endl;
	
	for (size_t i = 0; i < CalcSize(ary); i++) {
		for (size_t j = 0; j < CalcSize(ary[i]); j++)
			out << i << ' ' << j << ' ' << ary[i][j] << std::endl;
	}



	





}