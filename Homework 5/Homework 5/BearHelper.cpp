#include <string>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <unordered_map>
#include <fstream>
#include "BearHelper.h"

#include "ExpandableArray.h"

//This method constructs BearHelper object by reading the file f into the dictionary string
BearHelper::BearHelper(const char *f)
{
  //Open the file for reading
	FILE* a = fopen(f, "r");
  //Determine the number of characters in file.  Hint: you can use fseek and ftell.
	char b = NULL;
	size = 0;
	while (b != EOF)
	{
		b = getc(a);
		size++;
	}
  //Allocate a string large enough for the entire dictionary.
	theDictionary = new char[size];
  //Read the entire file into the string allocated
	fread(theDictionary, 1, size, a);
  //Replace every \n character with a null character.
	for (int i = 0; i < size; i++)
	{
		if (theDictionary[i] == '\n')
		{
			theDictionary[i] = '\0';
		}
	}
}


//Destructor for the BearHelper to free the memory used by dictionary
BearHelper::~BearHelper()
{
  //Destroy any memory allocated on heap and set pointer to null
}



/*
 * Returns true if all letters in "letters" are in group of letters "group" (duplicates should be accounted for)
 * therefore the letters: "ee" are in group "tree" but not in group "tea"
 *
 * parameter: letters - list of letters, group - a collection of letter
 * return: true of all letters are in set
 */
bool BearHelper::AllLettersInSet(const char *letters, char *set)
{
	int l[26];
	int s[26];
	for (int x = 0; x < 26; x++)
		l[x] = s[x] = 0;
	
	for (const char *t = letters; *t < strlen(letters); t++)
	{
		l[tolower(*t)-97]++;
	}
	for (const char *b = set; *b < strlen(set); b++)
	{
		s[tolower(*b)-97]++;
	}
	for (int x = 0; x < 26; x++)
		if (l[x] > s[x])
			return false;
	return true;
 
}


//Print all words that satisfy the condition: All characters in required must be in word and all letters in word must be in available
//The words are printed in order of length from longest to shortest.  
void BearHelper::GetAllWords(const char* required, const char* available)
{
	ExpandableArray a = ExpandableArray(size);
  //Go in order through the dictionary.
	for (int i = 0; i < sizeof(theDictionary); i++)
	{
		if (AllLettersInSet(required, theDictionary))
		{
			a.Append(theDictionary);
		}
	}
	a.Sort();
	for (int i = 0; i < size; i++)
	{
		printf(a.get(i));
	}
  //Check if each word matches.
  
  //If it does, add it to the expandable set.
  
  //Sort the expandable set.
  
  //Print the expandable set.
}


