#include <stdio.h>
#include "pilha.h"
char numstr[TAM];

void inicializa(tPilha *p) {
	p->topo = -1;
}

void empilhar(int x, tPilha *p) {
	if (p->topo == MAX)
		printf("\n\n\t\t# ERRO: Pilha cheia!");
	else {
		p->topo++;
		p->item[p->topo] = x;
	}

}

void desempilhar(int *x, tPilha *p) {
	if (p->topo == -1)
		printf("\n\n\t\t# ERRO: Pilha vazia!");
	else
		*x = p->item[p->topo--];

}

int isEmpty(tPilha *p) {
	if (p->topo < 0)
		return 1;
	return 0;
}

int acessaTopo(int *x, tPilha *p){
	if(isEmpty(p))
		return 0;
	*x = p->item[p->topo];
	return 1;
}

void print(tPilha *p) {
	for (int i = p->topo; i >= 0; i--)
		printf("\n\t\tPilha[%d]: %d",i, p->item[i]);

}