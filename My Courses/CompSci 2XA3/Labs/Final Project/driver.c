#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "cdecl.h"

int PRE_CDECL asm_main(int,char**) POST_CDECL;

void rconf(unsigned int *r, unsigned int n) {
  unsigned int i, j, t;
  for(i = 0; i < n; i++)
    r[i]=i+1;
  srand(time(NULL));
  if (n > 1) {
    for (i = 0; i < n - 1; i++) {
      j = i + rand() / (RAND_MAX / (n - i) + 1);
      t = r[j];
      r[j] = r[i];
      r[i] = t;
    }
  }
}

int main(int argc,char** argv) {
  int ret_status;
  ret_status = asm_main(argc,argv);
  return ret_status;
}
