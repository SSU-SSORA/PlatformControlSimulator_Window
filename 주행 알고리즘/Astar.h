#pragma once
#include "MapStruct.h"


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
		
	};
	
#ifdef __cplusplus
}//extern C
#endif