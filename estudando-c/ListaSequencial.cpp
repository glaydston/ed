#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lista.h"

// Implementação das operações

// inicializarSequencial: iniciliaza a lista
// atribuindo 0 ao primeiro e ultimo
void inicializarSequencial(tListaItens *l){
	l->primeiro = 0;
	l->ultimo = 0;
}

// inserirItem: insere um item na lista l
void inserirItem(tItemPedido item, tListaItens *l){
    if(l->ultimo == MAX_ITEM)		
		printf("Erro! Lista cheia!");
	else
		l->item[l->ultimo++] = item;    
}

// removeItem: remove um item da lista l,
// pela posicao
void removeItem(int posicao, tListaItens *l){
    int i;
	if(vaziaSequencial(l))
		printf("Erro!");
	else
		for(i=posicao; i< l->ultimo; i++)
			l->item[i] = l->item[i+1];
		l->ultimo--;
}

// vaziaSequencial: verifica se a lista l 
// está vazia
int vaziaSequencial(tListaItens *l){
	return (l->primeiro == l->ultimo);
}

// imprimirItem: imprime os itens da lista l
void imprimirItem(tListaItens *l){
    for(int i=0; i < l->ultimo; i++)
		printf("\n\n\t\t\tItem:  %s \n\t\t\tQuantidade: %d \n\t\t\tValor: %.2f", 
				l->item[i].descricao, 
				l->item[i].quantidade,				
				l->item[i].precoVenda);
}

// procuraNome: procura o item na lista l
// e retorna o indice do item, caso não encontre
// retorna -1
int procuraNome(char nome[], tListaItens *l){
	for(int i=0; i < l->ultimo; i++)
		// strcmpi: compara sem case sensitivity
		if(!strcmpi(nome, l->item[i].descricao))
			return i;
	return -1;
}