#include <stdio.h>
#include <stdlib.h>
#include "list.h"

main()
{
    int empty;
    struct tlist list;
    load(&list);
    add(4,&list);
    add(8,&list);
    add(9,&list);
    add(10,&list);
    empty = isEmpty(&list);
    if(empty)
        printf("# A LISTA NAO ESTA VAZIA!\n\n");
    else
            printf("# LISTA VAZIA!\n\n");
    print(&list);

    retire(2, &list);
    print(&list);
    getchar();
}
