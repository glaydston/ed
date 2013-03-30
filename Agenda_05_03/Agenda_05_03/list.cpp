#include <stdio.h>
#include <stdlib.h>
#include "list.h"
char numstr[TAM];

void load(tList *l)
{
    l->first = 0;
    l->last = 0;
}

void add(tItem contato, tList *l)
{
    if(l->last < MAX)
    {
        l->item[l->last++] = contato;
    }
}

void retire(int position, tList *l)
{
    int i;
    for(i=position; i< l->last; i++)
    {
        l->item[i] = l->item[i+1];
    }
    l->last--;

}

int isEmpty(tList *l)
{
    if(l->first == l->last)
        return 0;
    return 1;
}

int search(int x, tList *l)
{
    int i;
    for(i=0;i< l->last; i++)
		if(l->item[i].codigo == x)
            return i;
    return -1;
}

void print(tList *l)
{
    int i;
    for(i=0; i < l->last; i++){
		printf("\t\tCONTATO[%d] -----------------------------\n",i+1);
		printf("\n\t\t\tCODIGO: %d", l->item[i].codigo);
		printf("\n\t\t\tNOME: %s", l->item[i].nome);
		printf("\n\t\t\tE-MAIL: %s", l->item[i].email);
		printf("\n\t\t\tENDERECO: %s", l->item[i].endereco);
		printf("\n\t\t\tTELEFONE: %s", l->item[i].telefone);
		printf("\n\n\t\t----------------------------------------\n");
	}
}


