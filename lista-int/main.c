#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int filter_pass = 0;

void cabecalho(char title[MAX])
{
    system("cls");
    printf("\t\t\t####### LISTA INT #######\n");
    printf("\t\t\t####### %s\n\n", title);
}

void menu(int *op)
{
    cabecalho("MENU PRINCIPAL");
    printf("\t\t[1] INSERIR LISTA\n");
    printf("\t\t[2] RETIRAR LISTA\n");
    printf("\t\t[3] VERIFICAR NUMERO\n");
    printf("\t\t[4] IMPRIMIR LISTA\n");
    printf("\t\t[9] SAIR\n\n");
    printf("\t\t# OPCAO: ");
    geti(op);

}

void filter( int op, struct tlist *l)
{
    filter_pass = 1;
    int i, num;
    do
    {
        //verifica opção selecionada pelo usuario.
        if(op == 1)
        {
            cabecalho("INSERIR");
            if(l->last == MAX)
            {
                printf("\t\t# ERRO: Lista cheia! [ENTER]");
                getche();
                break;
            }
            else
            {
                printf("\t\tDIGITE UM NUMERO: ");
                geti(&num);
                i = search(num, l);
                if(i != -1)
                {
                    printf("\n\t\t# NUMERO JA ESTA NA LISTA! [ENTER]");
                    getche();
                }
                else add(num, l);
            }
        }
        else
        {
            cabecalho("REMOVER");
            printf("\t\tDIGITE O NUMERO: ");
            geti(&num);
            i = search(num, l);
            if(i == -1)
            {
                printf("\n\t\t# NUMERO NAO ENCONTRADO! [ENTER]");
                getche();
            }
            else retire(i, l);
        }
        printf("\n\n\t\t# DESEJA CONTINUAR? [1] SIM [9] NAO");
        printf("\n\t\t# OPCAO: ");
        geti(&op);

    }
    while(op == 1);

}

void pesquisar(struct tlist *l)
{
    int num, j;
    cabecalho("PESQUISA");
    if(filter_pass)
    {
        printf("\t\tDIGITE O NUMERO: ");
        geti(&num);
        j = search(num, l);
        if(j != -1)
            printf("\n\n\t\tITEM: %d - POSICAO %d. [ENTER]", l->item[j], j);
        else
            printf("\n\t\t# ERRO: NUMERO NAO ENCONTRADO! [ENTER]");
    }
    else  printf("\n\n\t\t# INSERIR DADOS! [ENTER]");
    getche();
}

void imprimir(struct tlist *l)
{
    cabecalho("IMPRESSAO");
    if(filter_pass)
    {
        print(l);
        printf("\n\t\t\t # [ENTER]");
    }
    else
        printf("\n\n\t\t# INSERIR DADOS! [ENTER]");
    getche();
}

void sair()
{
    cabecalho("SAIR");
    printf("\n\t\tFINALIZANDO SISTEMA... [ENTER]");
    getche();
}

void main()
{
    struct tlist list;
    int op = 0;
    //inicializa lista
    load(&list);
    do
    {
        menu(&op);
        switch(op)
        {
            case 1: filter(op, &list);  break;
            case 2: filter(op, &list);  break;
            case 3: pesquisar(&list);   break;
            case 4: imprimir(&list);    break;
            case 9: sair();             break;
            default:
                printf("\n\n\t\t# OPCAO [%d] INVALIDA! [ENTER]", op);getche();
        }
    }
    while(op != 9);
}
