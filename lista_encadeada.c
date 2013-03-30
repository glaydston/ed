// Implementação da biblioteca "lista.h"
#include <stdio.h>
#include <stdlib.h>

// Estrutura da lista encadeada 

typedef struct tcel{
             int item;
             struct tcel *prox;
} tcelula;

typedef struct {
             tcelula *primeiro;
             tcelula *ultimo;
} tlista;
    
// Operações da lista encadeada
    
void inicializa (tlista *l)
{
	l->primeiro = (tcelula *) malloc(sizeof(tcelula));
	l->ultimo = l->primeiro;
	l->ultimo->prox = NULL; 
}

int vazia (tlista *l)
{
	if (l->primeiro == l->ultimo)
		return 1;
	else return 0;
}

void insere (int x, tlista *l)
{
	l->ultimo->prox = (tcelula *)malloc(sizeof(tcelula)); 
	l->ultimo = l->ultimo->prox; 
	l->ultimo->item = x;         
	l->ultimo->prox = NULL;
}

void retira (tcelula *p, tlista *l, int *x)
{
	tcelula *q;

	if (vazia (l) || p== NULL || p->prox == NULL)
		printf("\n\nErro Lista vazia ou posicao invalida!");
	else
	{
		q = p->prox; 
		*x = q->item;
		p->prox = q->prox;
		if (q->prox == NULL)
			l->ultimo = p;
		free(q);
	}
}

void imprime (tlista *l)
{
	tcelula *aux=l->primeiro->prox;
	
	while (aux != NULL)
	{
		printf("%d ",aux->item);
		aux = aux->prox;
	}
}


void main()
{
     system("pause");
}
