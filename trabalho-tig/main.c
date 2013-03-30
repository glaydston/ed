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
	printf("\t\t\t########### Trabalho TIG ###########");
	printf("\n\t\t\t########### %s \n\n", subtitulo);
}

// menu: menu retorna o valor escolhido 
// pelo usuário
int menu(){	
	int opcao;
	cabecalho("Menu Principal");
	
	printf("\n\t\t1 - Incluir Aluno ");
	printf("\n\t\t2 - Pesquisar Aluno ");
	printf("\n\t\t3 - Imprimir Todos os Alunos ");
	printf("\n\t\t4 - Pesquisa por Aproximacao");
	printf("\n\t\t5 - Exclui um Aluno, dado uma posicao");
	printf("\n\t\t6 - Pesquisa por E-mail");
	printf("\n\t\t7 - Pesquisa por Matricula");
	printf("\n\t\t9 - Sair ");
	printf("\n\t\tOpcao: ");
	fflush(stdin); // limpa o lixo antes de uma inserção de dados
	scanf("%d", &opcao);

	return opcao;
}

// inserirAluno: Insere o aluno informado pelo
// usuário na matriz nomes
void inserirAluno(){	
	int tam;
	FILE *fpt;
	char str[LIMI], aluno[3][LIMI];
	cabecalho("Inserir Aluno");
	
	printf("\t\tMatricula: ");
	fflush(stdin);
	gets(aluno[2]);		

	do{
		printf("\t\tNome: ");
		fflush(stdin);
		gets(str);													
		tam = strlen(str);											// strlen() retorna o tamanho da string informada no parametro
		if(tam > LIM) printf("\n\t\tO numero maximo de caracteres foi excedido.\n");
	}while(tam > LIM);
		
	strcpy(aluno[0], str); // copia o nome para à estrutura

	printf("\t\tE-mail: ");
	fflush(stdin);
	gets(aluno[1]);
	
	fpt = fopen("arquivo.txt", "a");
	if(fpt == NULL){
		printf("\n\n\t\tERRO: Ao abrir arquivo!");
	} else{
		printf("\n\t\tAluno: %s inserido com sucesso! [ENTER]", aluno[0]);
		
		fputs(aluno[0], fpt);
		fputc(';', fpt);
		fputs(aluno[1], fpt);
		fputc(';', fpt);
		fputs(aluno[2], fpt);
		fputc('\n', fpt);
							
		fclose(fpt);
	}

	fflush(stdin);
	getchar();
}

// imprimir: imprime os alunos do arquivo
void imprimir(){
	FILE *fpt;
	int i = 0;
	char aux[LIMI], *token, aluno[3][LIMI];
	cabecalho("Impressao");
	fpt =  fopen("arquivo.txt", "r");
	if(fpt == NULL){
		printf("\n\n\t\tERRO: Ao abrir arquivo!");
	} else{
		if(fgets(aux, LIMI, fpt) != NULL){

			token = strtok(aux, ";");
			while(token){
				strcpy(aluno[i++], token);
				token = strtok(NULL, ";");
			}
					
			printf("\n\t\t\t Aluno");
			printf("\n\t\tNome: %s", aluno[0]);			
			printf("\n\t\tEmail: %s", aluno[1]);		
			printf("\n\t\tMatricula: %s", aluno[2]);

			while(fgets(aux, LIMI, fpt) != NULL){
				if(i==3) i = 0;

				token = strtok(aux, ";");
				while(token){
					strcpy(aluno[i++], token);
					token = strtok(NULL, ";");
				}

				printf("\n\t\t\t Aluno");
				printf("\n\t\tNome: %s", aluno[0]);			
				printf("\n\t\tEmail: %s", aluno[1]);		
				printf("\n\t\tMatricula: %s", aluno[2]);
			} 
		} else printf("\n\t\tInsera Nomes! [ENTER]");
		fclose(fpt);
	}
	fflush(stdin);
	getchar();
}

void lerArquivo(char f1[], char f2[], char str[]){
	FILE *fpt, *fpt2;
	char aux[LIMI], *token, aluno[LIMI];
	fpt =  fopen(f1, "r");	
	if(fpt == NULL){
		printf("\n\n\t\tERRO: Ao abrir arquivo!");
	} else{
		while(fgets(aux, LIMI, fpt) != NULL){	
			strcpy(aluno, aux);
			token = strtok(aux, ";");	
			if(strcmp(token, str) != 0){	
				fpt2 = fopen(f2, "a");
				fputs(aluno, fpt2);											
				fclose(fpt2);
			} 
		}
		fclose(fpt);
		fpt = fopen(f1, "w+");
		fclose(fpt);
	}
}

// exluirAluno: recebe como parametro o nome e 
// remove do arquivo
void excluirAluno(char str[]){
	printf("\n\t\tAluno: %s excluido!", str);
	lerArquivo("arquivo.txt", "arquivo2.txt", str);
	lerArquivo("arquivo2.txt", "arquivo.txt", str);
}

