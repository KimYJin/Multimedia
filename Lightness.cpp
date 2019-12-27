#include<iostream>
#include<algorithm>
#include<string>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv; // Mat


int main(void)
{
	string imageName1("../data/lady.jpg");
	Mat image = imread(imageName1.c_str(), IMREAD_COLOR); //Load the image						
	Mat result_image1 = Mat::zeros(image.size(), image.type());
	Mat result_image2 = Mat::zeros(image.size(), image.type());
	Mat result_image3 = Mat::zeros(image.size(), image.type());
	Mat result_image4 = Mat::zeros(image.size(), image.type());

	double k = 0.7;

	//1. YCbCr
	//color transform : RGB->YCrCb
	cvtColor(image, result_image1, COLOR_BGR2YCrCb);

	// Y,Cr,Cb 중 밝기 Y값만 바꾸면 되므로, Y인 [0]에 k를 곱해라.
	for (int y = 0; y < image.rows; y++)
	{
		for (int x = 0; x < image.cols; x++)
		{
			for (int c = 0; c < 3; c++) {

				if(c == 0)
					result_image1.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(image.at <Vec3b>(y, x)[c])*k;
			}
		}
	}
	cvtColor(result_image1, result_image1, COLOR_YCrCb2BGR);

	//2. RGB
	// 밝기 변경을 위해서 R,G,B 각각의 값에 k를 곱한다.
	for (int y = 0; y < image.rows; y++)
	{
		for (int x = 0; x < image.cols; x++)
		{
			for (int c = 0; c < 3; c++) {

					result_image2.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(image.at <Vec3b>(y, x)[c])*k;
			}
		}
	}

	//3.CMY

	for (int y = 0; y < image.rows; y++)
	{
		for (int x = 0; x < image.cols; x++)
		{
			for (int c = 0; c < 3; c++) {
				result_image3.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(255-(255-(image.at <Vec3b>(y, x)[c])*k) + (1-k));
			}
		}
	}


	//4. HSI
	// H,S,I 중 밝기 I값만 바꾸면 되므로, I인 [2]에 k를 곱해라.
	cvtColor(image, result_image4, COLOR_BGR2HSV);
	for (int y = 0; y < image.rows; y++)
	{
		for (int x = 0; x < image.cols; x++)
		{
			for (int c = 0; c < 3; c++) {
				if(c==2)
				result_image4.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(image.at <Vec3b>(y, x)[c])*k;
			}
		}
	}
	cvtColor(result_image4, result_image4, COLOR_HSV2BGR);



	namedWindow("original image", WINDOW_AUTOSIZE);
	namedWindow("result_image1", WINDOW_AUTOSIZE);
	namedWindow("result_image2", WINDOW_AUTOSIZE);
	namedWindow("result_image3", WINDOW_AUTOSIZE);
	namedWindow("result_image4", WINDOW_AUTOSIZE);


	//창 띄우기
	imshow("original image", image);
	imshow("result_image1", result_image1);
	imshow("result_image2", result_image2);
	imshow("result_image3", result_image3);
	imshow("result_image4", result_image4);

	waitKey();

	return 0;

}