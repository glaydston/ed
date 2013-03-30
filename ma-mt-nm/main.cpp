#include <stdio.h>
#include <stdlib.h>
#include "Pilha.h"
#define MAX 100

// cabecalho: exibi o cabecalho com o 
// atual subtitle informado
void cabecalho(char subtitle[])
{
    system("cls");
    printf("\t\t\t####### ATPS ES. DADOS #######\n");
    printf("\t\t\t####### %s\n\n", subtitle);
}

// menu: exibi as opções do menu
// e retorna a opção selecionada
int menu()
{
	int op;
    cabecalho("MENU PRINCIPAL");
    printf("\t\t[1] LER ARQUIVO\n");
    printf("\t\t[2] LER RESULTADO\n");
    printf("\t\t[9] SAIR\n\n");
    printf("\t\t# OPCAO: ");
	fflush(stdin);
	scanf("%d", &op);
	return op;

}

// moverAcima: move o bloco A para o 
// acima do bloco B, retornando à
// posição inicial os demais blocos sobre
// o bloco B
void moverAcima(int a, int b, int retornoA, int retornoB, tPilha p[]){
	int valorA, valorB, valorAux;

	if(acessaTopo(&valorA, (p + retornoA)) && valorA == a){
		desempilhar(&valorA, (p + retornoA));
		//verifica o topo do bloco B
		if(acessaTopo(&valorB, (p + retornoB)) && valorB == b){
			empilhar(valorA, (p + retornoB));
		}else{
			while(acessaTopo(&valorB, (p + retornoB)) && valorB != b){
				desempilhar(&valorAux, (p + retornoB));
				empilhar(valorAux, (p + valorAux));
			}
			empilhar(valorA, (p + retornoB));
		}
	}else{
		while(acessaTopo(&valorA, (p + retornoA)) && valorA != a){
			desempilhar(&valorAux, (p + retornoA));
			empilhar(valorAux, (p + valorAux));
		}
		desempilhar(&valorA, &p[retornoA]);
		//verifica o topo do bloco B
		if(acessaTopo(&valorB, (p + retornoB)) && valorB == b){
			empilhar(valorA, (p + retornoB));
		}else{
			while(acessaTopo(&valorB, (p + retornoB)) && valorB != a){
				desempilhar(&valorAux, (p + retornoB));
				empilhar(valorAux, (p + valorAux));
			}
			empilhar(valorA, (p + retornoB));
		}
	}
	printf("\n\t\tMOVER %d ACIMA %d",a, b);
}

// moverTopo: move o bloco A para o topo
// onde o bloco B esta, remove todos
// os blocos sobre o bloco A, retornando-os
// as posições iniciais
void moverTopo(int a, int b, int retornoA, int retornoB, tPilha *p){	
	int valorA, valorB, valorAux;

	if(acessaTopo(&valorA, (p + retornoA)) && valorA == a){
		desempilhar(&valorA, (p + retornoA));
		empilhar(valorA, (p + retornoB));
	}else{
		//verifica o valor do topo do bloco A
		while(acessaTopo(&valorA, &p[retornoA]) && valorA != a){
			desempilhar(&valorAux, &p[retornoA]);
			empilhar(valorAux, (p + valorAux));
		}
		desempilhar(&valorA, (p + retornoA));
		empilhar(valorA, (p + retornoB));
	}
	printf("\n\t\tMOVER %d TOPO %d", a, b);
}

// createFile: gera o arquivo de saida
// imprimindo a pilha p[], de forma inversa
// no arquivo
void createFile(tPilha p[]){
	FILE *fptr;
	int num[MAX];
	fptr = fopen("saida.txt", "w+");
	for(int i= 0; i <= sizeof(p); i++){
		tCelula *aux = p[i].topo->prox;
		fprintf(fptr,"\nBLOCO [%d]: ",i);
		int j = 0;
		while(aux != NULL){
			num[++j] = aux->item;
			aux = aux->prox;
		}
		while(0 < j)
			fprintf(fptr," %d",num[j--]);
	}
	fclose(fptr);
}

// filter: recebe os parametros da função openFile(), 
// e trata a o call das funções moverAcima() e moverTopo() 
void filter(tPilha p[], char ch[], int a, int b){
	int retornoA, retornoB;

	retornoA = procuraValor(a, p);
	retornoB = procuraValor(b, p);
	switch(ch[0]){
	case 'M':						
			if(a == b || comparaValor(a, b, p)){
				printf("\n\n\t\tERRO: COMANDO IGNORADO!");
			}else{
				//mover acima
				if(ch[1] == 'A')
					moverAcima(a, b, retornoA, retornoB, p);				
				//mover topo
				if(ch[1] == 'T')						
					moverTopo(a, b, retornoA, retornoB, p);
			}
		break;
	case 'S':
		createFile(p);
		printf("\n\t\tSAIR [ENTER]");
		break;
	default:
		break;
	}
}

// openFile: recebe com parâmetro o nome
// do arquivo a ser lido, imprime o dados
// do arquivo e retornar se foi possivel
// abrir ou não o arquivo
int openFile(char arquivo[], int escolha){
	FILE *fptr;
	int i = 0;
	char cha[MAX];	
	char ch[MAX];
	int	 a[MAX], b[MAX];
	tPilha p[MAX];
	cabecalho("LENDO ARQUIVO...");

	fptr = fopen(arquivo, "r");
	if(escolha){			
		if(fptr == NULL){
			printf("\t\t# ERRO: IMPOSSIVEL ABRIR O ARQUIVO. [ENTER]");
			fflush(stdin);
			getchar();
			return 0;
		}else{
			while(fscanf(fptr, "%s %d %d", ch, &a[i], &b[i]) != EOF){
				if(!i){
					// converte caracter para inteiro
					// pega o valor da primeira linha do arquivo
					int j = ch[0]-'0';
					// inicializa os blocos
					for(int i = 0; i < j; i++){
						inicializa(&p[i]);
						empilhar(i,&p[i]);
					}
				}
				filter(p, ch, a[i], b[i]);
				i++;			
			}
		}
		fflush(stdin);
		getchar();
	}else		
		if(fptr == NULL)
			return 0;	
		else
			while(fgets(cha,MAX, fptr) != NULL) 
				printf("\t\t%s", cha);

	fclose(fptr);
	return 1;
}

// getFile: Chama a função openFile() passando 
// o nome  do arquivo, caso ocorra algum erro
// ao tentar abrir o arquivo exibi na tela uma
// mensagem de erro
void getFile(){
	int valor = openFile("saida.txt", 0);
	if(!valor)
		printf("\n\n\t\t# ERRO: NAO FOI POSSIVEL ABRIR O ARQUIVO! [ENTER]");
	fflush(stdin);
	getchar();
}

// endApplication: Informa que a aplicação 
// está finalizando
void endApplication(){
	printf("\n\n\t\t# FINALIZANDO... [ENTER]");
	fflush(stdin);
    getchar();
}

// illegalValue: recebe como parâmetro
// a opção informada pelo usuario e informa
// que a opção o valor é invalido
void illegalValue(int op){
	printf("\n\n\t\t# OPCAO [%d] INVALIDA! [ENTER]",op);
	fflush(stdin);
	getchar();
}

// main: Executa as funções da aplicação
int main(){
	int op;
	do{
		op = menu();
		switch(op){
			case 1: openFile("comandos.txt",1);break;
			case 2: getFile();break;
			case 9: endApplication();break;
			default: illegalValue(op);break;
		}
	} while(op != 9);
	return 0;
}
