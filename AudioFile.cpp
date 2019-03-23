#include "stdafx.h"
#include "AudioFile.h"
#include <stdio.h>

AudioFile::AudioFile(char *path)
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