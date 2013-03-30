#include <stdio.h>
#include <stdlib.h>
#define MAX 20

// Definição das estruturas

typedef struct{
	char	nome[MAX];
	float	notas[8];
	int		faltas;
} tItem;

typedef struct tipoCelula{
	tItem	item;
	struct	tipoCelula *prox;
} tCelula;


typedef struct{
	tCelula *primeiro;
	tCelula *ultimo;
} tLista;

// Protótipo das funções
int		vazia(tLista *l);
void	inicializa(tLista *l);
void	insere(tItem x, tLista *l);
void	retira(tCelula *p, tLista *l, tItem *x);
void	imprime(tLista *l);
