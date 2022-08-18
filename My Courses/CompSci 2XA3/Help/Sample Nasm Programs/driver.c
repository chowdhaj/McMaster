#include "cdecl.h"

int PRE_CDECL asm_main(int,char**) POST_CDECL;

int main(int argc,char** argv) {
  int ret_status;
  ret_status = asm_main(argc,argv);
  return ret_status;
}
