#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"

char ch[TAM], ch2[TAM];
int a[TAM], b[TAM];

void cabecalho(char title[MAX])
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
	printf("\t\t[2] RESULTADO\n");
    printf("\t\t[9] SAIR\n\n");
    printf("\t\t# OPCAO: ");
	fflush(stdin);
	scanf("%d", &op);
	return op;

}
int openFile(char arquivo[], int escolha){
	FILE *fptr;
	int i = 0;
	char texto[MAX];
	//abre o arquivo somente para leitura
	fptr = fopen(arquivo,"r");
	if(fptr == NULL)
		return 0;
	if(escolha)
		while(fscanf(fptr, "%c %d %c %d",&ch[i], &a[i],&ch2[i], &b[i]) != EOF)
			i++;
	else
		while(fgets(texto,MAX, fptr) != NULL){
			printf("\t\t%s", texto);
			i = 1;
		}
	//fecha o arquivo
	fclose(fptr);
	return i;
}

void createFile(tPilha p[]){
	FILE *fptr;
	fptr = fopen("resultado.txt", "w+");
	for(int i= 0; i <= sizeof(p); i++){
		fprintf(fptr,"\nBLOCO [%d]: ",i);
		for (int k = 0; k <= (p+i) -> topo; k++)
			fprintf(fptr," %d",(p+i)->item[k]);
	}
	fclose(fptr);
}

int comparaValor(int a, int b, tPilha p[]){
	int j, k;
	for(int i= 0; i <= sizeof(p);i++)
		//primeira expressão j=0; j <= (p+i)->topo; j++;
		//segunda expressão k=j+1; k <= (p+i)->topo; k++;
		for(j= 0, k=j+1; j <= (p+i)->topo, k <= (p+i)->topo; j++, k++)
			if((p+i)->item[j] == a && (p+i)->item[k] == b)
				return 1;
	return 0;
}

int procuraValor(int a, tPilha p[]){
	for(int i= 0; i <= sizeof(p);i++)
		for(int j= 0; j <= (p+i)->topo; j++)
			if((p+i)->item[j] == a)
				return i;
	return 0;
}

void moverAcima(int i, int retornoA, int retornoB, tPilha *p){
	tPilha aux;
	inicializa(&aux);
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

void empilharAcima(int i, int retornoA, int retornoB, tPilha *p){
	tPilha aux;
	inicializa(&aux);
	int valorA, valorB, valorAux;
	if(acessaTopo(&valorA, (p + retornoA)) && valorA == a[i]){
		desempilhar(&valorA, (p + retornoA));		
		//verifica o topo do bloco B
		if(acessaTopo(&valorB, (p + retornoB)) && valorB == b[i]){
			empilhar(valorA, (p + retornoB));
		}else{
			//verifica o valor do topo do bloco B
			while(acessaTopo(&valorB, (p + retornoB)) && valorB != b[i]){
				desempilhar(&valorAux, (p + retornoB));
				empilhar(valorAux, (p + valorAux));
			}
			empilhar(valorA, (p + retornoB));
		}
	}else{
		//verifica o valor do topo do bloco A
		while(acessaTopo(&valorA, (p + retornoA)) && valorA != a[i]){
			desempilhar(&valorAux, (p + retornoA));
			empilhar(valorAux, &aux);
		}
		desempilhar(&valorA, (p + retornoA));
		
		//verifica o topo do bloco B
		if(acessaTopo(&valorB, (p + retornoB)) && valorB == b[i]){
			empilhar(valorA, (p + retornoB));
			while(!isEmpty(&aux)){
				desempilhar(&valorAux, &aux);
				empilhar(valorAux, (p + retornoB));
			}
		}else{
			//verifica o valor do topo do bloco B
			while(acessaTopo(&valorB, (p + retornoB)) && valorB != b[i]){
				desempilhar(&valorAux, (p + retornoB));
				empilhar(valorAux, (p + valorAux));
			}
			empilhar(valorA, (p + retornoB));
			while(!isEmpty(&aux)){
				desempilhar(&valorAux, &aux);
				empilhar(valorAux, (p + retornoB));
			}
		}
	}
	printf("\n\t\tEMPILHAR %d ACIMA %d", a[i], b[i]);
}

void empilharTopo(int i, int retornoA, int retornoB, tPilha *p){
	tPilha aux;
	inicializa(&aux);
	int valorA, valorB, valorAux;
		//verifica o valor do topo do bloco A
	while(acessaTopo(&valorA, (p + retornoA)) && valorA != a[i]){
		desempilhar(&valorAux, (p + retornoA));
		empilhar(valorAux, &aux);
	}
	desempilhar(&valorA, (p + retornoA));	
	empilhar(valorA, (p + retornoB));
	while(!isEmpty(&aux)){
		desempilhar(&valorAux, &aux);
		empilhar(valorAux, (p + retornoB));
	}
	printf("\n\t\tEMPILHAR %d TOPO %d", a[i], b[i]);
}

void readFile(){
	cabecalho("LENDO ARQUIVO...");
	int valor, valorA, valorB, retorno, retornoA, retornoB, valorAux;
	tPilha aux;
	inicializa(&aux);
	//valor recebe o retorno da função openFile(parametro);
	//openFile(parametro) atribui valor por referência
	valor = openFile("comandos.txt", 1);
	//verifica se o retorno é diferente de 0
	if(valor){
         //converte caracter para inteiro
         //pega o valor da primeira linha do arquivo
		 int j = ch[0]-'0';
		 tPilha p[TAM];
		 //inicializa os blocos
		 for(int i = 0; i < j; i++){
			 inicializa(&p[i]);
			 empilhar(i, &p[i]);
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
			case 'e':	
					if(a[i] == b[i] || comparaValor(a[i], b[i], p)){
						printf("\n\n\t\tERRO:  COMANDO IGNORADO!");
					}else{
						//empilha acima
						if(ch2[i] == 'a')
							empilharAcima(i, retornoA, retornoB, p);					
						//empilhar topo
						if(ch2[i] == 't')
							empilharTopo(i,retornoA, retornoB, p);
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

void getFile(){
	cabecalho("LENDO ARQUIVO GERADO...");
	int valor = openFile("resultado.txt", 0);
	if(!valor)
		printf("\t\tERRO: POR FAVOR, LEIA O ARQUIVO! [ENTER]");
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

int main(){
	int op;
	do{
		//menu() retorna o valor informado pelo usuário a op
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
