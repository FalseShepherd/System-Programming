#//
//  main.cpp
//  Lab3
//
//  Created by Nathan Sturtevant on 1/11/16.
//  Copyright © 2016 AI For Traditional Games. All rights reserved.
//

#include <iostream>
#include <cassert>
#include "voxel.h"

/*
Function that extracts and returns bits from input as follows:
You extract bits starting from the location "first" (starting from least significant bit) and take the bit at every "step".
For example if input is 10110111, first is 0 and step is 2
then the program returns 0111 because it started at 1 and skipped every other bit.
*/
uint32_t ExtractBits(uint32_t input, int first, int step)
{
	if (first > 30)
	{
		return 0;
	}
	return (input & (1 << first)) + ExtractBits(input, first + step, step);
}

//Return the x value encoded in the morton code
uint32_t DecodeMorton3X(uint32_t code)
{
	return ExtractBits(code, 0, 3);
}

//Return the y value encoded in the morton code
uint32_t DecodeMorton3Y(uint32_t code)
{
	return ExtractBits(code, 1, 3);
}

//Return the z value encoded in the morton code
uint32_t DecodeMorton3Z(uint32_t code)
{
	return ExtractBits(code, 2, 3);

}

/*
Function used to perform Morton encoding.  This will set the bits of the result using bits from input skipping every step.
*/
uint32_t SpreadBits(uint32_t input, int step)
{
	uint32_t value;
	for (int i = 0; i < 10; i = i + 1)
	{
		value += (((input << i) & 1) << i*step);
	}
	return value;
}

//Encode morton value from x, y, z data
//Only take 10 bits from each coordinate.
uint32_t EncodeMorton3D(uint32_t x, uint32_t y, uint32_t z)
{
	uint32_t result;
	result = SpreadBits(x, 3) | (SpreadBits(y, 3) << 1) | (SpreadBits(z, 3) << 2);
	return result;
}

//This function tests whether the decoding and encoding work
//Take the
void TestMorton3D()
{
	std::cout << "Start Test!\n";
	for (int x = 0; x < 1024; x += 3)
	{
		for (int y = 0; y < 1024; y += 3)
		{
			for (int z = 0; z < 1024; z += 3)
			{
				uint32_t value = EncodeMorton3D(x, y, z);
				assert(DecodeMorton3X(value) == x);
				assert(DecodeMorton3Y(value) == y);
				assert(DecodeMorton3Z(value) == z);
			}
		}
	}
	std::cout << "Test Passed!\n";
}
int main(int argc, const char * argv[])
{
	TestMorton3D();
	ImportAndExportVoxelMap("Simple_test3dnav.3dnav", "simple.txt");
	ImportAndExportVoxelMap("Complex_test3dnav.3dnav", "complex.txt");
	return 0;
}