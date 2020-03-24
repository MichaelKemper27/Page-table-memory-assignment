// pagetable.h
// Student: Kemper, Michael | Clode, Ryan
// RedID: (Kemper)822 86 7065 | (Clode)820 72 7161
#ifndef PAGETABLE_H
#define PAGETABLE_H

#include <iostream>
#include <fstream>
#include "level.h"
#include <math.h>

using namespace std;

extern char* outputFileName;
class PAGETABLE {
    public:
        int LevelCount;
        unsigned int *BitmaskAry;
        int *ShiftAry;
        int *EntryCount;
        bool log = false;

        LEVEL *RootNodePtr;

        PAGETABLE(int n, int *data){
            if(outputFileName) {
              ofstream clearCurrentOutputFile;
              clearCurrentOutputFile.open(outputFileName);
              clearCurrentOutputFile.close();
            }
            LevelCount = n;
            BitmaskAry = new unsigned int[n];
            ShiftAry = new int[n];
            EntryCount = new int[n];

            //fill EntryCount, ShiftAry, and BitMask
            int currentOffset = 32;
            for(int i = 0; i < n; i++){
                EntryCount[i] = data[i];
                currentOffset -= data[i];
                ShiftAry[i] = currentOffset;
                unsigned int bitMask = 0x00000000;
                int bits = pow(2, data[i]) - 1;
                bitMask = (bitMask | bits) << currentOffset;
                BitmaskAry[i] = bitMask;
            }
            RootNodePtr = new LEVEL(0, this);
        }

        void PageInsert(unsigned int LogicalAddress, unsigned int Frame);
        MAP * PageLookup(unsigned int LogicalAddress);
        void printTable();
        void logTranslations();

    private:
        MAP * PageLookup(LEVEL *Level, unsigned int LogicalAddress);
        void PageInsert(LEVEL *Level, unsigned int LogicalAddress, unsigned int Frame);
        void printLevel(LEVEL *Level, unsigned int current);
        int getOffset(unsigned int LogicalAddress, int depth);
        void logHere(LEVEL *Level, unsigned int LogicalAddress, int offset);

};


#endif
