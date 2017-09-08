#pragma once
typedef struct _MapStruct MapStruct;

#ifdef __cplusplus
extern "C" {
#endif
	struct _MapStruct {
		int **map;
		int **PathMap;
		int row, col; //row : ����,x�� col : ����,y�� arr[col][row] = arr[y][x]
		int StartX, StartY;
		int *VisitX, *VisitY; //�湮��ǥ �����������
		//int *VisitXY; // ���ڸ� �ڿ��� ���� x��ǥ * 100 + y��ǥ ex) 3,14 = 0314 // 0������� ������� �湮�Ѽ���
		void(*Init)(const char * fileName, MapStruct *this_);
		void(*ShowMap)(const MapStruct* this_);
		void(*ShowPathMap)(const MapStruct* this_);
		void(*ShowMapPretty)(const MapStruct* this_);
		void(*Destroy)(MapStruct * this_);
		//row, col, map**�� �̿��� ������ �����ϴ� �Լ� �ۼ�
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