#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <string>
#include <math.h>

using namespace cv;
using namespace std;

//오른쪽 이미지가 기준. 왼쪽이 비교하는 이미지.
//square size는 8*8 (5*5~10*10사이가 잘 나온다)
//right이미지의 point 대응하는 left 이미지 point에서 0~16 거리 point 까지 검사
//결국 index 인 0~16이 disparity

int main(char args, char** argv)
{
	int N = 8;
	int px, px2, py;

	// getting image
	string imageName1("../tsukuba/scene1.row3.col2.png");	
	string imageName2("../tsukuba/scene1.row3.col3.png");	

	Mat src_left = imread(imageName1.c_str(), IMREAD_GRAYSCALE);
	Mat src_right = imread(imageName2.c_str(), IMREAD_GRAYSCALE);
	Mat result_image = Mat::zeros(src_left.size(), src_left.type());

	if (src_left.empty() || src_right.empty()) {
		printf("error: no image");
		waitKey(0);
		return -1;
	}

	for (int row = 0; row < src_right.rows; row++)
	{
		for (int col = 0; col < src_right.cols; col++)
		{
			double ssd1 = 0;	//difference
		
			for (int y = -(N / 2); y <= (N / 2); y++)
			{
				for (int x = -(N / 2); x <= (N / 2); x++)
				{
					py = row + y - 1;
					px = col + x - 1;

					if (py < 0 || py > src_right.rows || px < 0 || px > src_right.cols)
					{
					}
					else
					{
						ssd1 = ssd1 + pow(src_left.at<uchar>(py, px) - src_right.at<uchar>(py, px), 2);
					}
				}
			}

			int disp = 0;	// disparity

			for (int i = 1; i < 16; i++) {
				double ssd2 = 0;	//difference

				for (int y = -(N / 2); y <= (N / 2); y++)
				{
					for (int x = -(N / 2); x <= (N / 2); x++)
					{
						py = row + y - 1;
						px2 = col + x - 1 + i;
						px= col + x - 1;

						if (py < 0 || py > src_right.rows || px < 0 || px > src_right.cols)
						{
						}
						else
						{
							ssd2 += pow(src_left.at<uchar>(py, px2) - src_right.at<uchar>(py, px), 2);
						}
					}
				}

				if (ssd1 > ssd2) {
					ssd1 = ssd2;
					disp = i;
				}
			}//end for (i:1~16)

			result_image.at<uchar>(row, col) = disp * 255 / 16.0;

		}//end for(col)
	}//end for(row)

	imshow("left_image", src_left);
	imshow("right_image", src_right);
	imshow("result_image", result_image);
	waitKey(0);

}//end main

