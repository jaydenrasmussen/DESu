#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using std::string;

void createNewDirectory(){
  system("mkdir -p ~/splitFiles");
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
  printf("file size in bytes: %d\n", size);
  fseek(fp, 0, SEEK_SET);
  //calculate split size
  int splitSize = size/numToSplit;
  printf("splitSize: %d\n", splitSize);
  //for each new file
  for(int i = 0; i < numToSplit; i++){
    printf("current file #: %d\n",i);
    //generate new file name
    string filenamestring(filename);
    string newFileName = filePath + filenamestring;
    newFileName += i+'0';
    //find value of i to add
    //printf("%s\n", newFileName);
    FILE *nf;
    //copy data
    for(int j = i * splitSize; j <= ((i+1) * splitSize - 1); j++){
      nf = fopen(newFileName.c_str(), "w");
      printf("   current position: %d\n", j);
      //fseek(fp, j, SEEK_SET);
      int c = fgetc(fp);
      printf("      character adding: %c\n", c);
      //fprintf(nf, c);
      fputc(c, nf);
      //fclose(nf);
    }

    //fclose(nf);
    //push that new file
  }
  fclose(fp);
}

int main(int argc, char * argv[]){
  for(int i = 0; i < argc; i++){
    printf("%s\n",argv[i]);
  }
  //get file name
  int numToSplit = *argv[2] - '0';
  createNewFiles(argv[1], numToSplit);

}
