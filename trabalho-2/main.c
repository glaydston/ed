#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 5
#define LIM 20
#define LIMI 99

char nomes[MAX][LIM];
int i = 0;

//Implementa��o da Aplica��o

// cabecalho: Limpa a tela e imprimi o cabecalho 
// com o respectivo subtitulo informado
void cabecalho(char subtitulo[]){
	system("cls");
	printf("\t\t\t########### Trabalho 2 ###########");
	printf("\n\t\t\t########### %s \n\n", subtitulo);
}

// menu: menu retorna o valor escolhido 
// pelo usu�rio
int menu(){	
	int opcao;
	cabecalho("Menu Principal");
	
	printf("\n\t\t1 - Incluir Nome ");
	printf("\n\t\t2 - Pesquisar Nome ");
	printf("\n\t\t3 - Imprimir Todos os Nomes ");
	printf("\n\t\t4 - Pesquisa por Aproximacao");
	printf("\n\t\t9 - Sair ");
	printf("\n\t\tOpcao: ");
	fflush(stdin); // limpa o lixo antes de uma inser��o de dados
	scanf("%d", &opcao);

	return opcao;
}

// inserirNome: Insere o nome informado pelo
// usu�rio na matriz nomes
void inserirNome(){	
	int tam;
	char str[LIMI];
	cabecalho("Inserir um Nome");
	if(i < MAX){														// verifica se o contador � menor que o MAX de nomes
		do{
			printf("\t\tInforme o nome: ");
			fflush(stdin);
			gets(str);													
			tam = strlen(str);											// strlen() retorna o tamanho da string informada no parametro
			if(tam > LIM) printf("\n\t\tO numero maximo de caracteres foi excedido.\n");
		}while(tam > LIM);
		strcpy(nomes[i], str);											// strcpy() copia a segunda string informada no parametro para a primeira string
		printf("\n\t\tNome: %s inserido com sucesso! [ENTER]", nomes[i]);
		i++;															// incrementa o contador para o pr�xima inser��o
	} else printf("\t\tLimite Atigindo! [ENTER]");
	fflush(stdin);
	getchar();
}

// imprimir: imprime os nomes da matriz
void imprimir(){
	int j;
	cabecalho("Impressao");
	if(i > 0){
		for(j = 0; j < i; j++)
			printf("\n\t\tNome: %s", nomes[j]);
	} else printf("\t\tInsera Nomes! [ENTER]");
	fflush(stdin);
	getchar();
}

// exluirNome: recebe como parametro a posi��o
// do nome e remove da matriz organizando-a
void excluirNome(int posicao){
	int j;
	printf("\n\t\tNome: %s excluido!", nomes[posicao]);
	for(j = posicao; j < i; j++)
		strcpy(nomes[j], nomes[j+1]);							// copia o nome da posi��o posterior para a posi��o atual
	i--;	
}

// procura: recebe um string por parametro
// e percorre a matriz comprando com o nome informado
// caso encontre retorna a posi��o do nome na matriz, 
// sen�o retornar -1 para valida��o
int procura(char str[]){
	int j;	
	for(j=0;j < i; j++)
		if(strcmp(nomes[j], str) == 0)
			return j;

	return -1;
}

// pesquisarNome:  pesquisa pelo nome informado
void pesquisarNome(){
	int tam;
	char str[LIMI];
	int posicao, opcao;
	cabecalho("Pesquisa por Nome");

	if(i > 0){
		do{
			printf("\t\tInforme o nome: ");
			fflush(stdin);
			gets(str);													
			tam = strlen(str);											// strlen() retorna o tamanho da string informada no parametro
			if(tam > LIM) printf("\n\t\tO numero maximo de caracteres foi excedido.\n");
		}while(tam > LIM);
		posicao = procura(str);									// passa o nome informado para fun��o procura() e recebe o retorno

		if( posicao != -1){										// verifica se a posi��o existe
			printf("\n\t\tNome: %s", nomes[posicao]);
		
			printf("\n\t\tDeseja Excluir? [1] Sim [0] Nao.");
			printf("\n\t\tOpcao: ");
			fflush(stdin);
			scanf("%d", &opcao);

			if(opcao == 1){										// verifica se o usu�rio deseja excluir
				excluirNome(posicao);							// chama a fun��o excluirNome() passando a posi��o do nome
			}
		} else printf("\n\t\tNome nao encontrado! [ENTER]");
	} else printf("\t\tInsera Nomes! [ENTER]");
	fflush(stdin);
	getchar();
}

// pesquisarAproximacao: pesquisa pelo caracter informado
void pesquisarAproximacao(){
	int j, tam;
	char str[LIMI];
	cabecalho("Pesquisa por Aproximacao");
	if(i > 0){
		do{
			printf("\t\tInforme o nome: ");
			fflush(stdin);
			gets(str);													
			tam = strlen(str);											// strlen() retorna o tamanho da string informada no parametro
			if(tam > LIM) printf("\n\t\tO numero maximo de caracteres foi excedido.\n");
		}while(tam > LIM);
		for(j=0;j < i; j++)
			if(strstr(nomes[j], str) != NULL)				// fun��o strstr() verifica a ocorr�ncia do segundo parametro no primeiro, 															
				printf("\n\t\tNome: %s", nomes[j]);			// sen�o encontrar retornar NULL	
	} else printf("\t\tInsera Nomes! [ENTER]");
	fflush(stdin);
	getchar();
}

void sair(){
	cabecalho("Sair");
	printf("\t\tFinalizando Aplicacao....! [ENTER]");
	fflush(stdin);
	getchar();
}

void main(){
	int opcao;
	do{
		// recebe o retorno da fun��o menu
		opcao = menu();
		switch(opcao){
			case 1: inserirNome();break;
			case 2: pesquisarNome();break;
			case 3: imprimir();break;
			case 4: pesquisarAproximacao();break;
			case 9:	sair();break;
			default: printf("\n\n\t\tOpcao invalida! [ENTER]");fflush(stdin);getchar();
		}
	}while(opcao != 9); // sai do loop quando a op��o informada pelo usu�rio for igual a 9
}