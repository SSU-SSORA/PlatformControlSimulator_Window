#pragma once
typedef struct _MapStruct MapStruct;

#ifdef __cplusplus
extern "C" {
#endif
	struct _MapStruct {
		int **map;
		int row, col;
		int StartX, StartY;
		void(*Init)(const char * fileName, MapStruct *this_);
		void(*ShowMap)(const MapStruct* this_);
		void(*ShowMapPretty)(const MapStruct* this_);
		void(*Destroy)(MapStruct * this_);
		//row, col, map**�� �̿��� ������ �����ϴ� �Լ� �ۼ�

		int **PathMap;
	};

void _ShowMap(const MapStruct* this_);
void _ShowMapPretty(const MapStruct* this_);
void _Init(const char * filename, MapStruct *this_);
void _Destroy(MapStruct *this_);

#ifdef __cplusplus
}//extern C
#endif