#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct a {
		char nome[40];
		float nota;
		struct a *prox;
} taluno;

void main()
{
	taluno *novo,*lista;
	char nome[40];
	int cont;
	float media;
	
	novo = NULL;
	lista = NULL;
	cont = 0;
	media = 0;

	printf("\n\n\tLeitura das informacoes dos alunos:\n\n");

	printf("\n\tEntre com o nome: ");
	fflush(stdin);
	gets(nome);

	while (strcmp(nome, "0")!=0)
	{
		novo = (taluno *) malloc(sizeof(taluno));
		printf("\n\tEntre com a nota: ");
		scanf("%f", &novo->nota);
		media += novo->nota;
		cont++;
		strcpy(novo->nome, nome);
		novo->prox = lista;
		lista = novo;
		printf("\n\tEntre com o nome: ");
		fflush(stdin);
		gets(nome);
	}

	if (cont!=0)
	{
		media /= cont;
	    printf("\n\n\tAlunos com nota acima da media: \n\n");
	    while (novo != NULL)
	    {
            if (novo->nota > media)
			    printf("\n\tNome: %s", novo->nome);
            novo = novo->prox;
            free(lista);
            lista = novo;
        }
	 } else printf("\n\n\tNenhum aluno foi cadastrado\n\n");
	 printf("\n\n\t");
	 system("pause");
}
