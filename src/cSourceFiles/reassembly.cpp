#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <dirent.h>
#include "newDir.h"

/*
to reassemble:
create final file
loop through file parts
take out all of each file and place into new file
delete old files
*/
void reassemble(char directory[], char fileName[]){
  DIR *fileDir;
  struct dirent *epdf;
  fileDir = opendir(directory);
  int currFile = 0;
  while ((epdf = readdir(fileDir)) != NULL){
      //printf("%s\n",epdf->d_name);
      //string tempFileName = "./";
    string tempFileName = epdf->d_name;
      //printf("%s\n", tempFileName.c_str());
    string currFileNum = std::to_string(currFile);
    string fileNum;
    int strPos = 0;
    while(currFileNum[strPos] != '%'){
      fileNum += tempFileName[strPos];
      strPos++;
    }
    if(currFileNum != fileNum)
      continue;
    if(tempFileName[0] == '.')
      continue;

    string tempFileNameFull = directory;
    tempFileNameFull += "/";
    tempFileNameFull += tempFileName;
    printf("Copying from %s\n", tempFileNameFull.c_str());
    FILE *fp = fopen(tempFileNameFull.c_str(), "r");
    if(fp != NULL){
        //printf("got here\n");
      fseek(fp, 0, SEEK_END);
      unsigned int size = ftell(fp);
      fseek(fp, 0, SEEK_SET);
      FILE *ff = fopen(fileName, "w");
          //fseek(ff, 0, SEEK_END);

      for(int i = 0; i < size; i++){
        fseek(fp, i, SEEK_SET);
        int c = fgetc(fp);
        fseek(ff, 0, SEEK_END);
        fputc(c, ff);
      }
      fclose(fp);
      fclose(ff);
    }
  }
  currFile += 1;
}


/*
usage:
argv[0] --./reassembly
argv[1] --directory holding files to assemble
argv[2] --name of final file
*/
int main(int argc, char * argv[]){
  if(argc != 3){
    std::cout << "Needs more arguments" << std::endl;
    return -1;
  }
  reassemble(argv[1], argv[2]);
}
