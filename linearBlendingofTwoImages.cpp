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

	//Mat클래스의 zeros 함수 : 이 첫 번째 parameter사이즈만큼의 이 이미지의 datatype으로 실제 공간을 할당(allocation)해준 뒤 zero(0)값으로 채워줌.
	Mat new_image = Mat::zeros(image1.size(), image1.type());

	//image1의 size로 image2사이즈를 맞추어서 new_image에 저장.
	resize(image2, new_image, image1.size(), 0, 0, INTER_LINEAR);

	cout << "Basic Linear Transforms" << endl;
	cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ" << endl;
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
				//saturate_cast란 최대, 최소값을 설정해주는 것. 0보다 작으면 0으로, 255보다 크면 255로 만들어줌. 
				//Vec3b는 8비트 짜리 3개, 즉 3바이트라는 뜻. 
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
