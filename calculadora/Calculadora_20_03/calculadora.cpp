#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"

void cabecalho(char title[TAM])
{
    system("cls");
    printf("\t\t\t####### CALCULADORA 1.0 #######\n");
    printf("\t\t\t####### %s\n\n", title);
}

int menu()
{
	int op;
    cabecalho("MENU PRINCIPAL");
    printf("\t\t[1] INSERIR FORMULA\n");
    printf("\t\t[9] SAIR\n\n");
    printf("\t\t# OPCAO: ");
	fflush(stdin);
	scanf("%d", &op);
	return op;

}

void filter(tPilha *p){
	char numstr[TAM];
	int x, y, result;
	cabecalho("CALCULO");
	printf("\t\tINFORME A EXPRESSAO: ");
	fflush(stdin);
	gets(numstr);	
	for(int i= 0; i < strlen(numstr);i++){
		switch(numstr[i]){
		case 'E':empilhar(0, p);break;
		case 'e':empilhar(0, p);break;
		case '+':
				desempilhar(&y,p);
				desempilhar(&x,p);
				result = x + y;
				empilhar(result, p);
				break;
		case '-':
				desempilhar(&y,p);
				desempilhar(&x,p);
				result = x - y;
				empilhar(result, p);
				break;
		case '/':
				desempilhar(&y,p);
				desempilhar(&x,p);
				result = x / y;
				empilhar(result, p);
				break;
		case '*':
				desempilhar(&y,p);
				desempilhar(&x,p);
				result = x * y;
				empilhar(result, p);
				break;
		default:
			desempilhar(&x,p);
			// numstr[i]-'0' hack de conversão para int
			result =  x*10 + (numstr[i]-'0');
			empilhar(result,p);
		}	
	}
	print(p);
	// zera pilha para novos calculos
	p->topo =-1;
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
			case 1: filter(&p);break;
			case 9: printf("\n\n\t\t# FINALIZANDO... [ENTER]");fflush(stdin);getchar();break;
			default: printf("\n\n\t\t# OPCAO [%d] INVALIDA! [ENTER]",op);fflush(stdin);getchar();
		}
	} while(op != 9);
}
