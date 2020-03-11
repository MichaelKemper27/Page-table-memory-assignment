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

            BitmaskAry[0] = 0xFF000000;
            BitmaskAry[1] = 0x00FF0000;
            BitmaskAry[2] = 0x0000FF00;

            ShiftAry[0] = 24;
            ShiftAry[1] = 16;
            ShiftAry[2] = 8;  

            EntryCount[0] = 8;
            EntryCount[1] = 8;
            EntryCount[2] = 8;  
            RootNodePtr = new LEVEL(0, this);
        }

        void p();
        void PageInsert(unsigned int LogicalAddress, unsigned int Frame);
        MAP * PageLookup(unsigned int LogicalAddress);
        MAP * PageLookup(LEVEL *Level, unsigned int LogicalAddress);
        void PageInsert(LEVEL *Level, unsigned int LogicalAddress, unsigned int Frame);
        int getOffset(unsigned int LogicalAddress, int depth);
};

#endif
