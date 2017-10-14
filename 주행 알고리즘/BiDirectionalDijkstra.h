#pragma once
#include "MapStruct.h"
#define INFINITE this_->row * this_->col * 10
#define VISITXYFILENAME "C:\\Users\\lkm28\\Desktop\\Bi-Directional_DijkstraVisitXY.txt"
#define PATHMAPFILENAME "C:\\Users\\lkm28\\Desktop\\Bi-Directional_DijkstraPathXY.txt"

#ifdef __cplusplus
extern "C" {
#endif
	struct BiDirectionalDijkstraStruct {
		int **MapWeightS;
		int **MapWeightF;
		char **VisitMapS;
		char **VisitMapF;
		int MeetX, MeetY;
		int V = 0;
		void BiDirectional_Dijkstra(MapStruct *this_);

	private:
		void BiDijkstra_Init(MapStruct *this_);
		void BiDijkstra_Destroy(MapStruct* this_);
		void BiDijkstra_PathXY(MapStruct* this_);
		void BiDijkstra_VisitXY(MapStruct* this_);
		void Searching(MapStruct* this_,int *CurrentX,int *CurrentY, int **MapWeight, char **VisitMap);
		int MeetDiscriminant(MapStruct* this_, int *CurrentX, int *CurrentY, int **MapWeight);
	};


#ifdef __cplusplus
}//extern C
#endif