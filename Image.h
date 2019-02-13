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

	void SetRed(int, int, uchar);
	void SetGreen(int, int, uchar);
	void SetBlue(int, int, uchar);

private:
	cv::Mat mat;
};

