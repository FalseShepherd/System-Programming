#include "ExpandableArray.h"
#include <string.h>

ExpandableArray::ExpandableArray()
{
	maxSize = 16;
	currentIndex = 0;
	theArray = new char*[16];
}
ExpandableArray::ExpandableArray(int InitialSize)
{
	maxSize = InitialSize;
	currentIndex = 0;
	theArray = new char*[InitialSize];
}
ExpandableArray::~ExpandableArray()
{
	delete[] theArray;
}
void ExpandableArray::ExpandArray()
{
	maxSize = maxSize * 2;
	char** temp = new char*[maxSize];
	for (int i = 0; i < maxSize; i++)
	{
		temp[i] = theArray[i];
	}
	theArray = temp;
}
void ExpandableArray::Append(char* element)
{
	if (currentIndex <= maxSize)
	{
		theArray[currentIndex] = element;
		currentIndex++;
	}
	else
	{
		ExpandArray();
		theArray[currentIndex] = element;
		currentIndex++;
	}
}
void ExpandableArray::Sort()
{
	for (int i = 0; i < maxSize; i++)
	{
		for (int j = i; j < maxSize; i++)
		{
			if (strlen(theArray[i]) < strlen(theArray[j]))
			{
				char* temp = theArray[i];
				theArray[i] = theArray[j];
				theArray[j] = temp;
			}
		}
	}
}
int ExpandableArray::length()
{
	return currentIndex;
}
char* ExpandableArray::get(int i)
{
	return theArray[i];
}
