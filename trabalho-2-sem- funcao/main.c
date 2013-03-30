#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 5
#define LIM 20
#define LIMI 99

//Implementação da Aplicação

void main(){	
	char nomes[MAX][LIM], str[LIMI];
	int i = 0, j, opcao, tam, posicao = -1;
	do{
		system("cls");
		printf("\t\t\t############ Trabalho 2 ############\n\n");
		printf("\n\t\t1 - Incluir Nome ");
		printf("\n\t\t2 - Pesquisar Nome ");
		printf("\n\t\t3 - Imprimir Todos os Nomes ");
		printf("\n\t\t4 - Pesquisa por Aproximacao");
		printf("\n\t\t9 - Sair ");
		printf("\n\t\tOpcao: ");
		fflush(stdin);																				// limpa o lixo antes de uma inserção de dados
		scanf("%d", &opcao);

		switch(opcao){
			case 1: 
				if(i < MAX){	
					system("cls");		
					printf("\t\t############ Inserir ############\n\n");																	// verifica se o contador é menor que o MAX de nomes
					do{
						printf("\t\tInforme o nome: ");
						fflush(stdin);
						gets(str);													
						tam = strlen(str);															// strlen() retorna o tamanho da string informada no parametro
						if(tam > LIM) printf("\n\t\tO numero maximo de caracteres foi excedido.\n");
					}while(tam > LIM);
					strcpy(nomes[i], str);															// strcpy() copia a segunda string informada no parametro para a primeira string
					printf("\n\t\tNome: %s inserido com sucesso! [ENTER]", nomes[i]);
					i++;																			// incrementa o contador para o próxima inserção
				} else printf("\n\n\t\tLimite Atigindo! [ENTER]");
				fflush(stdin);
				getchar();
				break;
			case 2: 
				if(i > 0){
					system("cls");		
					printf("\t\t############ Pesquisa ############\n\n");
					do{
						printf("\t\tInforme o nome: ");
						fflush(stdin);
						gets(str);													
						tam = strlen(str);															// strlen() retorna o tamanho da string informada no parametro
						if(tam > LIM) printf("\n\t\tO numero maximo de caracteres foi excedido.\n");
					}while(tam > LIM);
					// procura o nome na matriz
					for(j=0;j < i; j++)
						if(strcmp(nomes[j], str) == 0)		
							posicao = j;															// retornar o índice
					if( posicao != -1){																// verifica se a posição existe
						printf("\n\t\tNome: %s", nomes[posicao]);
		
						printf("\n\t\tDeseja Excluir? [1] Sim [0] Nao.");
						printf("\n\t\tOpcao: ");
						fflush(stdin);
						scanf("%d", &opcao);

						if(opcao == 1){																// verifica se o usuário deseja excluir
							printf("\n\t\tNome: %s excluido!", nomes[posicao]);
							for(j = posicao; j < i; j++)
								strcpy(nomes[j], nomes[j+1]);										// copia o nome da posição posterior para a posição atual
							i--;						
						}

					} else printf("\n\t\tNome nao encontrado! [ENTER]");
				} else printf("\n\n\t\tInsera Nomes! [ENTER]");
				fflush(stdin);
				getchar();
				break;
			case 3: 
				if(i > 0){
					system("cls");
					printf("\t\t############ Impressao ############\n\n");
					for(j = 0; j < i; j++)
						printf("\n\t\tNome: %s", nomes[j]);
				} else printf("\n\n\t\tInsera Nomes! [ENTER]");
				fflush(stdin);
				getchar();
				break;
			case 4: 		
				if(i > 0){
					system("cls");		
					printf("\t\t############ Pesquisa por Aproximacao ############\n\n");
					do{
						printf("\t\tInforme o nome: ");
						fflush(stdin);
						gets(str);													
						tam = strlen(str);																// strlen() retorna o tamanho da string informada no parametro
						if(tam > LIM) printf("\n\t\tO numero maximo de caracteres foi excedido.\n");
					}while(tam > LIM);
					for(j=0;j < i; j++)
						if(strstr(nomes[j], str) != NULL)												// função strstr() verifica a ocorrência do segundo parametro no primeiro, 															
							printf("\n\t\tNome: %s", nomes[j]);											// senão encontrar retornar NULL	
				} else printf("\n\n\t\tInsera Nomes! [ENTER]");
				fflush(stdin);
				getchar();
				break;
			case 9:	
				system("cls");
				printf("\t\t############ Sair ############\n\n");
				printf("\t\tFinalizando Aplicacao....! [ENTER]");
				fflush(stdin);
				getchar();
				break;
			default: printf("\n\n\t\tOpcao invalida! [ENTER]");fflush(stdin);getchar();
		}
	}while(opcao != 9);																					// sai do loop quando a opção informada pelo usuário for igual a 9
}