#include "pagetable.h"

using namespace std;

int main(int argc, char **argv){
  PAGETABLE *p = new PAGETABLE(3);
  //p->RootNodePtr->callp();
  p->p();
  cout << p->getOffset(0x12345678, 2) << endl;
  p->PageInsert(0x12345678, 0x0);
  cout << "last" << endl;
}
