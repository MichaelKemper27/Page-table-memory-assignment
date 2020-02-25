#include <iostream>
#include <fstream>
#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <cstring>
#include <exception>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

typedef struct {
long * CurrentStatus;
long InitialValue;
long TerminationValue;
} PROGRESS_STATUS;

long int count = 0;
long int wordCounter = 0;
//long int *countPtr;
PROGRESS_STATUS progStatus;
PROGRESS_STATUS* progStatusPtr = &progStatus;

long int wordCount(char * fileName){
  //open file stream
  ifstream file(fileName);
  string line;
  const char *seperators =
    "\n\r !\"#$%&()*+,-./0123456789:;<=>?@[\\]^_`{|}~";

  /* Check if file exists, and loop through each line.
   * break each line into tokens.
  */
  //int count = 0;
  //cout << "part 1" << endl;
  //countPtr = &count;
  //progStatusPtr = &progStatus;
  if(file && !file.fail()){

    while(getline(file, line)){
      try{
	//convert string to char *
	const char *line_cc = line.c_str();
	char *line_c = new char[strlen(line_cc) + 1]{};
	copy(line_cc, line_cc + strlen(line_cc), line_c);
  int tempLineByteCount = strlen(line_cc) + 1;
  count+=tempLineByteCount;
  //cout << "added this many bytes: " << tempLineByteCount << endl;
	//split line into tokens
	char *token = (char*)strtok(line_c, seperators);

	while(token != NULL){
	  //count each

	  wordCounter++;

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
  //cout << "part 3" << endl;

  file.close();

  return wordCounter;

}
long int hyphenCount = 0;
long int prevHyphenCount = 0;

void* progress_monitor(void *input) {

  while(prevHyphenCount <= hyphenCount) {
 
    long int tempLongInt = count;
    ((PROGRESS_STATUS *)input)->CurrentStatus = &tempLongInt;
    //long int tempCurrStatus = *(progStatus.CurrentStatus);
    //  hyphenCount = (long)((((double)(*(progStatus.CurrentStatus)) / (double)(*progStatusPtr).TerminationValue)) * (double)40);
    hyphenCount = (long)(((double)(*(((PROGRESS_STATUS *)input)->CurrentStatus)) / (double)(((PROGRESS_STATUS *)input)->TerminationValue)) * (double)40);

    for(int i = prevHyphenCount; i < hyphenCount; i++) {
      cout << "-";
      cout.flush();
    }

    prevHyphenCount = hyphenCount;
    if(*((((PROGRESS_STATUS *)input)->CurrentStatus)) >= ((PROGRESS_STATUS *)input)->TerminationValue) {
      cout << endl;
      //cout << hyphenCount << " hypens added. Current status byte amount: " << *(progStatus.CurrentStatus) << endl;
      break;
      //end the loop condition
    }
  }

  pthread_exit(0);
}

int main(int argc, char **argv){

  // progStatus = new PROGRESS_STATUS();
  // progStatusPtr = &progStatus;
// pthread_t threads[NUM_THREADS];
// int thread_args[NUM_THREADS];
// int result_code;
//
// for(unsigned int i = 0; i < NUM_THREADS; ++i) {
//   thread_args[i] = i;
//   result_code = pthread_create(&threads[i], 0, progress_monitor());
// }
  //check for command line args
  if(argc != 2) {
    cout << "incorrect number of arguments. Exactly 1 required." << endl;
    return 0;
  }
  //cout << "part part 1" << endl;
  progStatus.CurrentStatus = &count;
  struct stat buf = {0};
  lstat(argv[1], &buf);
  //printf("number of bytes for this file: %d\n", buf.st_size);
  progStatus.TerminationValue = (long int)buf.st_size;
   //(*progStatusPtr).TerminationValue = (long)1097929;
   (*progStatusPtr).InitialValue = (long)0;
   // cout << "part part 2" << endl;
   //cout << "pre-current status: " << *(progStatusPtr->CurrentStatus);
   //cout << " pre-term value: " << (*progStatusPtr).TerminationValue << endl;

  //progress_monitor(NULL);
  pthread_t tid;

  // pthread_attr_t attr;
  // pthread_aatr_init(&attr);
  int result_code = pthread_create(&tid, 0, progress_monitor, (void *)progStatusPtr);
  long int finalWordCount = wordCount(argv[1]);
  pthread_join(tid, NULL);

  cout << "There are " <<  finalWordCount << " words in " << argv[1] << "." << endl;

  //progress_monitor(progStatusPtr);

  //pthread_join(tid, NULL);
}
