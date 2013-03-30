//Main.cpp
#include <stdio.h>
#include <stdlib.h>
#include "Pilha.h"

// Implementação do sistema

// cabecalho: exibi cabecalho do sistema
// com respectivo titulo passado por
// parâmetro
void cabecalho(char subtitle[]){
	system("cls");
	printf("\t\t############## Pilha Encadeada 15/05 ##############\n");
	printf("\t\t############## %s\n\n", subtitle);
}

// menu: exibi as opções do menu
// retornando o valor informado por
// referência ao parâmetro
void menu(int *op){
	cabecalho("Menu Principal");
	printf("\t\t1 - Empilhar\n");
	printf("\t\t2 - Desempilhar\n");
	printf("\t\t3 - Imprimir\n");
	printf("\t\t0 - Sair\n");
	printf("\t\tOpcao: ");
	fflush(stdin);
	scanf("%d", op);
}

// empilhar: empilha o dado na
// pilha p
void empilhar(tPilha *p){
	cabecalho("Empilhar");
	int x;
	printf("\t\tNumero: ");
	fflush(stdin);
	scanf("%d", &x);
	empilha(x, p);
}

// desempilhar: desempilha o dado
// da pilha p
void desempilhar(tPilha *p){
	cabecalho("Desempilhar");
	int x;
	desempilha(&x, p);
	printf("\t\tNumero removido: %d",x);
	fflush(stdin);
	getchar();
}

// imprimir: imprimi os dados 
// da pilha p
void imprimir(tPilha *p){
	cabecalho("Pilha");
	imprime(p);
	fflush(stdin);
	getchar();
}


// main: executa as funções da
// aplicação
void main(){
	int opcao;
	tPilha p;
	inicializa(&p);
	do{
		menu(&opcao);
		switch(opcao){
		case 1: empilhar(&p);break;
		case 2: desempilhar(&p);break;
		case 3: imprimir(&p);break;
		case 0: printf("\n\n\t\t# Finalizando aplicacao... [ENTER]");getchar();break;
		default: printf("\n\n\t\t# Opcao [%d] invalida! [ENTER]", opcao);getchar();
		}
	}while(opcao != 0);
}