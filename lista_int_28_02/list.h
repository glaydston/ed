#define MAX 10
#define TAM 100
char numstr[TAM];

struct tlist
{
    int item[MAX];
    int first, last;
};

void load(struct tlist *l);

void add(int value, struct tlist *l);

void retire(int position, struct tlist *l);

int isEmpty(struct tlist *l);

int search(int x, struct tlist *l);

void print(struct tlist *l);

void geti(int *num);
