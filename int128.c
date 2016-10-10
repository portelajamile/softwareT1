#include "int128.h"
#include <stdlib.h> 
#include <math.h>

/*Auxiliares p teste*/
long getHigh (Int128 *a)
{ return a->high;}
long getLow (Int128 *a)
{ return a->low;}

/*Funções auxiliares */ 
int calcMax (void)
{
	return pow(2,sizeof(long)-1);
}

long swapLong(long in)
{
	long out;
	char *inp = (char *)&in;
	char *outp = (char *)&out;

	int i = 0;
	for (i = 0; i<sizeof(long); i++)
	{
		outp[i] = inp[(sizeof(long)-1) - i];
	}

	return out;
}

void dump(void *p, int n,FILE* f) {
	unsigned char *p1 = p;
	while (n--) {
		fprintf(f,"%02x",*p1);
		p1++;
	}
}

/*Funções principais*/

void int128_attr (Int128 *res, long l)
{	// extende com sinal (como o comando movz de assembly)
		if(l>0){
		res->high =0;
		res->low = l;	
	}
	else {
		res->high =-1;
		res->low = l;	
	}
		
}

void int128_add (Int128 *res, Int128 *v1, Int128 *v2)
{	//soma dois inteiros de 128 bits 
	int s=1, t=1, d=0, nmax;
	nmax=calcMax();
		
	if(v1->high<0 && v1->low>0)			//corrige sinal caso v1 seja neg
		s=-1;
	if(v2->high<0 && v2->low>0)			//corrige sinal caso v2 seja neg
		t=-1;
	
//soma o low		
	if( abs( s*v1->low+t*v2->low ) > nmax )	{
		// OVERFLOW
		if(s*v1->low+t*v2->low <0){
			d=s*v1->low+t*v2->low + nmax;
			res->high=-nmax;
		}
		else{ 
			d=s*v1->low+t*v2->low - nmax;
			res->high = nmax;
		}
	}
	else
		res->low=s*v1->low+t*v2->low;

// soma o high 

	s=1; t=1;
	
	if(v1->high == -1 || v1->high==0)		//v1 representa sinal
		s=0; 
	if(v2->high == -1 || v2->high==0)		//v2 representa sinal
		t=0;
		
	if( res->low < 0 ){					// res é negativo
		if ( v2->high > 0)					//v2 é valor
			t=-1;
		if (v1->high > 0)					//v1 é valor 
			s=-1;
	}	
	
	if(s==0 && t==0){					// v1 e v2 são sinal 
		if (d==0)
			res->high= (res->low > 0)? 0:-1;
		else
			res->high = d;
	}
	
	else {								// v1 e v2 são valores 
		if( abs ( s*v1->high + t*v2->high + d ) > nmax) {
			//OVERFLOW
			res->high=res->low=0;
			printf("Overflow! Nao foi possivel armazenar a soma dos inteiros de 128bits.");
		}
		res->high = s*v1->high + t*v2->high + d ;
	}
}

void int128_sub (Int128 *res, Int128 *v1, Int128 *v2)
{
}

void int128_shl (Int128 *res, Int128 *v, int n)
{
	int i;
	long j,arm;;
	if (n < 64)
	{
		j = v->low;
		arm = (j>>(64-n));
		res->low = (v->low << n);
		exibeInt(res);
		res->high = (v->high << n) + arm;
		exibeInt(res);
	}

	else if (n >= 64)
	{
		res->low = (v->low << n);
		n = n - 64;
		arm = v->low;
		res->high = (arm << n);
		exibeInt(res);
	}
}

void int128_shr (Int128 *res, Int128 *v, int n)
{
	
	
	
}

int int128_write(Int128 *v, FILE *f)
{
	int n = sizeof(v);
	long x, y;
	x = swapLong(v->high);
	y = swapLong(v->low); 
	unsigned char *p1 = v;
	while (n--) {
		fprintf(f, "%02x", *p1);
		p1++;
	}
return 0;
}

int int128_read(Int128 *v, FILE *f)
{
		long x, y;
	if (f == NULL)
	{
		printf("Erro no arquivo");
		return 1;
	}
	
	fscanf(f, "%08x", &x);
	x = swapLong(x);
	y = swapLong(y);

	v->low = x;
	v->high = y;
	v->high = y << 31;


	return 0;
}
