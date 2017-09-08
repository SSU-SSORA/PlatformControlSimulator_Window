#pragma once
typedef struct _MapStruct MapStruct;

#ifdef __cplusplus
extern "C" {
#endif
	struct _MapStruct {
		int **map;
		int **PathMap;
		int row, col; //row : 가로,x축 col : 세로,y축 arr[col][row] = arr[y][x]
		int StartX, StartY;
		int *VisitX, *VisitY; //방문좌표 순서대로저장
		//int *VisitXY; // 네자리 자연수 저장 x좌표 * 100 + y좌표 ex) 3,14 = 0314 // 0번방부터 순서대로 방문한순서
		void(*Init)(const char * fileName, MapStruct *this_);
		void(*ShowMap)(const MapStruct* this_);
		void(*ShowPathMap)(const MapStruct* this_);
		void(*ShowMapPretty)(const MapStruct* this_);
		void(*Destroy)(MapStruct * this_);
		//row, col, map**를 이용해 파일을 생성하는 함수 작성
		void(*ShowVisitXY)(const MapStruct* this_);
		
	};

void _ShowMap(const MapStruct* this_);
void _ShowPathMap(const MapStruct* this_);
void _ShowMapPretty(const MapStruct* this_);
void _Init(const char * filename, MapStruct *this_);
void _Destroy(MapStruct *this_);

void _ShowVisitXY(const MapStruct* this_);

#ifdef __cplusplus
}//extern C
#endif