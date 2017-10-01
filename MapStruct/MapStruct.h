#pragma once

#ifdef __cplusplus
extern "C" {
#endif
	struct MapStruct {
		int **map;
		int **PathMap;
		int row, col; //row : 가로,x축 col : 세로,y축 arr[col][row] = arr[y][x]
		int StartX, StartY;
		int FinishX, FinishY;
		int *VisitX, *VisitY; //방문좌표 순서대로저장
	
							  //int *VisitXY; // 네자리 자연수 저장 x좌표 * 100 + y좌표 ex) 3,14 = 0314 // 0번방부터 순서대로 방문한순서
		void Init (const char * fileName);
		void ShowMap();
		void ShowPathMap ();
		void ShowMapPretty ();
		void Destroy ();
		//row, col, map**를 이용해 파일을 생성하는 함수 작성
		void ShowVisitXY();
		

	};


#ifdef __cplusplus
}//extern C
#endif