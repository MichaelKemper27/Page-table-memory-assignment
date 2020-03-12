#ifndef PAGETABLE_H
#define PAGETABLE_H

#include <iostream>
#include "level.h"
#include <math.h>
//class LEVEL;

using namespace std;

class PAGETABLE {
    public:
        int LevelCount;
        unsigned int *BitmaskAry;
        int *ShiftAry;
        int *EntryCount;
        bool log = false;

        LEVEL *RootNodePtr;

        PAGETABLE(int n, int *data){
            LevelCount = n;
            BitmaskAry = new unsigned int[n];
            ShiftAry = new int[n];
            EntryCount = new int[n];

            int currentOffset = 32;
            for(int i = 0; i < n; i++){
                EntryCount[i] = data[i];
                currentOffset -= data[i];
                ShiftAry[i] = currentOffset;
                unsigned int bitMask = 0x00000000;
                int bits = pow(2, data[i]) - 1;
                cout << "bits " << bits << endl;
                cout << (bits | bitMask) << endl;
                bitMask = (bitMask | bits) << currentOffset;
                cout << "bitmask " << bitMask << endl;
                BitmaskAry[i] = bitMask;
            }

            cout << n << endl;
            cout << "array check: " << endl;
            for(int i = 0; i < n; i++){
                cout << EntryCount[i] << endl;
            }
            for(int i = 0; i < n; i++){
                cout << ShiftAry[i] << endl;
            }
            for(int i = 0; i < n; i++){
                cout << BitmaskAry[i] << endl;
            }
            cout << "array done" << endl;
            RootNodePtr = new LEVEL(0, this);
        }

        void p();
        void PageInsert(unsigned int LogicalAddress, unsigned int Frame);
        MAP * PageLookup(unsigned int LogicalAddress);
        MAP * PageLookup(LEVEL *Level, unsigned int LogicalAddress);
        void PageInsert(LEVEL *Level, unsigned int LogicalAddress, unsigned int Frame);
        int getOffset(unsigned int LogicalAddress, int depth);
        void printTable();
        void printLevel(LEVEL *Level, unsigned int current);
        void logTranslations();
};

#endif
