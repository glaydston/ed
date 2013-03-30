#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lista.h"

int menu() {
	int op;
	system("cls");
	printf("\t\t\tMENU DE OPCOES\n\n");
	printf("\n\t\t1. Incluir novo pedido");
	printf("\n\t\t2. Alterar situacao do pedido");
	printf("\n\t\t3. Incluir itens em um pedido");
	printf("\n\t\t4. Excluir itens de um pedido");
	printf("\n\t\t5. Excluir pedidos cancelados");
	printf("\n\t\t6. Consultar um pedido");
	printf("\n\t\t7. Sair");
	printf("\n\t\tOpcao: ");
	fflush(stdin);
	scanf("%d", &op);

	return op;	
}


void criaItem(tListaItens *lItem){
	tItemPedido item;

	printf("\n\t\tInforme a descricao do item: ");
	fflush(stdin);
	gets(item.descricao);

	printf("\t\tInforme a qtde do item: ");
	fflush(stdin);
	scanf("%d", &item.quantidade);

	printf("\t\tInforme o preco do item: ");
	fflush(stdin);
	scanf("%f", &item.precoVenda);
	// insere item na lista lItem sequencial
	inserirItem(item, lItem);
}

void criaItens(tListaItens *itens){	
	char go;

	do { 
		if(itens->ultimo < MAX_ITEM){
			criaItem(itens);
			printf("\n\t\tDeseja continuar? ");
			fflush(stdin);
			go = getchar();		
		}else{
			printf("\n\t\tNumero maximo de itens atingido: %d", MAX_ITEM);
			fflush(stdin);
			getchar();
			break;
		}
	} while(go != 'n');

}

// criarPedido: cria o pedido e insere
// na lista encadeada l
void criarPedido(tListaEnc *l){
	tPedido pedido;
	system("cls");
	printf("\t\t\tIncluir pedido\n\n");

	printf("\t\tInforme o numero do pedido: ");
	fflush(stdin);
	scanf("%d", &pedido.numero);

	printf("\t\tInforme a data do pedido: ");
	fflush(stdin);
	gets(pedido.data);

	printf("\t\tInforme o nome do cliente: ");
	fflush(stdin);
	gets(pedido.nomeCliente);

	printf("\t\tInforme o endereco do cliente: ");
	fflush(stdin);
	gets(pedido.endereco);

	pedido.situacao = 'P';

	printf("\t\t\tItem: ");
	//iniciliza a lista sequencial
	inicializarSequencial(&pedido.itens); 
	criaItens(&pedido.itens);

	// insere o pedido na lista l - encadeada
	insere(pedido, l);
}

// buscaPedido: busca o número do pedido na
// lista
void buscaPedido(tListaEnc *l){
	int numeroPed;
	tCelula *celula = l->primeiro->prox;
	char altera;
	
	system("cls");	
	printf("\t\t\tAlterar situacao do pedido\n\n");
	printf("\t\tDigite o pedido a ser alterado: ");
	fflush(stdin);
	scanf("%d", &numeroPed);

    while (celula != NULL){
		if((celula->item.numero != numeroPed) && (celula->item.situacao != 'P') ){  
			printf("\n\n\t\tPedido nao existe ou a sua situacao nao eh Pedente!");
			printf("\n\t\tSituaçao do pedido: %c", celula->item.situacao);

		 }else{
			printf("\n\t\tSituaçao do pedido: %c", celula->item.situacao);
			printf("\n\t\tAlterar Situaçao do pedido para:\n\t\t\t C - cancelado\n\t\t\t E - entregue");
	
			printf("\n\t\tOpcao: ");		
			fflush(stdin);
			scanf("%c", &altera);

			celula->item.situacao = altera;
			printf("\n\t\tSituaçao do pedido: %c", celula->item.situacao);
		}
	 }

	fflush(stdin);
	getchar();
}

