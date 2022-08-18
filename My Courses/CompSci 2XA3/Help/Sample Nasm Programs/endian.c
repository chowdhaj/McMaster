#include <stdio.h>

int main() {
  unsigned short word = 1;
  unsigned char *ptr = (unsigned char *) &word;

  if (ptr[0] == 1)
    printf("Little Endian Machine\n");
  else
    printf ("Big Endian Machine\n");
  return 0;
}
