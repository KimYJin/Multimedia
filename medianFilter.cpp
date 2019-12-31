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
#include<algorithm>
#include<string>

double alpha;
double beta;
using namespace std;
using namespace cv; // Mat

int main(int argc, char** argv)
{
	string imageName1("../data/lena_noise.png");	//Download a gray-scale image.
	Mat image1 = imread(imageName1.c_str(), IMREAD_GRAYSCALE); //Load the image
	Mat result_image = Mat::zeros(image1.size(), image1.type());

	float median[9];
	int a, b;

	//std::cout << "Input your n value : ";
	//std::cin >> n;

	for (int row = 0; row < image1.rows; row++)
	{
		for (int col = 0; col < image1.cols; col++)
		{
			float G_sum = 0, result = 0;
			int idx = 0, mid_idx=0;

			for (int y = 0; y < 3; y++)
			{
				for (int x = 0; x < 3; x++)
				{
					a = row + y - 1;
					b = col + x - 1;

					if ((a >= 0 && a < image1.rows) && (b >= 0 && b < image1.cols))
					{
						median[idx++] = image1.at<uchar>(a, b);
					}
				}
			}
			sort(median, median + 9);
			mid_idx = size(median)/2;
			result_image.at<uchar>(row, col) = saturate_cast<uchar>(median[mid_idx]);
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
