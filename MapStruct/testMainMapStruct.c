#include <stdio.h>
#include "MapStruct.h"

#define FILE_NAME "Sample_����.txt"
int main() {
	MapStruct mst;

	_Init(FILE_NAME, &mst);//�ʱ�ȭ �Լ�. �ݵ�� �۵���ų ��

	mst.ShowMap(&mst);//�ܼ��� ���ڷ� ���� ������
	mst.ShowMapPretty(&mst);//1�̻��� ����ġ�� �ִ� ���� ��, -1������ ���̰� �ִ� ����
	//��� �����ִ� �Լ�

	mst.Destroy(&mst);//�޸����� �� �����ʱ�ȭ
}