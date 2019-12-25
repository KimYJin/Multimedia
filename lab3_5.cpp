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
	string imageName1("../data/moon_laplacian_sharpening.png");	//Download a gray-scale image.
	Mat image1 = imread(imageName1.c_str(), IMREAD_GRAYSCALE); //Load the image
	Mat result_image = Mat::zeros(image1.size(), image1.type());

	float G[3][3] = { { 0,-1,0 },{ -1,4,-1 },{ 0,-1,0 } };
	int a, b;
	for (int row = 0; row < image1.rows; row++)
	{
		for (int col = 0; col < image1.cols; col++)
		{
			float G_sum=0, result = 0;
			
			for (int y = 0; y < 3; y++)
			{
				for (int x = 0; x < 3; x++)
				{
					a = row + y - 1;
					b = col + x - 1;
					if ((a>= 0 && a < image1.rows) && (b >= 0 && b < image1.cols))
					{
						G_sum = G_sum + image1.at<uchar>(a,b)*G[y][x];
					}
				}
			}
			result_image.at<uchar>(row, col) = saturate_cast<uchar>(image1.at<uchar>(row, col) + (G_sum));
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
