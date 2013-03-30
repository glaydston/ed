#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

//Implementação da Aplicação

// cabecalho: Limpa a tela e imprimi o cabecalho 
// com o respectivo subtitle informado
void cabecalho(char subtitle[]){
	system("cls");
	printf("\t\t\t########### Lista Encadeada 08/05 ###########");
	printf("\n\t\t\t########### %s \n\n",				subtitle);
}

// menu: menu atribui o valor escolhido 
// pelo usuário por referência
void menu(int *op){
	cabecalho("Menu Principal");

	// opções do menu
	printf("\t\t1 - Incluir\n");	
	printf("\t\t2 - Imprimir\n");
	printf("\t\t0 - Sair\n");

	printf("\n\t\tOpcao: ");
	fflush(stdin);
	scanf("%d", op);
}

void lerArquivo(tLista *l){
	FILE *fp;
	tItem item;

	inicializa(l);
	fp = fopen("turma.bin", "rb");
	if(fopen == NULL)
		return;
	while(fread(&item, sizeof(tItem), 1, fp))		
		insere(item, l);
	fclose(fp);
}

// gravarArquivo: grava os dados
// da lista no arquivo informando
void gravarArquivo(tLista *l){
	FILE *fp;
	tCelula *aux = l -> ultimo -> prox; 
	fp = fopen("turma.bin", "wb");
	
	if(fopen == NULL){
		printf("\n\t\t# Erro: Arquivo nao pode ser criado. [ENTER]");
		getchar();
		return;
	}

	while(aux != NULL){
		fwrite(aux, sizeof(tItem), 1, fp);
		aux = aux ->prox;
	}
	fclose(fp);
}

// incluir: inclui dados na lista
// encadeada
void incluir(tLista *l){
	tItem item;
	cabecalho("Incluir - Aluno");
	
	printf("\t\tInforme o codigo: ");
	fflush(stdin);
	scanf("%d", &item.codigo);

	printf("\n\t\tInforme o nome: ");
	fflush(stdin);
	gets(item.nome);

	printf("\n\t\tInforme a nota: ");
	fflush(stdin);
	scanf("%f", &item.nota);

	insere(item, l);
	gravarArquivo(l);
	fflush(stdin);
	getchar();
}

// imprimir: imprimi os dados da lista
// encadeada
void imprimir(tLista *l){
	cabecalho("Imprindo - Aluno(s)");
	lerArquivo(l);
	if(vazia(l))
		printf("\t\t# Erro: Não existe alunos cadastrados! [ENTER]");
	else imprime(l);

	fflush(stdin);
	getchar();
}

// finaliza: Informa que a aplicação
// está finalizando
void finaliza(){
	printf("\n\n\t\t# Finalizando aplicacao... [ENTER]");
	fflush(stdin);
	getchar();
}

// main: Executa as funções da aplicação
void main(){
	int opcao;
	tLista turma;
	inicializa(&turma);
	do{
		menu(&opcao);
		switch(opcao){
		case 1: incluir(&turma); break;
		case 2: imprimir(&turma); break;
		case 0: finaliza();
		}
	}while(opcao != 0);
}