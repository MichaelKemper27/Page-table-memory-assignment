#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include "pagetable.h"

using namespace std;

class LEVEL {
 public:
  int level;
  PAGETABLE pt;
 
  LEVEL(int n, PAGETABLE &table) {
   level = n;
   *pt = table;
  }
  
  
};

#endif
