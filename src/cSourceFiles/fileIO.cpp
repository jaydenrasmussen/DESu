#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>

using std::string;

bool showDebug = false;

void createNewDirectory(){
  system("mkdir -p /splitFiles");
}

void createNewFiles(char filename[], int numToSplit){
  //directory management
  createNewDirectory();
  string filePath = "~/splitFiles";

  //access the file
  FILE *fp = fopen(filename, "r");
  //go to the end, get the size, return to beginning
  fseek(fp, 0, SEEK_END);
  int size = ftell(fp);
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
    string filenamestring(filename);
    string newFileName = filenamestring;
    newFileName += i+'0';
    FILE *nf;
    //copy data
    nf = fopen(newFileName.c_str(), "w");
    for(int j = i * splitSize; j <= ((i+1) * splitSize - 1); j++){
      if(showDebug)
        printf("   current position: %d\n", j);
      fseek(fp, j, SEEK_SET);
      int c = fgetc(fp);
      fputc(c, nf);
      if(showDebug)
        printf("      character adding: %c\n", c);
    }
    fclose(nf);
  }
  fclose(fp);
}

int main(int argc, char * argv[]){
  if(showDebug){
    for(int i = 0; i < argc; i++){
      printf("%s\n",argv[i]);
    }
  }
  //get file name
  int numToSplit = *argv[2] - '0';
  createNewFiles(argv[1], numToSplit);
}
