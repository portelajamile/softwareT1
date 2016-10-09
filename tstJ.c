#include "int128.h"
#include <stdio.h>
/*
void int128_attr 
void int128_add 
void int128_sub 
void int128_shl
void int128_shr
int int128_write
int int128_read
*/

void dump (void *p, int n)
 {
  unsigned char *p1 = p;
  while (n--) {
    printf("%p - %02x\n", p1, *p1);
    p1++;
  }
}
 int main (void)
 {
	long a,c,d;
	Int128 b;
	a=-2147483647;
	
	int128_attr(&b,a);
	
	c=getHigh(&b);
	d=getLow(&b);	
	
	printf("a - %ld - dump de a:\n",a );
	dump(&a,sizeof(a));

	printf("HIGH long: %ld - dump:\n",c );
	dump(&c,sizeof(c));
	printf("LOW long: %ld - dump:\n",d );
	dump(&d,sizeof(d));
	
 	return 0;
 }