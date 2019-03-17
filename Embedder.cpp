#include "stdafx.h"
#include "Embedder.h"

using namespace cv;

Embedder::Embedder()
{
}


Embedder::~Embedder()
{
}

bool Embedder::Embed(Mat input,
	char* data,
	int dataLenght,
	Mat output) {

	return true;
}

int Embedder::CountPixels(cv::Mat input)
{
	int pixels;

	pixels = 0;

	for (int i = 0; i < input.rows; i++)
	{
		for (int j = 0; j < input.cols; j++)
		{
			if (input.data[i * input.rows + j] > 0) 
				pixels++;
		}
	}

	return pixels;
}

cv::Mat Embedder::RemoveBlueLayer(Mat input)
{
	Mat image = input.clone();

	for (int i = 0; i < input.rows; i++)
	{
		for (int j = 0; j < input.cols; j++)
		{
			Vec3b pixel = image.at<Vec3b>(i, j);
			pixel.val[0] = 0;
			image.at<Vec3b>(i, j) = pixel;
		}
	}

	return image;
}

cv::Mat Embedder::Sobel(cv::Mat input)
{
	Mat imgGrayscale;       // grayscale image
	Mat imgBlurred;         // blured image
	Mat imgCanny;

	double sigma = 500;
	int lowTh = 90;
	int highTh = 100;

	cvtColor(RemoveBlueLayer(input), imgGrayscale, CV_BGR2GRAY);
	GaussianBlur(imgGrayscale, imgBlurred, cv::Size(5, 5), sigma);
	Canny(imgBlurred, imgCanny, lowTh, highTh);

	return imgCanny;
}

cv::Mat Embedder::EmbedData(cv::Mat input2, uchar *data, int size)
{
	int addedData = 0;
	Mat input = input2.clone();
	Mat imgCanny = Sobel(input);

	for (int i = 0; i < imgCanny.rows; i++)
	{
		for (int j = 0; j < imgCanny.cols; j++)
		{
			if (imgCanny.data[i * imgCanny.rows + j] > 0) {

				Vec3b pixel = input.at<Vec3b>(i, j);
				printf("%d \n", pixel.val[0] & 0xF);

				pixel.val[0] = pixel.val[0] & 0xF0 | data[addedData];

				input.at<Vec3b>(i, j) = pixel;

				addedData++;
				if (addedData  == size)
				{
					break;
				}
			}
		}

		if (addedData == size)
		{
			break;
		}
	}

	return input;
}

uchar* Embedder::ExtractData(cv::Mat input)
{
	Mat imgCanny = Sobel(input);
	int count = 0;

	buffer = (uchar*)malloc(1000);

	for (int i = 0; i < imgCanny.rows; i++)
	{
		for (int j = 0; j < imgCanny.cols; j++)
		{

			if (imgCanny.data[i * imgCanny.rows + j] > 0) {

				Vec3b pixel = input.at<Vec3b>(i, j);
				printf("%d \n", pixel.val[0] & 0xF);

				count++;

				if (count > 15)
				{
					printf("done");
					break;
				}
			}
		}
		if (count > 15)
			break;
	}

	return buffer;

}