#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include "map.h"

class PAGETABLE;

using namespace std;

class LEVEL {
    public:
        int level;
        PAGETABLE *pt;
        LEVEL **NextLevelPtr;
        MAP *MapPtr;
 
        LEVEL(int n, PAGETABLE *table) {
            level = n;
            pt = table;
            
            fillDefault();
        }

        void callp();

    private:
        void fillDefault();
};

#endif
