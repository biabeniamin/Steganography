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

	double sigma = 1;
	int lowTh = 45;
	int highTh = 90;

	cvtColor(RemoveBlueLayer(input), imgGrayscale, CV_BGR2GRAY);
	GaussianBlur(imgGrayscale, imgBlurred, cv::Size(5, 5), sigma);
	Canny(imgBlurred, imgCanny, lowTh, highTh);

	return imgCanny;
}

cv::Mat Embedder::EmbedData(cv::Mat input2, uchar *data2, int size, int* length)
{
	int addedData = 0;
	Mat input = input2.clone();
	Mat imgCanny = Sobel(input);
	uchar *data = (uchar*)malloc(size + 2);

	memcpy(data + 2, data2, size);

	//write length
	size += 2;
	data[0] = size >> 8;
	data[1] = size & 0xFF;

	for (int i = 0; i < imgCanny.rows; i++)
	{
		for (int j = 0; j < imgCanny.cols; j++)
		{
			if (imgCanny.data[i * imgCanny.rows + j] > 0) {

				Vec3b pixel = input.at<Vec3b>(i, j);

				switch (addedData % 4)
				{
				case 0:
					pixel.val[0] = pixel.val[0] & 0xFC | (data[addedData / 4] >> 6 & 0x3);
					break;
				case 1:
					pixel.val[0] = pixel.val[0] & 0xFC | (data[addedData / 4] >> 4 & 0x3);
					break;
				case 2:
					pixel.val[0] = pixel.val[0] & 0xFC | (data[addedData / 4] >> 2 & 0x3);
					break;
				case 3:
					pixel.val[0] = pixel.val[0] & 0xFC | (data[addedData / 4] >> 0 & 0x3);
					break;
				}
				input.at<Vec3b>(i, j) = pixel;

				addedData++;
				if (addedData >> 2 == size)
				{
					break;
				}
			}
		}

		if (addedData >> 2  == size)
		{
			break;
		}
	}

	*length = addedData >> 2;
	if (addedData >> 2 < size)
	{
		printf("Could not embed in image because it is too small!");
	}

	return input;
}

uchar* Embedder::ExtractData(cv::Mat input, int *length)
{
	Mat imgCanny = Sobel(input);
	int count = 0;
	int size = 20;

	buffer = (uchar*)malloc(20);

	for (int i = 0; i < imgCanny.rows; i++)
	{
		for (int j = 0; j < imgCanny.cols; j++)
		{
			if (imgCanny.data[i * imgCanny.rows + j] > 0) {

				Vec3b pixel = input.at<Vec3b>(i, j);
				switch (count % 4)
				{
				case 0:
					buffer[count / 4] = (pixel.val[0] & 0x3) << 6;
					break;
				case 1:
					buffer[count / 4] |= (pixel.val[0] & 0x3) << 4;
					break;
				case 2:
					buffer[count / 4] |= (pixel.val[0] & 0x3) << 2;
					break;
				case 3:
					buffer[count / 4] |= (pixel.val[0] & 0x3) << 0;
					break;
				}

				count++;

				if (count == 8)
				{
					size = buffer[0] << 8 | buffer[1];
					buffer = (uchar*)realloc(buffer, size + 50);
				}

				if (count >> 2 == size)
				{
					printf("done\n");
					break;
				}
			}
		}
		if (count >> 2 == size)
			break;
	}

	*length = size - 2;

	if (count >> 2 < size)
	{
		printf("Could not embed in image because it is too small!");
		*length = 0;
	}

	

	return buffer + 2;

}