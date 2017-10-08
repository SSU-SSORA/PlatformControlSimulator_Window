#pragma once
#include "MapStruct.h"

#define VISITXYFILENAME "C:\\Users\\lkm28\\Desktop\\AstarVisitXY.txt"
#define PATHMAPFILENAME "C:\\Users\\lkm28\\Desktop\\AstarPathXY.txt"

#ifdef __cplusplus
extern "C" {
#endif
	struct AstarStruct {
		int **Open;
		int **Close;
		int **ParentsXY;
		int **F;
		int **G;
		int **H;
		void Astar(MapStruct *this_);

	private:
		void Astar_Init(MapStruct *this_);
		void Astar_Destroy(MapStruct *this_);
		void Astar_PathXY(MapStruct *this_);
		void Astar_VisitXY(MapStruct *this_);
	};
	
#ifdef __cplusplus
}//extern C
#endif