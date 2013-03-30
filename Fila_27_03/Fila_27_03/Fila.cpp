// Fila.cpp
#include <stdio.h>
#include <stdlib.h>
#include "Fila.h"

// Implementações das operações

// inicializa: faz a fila f ficar
// vazia, apontando f-> frente e 
// f->tras para a mesma posição
void inicializa(tFila *f){
	f->frente	= 0;
	f->tras		= 0;
}

// vazia: retorna 1 se a fila f está vazia,
// caso contrário, retorna 0
int vazia(tFila *f){
	if(f->frente == f->tras)
		return 1;
	return 0;
}

// enfileira: insere o item x no final 
// da fila f
void enfileira(int x, tFila *f){
	if((f->tras + 1) % MAX == f->frente)
		printf("Erro: Fila cheia.\n");
	else{
		f->item[f->tras] = x;
		f->tras =  (f->tras + 1) % MAX;
	}
}

// desenfileira: retira o item da frente 
// da fila f, retornando o no parâmetro x
void desenfileira(int *x, tFila *f){
	if(vazia(f))
		printf("Erro: Fila vazia.\n");
	else{
		*x = f->item[f->frente];
		f->frente = (f->frente + 1) % MAX;
	}
}

// imprime: imprime a fila f
void imprime(tFila *f){
	int i = f->frente;
	while(i != f->tras){
		printf("\nItem[%d]: %d", i, f->item[i]);
		i = (i + 1) % MAX;
	}
}