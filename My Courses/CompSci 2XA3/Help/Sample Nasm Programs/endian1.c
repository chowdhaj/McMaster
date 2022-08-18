#include <stdio.h>

int main() {
  unsigned long number = 0x41424344;
  unsigned char word[5] = {'A','B','C','D','\0'};
  unsigned char *ptr; 

  printf("how a number %u=%Xh is stored:\n",number,number);
  ptr = (unsigned char *) &number;
  printf("%Xh %Xh %Xh %Xh\n",ptr[0],ptr[1],ptr[2],ptr[3]);
  printf("%c   %c   %c   %c\n",ptr[0],ptr[1],ptr[2],ptr[3]);
  printf("how a bunch of characters %s=%Xh is stored:\n",word,
         *((unsigned long *) word));
  ptr = (unsigned char *) word;
  printf("%Xh %Xh %Xh %Xh\n",ptr[0],ptr[1],ptr[2],ptr[3]);
  printf("%c   %c   %c   %c\n",ptr[0],ptr[1],ptr[2],ptr[3]);

  return 0;
}
