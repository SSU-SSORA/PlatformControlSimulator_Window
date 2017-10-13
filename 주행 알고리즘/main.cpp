#include <stdio.h>
#include <string.h>
#include "MapStruct.h"
#include "Dijkstra.h"
#include "Astar.h"
#include "BiDirectionalDijkstra.h"
//#include "BFS.h"


#define FILE_NAME "C:\\Users\\lkm28\\Desktop\\스마트경진대회\\PlatformControlSimulator_Window\\샘플자료\\Sample_네모.txt"

int main() {

	MapStruct mst;
	DijkstraStruct dst;
	AstarStruct ast;
	BiDirectionalDijkstraStruct bdst;
	



	mst.Init(FILE_NAME);//초기화 함수. 반드시 작동시킬 것


	//ast.Astar = Astar;
	
	//mst.ShowMap();//단순히 숫자로 맵을 보여줌
	//ast.Astar(&mst);
	//dst.Dijkstra(&mst);
	bdst.BiDirectional_Dijkstra(&mst);
	mst.ShowPathMap();
	//mst.ShowMapPretty(&mst);//1이상의 가중치가 있는 길은 □, -1이하의 높이가 있는 벽은
							//■로 보여주는 함수
	mst.Destroy();//메모리해제 및 변수초기화

	
}





/*void ReadMap() {

	FILE *fp = fopen("C:\\Users\\lkm28\\Desktop\\MapTest.txt", "r");

	char ch[100];
	fgets(ch, 100, fp);


	char xc[5], yc[5],in[5];
	int x, y;
	int i = 0;

	strtok(ch, " ");
	strcpy(xc, ch);

	strtok(ch + strlen(xc) + 1, "\n");
	strcpy(yc, ch + strlen(xc)+1);



	
	if (strlen(xc) == 1)
		x = xc[0] - 48;
	else if (strlen(xc) == 2)
		x = xc[0] + xc[1] - 48*2;

	if (strlen(yc) == 1)
		y = yc[0] - 48;
	else if (strlen(yc) == 2)
		y = yc[0] + yc[1] - 48 * 2;


	
	
	char **map;


	map = (char**)malloc(sizeof(char*)*y);

	for (i = 0; i < y; ++i) {
		map[i] = (char*)malloc(sizeof(char)*x);
	}


	
	i = 0;
	int j = 0;
	while (!feof(fp)) {
		fgets(ch, 100, fp);
		
		while (i == 2) {
			while (ch[j] == ' ') {
				++j;
			}
			++i;
		}

	}
	
	
	for (i = 0; i < y; ++i) {
		for (j = 0; j < x; ++j) {
			printf("%d\t", map[i][j]);
		}
		printf("\n");
	}
	

	free(*map);
	free(map);

	fclose(fp);

	

	printf("Reading Map finish\n");



}*/