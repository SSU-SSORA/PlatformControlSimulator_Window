#pragma once
#include "MapStruct.h"
typedef struct _DijkstraStruct DijkstraStruct;


#ifdef __cplusplus
extern "C" {
#endif
	struct _DijkstraStruct {
		int **MapWeight;
		char **VisitMap;
		void(*Dijkstra)(MapStruct *this_, DijkstraStruct *this__);
		void(*DrawPathMap)(const MapStruct* this_,const DijkstraStruct* this__, int VisitX, int VisitY);

	};
	void Dijkstra(MapStruct *this_, DijkstraStruct *this__);
	void Dijstra_Init(MapStruct* this_, DijkstraStruct* this__);
	void DrawPathMap(const MapStruct* this_,const DijkstraStruct* this__, int VisitX, int VisitY);
	void Destroy(MapStruct* this_, DijkstraStruct* this__);

#ifdef __cplusplus
}//extern C
#endif