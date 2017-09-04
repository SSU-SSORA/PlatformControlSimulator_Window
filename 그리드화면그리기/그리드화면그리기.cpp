#include <opencv2\opencv.hpp>
#include <vector>
#include "�׸���ȭ��׸���.h"
#include "MapStruct.h"


#define LINE_THICKNESS 2

//note : opencv���� scalar�� BGR����
cv::Scalar GetGridImage::BLACK	= Scalar(0, 0, 0);
cv::Scalar GetGridImage::WHITE	= Scalar(255, 255, 255);
cv::Scalar GetGridImage::BLUE	= Scalar(255, 0, 0);
cv::Scalar GetGridImage::RED	= Scalar(0, 0, 255);
cv::Scalar GetGridImage::GREEN	= Scalar(0, 255, 0);
cv::Scalar GetGridImage::YELLOW = Scalar(0, 255, 255);

cv::Mat GetGridImage::MakeImage(const MapStruct* map) {
	int row = BASE_IMAGE_SIZE;
	int col = BASE_IMAGE_SIZE;

	int rowCnt = map->row;
	int colCnt = map->col;

	//���� ũ�⿡ ���� ���� ũ�⸦ �����Ѵ�.
	int rowSize(row / rowCnt * rowCnt + LINE_THICKNESS - 1);
	int colSize(col / colCnt * colCnt + LINE_THICKNESS - 1);
	cv::Size2i s(rowSize, colSize);
	cv::Mat target(s, CV_8UC3);

	//����Ʈ �� ����
	target = WHITE;

	return target;
}

cv::Mat GetGridImage::MakeGridImage(cv::Mat& target,const MapStruct *map){
	int rowCnt = map->row;
	int colCnt = map->col;
	int row = BASE_IMAGE_SIZE;
	int col = BASE_IMAGE_SIZE;

	
	/*
	cv::line ->
	1. cv::Mat
	2. Point
	3. Point
	4. Scalar - color
	5. thickness = 1
	*/


	//row
	for (int rowPixel = 0; rowPixel < row; rowPixel += row / rowCnt) {
		cv::Point start(0, rowPixel), end(col - 1, rowPixel);
		cv::line(target, start, end, BLACK, LINE_THICKNESS);
	}
	//col
	for (int colPixel = 0; colPixel < col; colPixel += row / colCnt) {
		cv::Point start(colPixel, 0), end(colPixel, row - 1);
		cv::line(target, start, end, BLACK, LINE_THICKNESS);
	}

	return target;
}

void GetGridImage::SaveImage(const cv::Mat target, const char* filename) {
	std::vector<int> a;
	a.push_back(PNG);
	a.push_back(PNG_DEFAULT_VALUE);
	cv::imwrite(filename, target, a);
}

void GetGridImage::makeSquareInfo(const MapStruct * map, 
	std::vector<std::pair<std::vector<Point>,Scalar>>& vec) {
	int initRow = BASE_IMAGE_SIZE / map->row / 2;
	int curRow = initRow;
	int initCol = BASE_IMAGE_SIZE / map->col / 2;
	int curCol = initCol;

	auto SelectColor = [=](unsigned char i) -> Scalar {
		if (i == 's')//start
			return GREEN;
		else if (i == 'f')//finish
			return RED;
		else if (245 <= i && i <= 255)//wall
			return BLUE;
		else {
			std::cout << "undefined block information\n";
			std::cout << __FILE__ << ' ' << __LINE__ << '\n';
			exit(1);
		}
	};
	for (int i = 0; i < map->row; ++i) {
		for (int j = 0; j < map->col; ++j) {//col���� �簢�� ���� Ž��
			if (map->map[i][j] != 1) {
				std::vector<Point> pointVec;
				pointVec.push_back(Point(curCol - initCol + LINE_THICKNESS, curRow - initRow + LINE_THICKNESS));
				pointVec.push_back(Point(curCol - initCol + LINE_THICKNESS, curRow + initRow + LINE_THICKNESS));
				pointVec.push_back(Point(curCol + initCol + LINE_THICKNESS, curRow + initRow + LINE_THICKNESS));
				pointVec.push_back(Point(curCol + initCol + LINE_THICKNESS, curRow - initRow + LINE_THICKNESS));
				
				vec.push_back(std::make_pair(pointVec, SelectColor(map->map[i][j])));
			}
			curCol += BASE_IMAGE_SIZE / map->col;
		}
		curCol = initCol;//col �ʱ�ȭ
		curRow += BASE_IMAGE_SIZE / map->row;//row ����
	}
}

cv::Mat GetGridImage::DrawSquare(cv::Mat& target, const MapStruct* map) {
	const int SQUARE_POINT_CNT = 4;
	std::vector<std::pair<std::vector<Point>,Scalar>> squareInfo;
	makeSquareInfo(map, squareInfo);//polylines�� ���� �ڷ� ����

	/* pts */
	Point **pts = new Point*[squareInfo.size()];//�׷��� �� �簢���� ���� ��ŭ ���� �Ҵ�
	//������� 13 * 13������ �ִ� 169���� �ǰ���
	int pts_index = 0;
	for (auto& square : squareInfo) {
		int point_index = 0;
		pts[pts_index] = new Point[SQUARE_POINT_CNT];//�� �װ��� ������ �� �ִ� �����͹迭 ����
		for (auto& point : square.first) {
			pts[pts_index][point_index++]= point;
		}
		pts_index++;
	}


	/* polylines */
	//void polylines(Mat& img, const Point**pts, const int* npts, int ncountours, 
	//				bool isClosed, const Scalar& color, int thickness = 1, int lineType = 8,
	//					int shift = 0)
	pts_index = 0;
	for (int i = 0; i < squareInfo.size(); ++i)
		cv::fillConvexPoly(target, pts[i], SQUARE_POINT_CNT, squareInfo[i].second);

	/* delete pts */
	for (int i = 0; i < squareInfo.size(); i++)
		delete[] pts[i];
	delete[] pts;

	
	return target;

}