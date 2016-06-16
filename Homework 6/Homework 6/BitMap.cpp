/*
 *  BitMap.cpp
 *  HW 3
 */

#include "BitMap.h"
#include <stdio.h>
#include <iostream>
#include <cmath>
#define _CRT_SECURE_NO_WARNINGS
BitMap::BitMap()
{

}
BitMap::BitMap(int width, int height)
{
	this->height = height;
	this->width = width;
	this->image = new uint8_t[width*height * 4];
}

BitMap::BitMap(BitMap& b)
{
	this->height = b.height;
	this->width = b.width;
	this->image = new uint8_t[width*height * 4];
	for (int i = 0; i < width*height * 4; i++)
	{
		this->image[i] = b.image[i];
	}
}

void BitMap::operator=(BitMap b)
{
	BitMap *temp= new BitMap();
	temp->height = b.height;
	temp->width = b.width;
	temp->image = new uint8_t[width*height * 4];
	for (int i = 0; i < width*height * 4; i++)
	{
		temp->image[i] = b.image[i];
	}
	if (image != NULL)
	{
		this->height=0;
		this->width=0;
		delete [] image;
	}
	for (int i = 0; i < width*height * 4; i++)
	{
		this->image[i] = temp->image[i];
	}
	this->height = temp->height;
	this->width = temp->width;
}


BitMap::~BitMap()
{
	delete[] image;
	height= 0;
	width = 0;
	//delete &bm;
}
int BitMap::GetWidth()
{
	return this->width;
}

int BitMap::GetHeight()
{
	return this->height;
}

void BitMap::SetPixel(BitMap *bm, int x, int y, uint8_t redByte, uint8_t greenByte, uint8_t blueByte, uint8_t alphaByte)
{
	bm->image[y*bm->width * 4 + x * 4] = redByte;
	bm->image[y*bm->width * 4 + x * 4 + 1] = greenByte;
	bm->image[y*bm->width * 4 + x * 4 + 2] = blueByte;
	bm->image[y*bm->width * 4 + x * 4 + 3] = alphaByte;
}

void BitMap::GetPixel(BitMap *bm, int x, int y, uint8_t &redByte, uint8_t &greenByte, uint8_t &blueByte, uint8_t &alphaByte)
{
	BitMap b = *bm;
	redByte = b.image[y*b.width * 4 + x * 4];
	greenByte = b.image[y*b.width * 4 + x * 4 + 1]; 
	blueByte = b.image[y*b.width * 4 + x * 4 + 2];
	alphaByte = b.image[y*b.width * 4 + x * 4 + 3];
}


void BitMap::Save(BitMap *bm, const char *file)
{
	// 1. Open the 
	FILE* a = fopen(file, "w+");
	if (a == NULL)
	{
		printf("null file");
		throw std::runtime_error(std::strerror(errno));
	}

	// 2. Create a header and write it to the file

	BitMapHeader header = BitMapHeader();
	header.biWidth = bm->width;
	header.biHeight = bm->height;
	uint16_t c = 19778;
	fwrite(&c, sizeof(uint16_t), 1, a);
	fwrite(&header, sizeof(BitMapHeader), 1, a);
	// 3. Write the bitmap data to the file
	fseek(a, sizeof(BitMapHeader), SEEK_SET);
	for (int i = 0; i < bm->width*bm->height * 4; i++)
	{
		fwrite(&(bm->image[i]), sizeof(uint8_t), i, a);
	}
	// 4. Close the file
	fclose(a);
}

BitMap* BitMap::Load(const char *file)
{
	// 0. If any of the operations fail, free any memory and return 0

	// 1. Open the file
	delete[] this->image;
	FILE* Map = fopen(file, "r");
	if (Map == NULL)
	{
		printf("NULL file");
		throw std::runtime_error(std::strerror(errno));
	}
	// 2a. Read the initial fields of the header; verify that the file type (BM) is correct.
	uint16_t a;
	fread(&a, sizeof(uint16_t), 1, Map);
	if (a == 19778)
	{
		BitMapHeader header;
		fseek(Map, 2 * sizeof(uint8_t), SEEK_SET);
		fread(&header, sizeof(BitMapHeader), 1, Map);
		this->width = header.biWidth;
		this->height = header.biHeight;
		if (this->height < 0)
		{
			this->image = new uint8_t[-1*(this->width * this->height) * 4];
		}
		else
		{
			this->image = new uint8_t[(this->width * this->height) * 4];
		}
		// 2b. Read the rest of the header.

		// 3. Verify if the file is 24 or 32 bits.

		// 4. Check if the rows are stored in reverse order (due to negative height)

		// 5. Make sure the file isn't compressed (compression should be 0)

		// 6. Load the file if it is 32 bits
		// 6a. If the file is 32 bits, you can read one row at a time.
		// 6b. If the height is negative, you need to read from disk into the rows in memory in reverse order
		// 6c. 32-bit files are never padded.

		if (header.biBitCount == 32)
		{
			if (this->height < 0)
			{
				for (int i = 0; i < -1*this->height; i++)
				{
					fread(&(this->image[i*header.biWidth * 4]), header.biWidth * 4, 1, Map);
					printf("this ran");
				}
			}
			else
			{
				for (int i = 0; i < this->height; i++)
				{
					fread(&(this->image[i*header.biWidth * 4]), header.biWidth * 4, 1, Map);
				}
			}
		}

		// 7. Load the file if it is 24 bits
		// 7a. If the file is 24 bits, you need to read 3 bytes at a time and make space in memory for
		//     the extra byte. (Since your internal storage should always be 32 bits.)
		// 7b. If the height is negative, you need to read from disk into the rows in memory in reverse order
		// 7c. If the length of each line isn't divisible by 4, you need to read extra padding from the file.
		//     This padding shouldn't be stored in the bitmap data in memory.
		if (header.biBitCount == 24)
		{
			if (this->height < 0)
			{
				for (int i = 0; i < -1 * this->height; i++)
				{
					printf("this ran");
					for (int j = 0; j < header.biWidth; j++)
					{
						fread(&(this->image[i*header.biWidth * 4]), sizeof(&this->image[0]), 1, Map);
						fread(&(this->image[i*header.biWidth * 4 + 1]), sizeof(&this->image[0]), 1, Map);
						fread(&(this->image[i*header.biWidth * 4 + 2]), sizeof(&this->image[0]), 1, Map);
						this->image[i*header.biWidth * 4 + 3]= 0;
					}
				}
			}
			else
			{
				for (int i = 0; i < this->height; i++)
				{
					for (int j = 0; j < header.biWidth; j++)
					{
						fread(&(this->image[i*header.biWidth * 4]), sizeof(&this->image[0]), 1, Map);
						fread(&(this->image[i*header.biWidth * 4 + 1]), sizeof(&this->image[0]), 1, Map);
						fread(&(this->image[i*header.biWidth * 4 + 2]), sizeof(&this->image[0]), 1, Map);
						this->image[i*header.biWidth * 4 + 3] = 0;
					}
				}
			}
		}
	}

	// 8. Close the file.
	fclose(Map);
	// 9. Return a pointer to the bitmap.
	return this;
}

