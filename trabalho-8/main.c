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
	tCelula *frente;
	tCelula *tras;
} tFila;

// Implementação das operações

// Inicializa: faz a fila ficar vazia (cria a
// celula cabeça e faz os ponteiros 
// primeiro e ultimo apontarem para ela)
void inicializa(tFila *f){
	f -> frente = (tCelula *)malloc(sizeof(tCelula));
	f -> tras = f -> frente;
	f -> tras->prox = NULL;
}

// vazia: retorna verdadeiro (1) se a fila f 
// está vazia, caso contrário, retorna 0 (falso)
int vazia(tFila *f){
	if(f -> frente == f -> tras) return 1;
	return 0;
}

// enfileira: enfileira o item x no final
// da fila f
void enfileira(tDisciplina disciplina, tFila *f){
	f -> tras -> prox = (tCelula *) malloc(sizeof(tCelula));
	f -> tras = f->tras -> prox;
	f -> tras -> disciplina = disciplina;
	f -> tras -> prox = NULL;	
}

// desenfileira: desenfileira a disciplina da fila
void desenfileira(tFila *f, tDisciplina *disciplina){
	tCelula *aux;
	if(vazia(f))
		printf("\n\t\t# ERRO: Lista vazia ou posicao invalida\n");
	else{
		aux = f->frente;
		f->frente = f->frente->prox;
		*disciplina = f->frente->disciplina;
		free(aux);
	}
}

// imprimeDisciplina: imprime a disciplina passada por parametro
void imprimeDisciplina(tDisciplina disciplina){
	printf("\n\t\tCodigo: %d", disciplina.codigo);
	printf("\n\t\tDisciplina: %s", disciplina.nome);
	printf("\n\t\tCarga Horaria: %.2f", disciplina.cargaHoraria);
	printf("\n");
}


// imprime: imprime os itens da fila f
void imprime(tFila *f){
	tCelula *aux = f -> frente -> prox;

	while(aux != NULL){
		imprimeDisciplina(aux->disciplina);		
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

// insereDisciplina: enfileira a disciplina informada na fila
void insereDisciplina(tFila *f){
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

	// enfileira a disciplina na fila
	enfileira(disciplina, f);
}

// excluiDisciplina: desenfileira o primeiro elemento da fila
void excluiDisciplina(tFila *f){
	int posicao, cont = 0, enc = 0;
	tDisciplina disciplina;

	if(vazia(f))		
		printf("\n\n\t\t# Erro: Cadastrar disciplinas! [ENTER]");
	else{
		cabecalho("Remover disciplina");	
		// remove a primeira disciplina da fila
		desenfileira(f, &disciplina);
		printf("\n\t\tDisciplina: %s removida! [ENTER]", disciplina.nome);	
	}

	fflush(stdin);
	getchar();
}

// verificaDisciplina: chama a função vazia() da fila e
// retorna ao usuario se a fila possui disciplinas cadastradas
void verificaDisciplina(tFila *f){
	if(vazia(f))		
		printf("\n\n\t\t# Erro: Cadastrar disciplinas! [ENTER]");
	else
		printf("\n\n\t\t# Atencao: Existe disciplinas! [ENTER]");

	fflush(stdin);
	getchar();
}

// esvaziarDisciplina: remove todos os elementos da fila
void esvaziarDisciplina(tFila *f){
	tDisciplina disciplina;
	// retira da fila enquanto 
	// ela não retorna que está vazia
	while(!vazia(f)){
		desenfileira(f, &disciplina);		
		printf("\n\t\tDisciplina: %s removida!", disciplina.nome);	
	}
	if(vazia(f))
		printf("\n\n\t\t# Atencao: Lista Vazia! [ENTER]");
	else		
		printf("\n\n\t\t# Erro: Ao remover as disciplinas! [ENTER]");

	fflush(stdin);
	getchar();
}

// pesquisaAvancada: permite ao usuario escolher
// qualquer forma deseja buscar na fila
void pesquisaAvancada(tFila *f){
	int codigo, opcao, flag = 0;
	float cargaHoraria;
	tCelula *celula = f->frente->prox;

	if(vazia(f))		
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
				while(celula != NULL){
				
					if(celula->disciplina.codigo == codigo){
						imprimeDisciplina(celula->disciplina);
						flag = 1;
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
						flag = 1;			
					}
					celula = celula->prox;
				}
				break;
			default:printf("\n\n\t\tOpcao invalida!");
		}
	}
	
	if(!flag) printf("\n\t\tNao ha resultados para essa consulta! [ENTER]");
	fflush(stdin);
	getchar();
}

// imprimeAllDisciplina: imprime todas as disciplinas
// que a fila contém
void imprimeAllDisciplina(tFila *f){
	if(vazia(f))
		printf("\n\n\t\t# Atencao: Lista Vazia! [ENTER]");
	else{				
		cabecalho("Disciplinas");	

		imprime(f);
	}
	fflush(stdin);
	getchar();
}

void main(){
	int opcao;
	tFila disciplinas;

	// inicializa a fila
	inicializa(&disciplinas);
	do{
		menu(&opcao);
		switch(opcao){
			case 1:insereDisciplina(&disciplinas);break;
			case 2:excluiDisciplina(&disciplinas);break;
			case 3:imprimeAllDisciplina(&disciplinas);break;
			case 4:verificaDisciplina(&disciplinas);break;
			case 5:esvaziarDisciplina(&disciplinas);break;
			case 6:pesquisaAvancada(&disciplinas);break;
			case 0:finaliza();break;
			default:printf("\n\n\t\tOpcao invalida!");fflush(stdin);getchar();
		}
	} while(opcao != 0);
}


