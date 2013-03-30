#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"
void cabecalho(char title[TAM])
{
    system("cls");
    printf("\t\t\t####### PILHA #######\n");
    printf("\t\t\t####### %s\n\n", title);
}

int menu()
{
	int op;
    cabecalho("MENU PRINCIPAL");
    printf("\t\t[1] EMPILHAR\n");
    printf("\t\t[2] DESEMPILHAR\n");
    printf("\t\t[3] IMPRIMIR\n");
    printf("\t\t[9] SAIR\n\n");
    printf("\t\t# OPCAO: ");
	fflush(stdin);
	scanf("%d", &op);

	return op;

}

void filter(int op, tPilha *p){
	int num = 0, choose;
	do{
		if(op){
			cabecalho("EMPILHAR");
			if(p->topo == MAX-1){
				printf("\t\t#ERRO: PILHA CHEIA! [ENTER]");
				fflush(stdin);
				getchar();
				break;
			}else{
				printf("\t\tNUMERO: ");
				fflush(stdin);
				scanf("%d",&num); 			
				//adiciona numero a pilha, empilhar(numero a ser adicionado, pilha);
				empilhar(num, p);
			}
		}else{
			cabecalho("DESEMPILHAR");
			//verifica se existe numeros cadastrados
			if(isEmpty(p)){
				printf("\t\t# ERRO: CADASTRE NUMERO(S)! [ENTER]");
				fflush(stdin);
				getchar();
				break;
			}else{
					num = p->item[p->topo];
					//remove o numero da pilha, desempilhar(numero, pilha);
					desempilhar(&num, p);
					printf("\n\t\t# NUMERO: %d DESEMPILHADO!\n",num);
				}
			}
		printf("\n\t\t# DESEJA CONTINUAR? [1] SIM [9] NAO");
		printf("\n\t\t# OPCAO: ");
		fflush(stdin);
		scanf("%d", &num);
	} while(num == 1);

}

void imprimir(tPilha *p){
	cabecalho("PILHA");
	//verifica se existe algo cadastrado
	if(isEmpty(p))
		printf("\t\t# ERRO: CADASTRE NUMERO(S)! [ENTER]");
	else
		//imprimi a pilha passada pelo parametro, print(pilha);
		print(p);
	fflush(stdin);
	getchar();
}


void main(){
	int op;
	tPilha p;
	//inicializa a pilha, load(pilha);
	load(&p);
	do{
		op = menu();
		switch(op){
			case 1: filter(1, &p);break;
			case 2: filter(0, &p);break;
			case 3: imprimir(&p);break;
			case 9: printf("\n\n\t\t# FINALIZANDO... [ENTER]");fflush(stdin);getchar();break;
			default: printf("\n\n\t\t# OPCAO [%d] INVALIDA! [ENTER]",op);fflush(stdin);getchar();
		}
	} while(op != 9);
}