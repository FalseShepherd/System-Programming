//
//  main.cpp
//  HW4
//
//  Created by Nathan Sturtevant on 1/26/16.
//  Copyright © 2016 Systems Programming. All rights reserved.
//

#include <string>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <unordered_map>
#include <fstream>

#include "BearHelper.h"

int main(int argc, char **argv)
{
	std::string required, available;
	
	const char *file = "Dictionary.txt";
  
	BearHelper bh(file);
	
	while (true)
	{
		std::cout << "Enter required letters: ";
		std::cin >> required;
		std::cout << "Enter available letters: ";
		std::cin >> available;
		bh.GetAllWords(required.c_str(), available.c_str());
	}

  return 0;
}



