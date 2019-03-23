#pragma once
#include "AudioFile.h"
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
	cv::Mat Sobel(cv::Mat input);

	cv::Mat EmbedData(cv::Mat input, uchar *data, int size, int *length);
	uchar* ExtractData(cv::Mat input, int *length);

	void EmbedDataInAudio(AudioFile *file, uchar *data, int size, int *length);
	uchar* ExtractDataFromAudio(AudioFile *input, int *length);

private:
	uchar * buffer;
};

