// Student: Kemper, Michael
// RedID: 822 86 7065

#include "dictionary.h"

using namespace std;

/*
 * Small C++ program that takes in two files, one a text and another a dictionary text file, to be checked for correctness.
 * if the word has characters outside a-z, A-Z, or ', then BADCHARS enum will be returned'.
 */
int main(int argc, char* argv[])
{
	//Ensures there are the 3 arguments passed in, one main executable call and two string arguments.
  if(argc == 3) {
    ifstream file(argv[2]);
    string str;
		//sets the seperators to be removed by strtok
    const char *separators = "\n\r !\"#$%&()*+,-./0123456789:;<=>?@[\\]^_`{|}~";
    while (std::getline(file, str))
    {
      const char* constCharStr = str.c_str();
      char *charStr = new char[strlen(constCharStr)+1];
      strcpy(charStr, constCharStr);
      char *token = (char*)strtok(charStr, separators);

      while (token != NULL)
      {
      const char *newToken = token;
			//inserts each valid token into the dictionary
      dictRoot->insert(newToken, newToken);
      token = strtok(NULL, separators);
      }
    }

    ifstream file2(argv[1]);
    string str2;
    while (std::getline(file2, str2))
    {
      const char* constCharStr = str2.c_str();
      char *charStr = new char[strlen(constCharStr)+1];
      strcpy(charStr, constCharStr);
      char *token = (char*)strtok(charStr, separators);

      while (token != NULL)
      {
      const char *newToken = token;
			//tries to find each valid token in the dictionary, and if it doesn't, it outputs it to cout
      dictRoot->find(newToken, newToken);
      token = strtok(NULL, separators);
      }
    }
  } else {
    cout << "Incorrect command line arguments. Supply two filepath\'s as strings in order for this program to work correctly.";
  }
    return 0;
};