// procura: recebe um string por parametro
// e percorre a matriz comprando com o nome informado
// caso encontre retorna a posição do nome na matriz, 
// senão retornar -1 para validação
int procura(char str[]){
	FILE *fpt;
	char aux[LIMI], *token;
	fpt =  fopen("arquivo.txt", "r");
	if(fpt == NULL){
		printf("\n\n\t\tERRO: Ao abrir arquivo!");
	} else{	
		while(fgets(aux, LIMI, fpt) != NULL){
			token = strtok(aux, ";");
			if(strcmp(token, str) == 0){				
				fclose(fpt);
				return 1;			
			}
		}		
		fclose(fpt);
	}
	return 0;
}

// pesquisarAluno:  pesquisa pelo aluno informado
void pesquisarAluno(){
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
				gets(str);
				//fgets(str, LIMI, stdin);									// le modo arquivo do teclado				
				tam = strlen(str);											// strlen() retorna o tamanho da string informada no parametro
				if(tam > LIM) printf("\n\t\tO numero maximo de caracteres foi excedido.\n");
			}while(tam > LIM);
				
			valor = procura(str);								

			if(valor){										
				printf("\n\t\tAluno: %s", str);
		
				printf("\n\t\tDeseja Excluir? [1] Sim [0] Nao.");
				printf("\n\t\tOpcao: ");
				fflush(stdin);
				scanf("%d", &opcao);

				if(opcao == 1){										// verifica se o usuário deseja excluir
					excluirAluno(str);							// chama a função excluirNome() passando o nome
				}
			} else printf("\n\t\tNome nao encontrado! [ENTER]");
		} else printf("\t\tInsera Nomes! [ENTER]");
	
		fclose(fpt);
	}
	fflush(stdin);
	getchar();
}

void excluirPorPosicao(){
	FILE *fpt;
	int posicao, i = 0;
	char aux[LIMI], *token;
	cabecalho("Excluir por Posicao");
	
	fpt =  fopen("arquivo.txt", "r");
	if(fpt == NULL){
		printf("\n\n\t\tERRO: Ao abrir arquivo!");
	} else
		if(fgets(aux, LIMI, fpt) != NULL){
			fclose(fpt);
						
			printf("\t\tPosicao a sera excluida: ");
			fflush(stdin);
			scanf("%d", &posicao);

			fpt =  fopen("arquivo.txt", "r");
			while(fgets(aux, LIMI, fpt) != NULL){
				token = strtok(aux, ";");
				if(i+1 == posicao)
					excluirAluno(aux);
				i++;
			}
		} else printf("\t\tInsera Alunos! [ENTER]");

	fflush(stdin);
	getchar();

}

void pesquisaEspecifica(int opcao, char nomeop[]){
	int j, tam;
	FILE *fpt;
	int i = 0;
	char str[LIMI], aux[LIMI], *token, aluno[3][LIMI];

	fpt =  fopen("arquivo.txt", "r");
	if(fpt == NULL){
		printf("\n\n\t\tERRO: Ao abrir arquivo!");
	} else{
		if(fgets(aux, LIMI, fpt) != NULL){
			fclose(fpt);

			printf("\t\t%s: ", nomeop);
			fflush(stdin);
			gets(str);					
			
			fpt =  fopen("arquivo.txt", "r");
			while(fgets(aux, LIMI, fpt) != NULL){
				if(i==3) i = 0;

				token = strtok(aux, ";");
				while(token){
					strcpy(aluno[i++], token);
					token = strtok(NULL, ";");
				}

				switch(opcao){
				case 4:
					if(strstr(aluno[0], str) != NULL){					
						printf("\n\t\t\t Aluno");
						printf("\n\t\tNome: %s", aluno[0]);			
						printf("\n\t\tEmail: %s", aluno[1]);		
						printf("\n\t\tMatricula: %s", aluno[2]);
					}
					break;
				case 6: 
					if(strcmp(aluno[1], str) == 0){					
						printf("\n\t\t\t Aluno");
						printf("\n\t\tNome: %s", aluno[0]);			
						printf("\n\t\tEmail: %s", aluno[1]);		
						printf("\n\t\tMatricula: %s", aluno[2]);
					}
					break;
				case 7: 
					aluno[2][strlen(aluno[2])-1] = '\0';
					if(strcmp(aluno[2], str) == 0){					
						printf("\n\t\t\t Aluno");
						printf("\n\t\tNome: %s", aluno[0]);			
						printf("\n\t\tEmail: %s", aluno[1]);		
						printf("\n\t\tMatricula: %s", aluno[2]);
					}
					break;
				}

			}
		} else printf("\t\tInsera Alunos! [ENTER]");
	
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
			case 1: inserirAluno();break;
			case 2: pesquisarAluno();break;
			case 3: imprimir();break;
			case 4: 
				cabecalho("Pesquisa por Nome");	
				pesquisaEspecifica(4, "Nome");	
				break;
			case 5: excluirPorPosicao();break;
			case 6: 
				cabecalho("Pesquisa por E-mail"); 
				pesquisaEspecifica(6, "E-mail");
				break;
			case 7:				
				cabecalho("Pesquisa por Matricula");	
				pesquisaEspecifica(7, "Matricula");
				break;
			case 9:	sair();break;
			default: printf("\n\n\t\tOpcao invalida! [ENTER]");fflush(stdin);getchar();
		}
	}while(opcao != 9); // sai do loop quando a opção informada pelo usuário for igual a 9
}