#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include "map.h"

class PAGETABLE;

using namespace std;

class LEVEL {
    public:
        int Depth;
        PAGETABLE *pt;
        LEVEL **NextLevelPtr;
        MAP *MapPtr;
 
        LEVEL(int n, PAGETABLE *table) {
            cout << "here" << endl;
            Depth = n;
            pt = table;
            
            fillDefault();
            cout << "here2" << endl;
        }

        void callp();
        //void insert();

    private:
        void fillDefault();
        
};

#endif
