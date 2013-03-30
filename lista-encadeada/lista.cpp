#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

// Implementação das operações

// Inicializa: faz a lista ficar vazia (cria a
// celula cabeça e faz os ponteiros 
// primeiro e ultimo apontarem para ela)
void inicializa(tLista *l){
	l -> primeiro = (tCelula *)malloc(sizeof(tCelula));
	l -> ultimo = l -> primeiro;
	l -> ultimo->prox = NULL;
}

// vazia: retorna verdadeiro (1) se a lista l 
// está vazia, caso contrário, retorna 0 (falso)
int vazia(tLista *l){
	if(l -> primeiro == l -> ultimo)
		return 1;
	return 0;
}

// insere: insere o item x no final
// da lista l
void insere(tItem item, tLista *l){
	l -> ultimo -> prox = (tCelula *) malloc(sizeof(tCelula));
	l -> ultimo 		= l->ultimo -> prox;
	l -> ultimo -> item = item;
	l -> ultimo -> prox = NULL;	
}

// retira: retira a célula seguinte à celula
// apontada por p e armazena o item
// retirado no parâmetro x.
void retira(tCelula *p, tLista *l, tItem *item){
	tCelula *q;
	if(vazia(l) || p == NULL || p->prox == NULL)
		printf("\n\t\t# ERRO: Lista vazia ou posição invalida\n");
	else{
		q = p -> prox;
		p -> prox   = q ->prox;
		*item = q -> item;
		if(q -> prox == NULL) l -> ultimo = p;
		free(q);			
	}
}

// imprime: imprime os itens da lista l
void imprime(tLista *l){
	tCelula *aux = l -> primeiro -> prox;

	while(aux != NULL){
		printf("\n\t\tCodigo: %d", aux->item.codigo);
		printf("\n\t\tNome: %s", aux->item.nome);
		printf("\n\t\tNota: %.2f\n\n", aux->item.nota);
		aux =  aux-> prox;
	}
}
