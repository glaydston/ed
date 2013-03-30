#include <stdio.h>
#include <stdlib.h>
#include "Fila.h"

void main(){
	tFila f;
	inicializa(&f);
	enfileira(10, &f);
	enfileira(15, &f);
	enfileira(20, &f);
	enfileira(25, &f);
	imprime(&f);
	fflush(stdin);
	getchar();
}