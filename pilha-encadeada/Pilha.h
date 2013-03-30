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
int	 vazia(tPilha *p);
void inicializa(tPilha *p);
void empilha(int x, tPilha *p);
void desempilha(int *x, tPilha *p);
void imprime(tPilha *p);