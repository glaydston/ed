#include <stdio.h>
#include <stdlib.h>

typedef struct {
		char nome[40];
		float nota;
} taluno;

void main()
{
	taluno *alunos;
	int i, n;
	float media=0;

	printf("\n\n\tEntre com a quantidade de alunos da turma: ");
	scanf("%d", &n);

	alunos  = (taluno *) malloc(n*sizeof(taluno));

	printf("\n\n\tLeitura das informacoes dos alunos:\n\n");
	for (i=0; i<n; i++)
	{
		printf("\n\tEntre com o nome: ");
		fflush(stdin);
		gets(alunos[i].nome);
		printf("\n\tEntre com a nota: ");
		scanf("%f", &alunos[i].nota);
		media += alunos[i].nota;
	}

	if (n!=0)
    {
		media /= n;
	    printf("\n\n\tAlunos com nota acima da media: \n\n");
	    for (i=0; i<n; i++)
		    if ((alunos+i)->nota > media)
			   printf("\n\tNome: %s", (alunos+i)->nome);
    }
    else printf("\n\n\tNenhum aluno foi cadastrado\n\n");
	
    printf("\n\n\t");
	system("pause");
}
