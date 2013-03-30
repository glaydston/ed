//Pilha.h
#include <stdio.h>
#include <stdlib.h>

// Definições das Estruturas
typedef struct tCel{
	int item;
	struct tCel *prox;
}tCelula;

typedef struct {
	tCelula *topo;
}tPilha;

// Prototipo das funções
void inicializa(tPilha *p);
void empilhar(int x, tPilha *p);
void desempilhar(int *x, tPilha *p);
void imprime(tPilha *p);
int	 vazia(tPilha *p);
int  acessaTopo(int *x, tPilha *p);
int	 procuraValor(int a, tPilha p[]);
