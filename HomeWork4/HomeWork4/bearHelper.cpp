//
//  bearHelper.cpp
//  FunctionTemplates
//
//  Created by Computer Science on 1/27/16.
//  Copyright (c) 2016 Computer Science. All rights reserved.
//

#include <string>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <unordered_map>
#include <fstream>
#include "bearHelper.h"

/*
 * Counts the number of words in a file named f
 * parameter: file name
 * return: number of words in file
 */
int GetNumEntriesInFile(const char *f)
{
  //1. Open the file for reading
	FILE* b = fopen(f, "r");
	if (fopen == NULL) perror("Error opening file");
	int number=0;
  //2. Count the number of words in file.  Hint: You can count the number of '\n' characters in file. Use fgetc to read one character at a time.
	char a = '0';
	while(a != EOF)
	{
		
		a = fgetc(b);
		if (a == '\n')
		{
			number++;
		}
	}
  //3. close file
	fclose(b);
  //4.return count
	return number;
}


/*
 * Creates an array of strings of size count and populates it with words in file named f
 * parameter: f - file name, count - number of words in file
 * return: An array of c-strings
 */
char **ReadWords(const char *f, int count)
{
  
  //1. Open file for reading
	FILE* a = fopen(f, "r");
	if (a)
	{
		//2. Allocate the array of c-strings
		char **b = new char*[count];
		//3. For each word in the file
		for (int i = 0; i < count; i++)
		{
			long start = ftell(a);
			char d = 'a';
			int sizeofword = 0;
			while (d != '\n')
			{
				d = fgetc(a);
				sizeofword++;
			}
			fseek(a, start, 0);
			b[i] = new char[sizeofword];
			fread(b[i], sizeof(char), sizeofword, a);
			b[i][sizeofword-1 ] = '\0';
			//3.a Determine the length of word
			//   (hint: use ftell to determine the location of the pointer in file before you start counting the letters, use fgetc to read a single character, then fseek to the location of the start of the word and read it).
			//3.b Allocate a string long enough to store word
			//3.c store word in array of words

		}
		//4. close file
		fclose(a);
		//5. return array of words
		return b;
	}
	else
	{
		std::cout << "error reading";
		return 0;
	}
}



/*
 * Returns true if all letters in "letters" are in group of letters "group" (duplicates should be accounted for)
 * therefore the letters: "ee" are in group "tree" but not in group "tea"
 *
 * parameter: letters - list of letters, group - a collection of letter
 * return: true of all letters are in set
 */
bool AllLettersInSet(const char *letters, const char *group)
{
	int a[26];
	int b[26];
	for (int i = 0; i < 26; i++)
	{
		a[i] = 0;
		b[i] = 0;
	}
	for (int i = 0; i < strlen(letters); i++)
	{
		a[tolower(letters[i])-'a']++;
	}
	for (int i = 0; i < strlen(group); i++)
	{
		b[tolower(group[i])-'a']++;
	}
	for (int i = 0; i < 26; i++)
	{
			if (a[i] > b[i])
			{
			return false;
			}
	}
	return true;

	
  
}

