#pragma once
#include <opencv2\opencv.hpp>//Scalar
#include <vector>
#include <tuple>
#include "MapStruct.h"
using namespace cv;


class GetGridImage {
	enum : int {
		_1 = 10,//511
		_2 = 13,//511
		_3 = 15,//508
		_4 = 17,//511
		_5 = 20,//501
		_6 = 21,//505
		_7 = 22,//507
		_8 = 23,//507
		_9 = 30,//511
		_10 = 32,//512
		_11 = 34,//511

		PNG = cv::IMWRITE_PNG_COMPRESSION,
		PNG_DEFAULT_VALUE = 3,
		JPEG = cv::IMWRITE_JPEG_QUALITY,
		JPEG_DEFAULT_VALUE = 95
	};
public:
	//�׸��� �� Mat ����
	static cv::Mat MakeImage(const MapStruct* map);

	//�׸��� �� �׸���
	static cv::Mat MakeGridImage(cv::Mat& target,const MapStruct *map);
	
	//�׸��� �� ���Ϸ� ����
	static void SaveImage(const cv::Mat target, const char* filename);

	//�׸��� �� �簢�� ä���ֱ�
	static cv::Mat DrawSquare(cv::Mat& target, const MapStruct* map);

private:
	GetGridImage() = delete;//�ν��Ͻ��� �ʿ����
	static Scalar BLACK, WHITE, YELLOW, GREEN, RED, BLUE;
	static constexpr int BASE_IMAGE_SIZE = 512;
	static void makeSquareInfo(const MapStruct * map,
		std::vector<std::pair<std::vector<Point>, Scalar>>& vec);
	//vector�� pair�� ��ҷ� ������
	//pair�� Point�� �迭�� Scalar�� ��ҷ� ������.
};