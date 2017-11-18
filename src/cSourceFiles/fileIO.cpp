#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include "newDir.h"

using std::string;

bool showDebug = true;

void createNewFiles(char filename[], int numToSplit, char newDirName[]){
  //create a new directory for the split up files
  createNewDirectory(newDirName);

  //access the to be split file
  FILE *fp = fopen(filename, "r");
  //go to the end, get the size, return to beginning
  fseek(fp, 0, SEEK_END);
  unsigned int size = ftell(fp);
  if(showDebug)
    printf("file size in bytes: %d\n", size);
  fseek(fp, 0, SEEK_SET);
  //calculate split size
  int splitSize = size/numToSplit;
  if(showDebug)
    printf("splitSize: %d\n", splitSize);
  //for each new file
  for(int i = 0; i < numToSplit; i++){
    if(showDebug)
      printf("current file #: %d\n",i);
    //generate a string of the form newDirName/newFileNamei.part
    char fileNumChars[12];
    sprintf(fileNumChars, "%d", i);
    string fileNum(fileNumChars);
    string filenamestring(filename);
    string newFileName = newDirName;
    newFileName += "/";
    newFileName += newDirName;
    newFileName += ".";
    newFileName += fileNum;
    if(showDebug)
      std::cout << newFileName << std::endl;
    //this is the new file
    FILE *nf;
    //copy data
    //open the new file for writing
    nf = fopen(newFileName.c_str(), "w");
    //loop through files part
    //i * splitSize gives start location, i+1 * splitSize -1 gives the start of the next but one before
    for(int j = i * splitSize; j <= ((i+1) * splitSize - 1); j++){
      if(showDebug)
        printf("   current position: %d\n", j);
      //possibly redundant, fgetc may move the character being read
      fseek(fp, j, SEEK_SET);
      //next character
      int c = fgetc(fp);
      //place character in new file
      fputc(c, nf);
      if(showDebug)
        printf("      character adding: %c\n", c);
    }
    //close the new file after each is done
    fclose(nf);
  }
  //close copied file now that we are done
  fclose(fp);
}

/*
argv[0] --./fileIO
argv[1] --fileLocation
argv[2] --number of files to split into
argv[3] --desired name of new directory
*/
int main(int argc, char * argv[]){
  if(argc != 4){
    std::cout << "usage: ./fileIO fileLocation #filesToSplit newDirectory" << std::endl;
    return -1;
  }
  if(showDebug){
    for(int i = 0; i < argc; i++){
      printf("%s\n",argv[i]);
    }
  }
  //get file name
  int numToSplit = atoi(argv[2]);
  if(numToSplit > 65535){
    printf("You don't need that many splits\n");
    return -1;
  }
  createNewFiles(argv[1], numToSplit, argv[3]);
  return 0;
}
