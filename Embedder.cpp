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