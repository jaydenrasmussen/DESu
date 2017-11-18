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
  //printf("executed reassemble\n");
  DIR *fileDir;
  struct dirent *epdf;
  fileDir = opendir(directory);
  //printf("opened directory!\n");
  int currFile = 0;
  while ((epdf = readdir(fileDir)) != NULL){
    //printf("at file #: %i\n", currFile);
    string tempFileName = epdf->d_name;
    if(tempFileName[0] != '.'){
      currFile++;
    }
  }
  closedir(fileDir);
  //printf("number of parts: %i\n", currFile);

  //loop for all files
  FILE *ff;
  ff = fopen(fileName, "w");
  //printf("opened output file\n");
  for(int i = 0; i < currFile; i++){
    //printf("adding file #: %i\n", i);

    FILE *nf;

    string currFileStr = directory;
    currFileStr += "/";
    currFileStr += std::to_string(i);
    //printf("current file: %s\n", currFileStr.c_str());
    nf = fopen(currFileStr.c_str(), "r");
    fseek(nf, 0, SEEK_END);
    int size = ftell(nf);
    for(int j = 0; j < size; j++){
      fseek(nf, j, SEEK_SET);
      int c = fgetc(nf);
      //printf("character: %s\n", c);
      fseek(ff, 0, SEEK_END);
      fputc(c, ff);
    }

    //fclose(nf);
  }
  //fclose(ff);
}


/*
    printf("current file: %i", currFile);
      //printf("%s\n",epdf->d_name);
      //string tempFileName = "./";
    string tempFileName = epdf->d_name;
      //printf("%s\n", tempFileName.c_str());
    string currFileNum = std::to_string(currFile);
    if(currFileNum != tempFileName)
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
*/

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
