
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
	//Mat클래스의 zeros 함수 : 이 첫 번째 parameter사이즈만큼의 이 이미지의 datatype으로 실제 공간을 할당(allocation)해준 뒤 zero(0)값으로 채워줌.

	cout << "Basic Linear Transforms" << endl;
	cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ" << endl;
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
				//saturate_cast란 최대, 최소값을 설정해주는 것. 0보다 작으면 0으로, 255보다 크면 255로 만들어줌. 
				//Vec3b는 8비트 짜리 3개, 즉 3바이트라는 뜻. 
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
