#ifndef PAGETABLE_H
#define PAGETABLE_H

#include <iostream>
#include "level.h"
//class LEVEL;

using namespace std;

class PAGETABLE {
    public:
        int LevelCount;
        unsigned int *BitmaskAry;
        int *ShiftAry;
        int *EntryCount;

        LEVEL *RootNodePtr;

        PAGETABLE(int n){
            LevelCount = n;
            BitmaskAry = new unsigned int[n];
            ShiftAry = new int[n];
            EntryCount = new int[n];

            RootNodePtr = new LEVEL(0, this);
        }

        void p();
        void PageInsert(unsigned int LogicalAddress, unsigned int Frame);
        void PageInsert(LEVEL *Level, unsigned int LogicalAddress, unsigned int Frame);
        int getOffset(unsigned int LogicalAddress, int depth);
};

#endif
