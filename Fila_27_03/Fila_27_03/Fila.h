// Fila.h
#include <stdio.h>
#include <stdlib.h>
#define MAX 100

// Definição da estrutura
typedef struct {
		int item[MAX];
		int frente;
		int tras;
}tFila;

// Prototipos das funções
int	vazia(tFila *f);
void	inicializa(tFila *f);
void	enfileira(int x, tFila *f);
void	desenfileira(int *x, tFila *f);
void	imprime(tFila *f);
