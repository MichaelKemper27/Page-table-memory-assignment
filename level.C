#include "level.h"
#include "pagetable.h"
#include "map.h"
#include <math.h>

using namespace std;

//fill NextLevelPtr with nullptrs and if leaf, fill MapPtr with invalid maps
void LEVEL::fillDefault(){
    int size = pow(2, pt->EntryCount[Depth]);

    if(Depth < pt->LevelCount - 1){
        NextLevelPtr = new LEVEL*[size];

        for(int i = 0; i < size; i++){
            NextLevelPtr[i] = nullptr;
        }
    }
    else {
        MapPtr = new MAP[size];

        for(int i = 0; i < size; i++){
            MapPtr[i] = MAP();
        }
    }
}

