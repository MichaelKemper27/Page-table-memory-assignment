#include "level.h"
#include "pagetable.h"
#include "map.h"
#include <math.h>

using namespace std;

void LEVEL::callp(){
    cout << (*pt).LevelCount << endl;
}

void LEVEL::fillDefault(){
    int size = pow(2, pt->EntryCount[Depth]);

    if(Depth < pt->LevelCount - 1){
        NextLevelPtr = new LEVEL*[size];

        for(int i = 0; i < size; i++){
            NextLevelPtr[i] = nullptr;
           // cout << "level" << endl;
        }
    }
    else {
        MapPtr = new MAP[size];

        for(int i = 0; i < size; i++){
            //cout << "here map" << size << endl;
            MapPtr[i] = MAP();
        }
    }
    cout << "here3" << endl;
}

// void LEVEL::insert(){
//     bool isLeaf = (Level == pt->LevelCount - 1);
//     cout << isLeaf << endl;
//     cout << Level << endl;
//     cout << pt->LevelCount << endl;

//     if(isLeaf){
//         cout << "leaf" << endl;
//     }
//     else {
//         NextLevelPtr[0]->insert();
//     }
// }

