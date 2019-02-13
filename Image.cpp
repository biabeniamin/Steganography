#include "stdafx.h"
#include "Image.h"

using namespace cv;

Image::Image(Mat M)
{
	mat = M;
}


Image::~Image()
{
}

uchar Image::GetRed(int row, int col)
{
	return mat.data[(row * mat.rows + col) * 3 + 0];
}

uchar Image::GetGreen(int row, int col)
{
	return mat.data[(row * mat.rows + col) * 3 + 1];
}

uchar Image::GetBlue(int row, int col)
{
	return mat.data[(row * mat.rows + col) * 3 + 2];
}