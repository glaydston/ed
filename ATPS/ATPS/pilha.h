#define MAX 100
#define TAM 100
struct tPilha
{
    int item[MAX];
    int topo;
};

void inicializa(tPilha *p);

void empilhar(int x, tPilha *p);

void desempilhar(int *x, tPilha *p);

int isEmpty(tPilha *p);

int acessaTopo(int *x, tPilha *p);

void print(tPilha *p);
