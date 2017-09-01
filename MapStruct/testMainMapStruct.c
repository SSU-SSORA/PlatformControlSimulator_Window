#include <stdio.h>
#include "MapStruct.h"

#define FILE_NAME "Sample_직선.txt"
int main() {
	MapStruct mst;

	_Init(FILE_NAME, &mst);//초기화 함수. 반드시 작동시킬 것

	mst.ShowMap(&mst);//단순히 숫자로 맵을 보여줌
	mst.ShowMapPretty(&mst);//1이상의 가중치가 있는 길은 □, -1이하의 높이가 있는 벽은
	//■로 보여주는 함수

	mst.Destroy(&mst);//메모리해제 및 변수초기화
}