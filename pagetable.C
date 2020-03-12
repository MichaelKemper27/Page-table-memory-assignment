#include <iomanip>
#include <iostream>
#include "pagetable.h"


using namespace std;

void PAGETABLE::PageInsert(unsigned int LogicalAddress, unsigned int Frame){
    PageInsert(RootNodePtr, LogicalAddress, Frame);
}

//recursive insert helper function
void PAGETABLE::PageInsert(LEVEL *Level, unsigned int LogicalAddress, unsigned int Frame){
    //decide if this level is a leaf
    bool isLeaf = (Level->Depth == LevelCount - 1);

    //get offset from current level
    int offset = getOffset(LogicalAddress, Level->Depth);
    if(isLeaf){
        //if leaf, set to valid and insert frame
        Level->MapPtr[offset].valid = true;
        Level->MapPtr[offset].Frame = Frame;

        if(log){
            logHere(Level, LogicalAddress, offset); 
        }
    }
    else {
        //if not leaf, check if level is already created, if not create new level
        if(!Level->NextLevelPtr[offset]){
            Level->NextLevelPtr[offset] = new LEVEL(Level->Depth + 1, this);
        }
        //drop down one level
        PageInsert(Level->NextLevelPtr[offset], LogicalAddress, Frame);
    }
}

//calculate offset
int PAGETABLE::getOffset(unsigned int LogicalAddress, int depth){
    int stripped = (LogicalAddress & BitmaskAry[depth]) >> ShiftAry[depth];
    return stripped;
}

MAP * PAGETABLE::PageLookup(unsigned int LogicalAddress){
    return PageLookup(RootNodePtr, LogicalAddress);
}

//recursive pageLookup helper method
MAP * PAGETABLE::PageLookup(LEVEL *Level, unsigned int LogicalAddress){
    bool isLeaf = (Level->Depth == LevelCount - 1);

    int offset = getOffset(LogicalAddress, Level->Depth);

    //if leaf, return map*
    if(isLeaf && Level->MapPtr[offset].valid){
        MAP *result = &(Level->MapPtr[offset]);
        if(log){
            logHere(Level, LogicalAddress, offset);
        }
        return result;
    }
    //if not leaf, drop down one level
    else if(!isLeaf && Level->NextLevelPtr[offset]){
        return PageLookup(Level->NextLevelPtr[offset], LogicalAddress);
    }
    //if at anypoint there is no where to go, return null
    return NULL;
}

void PAGETABLE::printTable(){
    printLevel(RootNodePtr, 0);
}

//recursive print helper method
void PAGETABLE::printLevel(LEVEL *Level, unsigned int current){
    bool isLeaf = (Level->Depth == LevelCount - 1);
    int size = pow(2, EntryCount[Level->Depth]);

    //print the entire current level
    for(int i = 0; i < size; i++){
        if(isLeaf && Level->MapPtr[i].valid){
            cout << setfill('0') << setw(8) << hex << current + i << " -> " << setfill('0') << setw(8) << hex << Level->MapPtr[i].Frame << endl;
        }
        //if its not a leaf, drop down a level
        else if(!isLeaf && Level->NextLevelPtr[i]){
            unsigned int adr = (i << ShiftAry[Level->Depth]) + current;
            printLevel(Level->NextLevelPtr[i], adr);
        }
    }
}

void PAGETABLE::logTranslations(){
    log = true;
}

//log the current translation
void PAGETABLE::logHere(LEVEL *Level, unsigned int LogicalAddress, int offset){
    int pageSize = 32;
    for(int i = 0; i < LevelCount; i++){
        pageSize -= EntryCount[i];
    }
    int powr = pow(2, pageSize) - 1;
    unsigned int finalOffset = LogicalAddress & powr;
    unsigned int physical = (Level->MapPtr[offset].Frame * pageSize) + finalOffset;
    cout << setfill('0') << setw(8) << hex << LogicalAddress << " -> " << setfill('0') << setw(8) << hex << physical << endl;
}


