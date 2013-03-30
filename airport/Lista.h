// Implementação da Lista.h
#include <stdio.h>
#include <stdlib.h>
#define MAX_ITEM 999

// Definições das Estruturas
// lista sequencial
typedef struct {
	int		codVoo;
	char	nome[30];
	int		numero;
	int		flag;
} tPassageiro;

typedef struct {
	tPassageiro item[MAX_ITEM];
	int primeiro;
	int ultimo;
} tListaPassageiros;

// Prototipo das funções lista sequencial

int	 vaziaPassageiro(tListaPassageiros *l);
void inicializaPassageiro(tListaPassageiros *l);
void inserePassageiro(tPassageiro passageiro, tListaPassageiros *l);
void removePassageiro(int posicao, tListaPassageiros *l);

// lista encadeada
typedef struct {
        int dia;
        int mes;
        int ano;
} tDate;

typedef struct {
        int horas;
        int minutos;
} tHour;

typedef struct {
	int codVoo;
    char cidadeOrigem[30];
    char cidadeDestino[30];
    tDate data;
    tHour hora;
    int dispInicial;
    int dispAtual;
	int col;
	int lin;
    int flag;
	tListaPassageiros passageiros;
} tVoo;

typedef struct tCelula{
	tVoo voo;
	struct tCelula *prox;
} tCelula;

typedef struct {
	tCelula *primeiro;
	tCelula *ultimo;
} tListaEnc;

// Prototipo das funções lista encadeada

int	 vaziaVoo(tListaEnc *l);
void inicializaVoo(tListaEnc *l);
void insereVoo(tVoo voo, tListaEnc *l);
void retiraVoo(tCelula *p, tListaEnc *l, tVoo *voo);
void imprimeVoo(tListaEnc *l);
