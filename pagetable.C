#include <iomanip>
#include <iostream>
#include "pagetable.h"


using namespace std;

void PAGETABLE::p(){
    

    for(int i = 0; i < LevelCount; i++){
        cout << BitmaskAry[i] << endl;
    }
}

void PAGETABLE::PageInsert(unsigned int LogicalAddress, unsigned int Frame){
    PageInsert(RootNodePtr, LogicalAddress, Frame);
}

void PAGETABLE::PageInsert(LEVEL *Level, unsigned int LogicalAddress, unsigned int Frame){
    bool isLeaf = (Level->Depth == LevelCount - 1);
    // cout << "------------------------------" << Level->Depth << endl;
    // cout << isLeaf << endl;
    // cout << Level->Depth << endl;
    // cout << LevelCount << endl;

    int offset = getOffset(LogicalAddress, Level->Depth);
    if(isLeaf){
        //cout << "leaf" << endl;
        Level->MapPtr[offset].valid = true;
        Level->MapPtr[offset].Frame = Frame;
        //cout << Level->MapPtr[offset].Frame << endl;
    }
    else {
       // cout << offset << "good" << endl;
        if(!Level->NextLevelPtr[offset]){
            Level->NextLevelPtr[offset] = new LEVEL(Level->Depth + 1, this);
        }
        PageInsert(Level->NextLevelPtr[offset], LogicalAddress, Frame);
    }
    //cout << "last2" << endl;
}

int PAGETABLE::getOffset(unsigned int LogicalAddress, int depth){
    int stripped = (LogicalAddress & BitmaskAry[depth]) >> ShiftAry[depth];
    return stripped;
}

MAP * PAGETABLE::PageLookup(unsigned int LogicalAddress){
    return PageLookup(RootNodePtr, LogicalAddress);
}

MAP * PAGETABLE::PageLookup(LEVEL *Level, unsigned int LogicalAddress){
    bool isLeaf = (Level->Depth == LevelCount - 1);
    // cout << "------------------------------" << Level->Depth << endl;
    // cout << isLeaf << endl;
    // cout << Level->Depth << endl;
    // cout << LevelCount << endl;

    int offset = getOffset(LogicalAddress, Level->Depth);

    if(isLeaf && Level->MapPtr[offset].valid){
        //cout << "leaf" << endl;
        MAP *result = &(Level->MapPtr[offset]);
        return result;
    }
    else if(!isLeaf && Level->NextLevelPtr[offset]){
        //cout << offset << "good" << endl;
        return PageLookup(Level->NextLevelPtr[offset], LogicalAddress);
    }
    return NULL;
}

void PAGETABLE::printTable(){
    printLevel(RootNodePtr, 0);
}

void PAGETABLE::printLevel(LEVEL *Level, unsigned int current){
    bool isLeaf = (Level->Depth == LevelCount - 1);
    int size = pow(2, EntryCount[Level->Depth]);

    for(int i = 0; i < size; i++){
        if(isLeaf && Level->MapPtr[i].valid){
            cout << setfill('0') << setw(8) << hex << current + i << " -> " << setfill('0') << setw(8) << hex << Level->MapPtr[i].Frame << endl;
        }
        else if(!isLeaf && Level->NextLevelPtr[i]){
            unsigned int adr = (i << ShiftAry[Level->Depth]) + current;
            printLevel(Level->NextLevelPtr[i], adr);
        }
    }
}


