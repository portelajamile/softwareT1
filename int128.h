#include <stdio.h>

typedef struct int128 {
  long high;
  long low;
} Int128;

/* Atribuicao */
void int128_attr (Int128 *res, long l);

/* Soma */
void int128_add (Int128 *res, Int128 *v1, Int128 *v2);

/* Substracao */
void int128_sub (Int128 *res, Int128 *v1, Int128 *v2);

/* Shift para esquerda */
void int128_shl (Int128 *res, Int128 *v, int n);

/* Shift para direita (aritmetico) */
void int128_shr (Int128 *res, Int128 *v, int n);

/* Grava um Int128 */
int int128_write(Int128 *v, FILE *f);

/* Le um Int128 */
int int128_read(Int128 *v, FILE *f);


/*Auxiliares de teste*/

long getHigh(Int128 *a);
long getLow(Int128 *a);


/*Operações básicas:
A função int128_attr atribui a um inteiro de 128 bits (res) o valor signed long fornecido por l.
As funções int128_add e int128_sub realizam, respectivamente, as operações de soma (v1 + v2) e subtração (v1 - v2) de dois inteiros de 128 bits, armazenando o resultado em res.
A função int128_shl realiza um deslocamento para a esquerda (shift left) de um inteiro de 128 bits (v << n), armazenando em res o resultado da operação. Sua implementação pode assumir que o valor de n é um inteiro no intervalo [0,127].
A função int128_shr realiza um deslocamento aritmético para a direita (shift right) de um inteiro de 128 bits (v >> n), armazenando em res o resultado da operação. Sua implementação pode assumir que o valor de n é um inteiro no intervalo [0,127].
Operações de persistência em arquivo:
A função int128_write recebe um inteiro de 128 bits (v) e o descritor de um arquivo aberto para a escrita, em modo binário (code>f). Ela deverá gravar, neste arquivo, o valor do inteiro de 128 bits em ordenação big-endian (ou seja, o byte mais significativo deve ser o primeiro a ser gravado).
A função deverá retornar o valor 0 se a gravação foi realizada com sucesso, e -1 em caso contrário (erro de E/S).

Atenção: A função int128_write não deve fechar o arquivo de saída. Como vários inteiros de 128 bits poderão ser armazenados em um mesmo arquivo, apenas a função que abriu o arquivo (provavelmente, a main) deve fechar o arquivo.

A função int128_read recebe o descritor de um arquivo aberto para a leitura, em modo binário (f). Ela deverá ler, deste arquivo, o valor de um inteiro de 128 bits que estará gravado no arquivo como descrito no item anterior (isto é, em ordenação big-endian). O valor lido deverá ser armazenado no inteiro de 128 bits v.
A função deverá retornar o valor 0 se a leitura foi realizada com sucesso, e -1 em caso contrário (erro de E/S).

Da mesma forma que a função int128_write, a função int128_read, não deve fechar o arquivo de saída.*/