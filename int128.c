#include "int128.h"
#include <stdlib.h> 

/*Auxiliares p teste*/
long getHigh (Int128 *a)
{ return a->high;}
long getLow (Int128 *a)
{ return a->low;}

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
{
	if(abs(v1->low+v2->low)>4294967295)	{
		// OVERFLOW, descobrir o q fazer aq 
		
	}
	else{
		res->low=v1->low+v2->low;
		if( (v1->high == -1 || v1->high==0)&& (v1->high == -1 || v2->high==0)) 
		{
			if (abs(v1->low)>abs(v2->low))
				res->high = v1->high;
			else 
				res->high=v2->high;
			// se o high dos 2 apenas representa o sinal , a resposta vai ter o sinal do maior
		//	res->high=(abs(v1->low)>abs(v2->low))? v1->high:v2->high; 
		}
		else {
			//algum ou os dois rep valor 
			if(( v1->high == -1 && v2->high>0)|| (v2->high == -1 && v1->high>0) ) 
				// se o high de 1 representa o sinal negativo e o outro rep valor positivo,
				// a resposta vai ser o valor positivo
				res->high=(v1->high>v2->high)? v1->high:v2->high; 
			else{
				if( abs(v1->high + v2->high) >0){
						//OVERFLOW, descobrir o que fazer aq
				}
				else
					res->high =v1->high +v2->high;
			}
		}
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
