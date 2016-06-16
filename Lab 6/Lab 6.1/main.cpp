//
//  main.cpp
//  FileIO
//
//  Created by Computer Science on 1/19/16.
//  Copyright (c) 2016 Computer Science. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <cstdint>

#include "PackedArray.h"
#include "TestLab5.h"


int main(int argc, const char * argv[])
{
  // Run tests with various size PackedArray
  std::cout << "Tests running.\n";
  TestLab5(4);
  
  TestLab5(6);
  
  TestLab5(2);
  
  TestLab5(64);
  
  TestLab5(32);
  
  TestLab5(33);
  
  TestLab5(1001);
  
  std::cout << "Testing complete.\n";
}
