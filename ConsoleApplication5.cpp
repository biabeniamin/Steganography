// ConsoleApplication5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include "Embedder.h"

using namespace cv;
using namespace std;

int main()
{
	Mat imgOriginal;        // input image
	Mat imgGrayscale;       // grayscale image
	Mat imgBlurred;         // blured image
	Mat imgCanny;
	Mat imgOriginal2;        // input image
	Mat imgGrayscale2;       // grayscale image
	Mat imgBlurred2;         // blured image
	Mat imgCanny2;
	Embedder embedder;

	imgOriginal = imread("monkey.jpg");
	imgOriginal2 = imread("monkey.jpg");

	for (int i = 0; i < imgOriginal.cols; i++)
	{
		for (int j = 0; j < imgOriginal.rows; j++)
		{

			
		}
	}

	double sigma = 500;

	cvtColor(imgOriginal, imgGrayscale, CV_BGR2GRAY);                   // convert to grayscale
	cvtColor(imgOriginal2, imgGrayscale2, CV_BGR2GRAY);                   // convert to grayscale
	GaussianBlur(imgGrayscale, imgBlurred, cv::Size(5, 5), sigma);
	GaussianBlur(imgGrayscale2, imgBlurred2, cv::Size(5, 5), sigma);
	int lowTh = 50;
	int highTh = 100;
	Canny(imgBlurred, imgCanny, lowTh, highTh);
	Canny(imgBlurred2, imgCanny2, lowTh, highTh);

	int pixels = 0;

	for (int i = 0; i < imgCanny.rows; i++)
	{
		for (int j = 0; j < imgCanny.cols; j++)
		{

			

			if (imgCanny.data[i * imgCanny.rows + j] > 0) {


				for (int k = 0; k < 1; k++)
					imgOriginal.data[(i * imgOriginal.rows + j) * 3 + k] =
					imgOriginal.data[(i * imgOriginal.rows + j) * 3 + k] & 0xFE;
			}
		}
	}

	cvtColor(imgOriginal, imgGrayscale, CV_BGR2GRAY);
	GaussianBlur(imgGrayscale, imgBlurred, cv::Size(5, 5), sigma);
	Canny(imgBlurred, imgCanny, lowTh, highTh);

	cout <<pixels << " "<< embedder.CountPixels(imgCanny)<<"   "<< embedder.CountPixels(imgCanny2);

	//cvNamedWindow("image", CV_WINDOW_AUTOSIZE);
	imshow("Image", imgOriginal);

	
	//cvNamedWindow("stabilized image", CV_WINDOW_AUTOSIZE);
	imshow("Image canny", imgCanny);

	imwrite("out.jpg", imgOriginal);
	waitKey(0);


    return 0;
}
