#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <dirent.h>
#include "newDir.h"

bool showDebug = true;
/*
to reassemble:
create final file
loop through file parts
take out all of each file and place into new file
delete old files
*/
void reassemble(char directory[], char fileName[]){
  if(showDebug)
    printf("executed reassemble\n");
  DIR *fileDir;
  struct dirent *epdf;
  fileDir = opendir(directory);
  if(showDebug)
    printf("opened directory!\n");
  int currFile = 0;
  while ((epdf = readdir(fileDir)) != NULL){
    if(showDebug)
      printf("at file #: %i\n", currFile);
    string tempFileName = epdf->d_name;
    if(tempFileName[0] != '.'){
      currFile++;
    }
  }
  closedir(fileDir);
  if(showDebug)
    printf("number of parts: %i\n", currFile);

  //loop for all files
  FILE *ff;
  ff = fopen(fileName, "w");
  if(showDebug)
    printf("opened output file\n");
  for(int i = 0; i < currFile; i++){
    if(showDebug)
      printf("adding file #: %i\n", i);

    FILE *nf;

    string currFileStr = directory;
    currFileStr += "/";
    currFileStr += std::to_string(i);
    if(showDebug)
      printf("current file: %s\n", currFileStr.c_str());
    nf = fopen(currFileStr.c_str(), "r");
    fseek(nf, 0, SEEK_END);
    int size = ftell(nf);
    for(int j = 0; j < size; j++){
      fseek(nf, j, SEEK_SET);
      int c = fgetc(nf);
      if(showDebug)
        printf("character: %d\n", c);
      fseek(ff, 0, SEEK_END);
      fputc(c, ff);
    }

    //fclose(nf);
  }
  //fclose(ff);
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
