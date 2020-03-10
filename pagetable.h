#ifndef PAGETABLE_H
#define PAGETABLE_H

#include <iostream>
#include "level.h"
//class LEVEL;

using namespace std;

class PAGETABLE {
    public:
        int LevelCount;
        int *BitmaskAry;
        int *ShiftAry;
        int *EntryCount;

        LEVEL *RootNodePtr;

        PAGETABLE(int n){
            LevelCount = n;
            BitmaskAry = new int[n];
            ShiftAry = new int[n];
            EntryCount = new int[n];

            RootNodePtr = new LEVEL(0, this);
        }

        void p();

};

#endif
