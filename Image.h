#pragma once

#include <opencv2\opencv.hpp>

class Image
{
public:
	Image(cv::Mat);
	~Image();

	uchar GetRed(int, int);
	uchar GetGreen(int, int);
	uchar GetBlue(int, int);

private:
	cv::Mat mat;
};

