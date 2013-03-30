#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lista.h"

//Implementação da Aplicação

// cabecalho: Limpa a tela e imprimi o cabecalho 
// com o respectivo subtitle informado
void cabecalho(char subtitle[]){
	system("cls");
	printf("\t\t\t########### Diario ###########");
	printf("\n\t\t\t########### %s \n\n",subtitle);
}

// menu: menu atribui o valor escolhido 
// pelo usuário por referência
void menu(int *op){
	cabecalho("Menu Principal");

	// opções do menu
	printf("\t\t1 - Ler arquivo\n");
	printf("\t\t2 - Gerar Listas\n");	
	printf("\t\t3 - Resultado\n");
	printf("\t\t0 - Sair\n");

	printf("\n\t\tOpcao: ");
	fflush(stdin);
	scanf("%d", op);
}

// lerArquivo: le o arquivo informado 
// e armazena na lista os dados do arquivo
void lerArquivo(char arquivo[],tLista *l){
	FILE *fp;
	tItem item;

	fp = fopen(arquivo, "rb");
	if(fopen == NULL)
		return;

	while(fread(&item, sizeof(tItem), 1, fp))		
		insere(item, l);
	fclose(fp);
}

// gravarArquivo: grava os dados
// da lista no arquivo informando
void gravarArquivo(char arquivo[], tLista *l){
	FILE *fp;
	tCelula *aux = l -> ultimo -> prox; 
	fp = fopen(arquivo, "wb");
	
	if(fopen == NULL){
		printf("\n\t\t# Erro: Arquivo nao pode ser criado. [ENTER]");
		getchar();
		return;
	}

	while(aux != NULL){
		fwrite(aux, sizeof(tItem), 1, fp);
		aux = aux ->prox;
	}
	fclose(fp);
}


// lerDados: chama a função lerArquivo e 
// imprime os dados da lista encadeada
void lerDados(tLista *l){
	cabecalho("Imprimindo - Aluno(s)");
	lerArquivo("diario.bin", l);
	if(vazia(l))
		printf("\t\t# Erro: Não existe alunos cadastrados! [ENTER]");
	else imprime(l);

	fflush(stdin);
	getchar();
}

// resultado: trata as notas dos alunos
// e salva-os nas devidas listas.
void resultado(tLista *l, tLista *a, tLista *r){	
	float soma;	
	// estrutura da celula
	tCelula *aux = l -> primeiro;
	tItem item;

	cabecalho("Gerar Lista");
	
	if(vazia(l))
		printf("\t\t# Erro: Carregar a lista! [ENTER]");
	else{
		while(!vazia(l)){
			soma = 0.0;
			for(int i = 0; i < 8; i++)
				soma += aux->prox->item.notas[i];
			retira(aux, l, &item);
			if(soma >= 60.0 && aux->prox->item.faltas <= 20)
				insere(item, a);
			else			
				insere(item, r);
		}

		// grava no arquivo
		gravarArquivo("aprovados.bin",	a);
		gravarArquivo("reprovados.bin", r);
		printf("\t\t# Informacao: Listas geradas! [ENTER]");
	}
	fflush(stdin);
	getchar();
}

void imprimir(tLista *a, tLista *r){	
	cabecalho("Resultado");
	if(vazia(a) || vazia(r))
		printf("\t\t# Erro: Carregar a lista! [ENTER]");
	else{
		// ler os arquivos	
		lerArquivo("aprovados.bin", a);
		lerArquivo("reprovados.bin",r);

		// imprime listas
		printf("\n\n\t\t\t######### Aprovados #########\n\n");	
		imprime(a);

		printf("\n\n\t\t\t######### Reprovados #########\n\n");
		imprime(r);
	}
	
	fflush(stdin);
	getchar();
}

// finaliza: Informa que a aplicação
// está finalizando
void finaliza(){
	printf("\n\n\t\t# Finalizando aplicacao... [ENTER]");
	fflush(stdin);
	getchar();
}

// main: Executa as funções da aplicação
void main(){
	int opcao;
	tLista diario;
	tLista aprovados;
	tLista reprovados;
	// inicializa as listas
	inicializa(&diario);
	inicializa(&aprovados);
	inicializa(&reprovados);
	do{
		menu(&opcao);
		switch(opcao){
		case 1: lerDados(&diario);break;
		case 2: resultado(&diario, &aprovados, &reprovados); break;
		case 3: imprimir(&aprovados, &reprovados); break;
		case 0: finaliza();break;
		default: printf("\n\n\t\tOpcao invalida!");fflush(stdin);getchar();
		}
	}while(opcao != 0);
}