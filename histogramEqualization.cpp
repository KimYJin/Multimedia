#include <opencv2\core.hpp>
#include <opencv2\imgcodecs.hpp>
#include <opencv2\highgui\highgui.hpp>

#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	string imageName1("../data/lena512_gray.bmp");	//Download a gray-scale image.
	Mat image = imread(imageName1.c_str(), IMREAD_GRAYSCALE); //Load the image
	Mat result_image = Mat::zeros(image.size(), image.type());
	int n;

	//이미지 인풋이 맞는지 확인
	if (image.empty())
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	/// n인풋 값 받기
	std::cout << "Input your n value : ";
	std::cin >> n;

	//오리지날 이미지 값 복사 하기
	//result_image = image.clone();

	for (int row = 0; row < image.rows; row++)
	{
		for (int col = 0; col < image.cols; col++)
		{
			float sum = 0;

			//마스크 만큼 확인하기
			for (int y = -(n / 2); y <= (n / 2); y++)
			{
				for (int x = -(n / 2); x <= (n / 2); x++)
				{
					if ((col + y >= 0 && col + y < image.cols) && (row + x >= 0 && row + x < image.rows))
					{
						sum += image.at<uchar>(row + y, col + x);
					}
				}
			}
			result_image.at<uchar>(row, col) = saturate_cast<uchar>(sum / (n * n));
		}
	}

	namedWindow("original image", 1);
	namedWindow("result_image", 1);

	//창 띄우기
	imshow("original image", image);
	imshow("result_image", result_image);

	waitKey(0);
	return 0;
}