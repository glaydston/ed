#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50

// Definição das estruturas

typedef struct{
	int		codigo;
	char	nome[MAX];
	float	cargaHoraria;
} tDisciplina;

typedef struct tipoCelula{
	tDisciplina	disciplina;
	struct	tipoCelula *prox;
} tCelula;


typedef struct{
	tCelula *primeiro;
	tCelula *ultimo;
} tLista;

// Protótipo das funções
int		vazia(tLista *l);
void	inicializa(tLista *l);
void	insere(tDisciplina d, tLista *l);
void	retira(tCelula *p, tLista *l, tDisciplina *d);
void	imprime(tLista *l);


// Implementação das operações

// Inicializa: faz a lista ficar vazia (cria a
// celula cabeça e faz os ponteiros 
// primeiro e ultimo apontarem para ela)
void inicializa(tLista *l){
	l -> primeiro = (tCelula *)malloc(sizeof(tCelula));
	l -> ultimo = l -> primeiro;
	l -> ultimo->prox = NULL;
}

// vazia: retorna verdadeiro (1) se a lista l 
// está vazia, caso contrário, retorna 0 (falso)
int vazia(tLista *l){
	if(l -> primeiro == l -> ultimo)
		return 1;
	return 0;
}

// insere: insere o item x no final
// da lista l
void insere(tDisciplina disciplina, tLista *l){
	l -> ultimo -> prox = (tCelula *) malloc(sizeof(tCelula));
	l -> ultimo 		= l->ultimo -> prox;
	l -> ultimo -> disciplina = disciplina;
	l -> ultimo -> prox = NULL;	
}

// retira: retira a célula seguinte à celula
// apontada por p e armazena o item
// retirado no parâmetro x.
void retira(tCelula *p, tLista *l, tDisciplina *disciplina){
	tCelula *q;
	if(vazia(l) || p == NULL || p->prox == NULL)
		printf("\n\t\t# ERRO: Lista vazia ou posicao invalida\n");
	else{
		q = p -> prox;
		p -> prox   = q ->prox;
		*disciplina = q -> disciplina;
		if(q -> prox == NULL) l -> ultimo = p;
		free(q);			
	}
}

// imprime: imprime os itens da lista l
void imprime(tLista *l){
	tCelula *aux = l -> primeiro -> prox;

	while(aux != NULL){
		printf("\n\t\tCodigo: %d", aux->disciplina.codigo);
		printf("\n\t\tDisciplina: %s", aux->disciplina.nome);
		printf("\n\t\tCarga Horaria: %.2f", aux->disciplina.cargaHoraria);
		printf("\n");
		aux =  aux-> prox;
	}
}


//Implementação da Aplicação

// cabecalho: Limpa a tela e imprimi o cabecalho 
// com o respectivo subtitle informado
void cabecalho(char subtitle[]){
	system("cls");
	printf("\t\t\t########### Cadastro de Disciplinas ###########");
	printf("\n\t\t\t########### %s \n\n",subtitle);
}

// menu: menu atribui o valor escolhido 
// pelo usuário por referência
void menu(int *op){
	cabecalho("Menu Principal");

	// opções do menu
	printf("\t\t1 - Cadastrar Disciplina\n");
	printf("\t\t2 - Excluir Disciplina\n");	
	printf("\t\t3 - Imprimir Disciplinas\n");
	printf("\t\t4 - Verificar Lista\n");
	printf("\t\t5 - Esvaziar Lista\n");
	printf("\t\t6 - Pesquisa Avancada\n");
	printf("\t\t0 - Sair\n");

	printf("\n\t\tOpcao: ");
	fflush(stdin);
	scanf("%d", op);
}

// finaliza: Informa que a aplicação
// está finalizando
void finaliza(){
	printf("\n\n\t\t# Finalizando aplicacao... [ENTER]");
	fflush(stdin);
	getchar();
}

void insereDisciplina(tLista *l){
	tDisciplina disciplina;
	cabecalho("Cadastro");
		
	printf("\t\tCodigo: ");
	fflush(stdin);
	scanf("%d", &disciplina.codigo);

	printf("\t\tNome da Disciplina: ");
	fflush(stdin);
	gets(disciplina.nome);

	printf("\t\tCarga Horaria: ");
	fflush(stdin);
	scanf("%f", &disciplina.cargaHoraria);

	// insere a disciplina na lista
	insere(disciplina, l);
}

