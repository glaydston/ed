Data - 05/03/2012

Exercício Laboratório – Agenda Eletrônica

Faça, em C/C++, um sistema de controle de uma agenda eletrônica. Os dados manipulados pelo sistema têm a seguinte estrutura:

#define MAX 100

struct titem {
	int codigo;
	char nome[40];
	char telefone[10];
	char endereco[50];
	char email[20];
};

struct tlista {
	titem item[MAX];
	int primeiro;
	int ultimo;
};
 
O sistema deve possuir um menu principal através do qual o usuário pode escolher a opção que deseja. As opções do menu principal são:
Incluir novo contato: Neste caso, deve-se entrar com o código, o nome, o telefone, o endereço e o email de uma única pessoa; essas informações serão armazenadas em uma lista sequencial. Não existem pessoas com o mesmo código.
Imprimir agenda: Neste caso, o sistema deve imprimir os dados de todas as pessoas que estão armazenadas na lista sequencial. 
Pesquisar: Neste caso, deve-se entrar com o código da pessoa que se deseja pesquisar. Então, o sistema apresenta os dados da pessoa em questão. Se o código da pessoa não existe, deve ser apresentada uma mensagem de erro.
Excluir: Neste caso, deve-se entrar com o código da pessoa que será excluída, o sistema mostra na tela os dados dessa pessoa e solicita uma confirmação para exclusão. Se o código da pessoa não existe, deve ser apresentada uma mensagem de erro.