// alterarPedido: altera o pedido da lista l
void alterarPedido(tListaEnc *l){
	int numeroPed;
	system("cls");
	printf("\t\t\tAlterar Pedido\n\n");
	printf("\t\tDigite o pedido a ser alterado: ");
	fflush(stdin);
	scanf("%d", &numeroPed);
	printf("Incluir itens do pedido\n\n\n");

	fflush(stdin);
	getchar();
}

// excluirItemPedido: exclui o item do pedido
// da lista l
void excluirItemPedido(tListaEnc *l){
	printf("\t\tExcluir itens do pedido\n\n");
	
	fflush(stdin);
	getchar();
}

// excluirPedidoCancelado: exclui o pedido
// cancelado da lista l
void excluirPedidoCancelado(tListaEnc *l){	
	printf("\t\tExcluir pedidos cancelados\n\n");			
	
	fflush(stdin);
	getchar();
}

// imprimirPedido: imprime o pedido,
// passado por parametro
void imprimirPedido(tPedido pedido){

	printf("\n\t\tNumero: %d", pedido.numero);
	printf("\n\t\tData: %s", pedido.data);
	printf("\n\t\tNome do cliente: %s", pedido.nomeCliente);
	printf("\n\t\tEndereco do cliente: %s", pedido.endereco);
	printf("\n\t\tSituaçao do pedido: %c", pedido.situacao);
	printf("\n\t\tItems do pedido:");

	// imprime os itens
	imprimirItem(&pedido.itens);
	
}

// consultaPedido: consultado o numero do pedido
// informando na lista l e exibi o mesmo.
void consultaPedido(tListaEnc *l){
	int numeroPed;
	tCelula *celula = l->primeiro->prox;

	system("cls");
	printf("\t\t\tConsultar pedidos\n\n");
	printf("\t\tDigite o pedido: ");
	fflush(stdin);
	scanf("%d", &numeroPed);

	while(celula != NULL){
		if(celula->item.numero == numeroPed){
			printf("O pedido consultado e:\n");
			imprimirPedido(celula->item);
		}
		celula = celula->prox;
	}

	fflush(stdin);
	getchar();
}

// lerArquivo: le os dados do arquivo
// e carrega na lista
void lerArquivo(tListaEnc *l){
	FILE *fp;
	tPedido pedido;
	fp = fopen("pedidos.bin","rb");	

	if(fp == NULL)
		printf("\n\t\tErro ao tentar ler o arquivo.");
	else
		while(fread(&pedido,sizeof(tPedido),1,fp))
			insere(pedido,l);

	fflush(stdin);
	getchar();
}

// gerarArquivo: gera o arquivo preenchendo com os
// pedidos que estão na lista l
void gerarArquivo(tListaEnc *l){
	FILE *fp;
	fp = fopen("pedidos.bin","wb");
	if(fp == NULL)
		printf("\n\t\tErro ao tentar gerar o arquivo.");
	else{
		tCelula *celula = l->primeiro->prox;
		while(!vazia(l)){
			retira(celula, l, &celula->item);
			fwrite(&celula->item, sizeof(tPedido),1, fp);
		}
		printf("\n\t\tArquivo atualizado!");
	}
	fflush(stdin);
	getchar();
}

void main() {	
	int op;
	tListaEnc l;
	// inicializar Lista
	inicializa(&l);
	// inicializa os dados na lista
	lerArquivo(&l);
	do{
		op = menu();
		switch (op){
			case 1:	criarPedido(&l);			break;
			case 2:	buscaPedido(&l);			break;
			case 3:	alterarPedido(&l);			break;
			case 4: excluirItemPedido(&l);		break;
			case 5:	excluirPedidoCancelado(&l);	break;
			case 6:	consultaPedido(&l);			break;
			case 7:	gerarArquivo(&l);			break;
			default: printf("\n\n\t\tOpcao invalida!");fflush(stdin);
		}		
	}while(op != 7);		
}