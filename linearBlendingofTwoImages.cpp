#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include<opencv2/imgproc/imgproc.hpp>

double alpha;
double beta;
using namespace std;
using namespace cv; // Mat

int main(int argc, char** argv)
{
	string imageName1("../data/lady.jpg");
	string imageName2("../data/rabbit.jpg");
	//Mat image = imread(argv[1]);
	Mat image1 = imread(imageName1.c_str(), IMREAD_COLOR);
	Mat image2 = imread(imageName2.c_str(), IMREAD_COLOR);

	//MatŬ������ zeros �Լ� : �� ù ��° parameter�����ŭ�� �� �̹����� datatype���� ���� ������ �Ҵ�(allocation)���� �� zero(0)������ ä����.
	Mat new_image = Mat::zeros(image1.size(), image1.type());

	//image1�� size�� image2����� ���߾ new_image�� ����.
	resize(image2, new_image, image1.size(), 0, 0, INTER_LINEAR);

	cout << "Basic Linear Transforms" << endl;
	cout << "�ѤѤѤѤѤѤѤѤѤѤѤ�" << endl;
	cout << "Enter alpha value [0.1-1.0] : ";
	cin >> alpha;
	//cout << "Enter beta value [0-100] : ";
	//cin >> beta;
	beta = 1 - alpha;

	for (int y = 0; y < image1.rows; y++)
	{
		for (int x = 0; x < image1.cols; x++)
		{
			for (int c = 0; c < 3; c++) {
				new_image.at<Vec3b>(y, x)[c] =
					saturate_cast<uchar>(alpha* (image1.at <Vec3b>(y, x)[c]) + beta* (new_image.at <Vec3b>(y, x)[c]));
				//saturate_cast�� �ִ�, �ּҰ��� �������ִ� ��. 0���� ������ 0����, 255���� ũ�� 255�� �������. 
				//Vec3b�� 8��Ʈ ¥�� 3��, �� 3����Ʈ��� ��. 
			}
		}
	}

	namedWindow("Original Image1", 1);
	namedWindow("Original Image2", 1);
	namedWindow("New Image", 1);

	imshow("Original Image1", image1);
	imshow("Original Image2", image2);
	imshow("New Image", new_image);

	waitKey();
	return 0;

}
