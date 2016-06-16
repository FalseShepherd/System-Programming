/*
 *  BitMap.cpp
 *  HW 3
 */

#include "BitMap.h"
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <thread>


BitMap::BitMap(int w, int h):width(w), height(h)
{
  image = new uint8_t[width*height*4];
}

BitMap::BitMap(const char* file)
{
  bool loadFailed = false;
  FILE *f = fopen(file, "rb+");
  BitMapHeader header;
  
  if (f == 0)
  {
    std::cout << "Unable to find file\n";
    loadFailed = true;
  }
  else
  {
    uint16_t bfType;
    fread(&bfType, sizeof(bfType), 1, f);
    if (bfType != 19778)
    {
      std::cout << "Unable to load file properly\n";
      fclose(f);
      loadFailed = true;
    }
    else
    {
      fread(&header, sizeof(BitMapHeader), 1, f);
      if (header.biBitCount < 24)
      {
        std::cout << "We only support 24 & 32-bit files\n";
        fclose(f);
        loadFailed = true;
      }
      else
      {
        std::cout << ":" << header.biBitCount << "bit image\n";
        
        if (header.biCompression != 0)
        {
          std::cout << "We don't support compressed files\n";
          fclose(f);
          loadFailed = true;
        }
        else
        {
          int signedHeight = header.biHeight;
          bool reverseHeight = false;
          if (signedHeight < 0)
          {
            std::cout << ":height reversed\n";
            height = -signedHeight;
            reverseHeight = true;
		  }
		  else {
			  height = signedHeight;
		  }
          
          width = header.biWidth;
          image = new uint8_t[height*width*4];
          
          fseek(f, header.bfOffBits, SEEK_SET);
          
          if (header.biBitCount == 32)
          {
            for (int x = 0; x < height; x++)
            {
              if (reverseHeight)
                fread(&image[(height-x-1)*width*4], sizeof(char), width*4, f);
              else
                fread(&image[x*width*4], sizeof(char), width*4, f);
            }
          }
          else if (header.biBitCount == 24)
          {
            bool padding = false;
            for (int x = 0; x < height; x++)
            {
              int bytesRead = 0;
              for (int y = 0; y < width; y++)
              {
                if (reverseHeight)
                  bytesRead += fread(&image[(height-x-1)*width*4+y*4], sizeof(char), 3, f);
                else
                  bytesRead += fread(&image[x*width*4+y*4], sizeof(char), 3, f);
                image[x*width*4+y*4+3] = 0;
              }
              while (0 != bytesRead%4)
              {
                char zero[4] = {0, 0, 0, 0};
                bytesRead += fread(zero, sizeof(char), 1, f);
                padding = true;
              }
            }
            if (padding)
              std::cout << ":padding necessary\n";
          }
          fclose(f);
        }
      }
    }
  }
  
  if(loadFailed)
  {
    width = 10;
    height = 10;
    image = new uint8_t[width*height*4];
    for(int i=0; i < width*height*4; i++)
    {
      image[i] = 255;
    }
  }

  
}

BitMap::BitMap(const BitMap& b):width(b.width), height(b.height)
{
  image = new uint8_t[width*height*4];
  
  for(int i=0; i < width*height*4; i++)
  {
    image[i] = b.image[i];
  }
}

BitMap::~BitMap()
{
  width = 0;
  height = 0;
  if(image)
  {
    delete[] image;
    image = NULL;
  }
}

BitMap& BitMap::operator=(const BitMap& b)
{
  if(this == &b)
    return *this;
  
  width = b.width;
  height = b.height;
  
  delete[] image;
  image = new uint8_t[width*height*4];
  
  for(int i=0; i < width*height*4; i++)
  {
    image[i] = b.image[i];
  }
  
  return *this;
}

void BitMap::Save(const char *file)
{
  FILE *f = fopen(file, "wb+");
  
  if (f == 0)
    return;
  
  BitMapHeader header;
  header.biWidth = width;
  header.biHeight = height;
  
  header.bfSize = sizeof(BitMapHeader)+2+(width)*height*4;
  header.biSizeImage = (width)*height*4;
  uint16_t bfType = 19778; // 0x4D42
  fwrite(&bfType, sizeof(bfType), 1, f);
  fwrite(&header, sizeof(header), 1, f);
  for (int x = 0; x < height; x++)
  {
    fwrite(&image[x*width*4], sizeof(char), width*4, f);
  }
  fclose(f);
}


