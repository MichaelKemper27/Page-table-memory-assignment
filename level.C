#include "level.h"
#include "pagetable.h"
#include <math.h>

using namespace std;

void LEVEL::callp(){
    cout << (*pt).LevelCount << endl;
}

void LEVEL::fillNextLevel(){
    int size = pow(2, pt->EntryCount[level]);
    NextLevelPtr = new LEVEL*[256];

    for(int i = 0; i < 256; i++){
        NextLevelPtr[i] = nullptr;
    }
}