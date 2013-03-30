//Pilha.cpp
#include <stdio.h>
#include <stdlib.h>
#include "Pilha.h"

// Implementação das operações

// iniciliaza: cria a celula cabeça
// e faz o topo apontar para ela
void inicializa(tPilha *p){
	p -> topo = (tCelula *) malloc(sizeof(tCelula));
	p -> topo -> prox = NULL;
}

// vazia: retornar 1  se a pilha está 
// vazia; caso contrário retorna 0
int vazia(tPilha *p){
	if(p -> topo -> prox == NULL)
		return 1;
	return 0;
}

// empilha: insere o item x no topo
// da pilha p
void empilha(int x, tPilha *p){
	tCelula *aux = (tCelula *) malloc(sizeof(tCelula));

	p->topo->item = x;
	aux->prox = p->topo;
	p->topo = aux;
}

// desempilha: retira o item que esta no
// topo da pilha p, armazenando-o no parâmetro x
void desempilha(int *x, tPilha *p){
	tCelula *aux;

	if(vazia(p))
		printf("\n\t\t#Erro: Pilha vazia!");
	else{
		aux = p->topo;
		p->topo = p->topo->prox;
		*x = p->topo->item;
		free(aux);
	}
}

// imprime: exibi todos os itens 
// contidos na pilha p
void imprime(tPilha *p){	
	tCelula *aux = p -> topo -> prox;
	if(vazia(p))
		printf("\t\t# Erro: Pilha Vazia!");
	else{
		while(aux != NULL){
			printf("\n\t\t\tItem: %d", aux->item);
			aux =  aux-> prox;
		}
	}
}