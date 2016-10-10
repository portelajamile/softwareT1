/*Jamile Baptista Campana Portela - 1412973*/
/*Rudá Fraga Valle - COLOCAR SUA MATRICULA AQUI*/

#include "int128.h"
#include <stdlib.h> 
#include <math.h>


/*Auxiliares p teste - REMOVER */
long getHigh (Int128 *a)
{ return a->high;}
long getLow (Int128 *a)
{ return a->low;}

/*Funções auxiliares */ 
long calcMax (void)
{ //calcula valor maximo que pode ser armazenado no long 
	return (long) pow(2,8*sizeof(long)-1);
}

long swapLong(long in)
{	//inverte a ordenação de bytes
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
		if(l<0)
		res->high =-1;
	else 
		res->high =0;
	res->low = l;		
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
			res->high= (res->low >= 0)? 0:-1;
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
{	//subtrai v2 de v1
	Int128 a;
	// a= -v2;
	if(v2-> high == -1){
		a.high = 0;
		if(v2->low < 0)
			a.low= - v2->low;
		}
	if(v2->high == 0){
		a.high = -1;
		if(v2->low >0)
			a.low = -v2->low;
	}
	// soma (v1+ a) = v1 + (-v2) 
	int128_add(res, v1, &a);
}

void int128_shl (Int128 *res, Int128 *v, int n)
{	// realiza o shift left (lógico) de n bits em um Int128bits
	long j,arm;
	int x = 8*sizeof(long);		//calcula tamanho em bits do long
	if (n < x)
	{
		j = v->low;
		arm = (j>>(x-n));
		res->low = (v->low << n);
		res->high = (v->high << n) + arm;
	}

	else if (n >= x)
	{
		res->low = (v->low << n);
		n = n - x;
		arm = v->low;
		res->high = (arm << n);
	}
}

void int128_shr (Int128 *res, Int128 *v, int n)
{	// realiza o shift right (aritmetico) de n bits em um Int128bits
	long a,b;
	int x= 8*sizeof(long);		//calcula o tamanho em bits do long
	
//se n menor que 8* sizeof(long)
	if(n < x ){
//move parte do high para o low
		a = v->high << (x-n);
		b = v->low >> n;
		res->low = ( a | b );
		
// acerta o high em fç do sinal do low
		if( res->low < 0)
			res->high = (v->high >> n | -1);
		else 
			res->high = (v->high >> n | 0);
	}
// se n maior que 8*sizeof(long)
	else {
		a= v->high << (2*x-n) ; // n-x = bits de interesse no high ; x-(n-x) bits a serem deslocados p obter a mascara
//usa a mascara e o sinal para obter o low e o high
		if(a < 0){
			res->low= ( a | -1 );
			res->high = -1;
		}		
		else{
			res->low = ( a | 0 );
			res->high = 0;
		}
		
	}
}

int int128_write(Int128 *v, FILE *f)
{	// grava um Int128bits em arquivo binario
//	int n = sizeof(v);
	long x, y;
	
	//corrige a ordenação para Little Endian
	x = swapLong(v->high);
	y = swapLong(v->low);
	
	//grava o valor	
	dump(&x, sizeof(x), f);
	dump(&y, sizeof(y), f);
	
/*	v->high = x;
	v->low = y;
	
	unsigned char *p1 = v;
	while (n--) {
		fprintf(f, "%02x", *p1);
		p1++;
	}
*/
	return 0;
}

int int128_read(Int128 *v, FILE *f)
{	//le um Int128bits em arquivo binario
	long x, y;
	if (f == NULL)
	{
		printf("Erro no arquivo");
		return 1;
	}

//	fscanf(f, "%08x %08x",&x, &y);
	fscanf(f, "%08ld %08ld",&x, &y); 
	
	
	// corrige a ordenação para Big Endian
	x = swapLong(x);
	y = swapLong(y);

	v->low = y;
	v->high = x;

	return 0;
}

