#include "pagetable.h"

using namespace std;

void PAGETABLE::p(){
    BitmaskAry[0] = 0xFF000000;
    BitmaskAry[1] = 0x00FF0000;
    BitmaskAry[2] = 0x0000FF00;

    ShiftAry[0] = 24;
    ShiftAry[1] = 16;
    ShiftAry[2] = 8;  

    EntryCount[0] = 8;
    EntryCount[1] = 8;
    EntryCount[2] = 8;  

    for(int i = 0; i < LevelCount; i++){
        cout << BitmaskAry[i] << endl;
    }
}

void PAGETABLE::PageInsert(unsigned int LogicalAddress, unsigned int Frame){
    PageInsert(RootNodePtr, LogicalAddress, Frame);
}

void PAGETABLE::PageInsert(LEVEL *Level, unsigned int LogicalAddress, unsigned int Frame){
    bool isLeaf = (Level->Depth == LevelCount - 1);
    cout << isLeaf << endl;
    cout << Level->Depth << endl;
    cout << LevelCount << endl;

    if(isLeaf){
        cout << "leaf" << endl;
    }
    else {
        int offset = getOffset(LogicalAddress, Level->Depth);
        cout << offset << endl;
        Level->NextLevelPtr[offset] = new LEVEL(1, this);
        //PageInsert(Level->NextLevelPtr[offset], LogicalAddress, Frame);
    }
    cout << "last2" << endl;
}

int PAGETABLE::getOffset(unsigned int LogicalAddress, int depth){
    int stripped = (LogicalAddress & BitmaskAry[depth]) >> ShiftAry[depth];
    return stripped;
}


