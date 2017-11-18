#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>

using std::string;

void createNewDirectory(char filename[]){
  string pathP1 = "mkdir -p ";
  string fullPath = pathP1 + filename + "/";
  //fullPath += filename;
  system(fullPath.c_str());
}
