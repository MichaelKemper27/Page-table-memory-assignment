#include "level.h"
#include "pagetable.h"
#include "map.h"
#include <math.h>

using namespace std;

void LEVEL::callp(){
    cout << (*pt).LevelCount << endl;
}

void LEVEL::fillDefault(){
    int size = pow(2, pt->EntryCount[level]);

    if(level == pt->LevelCount){
        NextLevelPtr = new LEVEL*[256];

        for(int i = 0; i < 256; i++){
            NextLevelPtr[i] = nullptr;
        }
    }
    else {
        MapPtr = new MAP[size];

        for(int i = 0; i < 256; i++){
            MapPtr[i] = MAP();
        }
    }
}

