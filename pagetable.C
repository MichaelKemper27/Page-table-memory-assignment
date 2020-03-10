#include "pagetable.h"

using namespace std;

void PAGETABLE::p(){
    BitmaskAry[0] = 1;
    BitmaskAry[1] = 2;
    BitmaskAry[2] = 33;

    for(int i = 0; i < LevelCount; i++){
        cout << BitmaskAry[i] << endl;
    }
}


