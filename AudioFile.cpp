#include "stdafx.h"
#include "AudioFile.h"
#include <stdio.h>

AudioFile::AudioFile(const char *path)
{
	FILE *file = fopen(path, "rb");

	fread(&header, sizeof(struct WAV_TYPE), 1, file);

	buffer = (uint16_t*)malloc(header.overall_size);
	fread(buffer, header.overall_size, 1, file);

	fclose(file);
}

AudioFile::~AudioFile()
{
	free(buffer);
}

int AudioFile::GetLength()
{
	return header.overall_size / 2;
}

uint16_t AudioFile::GetSample(int location)
{
	return buffer[location];
}

void AudioFile::SetSample(int location, uint16_t data)
{
	buffer[location] = data;
}

void AudioFile::WriteToFile(const char *path)
{
	FILE *file = fopen(path, "wb");

	fwrite(&header, sizeof(struct WAV_TYPE), 1, file);

	fwrite(buffer, header.overall_size, 1, file);

	fclose(file);
}