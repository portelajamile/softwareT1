#include "int128.h"
#include <stdio.h>
/* REMOVER DEPOIS
void int128_attr 
void int128_add 
void int128_sub 
void int128_shl
void int128_shr
int int128_write
int int128_read
*/

// FCS AUXILIARES P TESTE
void dump (void *p, int n)
 {
  unsigned char *p1 = p;
  while (n--) {
    printf("%p - %02x\n", p1, *p1);
    p1++;
  }
}
 void exibeInt( Int128* b)
 {
	long c,d;
	c=getHigh(b);
	d=getLow(b);	

	printf("HIGH long: %ld - dump:\n",c );
	dump(&c,sizeof(c));
	printf("LOW long: %ld - dump:\n",d );
	dump(&d,sizeof(d));
	 
 }
 void exibeLong (long a)
 {
	 printf("num - %ld - dump de num:\n",a );
	dump(&a,sizeof(a));
 }
 
 int main (void)
 {
	long a,b;
	Int128 i1,i2,i3;
	a=-2147483648;
	b= 2147483646;
	int128_attr(&i1,a);
	int128_attr(&i2,b);
	
	/* TESTA A FC ATTR	
	exibeLong(a);
	exibeInt(&i1);
	*/
	
	// TESTA A FC ADD 
	int128_add(&i3,&i1,&i2);
	exibeInt(&i1);
	exibeInt(&i2);
	exibeLong (a+b);
	exibeInt(&i3);
	
	
	
 	return 0;
 }