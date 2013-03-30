#include <stdio.h>
#include <stdlib.h>

#define MAX 5

typedef struct {
		char nome[40];
		float nota;
} taluno;

void main()
{
	taluno alunos[MAX];
	float media=0;
    int i;
    
	printf("\n\n\tLeitura das informacoes dos alunos:\n\n");
	for (i=0; i<MAX; i++)
	{
		printf("\n\tEntre com o nome: ");
		fflush(stdin);
		gets(alunos[i].nome);
		printf("\n\tEntre com a nota: ");
		scanf("%f", &alunos[i].nota);
		media += alunos[i].nota;
	}

	media /= MAX;
	
	printf("\n\n\tAlunos com nota acima da media: \n\n");
	for (i=0; i<MAX; i++)
		if (alunos[i].nota > media)
			printf("\n\tNome: %s", alunos[i].nome);
	
	printf("\n\n\t");
	system("pause");
}
