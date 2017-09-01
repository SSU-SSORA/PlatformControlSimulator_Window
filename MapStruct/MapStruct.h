#pragma once
typedef struct _MapStruct MapStruct;

struct _MapStruct {
	unsigned char **map;
	int row, col;
	void(*Init)(const char * fileName, MapStruct *this);
	void(*ShowMap)(const MapStruct* this);
	void(*ShowMapPretty)(const MapStruct* this);
	void(*Destroy)(MapStruct * this);

};






void _ShowMap(const MapStruct* this);
void _ShowMapPretty(const MapStruct* this);
void _Init(const char * filename, MapStruct *this);
void _Destroy(MapStruct *this);