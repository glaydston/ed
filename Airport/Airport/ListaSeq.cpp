#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"

// Implementação das operações

// inicializaPassageiro: iniciliaza a lista
// atribuindo 0 ao primeiro e ultimo
void inicializaPassageiro(tListaPassageiros *l){
	l->primeiro = 0;
	l->ultimo = 0;
}

// inserePassageiro: insere um passageiro na lista l
void inserePassageiro(tPassageiro passageiro, tListaPassageiros *l){
    if(l->ultimo == MAX_ITEM)		
		printf("Erro! Lista cheia!");
	else
		l->item[l->ultimo++] = passageiro;    
}

// removePassageiro: remove um passageiro da lista l,
// pela posicao
void removePassageiro(int posicao, tListaPassageiros *l){
    int i;
	if(vaziaPassageiro(l))
		printf("Erro!");
	else
		for(i=posicao; i< l->ultimo; i++)
			l->item[i] = l->item[i+1];
		l->ultimo--;
}

// vaziaPassageiro: verifica se a lista l 
// está vazia
int vaziaPassageiro(tListaPassageiros *l){
	return (l->primeiro == l->ultimo);
}
