#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void load(struct tlist *l)
{
    l->first = 0;
    l->last = 0;
}

void add(int value, struct tlist *l)
{
    if(l->last < MAX)
    {
        l->item[l->last++] = value;
    }
}

void retire(int position, struct tlist *l)
{
    int i;
    for(i=position; i< l->last; i++)
    {
        l->item[i] = l->item[i+1];
    }
    l->last--;

}

int isEmpty(struct tlist *l)
{
    if(l->first == l->last)
        return 0;
    return 1;
}

void print(struct tlist *l)
{
    int i;
    for(i=0; i < l->last; i++)
        printf("ITEM[%d] VALOR: %d\n", i, l->item[i]);
}

