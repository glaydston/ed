#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"

// Implementa��o das opera��es

// Inicializa: faz a lista ficar vazia (cria a
// celula cabe�a e faz os ponteiros 
// primeiro e ultimo apontarem para ela)
void inicializa(tLista *l){
	l -> primeiro = (tCelula *)malloc(sizeof(tCelula));
	l -> ultimo = l -> primeiro;
	l -> ultimo->prox = NULL;
}

// vazia: retorna verdadeiro (1) se a lista l 
// est� vazia, caso contr�rio, retorna 0 (falso)
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

// retira: retira a c�lula seguinte � celula
// apontada por p e armazena o item
// retirado no par�metro x.
void retira(tCelula *p, tLista *l, tItem *item){
	tCelula *q;
	if(vazia(l) || p == NULL || p->prox == NULL)
		printf("\n\t\t# ERRO: Lista vazia ou posicao invalida\n");
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
		printf("");
		printf("\n\t\tNome: %s", aux->item.nome);
		printf("\n\t\tFalta(s): %d", aux->item.faltas);
		printf("\n\t\tNota(s): [");
		for(int i = 0; i < 8; i++)
			if(i+1 == 8)
				printf("%.1f", aux->item.notas[i]);
			else
				printf("%.1f, ", aux->item.notas[i]);
		printf("]\n");
		aux =  aux-> prox;
	}
}
