#include <stdio.h>
#include <stdlib.h>
#define MAX 50
// Definição das estruturas

typedef struct {
	int	codigo;
	char	nome[MAX];
	float	cargaHoraria;
} tDisciplina;

struct tLista{
        tDisciplina disciplina;
        struct tLista *prox;
        struct tLista *ant;
};

struct tLista *Primeiro;
struct tLista *Ultimo;

// Implementação das operações

void inicializa(){
    struct  tLista *aux = (struct tLista*)malloc(sizeof(struct tLista));
    Primeiro = aux;
    Ultimo = Primeiro;
    Primeiro->ant = NULL;
}

// vazia: retorna verdadeiro (1) se a lista l
// está vazia, caso contrário, retorna 0 (falso)
int vazia(){
	if(Primeiro == Ultimo)
		return 1;
	return 0;
}

void insere(tDisciplina disciplina){
    struct  tLista *aux = (struct tLista*)malloc(sizeof(struct tLista));
    aux -> disciplina = disciplina;
    Ultimo -> prox = aux;
    aux -> ant = Ultimo;
    Ultimo = Ultimo -> prox;
    aux -> prox = NULL;
}

void retira(int x){
	struct tLista *aux = Primeiro -> prox;
	int flag = 0;
	while(aux != NULL){
		if(aux->disciplina.codigo == x){
			printf("\n\t\tDisciplina %s removida!", aux->disciplina.nome);
			if(aux->prox == NULL){
				Ultimo = aux->ant;
				aux-> ant->prox = NULL;
			} else {
				aux->ant->prox = aux->prox;
				aux->prox->ant = aux->ant;
			}
			aux = NULL;
			flag = 1;
		} else aux = aux->prox;
	}
	free(aux);
	if(!flag){
		printf("\n\t\tDisciplina %d nao se encontra nesta lista!!", x);
	}
}

void imprimeDisciplina(tDisciplina disciplina){
	printf("\n\t\tCodigo: %d", disciplina.codigo);
	printf("\n\t\tDisciplina: %s", disciplina.nome);
	printf("\n\t\tCarga Horaria: %.2f", disciplina.cargaHoraria);
	printf("\n");
}

void imprime(){
    struct tLista *aux = Primeiro->prox;
	if(vazia())
		printf("\n\n\t\t# Erro: Cadastrar disciplinas! [ENTER]");
	else 
		while(aux != NULL){
			 imprimeDisciplina(aux->disciplina);
			 aux = aux -> prox;
		}

	fflush(stdin);
	getchar();
}

void imprimeInvertido(){
    struct tLista *aux = Ultimo;
	if(vazia())
		printf("\n\n\t\t# Erro: Cadastrar disciplinas! [ENTER]");
	else 
		while(aux-> ant != NULL){
			 imprimeDisciplina(aux->disciplina);
			 aux = aux -> ant;
		}
	
	fflush(stdin);
	getchar();
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
	printf("\t\t7 - Imprimir Disciplinas Invertido\n");
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

void insereDisciplina(){
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
	insere(disciplina);
}

void excluiDisciplina(){
	int posicao, cont = 0, flag = 0;
	struct tLista *aux = Primeiro->prox;
	if(vazia())
		printf("\n\n\t\t# Erro: Cadastrar disciplinas! [ENTER]");
	else{
		cabecalho("Remover disciplina");
		printf("\t\tPosicao: ");
		fflush(stdin);
		scanf("%d", &posicao);
		while(aux != NULL){
			if(++cont == posicao){
				retira(aux->disciplina.codigo);
				flag = 1;
				break;
			} else aux = aux->prox;
		}
		if(!flag) printf("\n\t\tIndice nao encontrado! [ENTER]");
	}
	fflush(stdin);
	getchar();
}
void esvaziarDisciplina(){
	struct tLista *aux = Primeiro->prox;
	// retira da lista enquanto
	// ela não retorna que está vazia
	while(!vazia()){
		retira(aux->disciplina.codigo);
		aux = aux -> prox;
		
	};	
	if(vazia())
		printf("\n\n\t\t# Atencao: Lista Vazia! [ENTER]");
	else
		printf("\n\n\t\t# Erro: Ao remover as disciplinas! [ENTER]");
	fflush(stdin);
	getchar();
}

void verificarLista(){
	if(vazia())
		printf("\n\n\t\t# Erro: Cadastrar disciplinas! [ENTER]");
	else
		printf("\n\n\t\t# Atencao: Existe disciplinas! [ENTER]");

	fflush(stdin);
	getchar();
}

void pesquisaAvancada(){
	int codigo, opcao, flag = 0;
	float cargaHoraria;
	struct tLista *aux = Primeiro->prox;
	if(vazia())
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
				while(aux!= NULL){
					if(aux->disciplina.codigo == codigo){
						imprimeDisciplina(aux->disciplina);
						flag = 1;
					}
					aux = aux->prox;
				}
				break;
			case 2:
				printf("\n\t\tInforme a Carga Horaria: ");
				fflush(stdin);
				scanf("%f", &cargaHoraria);

				while(aux!= NULL){
					if(aux->disciplina.cargaHoraria == cargaHoraria){
						imprimeDisciplina(aux->disciplina);
						flag = 1;
					}
					aux = aux->prox;
				}
				break;
			default:printf("\n\n\t\tOpcao invalida!");
		}
	}
	if(!flag) printf("\n\t\tNao ha resultados para essa consulta! [ENTER]");
	fflush(stdin);
	getchar();
}

void main(){
	int opcao;
	// inicializa a lista
	inicializa();
	do{
		menu(&opcao);
		switch(opcao){
			case 1:insereDisciplina();break;
			case 2:excluiDisciplina();break;
			case 3:imprime();break;
			case 4:verificarLista();break;
			case 5:esvaziarDisciplina();break;
			case 6:pesquisaAvancada();break;
			case 7:imprimeInvertido();break;
			case 0:finaliza();break;
			default:printf("\n\n\t\tOpcao invalida!");fflush(stdin);getchar();
		}
	} while(opcao != 0);
}