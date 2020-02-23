#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <cstring>
#include <exception>

using namespace std;

int wordCount(char * fileName){
  //open file stream
  ifstream file(fileName);
  string line;
  const char *seperators =
    "\n\r !\"#$%&()*+,-./0123456789:;<=>?@[\\]^_`{|}~";
  
  /* Check if file exists, and loop through each line.
   * break each line into tokens.
  */
  int count = 0;
  if(file && !file.fail()){
    while(getline(file, line)){
      try{
	//convert string to char *
	const char *line_cc = line.c_str();
	char *line_c = new char[strlen(line_cc) + 1]{};
	copy(line_cc, line_cc + strlen(line_cc), line_c);
	
	//split line into tokens
	char *token = (char*)strtok(line_c, seperators);
	while(token != NULL){
	  //count each
	  count++;

	  token = strtok(NULL, seperators);
	}
      } catch(exception& e) {
	//print error if something goes wrong
	cout << "error: " << e.what() << endl;
      }
    }
  } else {
    cout << "file is not valid" << endl;
    return 0;
  }

  file.close();

  return count;
	
}


int main(int argc, char **argv){
  
  //check for command line args
  if(argc != 2){
    cout << "incorrect number of arguments. Exactly 1 required." << endl;
    return 0;
  }

  cout << wordCount(argv[1]) << endl;

}