void BitMap::SetPixel(int x, int y, uint8_t redByte, uint8_t greenByte, uint8_t blueByte, uint8_t alphaByte )
{
  // BGRA
  image[y*width*4+x*4+0] = blueByte;
  image[y*width*4+x*4+1] = greenByte;
  image[y*width*4+x*4+2] = redByte;
  image[y*width*4+x*4+3] = alphaByte;
}

void BitMap::GetPixel(int x, int y, uint8_t &redByte, uint8_t &greenByte, uint8_t &blueByte, uint8_t &alphaByte) const
{
  blueByte = image[y*width*4+x*4+0];
  greenByte = image[y*width*4+x*4+1];
  redByte = image[y*width*4+x*4+2];
  alphaByte = image[y*width*4+x*4+3];
}


BitMap* BitMap::DetectEdges(int threadCount) const
{
	BitMap *edge = new BitMap(this->width, this->height);
	int work = (this->height)*(this->width) / threadCount;
	std::thread **threads = new std::thread*[threadCount];
	for (int i = 0; i < threadCount; i++)
	{
		int work = ((this->height)*(this->width) / threadCount)*i;
		int workend = ((this->height)*(this->width) / threadCount)*(i+1);
	/*	if (workend >= this->height*this->width)
		{
			workend = this->height*this->width-1;
		}*/
		threads[i] = new std::thread(&BitMap::DetectEdge, *this, work, workend , edge);
	}
	for (int x = 0; x < threadCount; x++)
	{
		threads[x]->join();
		delete threads[x];
	}
	delete[] threads;
	return edge;

}

BitMap* BitMap::DetectEdge(int beginning, int end, BitMap *edge)
{
	for (int i = beginning; i < end; i++)
	{
		if (int(i - this->width) <= 0 ||i + this->width >= (edge->height*edge->width) || i%this->width == 0 || i%this->width == width-1)
		{
			//do nothing
		}
		else
		{
			uint8_t green;
			uint8_t red;
			uint8_t blue;
			uint8_t bleh;
			int Vx = 0;
			int Vy = 0;
			//Compute Vx by applying the Vertical Mask
			this->GetPixel((i%this->width) -1, ((i - i%this->width) / this->width)-1, red, green, blue, bleh);
			Vx += -(blue + green + red) / 3;
			this->GetPixel((i%this->width) - 1, ((i - i%this->width) / this->width), red, green, blue, bleh);
			Vx += -(blue + green + red) / 3;
			this->GetPixel((i%this->width) - 1, ((i - i%this->width) / this->width)+1, red, green, blue, bleh);
			Vx += -(blue + green + red) / 3;
			this->GetPixel((i%this->width) + 1, ((i - i%this->width) / this->width) - 1, red, green, blue, bleh);
			Vx += (blue + green + red) / 3;
			this->GetPixel((i%this->width) + 1, ((i - i%this->width) / this->width), red, green, blue, bleh);
			Vx += (blue + green + red) / 3;
			this->GetPixel((i%this->width) + 1, ((i - i%this->width) / this->width) + 1, red, green, blue, bleh);
			Vx += (blue + green + red) / 3;
			//Compute Vx by applying the Vertical Mask
			this->GetPixel((i%this->width) - 1, ((i - i%this->width) / this->width) - 1, red, green, blue, bleh);
			Vy += -(blue + green + red) / 3;
			this->GetPixel((i%this->width), ((i - i%this->width) / this->width) -1, red, green, blue, bleh);
			Vy += -(blue + green + red) / 3;
			this->GetPixel((i%this->width) + 1, ((i - i%this->width) / this->width) - 1, red, green, blue, bleh);
			Vy += -(blue + green + red) / 3;
			this->GetPixel((i%this->width) - 1, ((i - i%this->width) / this->width) + 1, red, green, blue, bleh);
			Vy += (blue + green + red) / 3;
			this->GetPixel((i%this->width), ((i - i%this->width) / this->width) + 1, red, green, blue, bleh);
			Vy += (blue + green + red) / 3;
			this->GetPixel((i%this->width) + 1, ((i - i%this->width) / this->width) + 1, red, green, blue, bleh);
			Vy += (blue + green + red) / 3;
			int grey = 255-sqrt(pow(Vx, 2) + pow(Vy, 2));
			edge->SetPixel((i%this->width), ((i - i%this->width) / this->width), uint8_t(grey), uint8_t(grey), uint8_t(grey), 0);
		}
	}
	return edge;
}


