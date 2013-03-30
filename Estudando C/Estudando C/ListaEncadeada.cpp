#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"

// Implementação das operações

// Inicializa: faz a lista ficar vazia (cria a
// celula cabeça e faz os ponteiros 
// primeiro e ultimo apontarem para ela)
void inicializa(tListaEnc *l){
	l -> primeiro = new tCelula;
	l -> ultimo	  = l -> primeiro;
	l -> ultimo->prox = NULL;
}

// vazia: retorna verdadeiro (1) se a lista l 
// está vazia, caso contrário, retorna 0 (falso)
int vazia(tListaEnc *l){
	return (l -> primeiro == l -> ultimo);
}

// insere: insere o item x no final
// da lista l
void insere(tPedido pedido, tListaEnc *l){
	l -> ultimo -> prox = (tCelula *) malloc(sizeof(tCelula));
	l -> ultimo 		= l->ultimo -> prox;
	l -> ultimo -> item = pedido;
	l -> ultimo -> prox = NULL;	
}

// retira: retira a celula seguinte à celula
// apontada por cel e armazena o item
// retirado no parâmetro pedido.
void retira(tCelula *cel, tListaEnc *l, tPedido *pedido){
	tCelula *aux;
	if(vazia(l) || cel == NULL || cel->prox == NULL)
		printf("Erro!");
	else{
		aux = cel -> prox;
		cel -> prox   = aux ->prox;
		*pedido = aux -> item;
		if(aux -> prox == NULL) 
			l -> ultimo = cel;
		free(aux);			
	}
}

// imprime: imprime todos os itens da lista l
void imprime(tListaEnc *l){
	tCelula *aux = l -> primeiro -> prox;
	while(aux != NULL){
		printf("\n\t\tNumero: %d", aux->item.numero);
		printf("\n\t\tData: %s", aux->item.data);
		printf("\n\t\tEndereco: %s", aux->item.endereco);
		printf("\n\t\tCliente: %s", aux->item.nomeCliente);
		printf("\n\t\tSituacao: %c", aux->item.situacao);
		printf("\n\t\tItens do pedido: ");
		imprimirItem(&aux->item.itens);
		aux =  aux-> prox;
	}
}

// imprimePedido: imprime o pedido,
// passado por parametro
void imprimePedido(tPedido pedido){
	printf("\n\t\tNumero: %d", pedido.numero);
	printf("\n\t\tData: %s", pedido.data);
	printf("\n\t\tNome do cliente: %s", pedido.nomeCliente);
	printf("\n\t\tEndereco do cliente: %s", pedido.endereco);
	printf("\n\t\tSituacao do pedido: %c", pedido.situacao);
	printf("\n\t\tItens do pedido:");
	// imprime os itens
	imprimirItem(&pedido.itens);
	
}

// procuraNumero: encontra o numero na lista l,
// retornando 1 caso encontre e 0, caso não 
// encontre o numero na lista 
int procuraNumero(int numero, tListaEnc *l){	
	tCelula *aux = l -> primeiro -> prox;
	while(aux != NULL){
		if(aux->item.numero == numero)
			return 1;
		aux = aux->prox;
	}
	return 0;
}