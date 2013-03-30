#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"
char ch[MAX] = "";

void cabecalho(char title[TAM])
{
    system("cls");
    printf("\t\t\t####### ATPS ES. DADOS #######\n");
    printf("\t\t\t####### %s\n\n", title);
}

int menu()
{
	int op;
    cabecalho("MENU PRINCIPAL");
    printf("\t\t[1] LER ARQUIVO\n");
	printf("\t\t[2] GERAR RESULTADO\n");
    printf("\t\t[9] SAIR\n\n");
    printf("\t\t# OPCAO: ");
	fflush(stdin);
	scanf("%d", &op);
	return op;

}
int openFile(){
	FILE *fptr;
	char ch2[MAX];
	//zera a string
	strcpy(ch,"");
	//abre o arquivo somente para leitura
	fptr = fopen("comandos.txt","r");
	if(fptr == NULL)
		return 0;	
	while(fgets(ch2, MAX, fptr) != NULL)
		strcat(ch, ch2);
	//fecha o arquivo
	fclose(fptr);
	return 1;
}

void readFile(tPilha *p){
	cabecalho("LENDO ARQUIVO...");
	int valor;
	char command[MAX];
	//valor recebe o retorno da função openFile(parametro);
	//openFile(parametro) atribui valor por referência
	valor = openFile();
	//verifica se o retorno é diferente de 0
	if(valor){
		printf("%s",ch);
	}else		
		printf("\n\n\t\t# ERRO: NAO FOI POSSIVEL ABRIR O ARQUIVO! [ENTER]");
	fflush(stdin);
	getchar();
}

void createFile(tPilha *p){
	cabecalho("GERANDO ARQUIVO...");
	printf("\n\n\tEM CONSTRUCAO! [ENTER]");
	fflush(stdin);
	getchar();
}

void endApplication(){
	printf("\n\n\t\t# FINALIZANDO... [ENTER]");
	fflush(stdin);
	getchar();
}

void illegalValue(int op){
	printf("\n\n\t\t# OPCAO [%d] INVALIDA! [ENTER]",op);
	fflush(stdin);
	getchar();
}

void main(){
	int op;
	tPilha p;
	do{
		//menu() retorna o valor informado pelo usuário a op 
		op = menu();
		switch(op){
			case 1: readFile(&p);break;
			case 2: createFile(&p);break;
			case 9: endApplication();break;
			default: illegalValue(op);
		}
	} while(op != 9);
}
