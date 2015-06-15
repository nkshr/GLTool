#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "nkgl_texture.h"

using namespace std;

GLuint load_bmp(const char * imagepath)
{
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int width, height;
	unsigned int imageSize;
	unsigned char * data;

	FILE * file = fopen(imagepath, "rb");
	if (file == NULL)
	{
		cerr << "Error: Couldn't open the image." << endl;
		return false;
	}

	if (fread(header, 1, 54, file) != 54)
	{
		cerr << "Error: Not BMP file." << endl;
		return false;
	}

	if (header[0] != 'B' || header[1] != 'M')
	{
		cerr << "Error: Not BMP file." << endl;
		return false;
	}
	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);
	printf("%x %x %x\n", imageSize, header[0x12], height);
	if (imageSize == 0)
		imageSize = width*height * 3;
	if (dataPos == 0)
		dataPos = 54;
	data = new unsigned char[imageSize];
	fread(data, 1, imageSize, file);
	fclose(file);

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	return 0;
}