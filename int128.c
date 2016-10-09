#include "int128.h"
#include <stdlib.h> 

/*Auxiliares p teste*/
long getHigh (Int128 *a)
{ return a->high;}
long getLow (Int128 *a)
{ return a->low;}


/*Funções principais*/
void int128_attr (Int128 *res, long l)
{
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
	if(abs(v1->low+v2->low)>4294967295) //há overflow
	{
		// descobrir o q fazer aq
		
		
	}
	else{
		res->low=v1->low+v2->low;
		if( (v1->high == -1 || v1->high==0)&& (v12->high == -1 || v2->high==0)) 
			// se o high apenas representa o sinal , a resposta vai ter o sinal do maior
			res->high=(v1->low>v2->low)? v1->high:v2->high; 
		else 
			
		if(v1->high ==0 && v2->high ==0)
			
	}
}

void int128_sub (Int128 *res, Int128 *v1, Int128 *v2)
{
}

void int128_shl (Int128 *res, Int128 *v, int n)
{
}

void int128_shr (Int128 *res, Int128 *v, int n)
{
}

int int128_write(Int128 *v, FILE *f)
{
return 0;
}

int int128_read(Int128 *v, FILE *f)
{
return 0;
}