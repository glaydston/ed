#include <stdio.h>
#include <stdlib.h>
#include "Pilha.h"
#define MAX 100

char ch[MAX], ch2[MAX];
int a[MAX], b[MAX];

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

// openFile: recebe com parâmetro o nome
// do arquivo a ser lido, imprime o dados
// do arquivo e retornar se foi possivel
// abrir ou não o arquivo
int openFile(char arquivo[], int escolha){
	FILE *fptr;
	char cha[MAX];
	int i = 0;
	fptr = fopen(arquivo,"r");
	if(fptr == NULL)
		return 0;	
	if(escolha)
		while(fscanf(fptr, "%c %d %c %d",&ch[i], &a[i],&ch2[i], &b[i]) != EOF)
			i++;
	else
		while(fgets(cha,MAX, fptr) != NULL){ 
			printf("\t\t%s", cha);
			i = 1;
		}	
	fclose(fptr);
	return i;
}

// getFile: Chama a função openFile() passando 
// o nome  do arquivo, caso ocorra algum erro
// ao tentar abrir o arquivo exibi na tela uma
// mensagem de erro
void getFile(){
	char texto[MAX];
	cabecalho("LENDO ARQUIVO...");
	int valor = openFile("saida.txt", 0);
	if(!valor)
		printf("\n\n\t\t# ERRO: NAO FOI POSSIVEL ABRIR O ARQUIVO! [ENTER]");
	fflush(stdin);
	getchar();
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

// comparaValor:  compara se a e b estão
// na mesma pilha p, retorna 1 para sim e
// 0 caso não estejam em pilhas diferentes
int comparaValor(int a, int b, tPilha p[]){

	for(int i= 0; i <= sizeof(p);i++){
		tCelula *aux = p[i].topo->prox;
		while(aux != NULL){
			tCelula *aux2 = aux->prox;
			while(aux2 != NULL){
				if(aux->item == a && aux2->item == b)
					return 1;
				aux2 = aux2->prox;
			}
			aux = aux->prox;
		}
	}
	return 0;
}

// procuraValor: procura a na pilha p
// retornando o indice para pilha, onde a
// foi encontrado, caso não encontre retorna 0
int procuraValor(int a, tPilha p[]){
	for(int i= 0; i <= sizeof(p);i++){
		tCelula *aux = p[i].topo->prox;
		while(aux != NULL){
			if(aux->item == a)
				return i;
			aux = aux ->prox;
		}
	}
	return 0;
}

// moverAcima: move o bloco A para o 
// acima do bloco B, retornando à
// posição inicial os demais blocos sobre
// o bloco B
void moverAcima(int i, int retornoA, int retornoB, tPilha p[]){
	int valorA, valorB, valorAux;

	if(acessaTopo(&valorA, (p + retornoA)) && valorA == a[i]){
		desempilhar(&valorA, (p + retornoA));
		//verifica o topo do bloco B
		if(acessaTopo(&valorB, (p + retornoB)) && valorB == b[i]){
			empilhar(valorA, (p + retornoB));
		}else{
			while(acessaTopo(&valorB, (p + retornoB)) && valorB != b[i]){
				desempilhar(&valorAux, (p + retornoB));
				empilhar(valorAux, (p + valorAux));
			}
			empilhar(valorA, (p + retornoB));
		}
	}else{
		while(acessaTopo(&valorA, (p + retornoA)) && valorA != a[i]){
			desempilhar(&valorAux, (p + retornoA));
			empilhar(valorAux, (p + valorAux));
		}
		desempilhar(&valorA, &p[retornoA]);
		//verifica o topo do bloco B
		if(acessaTopo(&valorB, (p + retornoB)) && valorB == b[i]){
			empilhar(valorA, (p + retornoB));
		}else{
			while(acessaTopo(&valorB, (p + retornoB)) && valorB != b[i]){
				desempilhar(&valorAux, (p + retornoB));
				empilhar(valorAux, (p + valorAux));
			}
			empilhar(valorA, (p + retornoB));
		}
	}
	printf("\n\t\tMOVER %d ACIMA %d",a[i], b[i]);
}

// moverTopo: move o bloco A para o topo
// onde o bloco B esta, remove todos
// os blocos sobre o bloco A, retornando-os
// as posições iniciais
void moverTopo(int i, int retornoA, int retornoB, tPilha *p){	
	int valorA, valorB, valorAux;

	if(acessaTopo(&valorA, (p + retornoA)) && valorA == a[i]){
		desempilhar(&valorA, (p + retornoA));
		empilhar(valorA, (p + retornoB));
	}else{
		//verifica o valor do topo do bloco A
		while(acessaTopo(&valorA, &p[retornoA]) && valorA != a[i]){
			desempilhar(&valorAux, &p[retornoA]);
			empilhar(valorAux, (p + valorAux));
		}
		desempilhar(&valorA, (p + retornoA));
		empilhar(valorA, (p + retornoB));
	}
	printf("\n\t\tMOVER %d TOPO %d",a[i], b[i]);
}

// readFile: chama a função openFile(), recebendo seu retorno
// e trata a o call das funções moverAcima() e moverTopo() 
void readFile(){
	int valor,retornoA, retornoB;
	cabecalho("LENDO ARQUIVO...");
	//valor recebe o retorno da função openFile(parametro);
	valor = openFile("comandos.txt", 1);
	//verifica se o retorno é diferente de 0
	if(valor){
		//converte caracter para inteiro
        //pega o valor da primeira linha do arquivo
		int j = ch[0]-'0';
		tPilha p[MAX];
		//inicializa os blocos
		for(int i = 0; i < j; i++){
			inicializa(&p[i]);
			empilhar(i,&p[i]);
		}		
        //valor = quantidade de linha de comandos do arquivo
		for(int i = 1; i < valor; i++ ){		
			retornoA = procuraValor(a[i], p);
			retornoB = procuraValor(b[i], p);
			switch(ch[i]){
			case 'm':						
					if(a[i] == b[i] || comparaValor(a[i], b[i], p)){
						printf("\n\n\t\tERRO: COMANDO IGNORADO!");
					}else{
						//mover acima
						if(ch2[i] == 'a')
							moverAcima(i, retornoA, retornoB, p);				
						//mover topo
						if(ch2[i] == 't')						
							moverTopo(i, retornoA, retornoB, p);
					}
				break;
			case 's':
				createFile(p);
				printf("\n\t\tSAIR [ENTER]");
				break;
			default:
				break;
			}
		}
	}else
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
			case 1: readFile();break;
			case 2: getFile();break;
			case 9: endApplication();break;
			default: illegalValue(op);break;
		}
	} while(op != 9);
	return 0;
}