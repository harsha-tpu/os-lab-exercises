#include <stdio.h>

#define MPROC 5 
#define MRESC 3 

void calcNeed(int need[MPROC][MRESC], int max[MPROC][MRESC], int alloc[MPROC][MRESC], int np, int nr) {
  for (int i=0; i<np; i++) {
    for (int j=0; j<nr; j++) {
      need[i][j] = max[i][j] - alloc[i][j];
    }
  }
}
 
int isSafe(); 

int main() {
  int np = 5; 
  int nr = 3; 
  int avble[MRESC] = {3, 3, 2};
  int max[MPROC][MRESC] = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
  };
  
  int alloc[MPROC][MRESC] = {
    {},
    {},
    {},
    {},
    {}
  };
  isSafe(avble, max, alloc, np, nr);
  return 0; 
}
