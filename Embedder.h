#pragma once

#include <opencv2\opencv.hpp>

class Embedder
{
public:
	Embedder();
	~Embedder();

	bool Embed(cv::Mat input,
		char* data,
		int dataLenght,
		cv::Mat output);

	int CountPixels(cv::Mat input);

	cv::Mat RemoveBlueLayer(cv::Mat input);
};

