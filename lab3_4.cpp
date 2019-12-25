/**
@file videocapture_basic.cpp
@brief A very basic sample for using VideoCapture and VideoWriter
@author PkLab.net
@date Aug 24, 2016
*/

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
	string imageName1("../data/lena512_gray.bmp");	//Download a gray-scale image.
	Mat image1 = imread(imageName1.c_str(), IMREAD_GRAYSCALE); //Load the image
	Mat result_image = Mat::zeros(image1.size(), image1.type());

	/// 3 x 3 Sobel filtering
	//int n=3;

	float Gx[3][3] = { { 1,0,-1 },{ 2,0,-2 },{ 1,0,-1 } }, Gy[3][3] = { { 1,2,1 },{ 0,0,0 },{ -1,-2,-1 } };

	for (int row = 0; row < image1.rows; row++)
	{
		for (int col = 0; col < image1.cols; col++)
		{
			float Gx_sum = 0, Gy_sum = 0, result = 0;
			for (int y = 0; y < 3; y++)
			{
				for (int x = 0; x < 3; x++)
				{
					if ((col + x >= 0 && col + x < image1.cols) && (row + y >= 0 && row + y < image1.rows))
					{
						Gx_sum = Gx_sum + image1.at<uchar>(row + y, col + x)*Gx[y][x];
						Gy_sum = Gy_sum + image1.at<uchar>(row + y, col + x)*Gy[y][x];
					}
				}
			}
			result = Gx_sum*Gx_sum + Gy_sum*Gy_sum;
			result = sqrt(result);
			result_image.at<uchar>(row, col) = saturate_cast<uchar>(result);
		}
	}

	namedWindow("original image", 1);
	namedWindow("result_image", 1);

	//Ã¢ ¶ç¿ì±â
	imshow("original image", image1);
	imshow("result_image", result_image);

	waitKey();
	return 0;

}
