#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 5
#define LIM 20
#define LIMI 99

//Implementação da Aplicação

// cabecalho: Limpa a tela e imprimi o cabecalho 
// com o respectivo subtitulo informado
void cabecalho(char subtitulo[]){
	system("cls");
	printf("\t\t\t########### Trabalho 2 ###########");
	printf("\n\t\t\t########### %s \n\n", subtitulo);
}

// menu: menu retorna o valor escolhido 
// pelo usuário
int menu(){	
	int opcao;
	cabecalho("Menu Principal");
	
	printf("\n\t\t1 - Incluir Nome ");
	printf("\n\t\t2 - Pesquisar Nome ");
	printf("\n\t\t3 - Imprimir Todos os Nomes ");
	printf("\n\t\t4 - Pesquisa por Aproximacao");
	printf("\n\t\t9 - Sair ");
	printf("\n\t\tOpcao: ");
	fflush(stdin); // limpa o lixo antes de uma inserção de dados
	scanf("%d", &opcao);

	return opcao;
}

// inserirNome: Insere o nome informado pelo
// usuário na matriz nomes
void inserirNome(){	
	int tam;
	FILE *fpt;
	char str[LIMI];
	cabecalho("Inserir um Nome");
	do{
		printf("\t\tInforme o nome: ");
		fflush(stdin);
		gets(str);													
		tam = strlen(str);											// strlen() retorna o tamanho da string informada no parametro
		if(tam > LIM) printf("\n\t\tO numero maximo de caracteres foi excedido.\n");
	}while(tam > LIM);
	
	fpt = fopen("arquivo.txt", "a");
	if(fpt == NULL){
		printf("\n\n\t\tERRO: Ao abrir arquivo!");
	} else{
		printf("\n\t\tNome: %s inserido com sucesso! [ENTER]", str);
		strcat(str, "\n");
		fputs(str, fpt);											
		fclose(fpt);
	}

	fflush(stdin);
	getchar();
}

// imprimir: imprime os nomes do arquivo
void imprimir(){
	FILE *fpt;
	char aux[LIMI];
	cabecalho("Impressao");
	fpt =  fopen("arquivo.txt", "r");
	if(fpt == NULL){
		printf("\n\n\t\tERRO: Ao abrir arquivo!");
	} else{
		if(fgets(aux, LIMI, fpt) != NULL){
			printf("\n\t\tNome: %s", aux);
			while(fgets(aux, LIMI, fpt) != NULL){
				printf("\n\t\tNome: %s", aux);
			} 
		} else printf("\t\tInsera Nomes! [ENTER]");
		fclose(fpt);
	}
	fflush(stdin);
	getchar();
}

void lerArquivo(char f1[], char f2[], char str[]){
	FILE *fpt, *fpt2;
	char aux[LIMI];
	fpt =  fopen(f1, "r");	
	if(fpt == NULL){
		printf("\n\n\t\tERRO: Ao abrir arquivo!");
	} else{
		while(fgets(aux, LIMI, fpt) != NULL){
			if(strcmp(aux, str) != 0){	
				fpt2 = fopen(f2, "a");
				fputs(aux, fpt2);											
				fclose(fpt2);
			} 
		}
		fclose(fpt);
		fpt = fopen(f1, "w+");
		fclose(fpt);
	}
}

// exluirNome: recebe como parametro o nome e 
// remove do arquivo
void excluirNome(char str[]){
	lerArquivo("arquivo.txt", "arquivo2.txt", str);
	lerArquivo("arquivo2.txt", "arquivo.txt", str);
}

// procura: recebe um string por parametro
// e percorre a matriz comprando com o nome informado
// caso encontre retorna a posição do nome na matriz, 
// senão retornar -1 para validação
int procura(char str[]){
	FILE *fpt;
	char aux[LIMI];
	fpt =  fopen("arquivo.txt", "r");
	if(fpt == NULL){
		printf("\n\n\t\tERRO: Ao abrir arquivo!");
	} else{	
		while(fgets(aux, LIMI, fpt) != NULL){
			if(strcmp(aux, str) == 0){				
				fclose(fpt);
				return 1;			
			}
		}		
		fclose(fpt);
	}
	return 0;
}

// pesquisarNome:  pesquisa pelo nome informado
void pesquisarNome(){
	int tam;
	FILE *fpt;
	char str[LIMI], aux[LIMI];
	int valor, opcao;
	cabecalho("Pesquisa por Nome");
	
	fpt =  fopen("arquivo.txt", "r");	
	if(fpt == NULL){
		printf("\n\n\t\tERRO: Ao abrir arquivo!");
	} else{
		if(fgets(aux, LIMI, fpt) != NULL){
			fclose(fpt);
			do{
				printf("\t\tInforme o nome: ");
				fflush(stdin);
				fgets(str, LIMI, stdin);									// le modo arquivo do teclado				
				tam = strlen(str);											// strlen() retorna o tamanho da string informada no parametro
				if(tam > LIM) printf("\n\t\tO numero maximo de caracteres foi excedido.\n");
			}while(tam > LIM);
				
			valor = procura(str);								

			if(valor){										
				printf("\n\t\tNome: %s", str);
		
				printf("\n\t\tDeseja Excluir? [1] Sim [0] Nao.");
				printf("\n\t\tOpcao: ");
				fflush(stdin);
				scanf("%d", &opcao);

				if(opcao == 1){										// verifica se o usuário deseja excluir
					excluirNome(str);							// chama a função excluirNome() passando o nome
				}
			} else printf("\n\t\tNome nao encontrado! [ENTER]");
		} else printf("\t\tInsera Nomes! [ENTER]");
	
		fclose(fpt);
	}
	fflush(stdin);
	getchar();
}

// pesquisarAproximacao: pesquisa pelo caracter informado
void pesquisarAproximacao(){
	int j, tam;
	FILE *fpt;
	char str[LIMI], aux[LIMI];
	cabecalho("Pesquisa por Aproximacao");	
	
	fpt =  fopen("arquivo.txt", "r");
	if(fpt == NULL){
		printf("\n\n\t\tERRO: Ao abrir arquivo!");
	} else{
		if(fgets(aux, LIMI, fpt) != NULL){
			fclose(fpt);
			do{
				printf("\t\tInforme o nome: ");
				fflush(stdin);
				gets(str);													
				tam = strlen(str);											// strlen() retorna o tamanho da string informada no parametro
				if(tam > LIM) printf("\n\t\tO numero maximo de caracteres foi excedido.\n");
			}while(tam > LIM);

			fpt =  fopen("arquivo.txt", "r");
			while(fgets(aux, LIMI, fpt) != NULL){
				if(strstr(aux, str) != NULL)				// função strstr() verifica a ocorrência do segundo parametro no primeiro, 															
					printf("\n\t\tNome: %s", aux);			// senão encontrar retornar NULL	
			}
		} else printf("\t\tInsera Nomes! [ENTER]");
	
		fclose(fpt);
	}
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
		// recebe o retorno da função menu
		opcao = menu();
		switch(opcao){
			case 1: inserirNome();break;
			case 2: pesquisarNome();break;
			case 3: imprimir();break;
			case 4: pesquisarAproximacao();break;
			case 9:	sair();break;
			default: printf("\n\n\t\tOpcao invalida! [ENTER]");fflush(stdin);getchar();
		}
	}while(opcao != 9); // sai do loop quando a opção informada pelo usuário for igual a 9
}