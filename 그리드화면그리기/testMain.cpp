#include "�׸���ȭ��׸���.h"

int main() {
	MapStruct map;
	_Init("Sample_basic.txt", &map);

	auto target = GetGridImage::MakeImage(&map);
	GetGridImage::DrawSquare(target, &map);
	GetGridImage::MakeGridImage(target, &map);
	GetGridImage::SaveImage(target, "C:\\Users\\�¿�\\Desktop\\target.png");
	
}