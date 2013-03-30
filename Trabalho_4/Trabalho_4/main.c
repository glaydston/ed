#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10

void cabecalho(char subtitle[]){
	system("cls");
	printf("\t\t\t########## TRABALHO - 4 ##########\n");
	printf("\t\t\t########## %s \n\n", subtitle);
}

int menu(){
	int op;
	cabecalho("MENU PRINCIPAL");

	printf("\t\t1 -  Calcular MDC\n");	
	printf("\t\t2 -  Quantidade Impares\n");
	printf("\t\t3 -  Calcular Fibonacci\n");
	printf("\t\t4 -  Calcular Potencia\n");
	printf("\t\t5 -  Converte Decimal Para Binario\n");
	printf("\t\t6 -  Calcular Fatorial\n");
	printf("\t\t7 -  Palidromo\n");
	printf("\t\t8 -  Torre de HANOI\n");
	printf("\t\t9 -  Sair");

	printf("\n\n\t\tOpcao: ");
	fflush(stdin);
	scanf("%d", &op);

	return op;
}

// MDC

int mdc(int a, int b)
{
	if(a % b != 0)
		return mdc(b, a % b);
	else
		return b;
}

void calcularMDC(){
	int a, b;
	cabecalho("MDC");
	printf("\t\tPrimeiro numero: ");
	fflush(stdin);
	scanf("%d", &a);

	printf("\t\tSegundo numero: ");
	fflush(stdin);
	scanf("%d", &b);

	printf("\t\tMDC: %d  [ENTER]", mdc(a, b));
	fflush(stdin);
	getchar();
}

// IMPAR

int impar(int vet[], int i, int cont){
	if(i < 0)
		return cont;
	if(vet[i] % 2 == 1)
		return impar(vet, --i, ++cont);
	else 
		return impar(vet, --i, cont);
}

void quantidadeImpares(){
	int i, vetor[MAX];
	cabecalho("Impares");

	for(i = 0; i <MAX; i++){
		printf("\t\t Informe o %d numero: ", i+1);
		fflush(stdin);
		scanf("%d", &vetor[i]);
	}

	printf("\t\tQuantidade de numeros impares: %d", impar(vetor, MAX-1, 0));
	fflush(stdin);
	getchar();
}

// FIBONACCI

int fib(int n) 
{   int retorno;
	if(n < 2) 
		retorno = 1;
	else
		retorno = fib(n-1) + fib(n-2); 
	return retorno;
} 

void calcularFibonacci(){
	int n, i;
	cabecalho("Fibonacci");

	printf("\t\tInforme a quantidade de termos da sequencia: ");
	fflush(stdin);
	scanf("%d", &n);

	printf("\t\tA sequencia e : ");
	for(i=0; i<n; i++)
		printf("%d ", fib(i));

	fflush(stdin);
	getchar();

}


// POTÊNCIA 

int potencia(int x, int y){
	if(y == 0)
		return 1;
	else{
		if(y < 0)
			return 1/(x*potencia(x, abs(y)-1));
		else
			return (x*potencia(x, y-1));
	}
}

void calcularPotencia(){
	int x, y;
	cabecalho("Potencia");

	printf("\t\tInforme (X): ");
	fflush(stdin);
	scanf("%d", &x);

	printf("\t\tInforme (Y): ");
	fflush(stdin);
	scanf("%d", &y);

	printf("\n\n\t\tResultado X^Y: %d. [ENTER]", potencia(x, y));
	fflush(stdin);
	getchar();
}

// CONVERSOR

void conversor(int num){	
	int quociente, resto;
    if(num != 0){
        quociente = num / 2;
        resto = num - quociente * 2;
        conversor(quociente);
        printf("%d", resto);
    }
}

void converteDB(){
	int num;
	cabecalho("Conversor de Decimal P/ Binario");

	printf("\t\tInforme o numero: ");
	fflush(stdin);
	scanf("%d", &num);

	printf("\n\n\t\tResultado da conversao: ");
	conversor(num);
	printf(" [ENTER]");
	fflush(stdin);
	getchar();
}

// FATORIAL

double fac(double n){
	if(n != 0)
		n = 1/n + fac(n-1);
	return n;
}

void calcularFatorial(){
	int n;
	cabecalho("Fatorial");

	printf("\t\tNumero de Elementos: ");
	fflush(stdin);
	scanf("%d", &n);

	printf("\n\n\t\tSoma dos Elementos: %f", fac(n));
	fflush(stdin);
	getchar();
}


// PALIDROME

int palindromo (char *v, int i, int j){
	if(i >= j ) return 1;
	else{
		if(v[i] == v[j])
			return palindromo(v, i+1, j-1);
		else
			return 0; 
	}
}  

void verificarPalindromo(){
	char v[50];
	cabecalho("Palindromo");

	printf("\t\tInforme a palavra: ");
	fflush(stdin);
	gets(v);
	if(palindromo(v, 0, strlen(v)-1))
		printf("\n\t\tA palavra %s e palidromo! [ENTER]", v);
	else
		printf("\n\t\tA palavra %s nao e palidromo! [ENTER]", v);
	fflush(stdin);
	getchar();
}

// HANOI

void moveDisco(char origem, char destino, int n){
	printf("\n\t\tMovimento: %c -> %c do Disco: %d", origem, destino, n);
}

void hanoi(int n, char origem, char destino, char aux){
	if(n == 1)
		moveDisco(origem, destino, n);
	else{
		hanoi(n-1, origem, aux, destino);
		moveDisco(origem, destino, n);
		hanoi(n-1, aux, destino, origem);
	}
}

void moverTorre(){
	int n;
	char origem, destino, aux;
	cabecalho("Torre e HANOI");

	printf("\t\tNumero de disco(s): ");
	fflush(stdin);
	scanf("%d", &n);

	printf("\t\tTorre Origem: ");
	fflush(stdin);
	scanf("%c", &origem);
	
	printf("\t\tTorre Destino: ");
	fflush(stdin);
	scanf("%c", &destino);

	if((origem == 'A' && destino == 'B') || (origem == 'B' && destino == 'A') ||
	   (origem == 'a' && destino == 'b') || (origem == 'b' && destino == 'a'))
		aux = 'C';

	if((origem == 'C' && destino == 'B') || (origem == 'B' && destino == 'C') ||
	   (origem == 'c' && destino == 'b') || (origem == 'b' && destino == 'c'))
		aux = 'A';

	if((origem == 'C' && destino == 'A') || (origem == 'A' && destino == 'C') ||
	   (origem == 'c' && destino == 'a') || (origem == 'a' && destino == 'c'))
		aux = 'B';

	hanoi(n, origem, destino, aux);
	fflush(stdin);
	getchar();
}

void sair(){
	cabecalho("SAIR");
	printf("\t\t# Finalizando sistema!  [ENTER]");
	fflush(stdin);
	getchar();
}

int main(){
	int op;
	do{
		op = menu();
		switch(op){
		case 1: calcularMDC();break;
		case 2: quantidadeImpares();break;
		case 3: calcularFibonacci();break;
		case 4: calcularPotencia();break;
		case 5: converteDB();break;
		case 6: calcularFatorial();break;
		case 7: verificarPalindromo();break;
		case 8: moverTorre();break;
		case 9: sair();break;
		default: printf("\n\n\t\t# Opcao [%d] invalida! [ENTER]", op);fflush(stdin);getchar();
		}
	} while(op != 9);
	return 0;
}