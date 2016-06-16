/*
 *  BitMap.cpp
 *  HW 3
 */

#include "BitMap.h"
#include <stdio.h>
#include <iostream>
#define _CRT_SECURE_NO_WARNINGS

BitMap *CreateBitMapPic(int width, int height)
{
	BitMap *b = new BitMap;
	b->height = height;
	b->width = width;
	b->image = new uint8_t[width*height * 4];
	return b;
}

void Free(BitMapPointer &bm)
{
	delete[](*bm).image;
	(*bm).image = NULL;
	(*bm).height= 0;
	(*bm).width = 0;
	//delete &bm;
}

void SetPixel(BitMap *bm, int x, int y, uint8_t redByte, uint8_t greenByte, uint8_t blueByte, uint8_t alphaByte)
{
	(*bm).image[y*(*bm).width * 4 + x * 4] = redByte;
	(*bm).image[y*(*bm).width * 4 + x * 4 + 1] = greenByte;
	(*bm).image[y*(*bm).width * 4 + x * 4 + 2] = blueByte;
	(*bm).image[y*(*bm).width * 4 + x * 4 + 3] = alphaByte;
}

void GetPixel(BitMap *bm, int x, int y, uint8_t &redByte, uint8_t &greenByte, uint8_t &blueByte, uint8_t &alphaByte)
{
	BitMap b = *bm;
	redByte = b.image[y*b.width * 4 + x * 4];
	greenByte = b.image[y*b.width * 4 + x * 4 + 1]; 
	blueByte = b.image[y*b.width * 4 + x * 4 + 2];
	alphaByte = b.image[y*b.width * 4 + x * 4 + 3];
}


void Save(BitMap *bm, const char *file)
{
	// 1. Open the 
	FILE* a = fopen(file, "wb+");
	if (a == NULL)
	{
		printf("null file");
		throw std::runtime_error(std::strerror(errno));
	}

	BitMap b = *bm;
	// 2. Create a header and write it to the file

	BitMapHeader header;
	header.biSize = sizeof(bm);
	header.biWidth = b.width;
	header.biHeight = b.height;
	fwrite(&header, sizeof(BitMapHeader), 1, a);
	// 3. Write the bitmap data to the file
	fwrite(&b, sizeof(b), 1, a);
	// 4. Close the file
	fclose(a);
}

BitMap *Load(const char *file)
{
	// 0. If any of the operations fail, free any memory and return 0

	// 1. Open the file
	BitMap *b = new BitMap;

	FILE* Map = fopen(file, "wb+");
	if (Map == NULL)
	{
		printf("NULL file");
		throw std::runtime_error(std::strerror(errno));
	}
	
	// 2a. Read the initial fields of the header; verify that the file type (BM) is correct.
	BitMapHeader header;
	if (fread(&header, sizeof(BitMapHeader), 1, Map) != 1) {
		printf("Bad header");
		throw std::runtime_error(std::strerror(errno));
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
		if (header.biHeight < 0)
		{
			for (int i = 0; i > header.biHeight; i--)
			{
				fread(&(*b).image[(header.biHeight+i)*(-1)*header.biWidth * 4], header.biWidth * 4, 1, Map);
				printf("this ran");
			}
		}
		else
		{
			for (int i = 0; i < header.biHeight; i++)
			{
				fread(&(*b).image[i*header.biWidth * 4], header.biWidth * 4, 1, Map);
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
		if (header.biHeight < 0)
		{
			for (int i = 0; i < header.biHeight; i++)
			{
				printf("this ran");
				for (int j = 0; j < header.biWidth; j++)
				{
					fread(&(*b).image[(header.biHeight + i)*(-1) * header.biWidth * 4 + j * 4], sizeof(&(*b).image[0]), 1, Map);
					fread(&(*b).image[(header.biHeight + i)*(-1) * header.biWidth * 4 + j * 4 + 1], sizeof(&(*b).image[0]), 1, Map);
					fread(&(*b).image[(header.biHeight + i)*(-1) * header.biWidth * 4 + j * 4 + 2], sizeof(&(*b).image[0]), 1, Map);
					(*b).image[(header.biHeight + i)*(-1)* header.biWidth * 4 + j * 4 + 3] = 0;
				}
			}
		}
		else
		{
			for (int i = 0; i < header.biHeight; i++)
			{
				for (int j = 0; j < header.biWidth; j++)
				{
					fread(&(*b).image[i * header.biWidth * 4 + j * 4], sizeof(&(*b).image[0]), 1, Map);
					fread(&(*b).image[i * header.biWidth * 4 + j * 4 + 1], sizeof(&(*b).image[0]), 1, Map);
					fread(&(*b).image[i * header.biWidth * 4 + j * 4 + 2], sizeof(&(*b).image[0]), 1, Map);
					(*b).image[i * header.biWidth * 4 + j * 4 + 3] = 0;
				}
			}
		}
	}


	// 8. Close the file.
	fclose(Map);
	// 9. Return a pointer to the bitmap.
	return b;
}

