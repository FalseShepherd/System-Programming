//
//  PackedArray.cpp
//  Lab 5
//

#include <iostream>

#include "PackedArray.h"

PackedArray CreateArray(int aSize)
{
	PackedArray a;
	a.numRows = aSize;
	a.rows = new uint64_t[aSize];
	for (int i = 0; i < aSize; i++)
	{
		a.rows[i] = 0;
	}
	return a;
};

// Frees memory for the array
void FreeArray(PackedArray &array)
{
	delete[]array.rows;
	array.rows = NULL;
	array.numRows = 0;

}

// Sets all entries in the array to the value parameter
void FillArray(PackedArray &array, uint64_t value)
{
	for (int i = 0; i < array.numRows; i++)
	{
		array.rows[i] = value;
	}
}
// Clears all entries to 0 in the array
void ClearArray(PackedArray &array)
{
	for (int i = 0; i < array.numRows; i++)
	{
		array.rows[i] = 0;
	}
}

// Get the value of the entry at the specified row and col.
// If row or col are outside of the range for this PackedArray,
// returns 0.
int GetEntry(const PackedArray &array, int row, int col)
{
	return array.rows[row] & (3 << (64 - (col * 2)));
}
// Sets entry in the location row, col to the specified value.
// If row or col are outside of the range for this PackedArray,
// function has no effect.
void SetEntry(PackedArray &array, int row, int col, uint64_t value)
{
	if (row >= array.numRows | col >31)
	{
	}
	else
	{
		array.rows[row] = array.rows[row] & ~(3 << (64 - (col * 2)));
		array.rows[row] = array.rows[row] & ((value & 3) << (64 - (col * 2)));
	}
}

// Sum all the entries in the array
int SumEntries(const PackedArray &array)
{
	int sum = 0;
	for (int i = 0; i < array.numRows; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			sum = sum + GetEntry(array, i, j);
		}
	}
	return sum;
}