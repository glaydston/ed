#define MAX 10
#define TAM 100

struct tItem{
	int codigo;
	char nome[TAM];
	char telefone[TAM];
	char endereco[TAM];
	char email[TAM];
};

struct tList
{
	tItem item[MAX];
	int first, last;
};

void load(tList *l);

void add(tItem contato, struct tList *l);

void retire(int position, struct tList *l);

int isEmpty(struct tList *l);

int search(int x, struct tList *l);

void print(struct tList *l);

