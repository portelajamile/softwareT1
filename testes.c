#include <stdio.h> 
#include <ctype.h>
#include <stdlib.h>
long string2long (char *s, int base) {
  long a = 0;
  for (; *s; s++) {
    if(isdigit(*s))
      a = a*base + (*s - '0');
    else if((*s >= 'A') && (*s < (base-10+'A')))
      a = a*base + ((*s - 'A') + 10);
    else if((*s >= 'a') && (*s < (base-10+'a')))
      a = a*base + ((*s - 'a') + 10);
    else {
      printf("pane: numero invalido! \n");
      exit(1);
    }
  }
  return a;
}
int main (int argc, char **argv) {
  long x;
  if (argc != 2) {
    printf ("erro. forneça o numero em hexadecimal");
    exit(1);
  }
  x=string2long(argv[1], 16);
  printf ("%ld\n", x);
  return 0;
}
