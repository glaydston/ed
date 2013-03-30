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

// retira: retira a célula seguinte à celula
// apontada por p e armazena o item
// retirado no parâmetro pedido.
void retira(tCelula *p, tListaEnc *l, tPedido *pedido){
	tCelula *q;
	if(vazia(l) || p == NULL || p->prox == NULL)
		printf("Erro!");
	else{
		q = p -> prox;
		p -> prox   = q ->prox;
		*pedido = q -> item;
		if(q -> prox == NULL) 
			l -> ultimo = p;
		free(q);			
	}
}

// imprime: imprime os itens da lista l
void imprime(tListaEnc *l){
	tCelula *aux = l -> primeiro -> prox;
	while(aux != NULL){
		printf("\n\t\tNumero: %d", aux->item.numero);
		printf("\n\t\tData: %s", aux->item.data);
		printf("\n\t\tEndereco: %s", aux->item.endereco);
		printf("\n\t\tCliente: %s", aux->item.nomeCliente);
		printf("\n\t\Situacao: %c", aux->item.situacao);
		printf("\n\t\Itens: ");
		imprimirItem(&aux->item.itens);
		aux =  aux-> prox;
	}
}
