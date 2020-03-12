#include <iomanip>
#include <iostream>
#include "pagetable.h"


using namespace std;
ofstream myfile;
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

        if(log){
            int pageSize = 32;
            for(int i = 0; i < LevelCount; i++){
                pageSize -= EntryCount[i];
            }
            int powr = pow(2, pageSize) - 1;
            unsigned int finalOffset = LogicalAddress & powr;
            unsigned int physical = (Level->MapPtr[offset].Frame * pageSize) + finalOffset;
            cout << setfill('0') << setw(8) << hex << LogicalAddress << " -> " << setfill('0') << setw(8) << hex << physical << endl; 
            myfile.open(outputFileName, std::ios_base::app);
            myfile << setfill('0') << setw(8) << hex << LogicalAddress << " -> " << setfill('0') << setw(8) << hex << physical << endl; 
            myfile.close();
        }
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
        if(log){
            int pageSize = 32;
            for(int i = 0; i < LevelCount; i++){
                pageSize -= EntryCount[i];
            }
            int powr = pow(2, pageSize) - 1;
            unsigned int finalOffset = LogicalAddress & powr;
            unsigned int physical = (Level->MapPtr[offset].Frame * pageSize) + finalOffset;
            cout << setfill('0') << setw(8) << hex << LogicalAddress << " -> " << setfill('0') << setw(8) << hex << physical << endl; 
        }
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
            if(outputFileName) {
                myfile.open(outputFileName, std::ios_base::app);
                myfile << setfill('0') << setw(8) << hex << current + i << " -> " << setfill('0') << setw(8) << hex << Level->MapPtr[i].Frame << endl;
                myfile.close();
            }
        }
        else if(!isLeaf && Level->NextLevelPtr[i]){
            unsigned int adr = (i << ShiftAry[Level->Depth]) + current;
            printLevel(Level->NextLevelPtr[i], adr);
        }
    }
}

void PAGETABLE::logTranslations(){
    log = true;
}


