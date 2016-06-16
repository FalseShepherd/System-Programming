/*
 *  main.cpp
 *  HW 3
 */

#include <iostream>
#include "BitMap.h"

int main(int argc, const char * argv[])
{
	/* This code tests your bitmap implementation on 24-bit and 32-bit files. The desired output
	 * files are included for comparison purposes.
	 */
	
	
	/** Test #1: Create a new file with a gradient from yellow to green to cyan (bottom to top) */
	//parameterized  constructor
	BitMap *bm = new BitMap(255, 255);
	//bm->Load("picture.bmp");

	for (int x = 0; x < 255; x++)
	{
		for (int y = 0; y < 255; y++)
		{
			//std::cout << "x: " << x << "y: " << y << std::endl;
			bm->SetPixel(bm, x, y, 255-y, 255, y, 255);
		}
	}
	
	/** copy constructor*/
	BitMap *a = new BitMap(*bm);
	/** assignment Operator*/
	*a = *a;
	std::cout << "Get Height function: " << a->GetHeight() << "\n";
	std::cout << "Get Width function: " << a->GetWidth() << "\n";
	/** Destructor*/
	bm->~BitMap();

	/*std::cout << "processing test.bmp\n";
	bm->Save(bm, "test.bmp");*/
	///* test #2: a 24-bit file with reversed height; add a 40x40 red square in the lower right corner */
	//std::cout << "processing picture.bmp\n";
	//bm = bm->Load("picture.bmp");
	//if (bm == 0)
	//{
	//	std::cout << "load of 'picture.bmp' failed\n";
	//}
	//else {
	//	for (int x = 0; x < 40; x++)
	//	{
	//		for (int y = 0; y < 40; y++)
	//		{
	//			bm->SetPixel(bm, (bm->GetWidth())-x-1, y, 255, 0, 0, 255);
	//		}
	//	}
	//	bm->Save(bm, "picture new.bmp");
	//	free(bm);
	//}

	///** test #3: a 24-bit file; add a 40x40 blue square in the upper right corner */
	//std::cout << "processing train.bmp\n";
	//bm = bm->Load("train.bmp");
	//if (bm == 0)
	//{
	//	std::cout << "load of 'train.bmp' failed\n";
	//}
	//else {
	//	for (int x = 0; x < 40; x++)
	//	{
	//		for (int y = 0; y < 40; y++)
	//		{
	//			bm->SetPixel(bm, bm->GetWidth()-x-1, bm->GetHeight()-y-1, 0, 0, 255, 255);
	//		}
	//	}
	//	bm->Save(bm, "train new.bmp");
	//	free(bm);
	//}

	///** test #4: a 24-bit file with padding; add a 40x40 blue square in the upper right corner */
	//std::cout << "processing mountain.bmp\n";
	//bm = bm->Load("mountain.bmp");
	//if (bm == 0)
	//{
	//	std::cout << "load of 'mountain.bmp' failed\n";
	//}
	//else {
	//	// convert to grayscale
	//	for (int x = 0; x < bm->GetWidth(); x++)
	//	{
	//		for (int y = 0; y < bm->GetHeight(); y++)
	//		{
	//			uint8_t r, g, b, a;
	//			bm->GetPixel(bm, x, y, r, g, b, a);
	//			uint8_t average = (r+g+b)/3;
	//			bm->SetPixel(bm, x, y, average, average, average, a);
	//		}
	//	}
	//	bm->Save(bm, "mountain new.bmp");
	//	free(bm);
	//}

	///** test #4: a 32-bit file with reversed height; extract the green channel */
	//std::cout << "processing canmore.bmp\n";
	//bm = bm->Load("canmore.bmp");
	//if (bm == 0)
	//{
	//	std::cout << "load of 'canmore.bmp' failed\n";
	//}
	//else {
	//	for (int x = 0; x < bm->GetWidth(); x++)
	//	{
	//		for (int y = 0; y < bm->GetHeight(); y++)
	//		{
	//			uint8_t r, g, b, a;
	//			bm->GetPixel(bm, x, y, r, g, b, a);
	//			bm->SetPixel(bm, x, y, 0, g, 0, a);
	//		}
	//	}
	//	bm->Save(bm, "canmore new.bmp");
	//	free(bm);
	//}
	//
	
	return 0;
}
