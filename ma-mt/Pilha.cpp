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

// empilhar: insere o item x no topo
// da pilha p
void empilhar(int x, tPilha *p){
	tCelula *aux = (tCelula *) malloc(sizeof(tCelula));

	p->topo->item = x;
	aux->prox = p->topo;
	p->topo = aux;
}

// desempilhar: retira o item que esta no
// topo da pilha p, armazenando-o no parâmetro x
void desempilhar(int *x, tPilha *p){
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
// da pilha p
void imprime(tPilha p[]){
	int tam = sizeof(p);
	if(vazia(p))
		printf("\t\t# Erro: Pilha Vazia!");
	else
		for(int i= 0; i <= tam; i++){
			tCelula *aux = p[i].topo->prox;
			printf("\nBLOCO [%d]: ",i);
			while(aux != NULL){
				printf(" %d",aux->item);
				aux = aux->prox;
			}
		}
}

// acessaTopo: exibi o item que esta no 
// topo da pilha p, armazenando-o no parâmetro x
int acessaTopo(int *x, tPilha *p){
	tCelula *aux = p->topo->prox;
	if(vazia(p))
		return 0;
	*x = aux->item;
	return 1;
}

