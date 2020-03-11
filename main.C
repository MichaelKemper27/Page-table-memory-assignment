#include <unistd.h>
#include <iostream>

#include "pagetable.h"

using namespace std;

char* outputFileName;
char* inputTraceFileName;
int* entryCountSizes;
int entryCountIndex = 0;
bool showLogToPhysTranslation = false;

void parseArguments(int argc, char **argv) {
  int numMemoryRefs = -1;
  int option;
  int flagCount = 0;
  entryCountSizes = new int[argc];
  while ( (option = getopt(argc, argv, "n:p:t")) != -1) {
    switch (option) {
      case 'n': /* Number of addresses to process */
      numMemoryRefs = atoi(optarg);
      flagCount++;
      // optarg will contain the string following -n
      // Process appropriately (e.g. convert to integer atoi(optarg))
      break;
      case 'p': /* produce map of pages */
      // optarg contains name of page file…
      outputFileName = optarg;
      flagCount++;
      break;
      case 't': /* Show address translation */
      // No argument this time, just set a flag
      showLogToPhysTranslation = true;
      break;
      default:
      // print something about the usage and die…
      //exit(BADFLAG); // BADFLAG is an error # defined in a header
      cout << "default called" << endl;
      break;
    }
 //idx = optind;
  }
  cout << "num of args: " << argc << endl;
  
  int flagTotalCounter = flagCount*2 + (int)showLogToPhysTranslation;
  //int flagOffset = 
  //int intCheck;
  if(argc > 1) {
    for(int i = flagTotalCounter+1; i < argc; i++) {
      if (isdigit(argv[i][0])) {
        int argAsInt = atoi(argv[i]);
        entryCountSizes[entryCountIndex] = argAsInt;
        cout << "digit found: " << argAsInt << endl;
        entryCountIndex++;
      } else if(sizeof(argv[i]) > 2 && isalpha(argv[i][0])) {
        inputTraceFileName = argv[i];
        cout << "trace file found: " << argv[i] << endl;

      }
    }
  }
}

int main(int argc, char **argv){
  PAGETABLE *p = new PAGETABLE(3);
  //p->RootNodePtr->callp();
  p->p();
  cout << p->getOffset(0x12345678, 2) << endl;
  p->PageInsert(0x12345678, 0x00000003);
  cout << "last" << endl;

  parseArguments(argc, argv);
}
