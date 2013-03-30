#include <stdlib.h>
#include <stdio.h>
#include "list.h"
//exibe o cabecalho com subtitulo, cabecalho(titulo da tela);
void cabecalho(char title[TAM])
{
    system("cls");
    printf("\t\t\t####### AGENDA DE CONTATOS #######\n");
    printf("\t\t\t####### %s\n\n", title);
}

int menu()
{
	int op;
    cabecalho("MENU PRINCIPAL");
    printf("\t\t[1] INCLUIR CONTATO\n");
    printf("\t\t[2] EXCLUIR CONTATO\n");
    printf("\t\t[3] PESQUISAR CONTATO\n");
    printf("\t\t[4] IMPRIMIR AGENDA\n");
    printf("\t\t[9] SAIR\n\n");
    printf("\t\t# OPCAO: ");
	fflush(stdin);
	scanf("%d", &op);

	return op;

}
//filtra as solicitações, filter(opcao, lista); (opcao)?1 = adicionar:0 = excluir;
void filter(int op, tList *l){
	int num = 0, choose;
	tItem contato;
	do{
		if(op){
			cabecalho("INSERIR CONTATO");
			if(l->last == MAX){			
				printf("\t\t#ERRO: LISTA CHEIA! [ENTER]");
				fflush(stdin);
				getchar();
				break;
			} else{
				printf("\t\tCODIGO: ");
				fflush(stdin);
				scanf("%d",&num); 
				//verifica se codigo já existe na lista de contatos, search(codigo, lista);
				choose = search(num, l);
				if(choose != -1)
				{
					printf("\n\t\t# ERRO: JA EXISTE CONTATO COM CODIGO [%d]!", num);
				} else {
					contato.codigo = num;

					printf("\t\tNOME: ");
					fflush(stdin);
					gets(contato.nome);

					printf("\t\tE-MAIL: ");
					fflush(stdin);
					gets(contato.email);

					printf("\t\tENDERECO: ");
					fflush(stdin);
					gets(contato.endereco);

					printf("\t\tTELEFONE: ");
					fflush(stdin);
					gets(contato.telefone);
					//adiciona contato a lista, add(contato a ser adicionado, lista);
					add(contato, l);
				}
			}
		}else{
			cabecalho("EXCLUIR");
			//verifica se existe contatos cadastrados
			if(isEmpty(l)){
				printf("\t\t# ERRO: CADASTRE CONTATO(S)! [ENTER]");
				fflush(stdin);
				getchar();
				break;
			}else{
				printf("\t\tDIGITE O CODIGO: ");
				fflush(stdin);
				scanf("%d", &num);
				//verifica se a lista possui o contato, search(numero de pesquisa, lista);
				choose = search(num, l);
				if(choose == -1){				
					printf("\n\t\t# ERRO: CODIGO [%d] NAO ENCONTRADO!\n", num);
				}else{
					printf("\n\t\t# CONTATO: %s EXCLUIDO!\n",l->item[choose].nome);
					//remove o contato da lista, retire(posicao do contato, lista);
					retire(choose, l);
				}
			}
		}
		printf("\n\t\t# DESEJA CONTINUAR? [1] SIM [9] NAO");
		printf("\n\t\t# OPCAO: ");
		fflush(stdin);
		scanf("%d", &num);
	} while(num == 1);
}

void imprimir(tList *l){
	cabecalho("CONTATO(S)");
	//verifica se existe contatos cadastrados
	if(isEmpty(l))
		printf("\t\t# ERRO: CADASTRE CONTATO(S)! [ENTER]");
	else
		//imprimi a lista passada pelo parametro, print(lista);
		print(l);
	fflush(stdin);
	getchar();
}

void pesquisar(tList *l){
	int i, cod;
	cabecalho("PESQUISAR CONTATO");
	//verifica se existe contatos cadastrados
	if(isEmpty(l))
		printf("\t\t# ERRO: CADASTRE CONTATO(S)! [ENTER]");
	else{
		printf("\t\tDIGITE O CODIGO: ");
		fflush(stdin);
		scanf("%d", &cod);
		//pesquisa o codigo passado na lista, search(numero da pesquisa, lista);
		i = search(cod, l);	
		//verifica se codigo informado está na lista
		if(i == -1){
			printf("\n\t\t# ERRO: CODIGO [%d] NAO ENCONTRADO! [ENTER]", cod);
		}else{
			//imprimi o contato de acordo com o indice encontrado
			printf("\n\t\tCONTATO --------------------------------\n");
			printf("\n\t\t\tCODIGO: %d", l->item[i].codigo);
			printf("\n\t\t\tNOME: %s", l->item[i].nome);
			printf("\n\t\t\tE-MAIL: %s", l->item[i].email);
			printf("\n\t\t\tENDERECO: %s", l->item[i].endereco);
			printf("\n\t\t\tTELEFONE: %s", l->item[i].telefone);
			printf("\n\t\t---------------------------------- [ENTER]");
		}
	}
	fflush(stdin);
	getchar();
}

void main(){
	int op;
	tList l;
	//inicializa a lista, load(lista);
	load(&l);
	do{
		op = menu();
		switch(op){
			case 1: filter(1, &l);break;
			case 2: filter(0, &l);break;
			case 3: pesquisar(&l);break;
			case 4: imprimir(&l);break;
			case 9: printf("\n\n\t\t# FINALIZANDO... [ENTER]");getchar();break;
			default: printf("\n\n\t\t# OPCAO [%d] INVALIDA! [ENTER]",op);getchar();
		}

	} while(op != 9);
}
