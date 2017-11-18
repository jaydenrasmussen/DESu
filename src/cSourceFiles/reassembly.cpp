#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>

/*
to reassemble:
create final file
loop through file parts
take out all of each file and place into new file
delete old files
*/

/*
usage:
argv[0] --./reassembly
argv[1] --directory holding files to assemble
argv[2] --number of files total!!!The program may be able to figure this out
argv[3] --name of final file
*/
int main(int argc, char * argv[]){
  if(argc != 4){
    std::cout << "Needs more arguments" << std::endl;
    return -1;
  }

}
