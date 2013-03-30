#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"

// menu: solicita a opcao do menu e retorna-a
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

// criaItem: solicita informações sobre o item
// e adiciona-o na lista lItem
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

// criaItens: recebe a lista itens, e gerencia 
// a solicitação da função criaItem
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


// excluirItem: exclui o item informado,
// na lista itens
void excluirItem(tListaItens *itens){
	char nome[30], go;
	printf("\n\n\t\t\tExcluir itens\n");
	do { 
		if(!vaziaSequencial(itens)){			
			printf("\n\t\tInforme o nome do item: ");
			fflush(stdin);
			gets(nome);

			// posicao: recebe o retorno da função
			int posicao = procuraNome(nome, itens);
			if(posicao != -1){
				removeItem(posicao, itens);
				printf("\n\t\tItem removido!\n");
			}else{
				printf("\n\t\tItem nao encontrado!\n");
			}

			printf("\n\t\tDeseja continuar? ");
			fflush(stdin);
			go = getchar();		
		}else{
			printf("\n\t\tLista vazia!");
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
	int numero;
	system("cls");
	printf("\t\t\tIncluir pedido\n\n");

	printf("\t\tInforme o numero do pedido: ");
	fflush(stdin);
	scanf("%d", &numero);
	// verifica se o numero de pedido já existe
	if(procuraNumero(numero, l)){
		printf("\n\n\t\tNumero de pedido ja existe!");
		fflush(stdin);
		getchar();
	} else{
		pedido.numero = numero;
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
}

// alterarSituacaoPedido: altera a situação
// do pedido na lista l
void alterarSituacaoPedido(tListaEnc *l){
	int numeroPed;
	tCelula *celula = l->primeiro->prox;
	char altera;
	
	system("cls");	
	printf("\t\t\tAlterar situacao do pedido\n\n");
	printf("\t\tDigite o pedido a ser alterado: ");
	fflush(stdin);
	scanf("%d", &numeroPed);

    while (celula != NULL){
		if(celula->item.numero == numeroPed){
			if(celula->item.situacao != 'P'){  
				printf("\n\n\t\tA situacao do pedido nao e Pedente!");
				printf("\n\t\tSituacao: %c", celula->item.situacao);
			} else{
				printf("\n\t\tSituacao do pedido: %c", celula->item.situacao);
				printf("\n\t\tAlterar Situacao do pedido para:\n\t\t\t C - cancelado\n\t\t\t E - entregue");

				do{
					printf("\n\t\tOpcao: ");		
					fflush(stdin);
					altera = getchar();
					if(altera != 'C' && altera != 'E')
						printf("\t\tErro: Opcao invalida!");
					
				}while(altera != 'C' && altera != 'E');

				celula->item.situacao = altera;
				printf("\n\t\tSituacao do pedido: %c", celula->item.situacao);
				
			}
			fflush(stdin);
			getchar();
			return;
		}		
		celula = celula->prox;
	}	
	printf("\n\n\t\tPedido consultado nao existe!");
	fflush(stdin);
	getchar();
}

// incluirItemPedido: inclui um novo item
// no pedido da lista l
void incluirItemPedido(tListaEnc *l){
	int numeroPed;
	tCelula *celula = l->primeiro->prox;

	system("cls");
	printf("\t\t\tAlterar Pedido\n\n");
	printf("\t\tDigite o pedido a ser atualizado: ");
	fflush(stdin);
	scanf("%d", &numeroPed);

	 while (celula != NULL){
		if(celula->item.numero == numeroPed){	
			// imprime o pedido		
			imprimePedido(celula->item);

			if(celula->item.situacao != 'P'){  
				printf("\n\n\t\tA situacao do pedido nao e Pedente!");
				fflush(stdin);
				getchar();
			} else{				
				printf("\n\n\t\t\tIncluir novos itens\n");
				criaItens(&celula->item.itens);
			}
			return;
		}		
		celula = celula->prox;
	}	
	printf("\n\n\t\tPedido consultado nao existe!");
	fflush(stdin);
	getchar();
}

// excluirItemPedido: exclui um item do pedido
// da lista l
void excluirItemPedido(tListaEnc *l){
	int numeroPed;
	tCelula *celula = l->primeiro->prox;
	
	system("cls");
	printf("\t\tExcluir itens do pedido\n\n");
	printf("\t\tDigite o pedido a ser alterada: ");
	fflush(stdin);
	scanf("%d", &numeroPed);

	 while (celula != NULL){
		if(celula->item.numero == numeroPed){	
			// imprime o pedido
			imprimePedido(celula->item);

			if(celula->item.situacao != 'P'){  
				printf("\n\n\t\tA situacao do pedido nao e Pedente!");
				fflush(stdin);
				getchar();
			} else{		
				excluirItem(&celula->item.itens);
			}
			return;
		}		
		celula = celula->prox;
	}	
	printf("\n\n\t\tPedido consultado nao existe!");
	fflush(stdin);
	getchar();
}

// excluirPedidoCancelado: exclui o pedido
// cancelado da lista l
void excluirPedidoCancelado(tListaEnc *l){	
	tCelula *aux = l->primeiro;
	tListaEnc lAux;
	tPedido pedido;
	// inicializa lista lAux	
	inicializa(&lAux);

	system("cls");
	printf("\t\tExcluir pedidos cancelados\n");	

	while (!vazia(l)){
		retira(aux, l, &pedido);
		if(pedido.situacao == 'C')			
			printf("\n\t\tPedido: %d removido. ", pedido.numero);
		else
			insere(pedido, &lAux);
	}

	aux = lAux.primeiro;
	while(!vazia(&lAux)){
		retira(aux, &lAux, &pedido);
		insere(pedido, l);
	}

	fflush(stdin);
	getchar();
}

// consultaPedido: consultado o numero do pedido
// informando na lista l e exibi o mesmo.
void consultaPedido(tListaEnc *l){
	int numeroPed;
	tCelula *celula = l->primeiro->prox;

	system("cls");
	printf("\t\t\tConsultar pedidos\n\n");
	printf("\t\tDigite numero do pedido: ");
	fflush(stdin);
	scanf("%d", &numeroPed);

	while(celula != NULL){
		if(celula->item.numero == numeroPed){
			printf("\n\t\tO pedido consultado e:\n");
			imprimePedido(celula->item);			
			fflush(stdin);
			getchar();
			return;
		}
		celula = celula->prox;
	}
	printf("\n\n\t\tPedido consultado nao existe!");
	fflush(stdin);
	getchar();
}

// lerArquivo: le os dados do arquivo
// e carrega na lista
void lerArquivo(tListaEnc *l){
	FILE *fp;
	tPedido pedido;
	fp = fopen("pedidos.bin","rb");	

	if(fp == NULL){
		printf("\n\t\tErro ao tentar ler o arquivo.");
		fflush(stdin);
		getchar();
	} else
		while(fread(&pedido, sizeof(tPedido), 1, fp))
			insere(pedido, l);		
	
}

// gerarArquivo: gera o arquivo preenchendo com os
// pedidos que estão na lista l
void gerarArquivo(tListaEnc *l){
	FILE *fp;
	tPedido pedido;
	tCelula *celula = l->primeiro;
	fp = fopen("pedidos.bin","wb");

	if(fp == NULL){
		printf("\n\t\tErro ao tentar gerar o arquivo.");
		fflush(stdin);
		getchar();
	} else
		while(!vazia(l)){
			retira(celula, l, &pedido);
			fwrite(&pedido, sizeof(tPedido), 1, fp);
		}
}

// listaNumeroPedidos: Função de auxilio,
// imprime todos os numeros de pedidos da
// da lista encadeada
void listaNumeroPedidos(tListaEnc *l){
	tCelula *cel = l->primeiro->prox;
	
	system("cls");
	printf("\t\t\tNumero(s) de Pedido(s)\n\n");
	while(cel != NULL){
		printf("\n\t\tNumero de pedido: %d", cel->item.numero);
		cel = cel->prox;
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
			case 2:	alterarSituacaoPedido(&l);	break;
			case 3:	incluirItemPedido(&l);		break;
			case 4: excluirItemPedido(&l);		break;
			case 5:	excluirPedidoCancelado(&l);	break;
			case 6:	consultaPedido(&l);			break;
			case 7:	gerarArquivo(&l);			break;
			case 99: listaNumeroPedidos(&l);	break;
			default: printf("\n\n\t\tOpcao invalida!");
					 fflush(stdin);
					 getchar();
		}		
	}while(op != 7);		
}