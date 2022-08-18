#include <stdio.h>
#include <string.h>

int get_next(FILE* fp) {
  static int c1;
  static bool c1w=false;
  static bool _end=false;
  int c;
  
  if (c1w) {
    c1w=false;
    return c1;
  }
  if (_end) return 0;

  c = fgetc(fp);
  if (feof(fp)) {
     _end=true;
     return 0;
  }
  if (c == '\r') {
    c1=fgetc(fp);
    if (feof(fp)) {
      _end=true;
      return '\n';
    }
    if (c1 == '\n') {
      return '\n';
    }
    c1w=true;
    return '\n';
  }else{
    return c;
  }
}

int main(int argc,char** argv) {
  int c, bufi, i, j;
  char buf[1000];

  if (argc != 2) {
    printf("usage -- %s <infile>\n",argv[0]);
    return 0;
  }
  FILE* fp = fopen(argv[1],"r");
  if (fp==0) {
    printf("can't open input file \"%s\"\n",argv[1]);
    return 0;
  }
  bufi=-1;
  while((c=get_next(fp))!=0) {
    if (c == '\n') {
      printf("%s\n",buf);
      bufi=-1;
	  buf[0]='\0';
      continue;
    }
    if (c == '.') {
      for(j = 0; buf[j]==' '; j++);
      printf("%s.\n\n",&buf[j]);
      bufi=-1;
	  buf[0]='\0';
      continue;
    }
    buf[++bufi]=c;  
    buf[bufi+1]='\0';
    if (bufi > 80) {
      for(i=79; i>=0 && buf[i]!=' '; i--);
      buf[i]='\0';
      for(j = 0; buf[j]==' '; j++);
      printf("%s\n",&buf[j]);
      i++;
      for(j=0; i <= bufi; buf[j++]=buf[i++]);
      bufi=j;
      buf[bufi+1]='\0';  
      continue;
    }
  }
  fclose(fp);

  if (bufi>0) {
    for(j = 0; buf[j]==' '; j++);
    printf("(4)%s\n",&buf[j]);
  }
  return 0;
}
