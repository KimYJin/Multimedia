
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>

double alpha; //simple contrast control
int beta; //simple brightness control
using namespace std;
using namespace cv; // Mat

int main(int argc, char** argv)
{
	string imageName("../data/lady.jpg");
	//Mat image = imread(argv[1]);
	Mat image = imread(imageName.c_str(), IMREAD_COLOR);

	Mat new_image = Mat::zeros(image.size(), image.type());
	//MatŬ������ zeros �Լ� : �� ù ��° parameter�����ŭ�� �� �̹����� datatype���� ���� ������ �Ҵ�(allocation)���� �� zero(0)������ ä����.

	cout << "Basic Linear Transforms" << endl;
	cout << "�ѤѤѤѤѤѤѤѤѤѤѤ�" << endl;
	cout << "Enter alpha value [1.0-3.0] : ";
	cin >> alpha;
	cout << "Enter beta value [0-100] : ";
	cin >> beta;

	for (int y = 0; y < image.rows; y++)
	{
		for (int x = 0; x < image.cols; x++)
		{
			for (int c = 0; c < 3; c++) {
				new_image.at<Vec3b>(y, x)[c] =
					saturate_cast<uchar>(alpha* (image.at <Vec3b>(y, x)[c]) + beta);
				//saturate_cast�� �ִ�, �ּҰ��� �������ִ� ��. 0���� ������ 0����, 255���� ũ�� 255�� �������. 
				//Vec3b�� 8��Ʈ ¥�� 3��, �� 3����Ʈ��� ��. 
			}
		}
	}

	namedWindow("Original Image", 1);
	namedWindow("New Image", 1);

	imshow("Original Image", image);
	imshow("New Image", new_image);

	waitKey();
	return 0;

}
