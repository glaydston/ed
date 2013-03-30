#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"

// Implementação das operações

// inicializaVoo: faz a lista ficar vazia (cria a
// celula cabeça e faz os ponteiros 
// primeiro e ultimo apontarem para ela)
void inicializaVoo(tListaEnc *l){
	l -> primeiro = (tCelula *) malloc(sizeof(tCelula));
	l -> ultimo	  = l -> primeiro;
	l -> ultimo->prox = NULL;
}

// vaziaVoo: retorna verdadeiro (1) se a lista l 
// está vazia, caso contrário, retorna 0 (falso)
int vaziaVoo(tListaEnc *l){
	return (l -> primeiro == l -> ultimo);
}

// insereVoo: insere o item x no final
// da lista l
void insereVoo(tVoo voo, tListaEnc *l){
	l -> ultimo -> prox = (tCelula *) malloc(sizeof(tCelula));
	l -> ultimo 		= l->ultimo -> prox;
	l -> ultimo -> voo = voo;
	l -> ultimo -> prox = NULL;	
}

// retiraVoo: retira a célula seguinte à celula
// apontada por p e armazena o item
// retirado no parâmetro pedido.
void retiraVoo(tCelula *p, tListaEnc *l, tVoo *voo){
	tCelula *q;
	if(vaziaVoo(l) || p == NULL || p->prox == NULL)
		printf("Erro!");
	else{
		q = p -> prox;
		p -> prox   = q ->prox;
		*voo = q -> voo;
		if(q -> prox == NULL) 
			l -> ultimo = p;
		free(q);			
	}
}

// imprime: imprime os itens da lista l
void imprimeVoo(tListaEnc *l){
	tCelula *aux = l -> primeiro -> prox;
	while(aux != NULL){
		printf("Codigo:\t\t\t%d\n", aux->voo.codVoo);
        printf("Origem/Destino \t\t%s/%s\n", aux->voo.cidadeOrigem, aux->voo.cidadeDestino);
        printf("Data: \t\t\t%d/%d/%d\n",aux->voo.data.dia, aux->voo.data.mes, aux->voo.data.ano);
        printf("Hora: \t\t\t%d:%d\n", aux->voo.hora.horas, aux->voo.hora.minutos);
        printf("Disponibilidade Ini: \t%d\n",aux->voo.dispInicial);
        printf("Disponibilidade Atual: \t%d\n", aux->voo.dispAtual);
        printf("Status do voo: \t\t%d\n\n", aux->voo.flag);
        printf("-------------------------------------------------\n");
		aux =  aux-> prox;
	}
}
