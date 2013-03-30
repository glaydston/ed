// Implementação da Lista.h
#include <stdio.h>
#include <stdlib.h>
#define MAX_ITEM 5

// Definições das Estruturas

// lista sequencial
typedef struct {
	char	descricao[30];
	int		quantidade;	
	float	precoVenda;
} tItemPedido;

typedef struct {
	tItemPedido item[MAX_ITEM];
	int primeiro;
	int ultimo;
} tListaItens;

// lista encadeada
typedef struct {
	int numero;
	char data[11];
	char nomeCliente[30];
	char endereco[40];
	char situacao;
	tListaItens itens;
} tPedido;

typedef struct tCel{
	tPedido item;
	struct tCel *prox;
} tCelula;

typedef struct {
	tCelula *primeiro;
	tCelula *ultimo;
} tListaEnc;


// Prototipo das funções lista sequencial

int	 vaziaSequencial(tListaItens *l);
int  procuraNome(char nome[], tListaItens *l);
void inicializarSequencial(tListaItens *l);
void inserirItem(tItemPedido pedido, tListaItens *l);
void removeItem(int posicao, tListaItens *l);
void imprimirItem(tListaItens *l);

// Prototipo das funções lista encadeada

int	 vazia(tListaEnc *l);
int  procuraNumero(int numero, tListaEnc *l);
void inicializa(tListaEnc *l);
void insere(tPedido pedido, tListaEnc *l);
void retira(tCelula *p, tListaEnc *l, tPedido *pedido);
void imprime(tListaEnc *l);
void imprimePedido(tPedido pedido);
