#pragma once

#ifdef __cplusplus
extern "C" {
#endif
	struct MapStruct {
		int **map;
		int **PathMap;
		int row, col; //row : ����,x�� col : ����,y�� arr[col][row] = arr[y][x]
		int StartX, StartY;
		int FinishX, FinishY;
		int *VisitX, *VisitY; //�湮��ǥ �����������
	
							  //int *VisitXY; // ���ڸ� �ڿ��� ���� x��ǥ * 100 + y��ǥ ex) 3,14 = 0314 // 0������� ������� �湮�Ѽ���
		void Init (const char * fileName);
		void ShowMap();
		void ShowPathMap ();
		void ShowMapPretty ();
		void Destroy ();
		//row, col, map**�� �̿��� ������ �����ϴ� �Լ� �ۼ�
		void ShowVisitXY();
		

	};


#ifdef __cplusplus
}//extern C
#endif