void excluiDisciplina(tLista *l){
	int posicao, cont = 0, enc = 0;
	tCelula *celula = l->primeiro;
	tDisciplina disciplina;
	tLista aux;

	// inicializa lista aux;
	inicializa(&aux);

	if(vazia(l))		
		printf("\n\n\t\t# Erro: Cadastrar disciplinas! [ENTER]");
	else{
		cabecalho("Remover disciplina");
		
		printf("\t\tPosicao: ");
		fflush(stdin);
		scanf("%d", &posicao);

		while(!vazia(l)){
			retira(celula, l, &disciplina);
			if(++cont != posicao)
				insere(disciplina, &aux);
			else {
				printf("\n\t\tDisciplina: %s removida! [ENTER]", disciplina.nome);
				enc = 1;
			}			
		}

		celula = aux.primeiro;
		while(!vazia(&aux)){
			retira(celula, &aux, &disciplina);
			insere(disciplina, l);
		}			

		if(!enc) printf("\n\t\tIndice nao encontrado! [ENTER]");
	}
	
	fflush(stdin);
	getchar();
}

void imprimiDisciplina(tLista *l){
	if(vazia(l))		
		printf("\n\n\t\t# Erro: Cadastrar disciplinas! [ENTER]");
	else{
		cabecalho("Disciplinas");
		imprime(l);
	}
	
	fflush(stdin);
	getchar();
}

void verificaDisciplina(tLista *l){
	if(vazia(l))		
		printf("\n\n\t\t# Erro: Cadastrar disciplinas! [ENTER]");
	else
		printf("\n\n\t\t# Atencao: Existe disciplinas! [ENTER]");

	fflush(stdin);
	getchar();
}

void esvaziarDisciplina(tLista *l){
	tCelula *celula = l->primeiro;
	tDisciplina disciplina;

	// retira da lista enquanto 
	// ela não retorna que está vazia
	while(!vazia(l))
		retira(celula, l, &disciplina);

	if(vazia(l))
		printf("\n\n\t\t# Atencao: Lista Vazia! [ENTER]");
	else		
		printf("\n\n\t\t# Erro: Ao remover as disciplinas! [ENTER]");

	fflush(stdin);
	getchar();
}

void imprimeDisciplina(tDisciplina disciplina){
	printf("\n\t\tCodigo: %d", disciplina.codigo);
	printf("\n\t\tDisciplina: %s", disciplina.nome);
	printf("\n\t\tCarga Horaria: %.2f", disciplina.cargaHoraria);
	printf("\n");
}

void pesquisaAvancada(tLista *l){
	int codigo, opcao, enc = 0;
	float cargaHoraria;
	tCelula *celula = l->primeiro->prox;

	if(vazia(l))		
		printf("\n\n\t\t# Erro: Cadastrar disciplinas! [ENTER]");
	else{

		cabecalho("Pesquisa Avancada");

		printf("\t\t\t1 - Codigo");
		printf("\n\t\t\t2 - Carga Horaria");
		printf("\n\n\t\tOpcao: ");
		fflush(stdin);
		scanf("%d", &opcao);

		switch(opcao){
			case 1: 
				printf("\n\t\tInforme o codigo: ");
				fflush(stdin);
				scanf("%d", &codigo);
				while(celula!= NULL){
				
					if(celula->disciplina.codigo == codigo){
						imprimeDisciplina(celula->disciplina);
						enc = 1;
					}
					celula = celula->prox;
				}
				break;
			case 2: 
				printf("\n\t\tInforme a Carga Horaria: ");
				fflush(stdin);
				scanf("%f", &cargaHoraria);
				while(celula!= NULL){
				
					if(celula->disciplina.cargaHoraria == cargaHoraria){
						imprimeDisciplina(celula->disciplina);	
						enc = 1;				
					}
					celula = celula->prox;
				}
				break;
			default:printf("\n\n\t\tOpcao invalida!");
		}
	}
	
	if(!enc) printf("\n\t\tNao ha resultados para essa consulta! [ENTER]");
	fflush(stdin);
	getchar();
}

void main(){
	int opcao;
	tLista disciplinas;

	// inicializa a lista
	inicializa(&disciplinas);
	do{
		menu(&opcao);
		switch(opcao){
			case 1:insereDisciplina(&disciplinas);break;
			case 2:excluiDisciplina(&disciplinas);break;
			case 3:imprimiDisciplina(&disciplinas);break;
			case 4:verificaDisciplina(&disciplinas);break;
			case 5:esvaziarDisciplina(&disciplinas);break;
			case 6:pesquisaAvancada(&disciplinas);break;
			case 0:finaliza();break;
			default:printf("\n\n\t\tOpcao invalida!");fflush(stdin);getchar();
		}
	} while(opcao != 0);
}


