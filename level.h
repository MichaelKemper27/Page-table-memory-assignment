#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>

class PAGETABLE;

using namespace std;

class LEVEL {
    public:
        int level;
        PAGETABLE *pt;
        LEVEL **NextLevelPtr;
 
        LEVEL(int n, PAGETABLE *table) {
            level = n;
            pt = table;
            fillNextLevel();
        }

        void callp();

    private:
        void fillNextLevel();
};

#endif
