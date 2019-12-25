//Gaussian filtering.
//The parameters of the algorithm are 1) N(kernel size), 2) sigma(standard deviation)표준편차.

#include<iostream>
#include<algorithm>
#include<string>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

double alpha;
double beta;
using namespace std;
using namespace cv; // Mat

const double pi = 3.14;

void GaussianFiltering(int N, double sigma);

int main(void)
{
	double sigma;
	int N;

	cout<< "Input kernel size : ";
	cin >> N;
	cout << "Input sigma : ";
	cin >> sigma;

	GaussianFiltering(N, sigma);

	return 0;

}

void GaussianFiltering(int N, double sigma)
{
	// Load an image (using cv::imread)
	string imageName1("../data/lena512_gray.bmp");	
	Mat image1 = imread(imageName1.c_str(), IMREAD_GRAYSCALE); //Load the image						
	Mat result_image = Mat::zeros(image1.size(), image1.type());

	int px, py;
	double gau, sum;

	for (int row = 0; row < image1.rows; row++)
	{
		for (int col = 0; col < image1.cols; col++)
		{
			sum = 0;
			double gs = 0;
			for (int y = -(N/2); y <= (N / 2); y++)
			{
				for (int x = -(N / 2); x <= (N / 2); x++)
				{
					py = row + y - 1;
					px = col + x - 1;

					if ((py >= 0 && py < image1.rows) && (px >= 0 && px < image1.cols))
					{
						gau = exp(-(pow(x, 2) + pow(y, 2)) / (2 * sigma * sigma))/(2*pi*sigma*sigma);
						gs += gau;
						sum += image1.at<uchar>(py,px)*gau;
					}
				}
			}
			sum /= gs;
			result_image.at<uchar>(row, col) = saturate_cast<uchar>(sum);
		}
	}

	namedWindow("original image",  WINDOW_AUTOSIZE);
	namedWindow("result_image",  WINDOW_AUTOSIZE);

	//창 띄우기
	imshow("original image", image1);
	imshow("result_image", result_image);

	waitKey();
}
