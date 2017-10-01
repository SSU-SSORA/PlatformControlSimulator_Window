#pragma once
#include "MapStruct.h"

#define INFINITE this_->row * this_-> col * 10
#define VISIT_NO 0
#define VISIT_SEARCHING 1
#define VISIT_FINISH 2
#define VISITXYFILENAME "C:\\Users\\lkm28\\Desktop\\DijkstraVisitXY.txt"
#define PATHMAPFILENAME "C:\\Users\\lkm28\\Desktop\\DijkstraPathXY.txt"

#ifdef __cplusplus
extern "C" {
#endif
	struct DijkstraStruct {
		int **MapWeight;
		char **VisitMap;
		void Dijkstra(MapStruct *this_);

	private:
		void Dijstra_Init(MapStruct* this_);
		void PathXYData(MapStruct* this_);
		void Destroy(MapStruct* this_);
		void VisitXYData(const MapStruct* this_);
	};


#ifdef __cplusplus
}//extern C
#endif