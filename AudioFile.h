#pragma once
#include <opencv2\opencv.hpp>

// WAVE file header format
struct WAV_TYPE {
	unsigned char riff[4];						// RIFF string
	unsigned int overall_size;				// overall size of file in bytes
	unsigned char wave[4];						// WAVE string
	unsigned char fmt_chunk_marker[4];			// fmt string with trailing null char
	unsigned int length_of_fmt;					// length of the format data
	uint16_t format_type;					// format type. 1-PCM, 3- IEEE float, 6 - 8bit A law, 7 - 8bit mu law
	uint16_t channels;						// no.of channels
	unsigned int sample_rate;					// sampling rate (blocks per second)
	unsigned int byterate;						// SampleRate * NumChannels * BitsPerSample/8
	uint16_t block_align;					// NumChannels * BitsPerSample/8
	uint16_t bits_per_sample;				// bits per sample, 8- 8bits, 16- 16 bits etc
	unsigned char data_chunk_header[4];		// DATA string or FLLR string
	unsigned int data_size;						// NumSamples * NumChannels * BitsPerSample/8 - size of the next chunk that will be read
};

class AudioFile
{
public:
	AudioFile(char *path);
	~AudioFile();

	int GetLength();
	uint16_t GetSample(int location);
	void SetSample(int location, uint16_t data);
private:
	struct WAV_TYPE header;
	uint16_t *buffer;
};

