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
    cout << "------------------------------" << Level->Depth << endl;
    cout << isLeaf << endl;
    cout << Level->Depth << endl;
    cout << LevelCount << endl;

    int offset = getOffset(LogicalAddress, Level->Depth);
    if(isLeaf){
        cout << "leaf" << endl;
        Level->MapPtr[offset].valid = true;
        Level->MapPtr[offset].Frame = Frame;
        cout << Level->MapPtr[offset].Frame << endl;
    }
    else {
        cout << offset << "good" << endl;
        Level->NextLevelPtr[offset] = new LEVEL(Level->Depth + 1, this);
        PageInsert(Level->NextLevelPtr[offset], LogicalAddress, Frame);
    }
    cout << "last2" << endl;
}

int PAGETABLE::getOffset(unsigned int LogicalAddress, int depth){
    int stripped = (LogicalAddress & BitmaskAry[depth]) >> ShiftAry[depth];
    return stripped;
}


