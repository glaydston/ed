#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lista.h"


//************************* AUXILIARES ******************************

// função para exibir o menu de opções.
int menu(){
	int op;
	system("cls");
	printf("GERENCIA DE VOOS\n");
	printf("---------------------------------\n\n");
	printf("1 - Cadastrar Voo\n");
	printf("2 - Alterar Voo\n");
	printf("3 - Excluir Voo\n");
	printf("4 - Ativar Voo\n");
	printf("5 - Listar Voos\n");

	printf("\n\n\nVENDA DE PASSAGENS\n");
	printf("---------------------------------\n\n");
	printf("6 - Vender Passagem\n");
	printf("7 - Listar passageiros\n");
	printf("8 - Exibe Cidades Cadastradas\n");
	printf("9 - Sair\n\n");
	printf("Opcao: ");
	fflush(stdin);
	scanf("%d", &op);

	return op;
}

int menuAlterar(){
	int opc;
	printf("\nQual campo deseja alterar ?\n\n");        
	printf("1 - Cidade de Origem \n");
	printf("2 - Cidade de Destino \n");
	printf("3 - Data do voo \n");
	printf("4 - Hora do voo \n");
	printf("9 - VOLTAR \n");
	printf("Opcao: ");
	fflush(stdin);
	scanf("%d",&opc);

	return opc;
}



int encontraCidade(char cidade[40]){
	char c[40];	
	int retorno = 0;
    FILE * fp = fopen("cidades.txt","r"); 
	if(!fp){
		printf("\nErro na abertura do arquivo texto!");
		fflush(stdin);
		getchar();
	}
	while (fgets(c, 40, fp))
		if(stricmp(c, cidade) == 0){
			retorno = 1;
			break;
		}
	fclose(fp);
	return retorno;    
}

void insereCidadeOrigem(tVoo *voo){
	int opc;
	char str[40];
	do{
		printf("\nEntre com a cidade de origem: ");
		fflush(stdin);
		gets(str);
		opc = encontraCidade(str);
	} while(opc != 0);
	strcpy(voo->cidadeOrigem, str);
}

void insereCidadeDestino(tVoo *voo){
	int opc;
	char str[40];
	do{
		printf("Entre com a cidade de destino: ");
		fflush(stdin);
		gets(str);
		opc = encontraCidade(str);
	} while(opc != 0);		
	strcpy(voo->cidadeDestino, str);
}

void insereData(tVoo *voo){
	int opc;
	do{
		printf("Entre com a data: ");
		fflush(stdin);
		scanf("%d/%d/%d", &voo->data.dia, &voo->data.mes, &voo->data.ano);
		if(((voo->data.dia < 1)||(voo->data.dia > 31)) || ((voo->data.mes < 1)||(voo->data.mes > 12)) || (voo->data.ano < 2012)){				
			printf("\nData invalida, tente novamente !\n");
			opc = 1;
		} else opc = 0;
	} while(opc != 0);
}

void insereHora(tVoo *voo){
	int opc;
	do{
		printf("Entre com a hora do voo: ");
		fflush(stdin);
		scanf("%d:%d",&voo->hora.horas, &voo->hora.minutos);
		if(((voo->hora.horas < 0)||(voo->hora.horas > 23)) || ((voo->hora.minutos < 0)||(voo->hora.minutos > 59))){					
			printf("\nHora invalida, tente novamente !\n");
			opc = 1;
		} else opc = 0;
	} while(opc != 0);
}

//gera o mapa do voo
int mapaVoo(tVoo *voo){ 
    int col, lin;
	char c;
	tPassageiro passageiro;
	do{
		printf("Entre com o numero de fileiras: (MAXIMO 26) ");
		fflush(stdin);
		scanf("%d", &col);
	} while(col > 10);
	
    printf("\nE: ");
    printf("\nEntre com o numero de poltronas por fileiras: ");
    fflush(stdin);
    scanf("%d",&lin);

	inicializaPassageiro(&voo->passageiros);
	
	voo->col = col;
	voo->lin = lin;

    int aux = 65;
    for(int i=0;i<lin;i++){
        for(int j=0;j<col;j++){	
			passageiro.numero = i+1;
			passageiro.flag   = 0;
			passageiro.codVoo = voo->codVoo;
            printf("%d %c\t", i+1, aux+j);		
			inserePassageiro(passageiro, &voo->passageiros); 
        }
		printf("\n");
    }
	return col*lin;
}
//************************* GERENCIA DE VOOS ******************************

// funçao que gera id novo para cada voo e armazena em um arquivo texto para controle.
int geraCodVoo(){
    int cod;
    FILE * fp = fopen("codVoo.txt","r");
	while (!feof(fp))
  		fscanf(fp,"%d",&cod);
  	fclose(fp);
    cod++;
       
	fp = fopen("codVoo.txt","w");
    if (!fp){
        printf("Erro na abertura do arquivo texto");
        exit(1);
    }
    fprintf(fp,"%d", cod);
	fclose(fp);	
	return cod;
}

void cadastrarVoo(tListaEnc *l){
	int opc, quant;
    tVoo voo;
    do{
		system("cls");
		printf("\t\t\tCadastro de Voo \n\n");
		
        voo.codVoo = geraCodVoo();	
		quant = mapaVoo(&voo);		
		insereCidadeOrigem(&voo);
		insereCidadeDestino(&voo);		
		insereData(&voo);
		insereHora(&voo);		

		voo.dispInicial = quant;
        voo.dispAtual = voo.dispInicial;        
        voo.flag = 1;        
		
        insereVoo(voo, l);        

        printf("\n\nDeseja cadastrar outro Voo ?(0 PARA SAIR)");
		fflush(stdin);
        scanf("%d", &opc);
    } while(opc != 0);
}

void imprimePassageirosVoo(tListaEnc *l){
	if(vaziaVoo(l)){
		printf("\n\nLista Vazia, cadastre voo(s)!");
		fflush(stdin);
		getchar();
		return;
	}

    int numeroVoo, encontra = 0;
	tCelula *celula = l->primeiro->prox;
	system("cls");
	printf("\t\t\tConsultar voo\n\n");
	printf("\t\tDigite numero do voo: ");
	fflush(stdin);
	scanf("%d", &numeroVoo);
	
	while(celula != NULL){
		if(celula->voo.codVoo == numeroVoo){			
			printf("\nLISTAGEM DE PASSAGEIROS\n\n");
			int aux = 65;
			for(int i=0;i<celula->voo.lin;i++){
				 for(int j=0;j<celula->voo.col;j++){
					 if(celula->voo.passageiros.item[i].flag != 0)
						printf("Assento: %d%c  Nome: \t", i+1, aux+j, celula->voo.passageiros.item[i].nome);
					 
				}
				printf("\n");
			}
			encontra = 1;
		}
		celula = celula->prox;
	}	

	if(encontra == 0) printf("\n\nVoo nao encontrado !!");	
	fflush(stdin);
	getchar();
}

void imprimirVoo(tVoo voo){
	printf("\n\n-------------------------------------------------\n");
	printf("Codigo:\t\t\t%d\n", voo.codVoo);
	printf("Origem/Destino \t\t%s/%s\n",voo.cidadeOrigem, voo.cidadeDestino);
	printf("Data: \t\t\t%d/%d/%d\n", voo.data.dia, voo.data.mes, voo.data.ano);
	printf("Hora: \t\t\t%d:%d\n", voo.hora.horas, voo.hora.minutos);
	printf("Disponibilidade: \t%d\n", voo.dispInicial);
	printf("Status do voo: \t\t%d\n\n", voo.flag);
}

// funçao que altera voo 
void alteraVoo(tListaEnc *l){
	if(vaziaVoo(l)){
		printf("\n\nLista Vazia, cadastre voo(s)!");
		fflush(stdin);
		getchar();
		return;
	}

    int opc, numeroVoo, encontra = 0;
	tCelula *celula = l->primeiro->prox;

	system("cls");
	printf("\t\t\Alterar voo\n\n");
    printf("Entre com o codigo do voo que deseja alterar: ");
	fflush(stdin);
	scanf("%d", &numeroVoo);

	while(celula != NULL){
		if(celula->voo.codVoo == numeroVoo){			
			printf("\nO resultado da sua busca foi a seguinte: ");
		 	imprimirVoo(celula->voo);
			printf("-------------------------------------------------\n");
			do{
				opc = menuAlterar();
				switch(opc){
					case 1: insereCidadeOrigem(&celula->voo); 		break;
					case 2:	insereCidadeDestino(&celula->voo); 		break;
					case 3: insereData(&celula->voo);				break;
					case 4: insereHora(&celula->voo);				break;
					case 9:	opc = 9;								break;
					default: printf("\n\n\t\tOpcao invalida!");
				}
			} while(opc != 9);
			encontra = 1;
		}
		celula = celula->prox;
	}	
          	 
	if(encontra == 0){
		printf("\n\nVoo nao encontrado !!");	
		fflush(stdin);
		getchar();
	}   
}


// função que exclui um voo cadastrado de acordo com seu id
void excluiVoo(tListaEnc *l){
	if(vaziaVoo(l)){
		printf("\n\nLista Vazia, cadastre voo(s)!");
		fflush(stdin);
		getchar();
		return;
	}

    int encontra = 0;
    int numeroVoo;
	tCelula *celula = l->primeiro->prox;
	system("cls");
	printf("\t\t\Excluir voo\n\n");
	printf("Entre com o codigo do voo que deseja excluir: ");
	fflush(stdin);
	scanf("%d", &numeroVoo);

	while(celula != NULL){
		if(celula->voo.codVoo == numeroVoo){			
			celula->voo.flag = 0;		
            printf("\nO Voo foi excluido com sucesso !!: ");
		 	imprimirVoo(celula->voo);
			encontra = 1;
		}
		celula = celula->prox;
	}	
          	 
	if(encontra == 0) printf("\n\nVoo nao encontrado !!");	
	fflush(stdin);
	getchar();

}

void ativaVoo(tListaEnc *l){  
	if(vaziaVoo(l)){
		printf("\n\nLista Vazia, cadastre voo(s)!");
		fflush(stdin);
		getchar();
		return;
	}

	int encontra = 0;
    int numeroVoo;
	tCelula *celula = l->primeiro->prox;
	system("cls");
	printf("\t\t\tAtivar voo\n\n");
	printf("\t\tEntre com o codigo do voo que deseja ativar: ");
	fflush(stdin);
	scanf("%d", &numeroVoo);

	while(celula != NULL){
		if(celula->voo.codVoo == numeroVoo){			
			celula->voo.flag =1;		
			printf("\nO Voo foi ativado com sucesso !! ");
			imprimirVoo(celula->voo);
			encontra = 1;
		}
		celula = celula->prox;
	}	
          	 
	if(encontra == 0) printf("\n\nVoo nao encontrado !!");	
	fflush(stdin);
	getchar();
}

//************************* VENDA DE PASSAGENS ******************************

// funçao que gera id novo para cada voucher armazena em um arquivo texto para controle. **idem a codigo do voo
int geraNumVoucher(){
    int cod;
    FILE * fp = fopen("codVoucher.txt","r");
	while (!feof(fp)) fscanf(fp,"%d", &cod);
	fclose(fp);   

    cod++;       

	fp = fopen("codVoucher.txt","w");
    if (!fp){
        printf("Erro na abertura do arquivo texto");
        exit(1);
    }
    fprintf(fp,"%d", cod);
	fclose(fp);
	
	return cod;
}

int condicaoVenda(tCelula *celula, tVoo voo){
	int verif = 0;
	if(		(strcmp(celula->voo.cidadeOrigem, voo.cidadeOrigem) == 0)	&&	// comparo as cidades de origem
			(strcmp(celula->voo.cidadeDestino, voo.cidadeDestino) == 0) &&	// comparo as cidades de destino
			(celula->voo.flag != 0) &&										// verifico a flag
			(	(	(celula->voo.data.dia == voo.data.dia)				&& 
					(celula->voo.data.mes == voo.data.mes)				&& 
					(celula->voo.data.ano == voo.data.ano)
				)														||
				(	(celula->voo.data.dia+1 ==	voo.data.dia)			&& 
					(celula->voo.data.mes	==	voo.data.mes)			&& 
					(celula->voo.data.ano	==	voo.data.ano)
				)														||
				(	(celula->voo.data.dia-1 == voo.data.dia)			&& 
					(celula->voo.data.mes == voo.data.mes)				&& 
					(celula->voo.data.ano == voo.data.ano)
				)
			)																// comparo a data escolhida		
		){// se todos os dados forem iguais eu imprimo os voos encontrados.
              //voo.dispAtual = (voo.dispInicial/11); // testando mensagem de ultimos assentos disponíveis
              printf("\n\n------------------------------------------------\n\n");
              printf("Codigo:\t\t\t%d\n", celula->voo.codVoo);
              printf("Origem/Destino \t\t%s/%s\n", celula->voo.cidadeOrigem,voo.cidadeDestino);
              printf("Data: \t\t\t%d/%d/%d\n", celula->voo.data.dia,voo.data.mes,voo.data.ano);
              printf("Hora: \t\t\t%d:%d\n", celula->voo.hora.horas, celula->voo.hora.minutos);
              printf("Disponibilidade Atual: \t%d", celula->voo.dispAtual);
              verif = 1;// se encontrar voo, atribui a variavel com o valor 1, se nao encontrar nenhum voo imprime a msg de voo nao encontrado.
              int mindispAtual = (celula->voo.dispInicial/10); // calcula 10% da capacidade de voo
              if(celula->voo.dispAtual < mindispAtual) printf("  (Ultimos assentos disponiveis !!)\n\n");      
            }// acabei de imprimir
	return verif;
}

void imprimeMapa(tVoo voo){
	int aux = 65;
	for(int i=0;i<voo.col;i++){
        for(int j=0;j<voo.col;j++){	
			if(voo.passageiros.item[i].flag)
				printf(" - \t");		
			else
				printf("%d %c\t", i+1, aux+j);		
        }
		printf("\n");
    }
}

void vendaPassagem(tListaEnc *l){
    int cod, quantAssentos, cod_voucher, verif, opc = 0;
    tDate dataPassagem;
    tVoo voo;
	tCelula *celula = l->primeiro->prox;
    tPassageiro passageiro;	

	if(vaziaVoo(l)){
		printf("\n\nLista Vazia, cadastre voo(s)!");
		fflush(stdin);
		getchar();
		return;
	}

	system("cls");
	printf("\t\tVenda de Passagem\n\n");

	insereCidadeOrigem(&voo);
	insereCidadeDestino(&voo);
	insereData(&voo);
	
	do{		
		tCelula *cel = l->primeiro->prox;
		tCelula *aux = l->primeiro->prox;

		printf("\n\n\t\tVOOS DISPONIVEIS !\n");
		printf("------------------------------------------------\n");

		while(cel != NULL){
			verif = condicaoVenda(cel, voo);
			cel = cel->prox;
		}
		if (verif != 1){
			printf("\n\nNao existe voo cadastrado com a ORIGEM/DESTINO na data solicitada !\n\nPressione qualquer tecla para continuar !");
			opc = 9;
		}else {
			printf("\n\nEntre com o codigo de um dos voos exibidos que deseja comprar a(s) passagem(ns): ");
			fflush(stdin);
			scanf("%d",&cod);

			int retorno = 0;
			while(aux != NULL){
				if(aux->voo.codVoo == cod){
					imprimeMapa(aux->voo);
					// fazer um tratamento de erro e uma condiçao para caso o usuario insira um codigo que não é exibido nas opçoes ou que esteja desabilitado
					printf("Agora entre com o numero de assentos que deseja: ");
					fflush(stdin);
					scanf("%d",&quantAssentos);
					if(aux->voo.dispAtual < quantAssentos){			
						 printf("\n\nNAO HA A QUANTIDADE DE ASSENTOS SOLICITADOS PARA COMPRA NESTE VOO !\n");
						 printf("\n\nESCOLHA OUTRO VOO ! !\n");
						 printf("------------------------------------------------\n");
					} else { 					
						aux->voo.dispAtual = aux->voo.dispAtual - quantAssentos;
						for(int i=1;i<=quantAssentos;i++){
							 printf("Entre com o nome do passageiro: ");
							 fflush(stdin);
							 gets(passageiro.nome);

							 cod_voucher = geraNumVoucher();

							 printf("\n\n**********************************VOUCHER************************************\n");
							 printf("Codigo do voucher: %d\n",	cod_voucher);
							 printf("Numero do voo: %d\n",		aux->voo.codVoo);
							 printf("Cidade de Origem: %s\n",	aux->voo.cidadeOrigem);
							 printf("Cidade de Destino: %s\n",	aux->voo.cidadeDestino);
							 printf("Data do voo: %d/%d/%d/n",	aux->voo.data.dia,aux->voo.data.mes,aux->voo.data.ano);
							 printf("Horario do voo: %d:%d",	aux->voo.hora.horas,aux->voo.hora.minutos);
							 printf("Nome do passageiro: %s\n\n",	passageiro.nome);
							 printf("\n\n*****************************************************************************\n");
							 int salvar;
							 printf("\n\nDeseja salvar o voucher em um arquivo .txt ? (1 - sim | qualquer outra tecla - nao)\n");                    
							 scanf("%d",&salvar);

							 inserePassageiro(passageiro, &aux->voo.passageiros);

							 if(salvar == 1){
								   FILE * ft;
								   ft = fopen(passageiro.nome,"w");
								   fprintf(ft,"%d|%d|%s|%s|%d/%d/%d|%d:|%d||%s",cod_voucher, aux->voo.codVoo, aux->voo.cidadeOrigem, aux->voo.cidadeOrigem
								   , aux->voo.data.dia, aux->voo.data.mes, aux->voo.data.ano, aux->voo.hora.horas, aux->voo.hora.minutos, passageiro.nome);
								   fclose(ft);
								   fflush(stdin);
								   FILE * ft2;
								   ft2 = fopen("vendas.txt","a+");
								   fprintf(ft2,"%d|%d|%s\n", cod_voucher, aux->voo.codVoo,passageiro.nome);
								   fclose(ft2);
								   FILE * fb2;
								   fb2 = fopen("passageiros.bin","ab+");
								   passageiro.codVoo = aux->voo.codVoo;
								   fwrite(&passageiro,sizeof(tPassageiro),1,fb2);
								   fclose(fb2);
							}
						}
						opc = 9;		
					}
					retorno = 1;
					break;
				}
				aux = aux->prox;
			}
			if(retorno == 0) printf("\n\nVoo nao encontrado !!");
		}
		fflush(stdin);
		getchar();
	} while(opc != 9);	// se sair é porque encontrou um voo valido e que tem passagens o suficiente.   
     // fornece cidade de origem
     // fornece cidade de destino
     // fornece o dia da passagem
     // O sistema apresenta os codigos dos voos para aquele dia de acordo com a combinação de cidades escolhidas
     // Para cada opção de vôo, o sistema deve apresentar o horário e os assentos disponíveis.
     // if assentos disponiveis < 10% do total ... printf("ultimos assentos disponiveis")
     // escolhe um voo e fornece a quantidade de passagens que quer comprar
     // se tiver assentos disponiveis pede o nome do passageiro, senão fala pra ele escolher outro voo.
     // exibe novamente os codigos dos voos para aquele dia de acordo com a combinaão de cidades escolhidas
     // deve dar a opçao de salvar os vouchers em arquivo .txt, contendo os dados: número do voucher (gerado pelo sistema e único), 
     // número do vôo, cidades de origem e destino, horário e nome do passageiro.
     // As vendas com o número do voucher, número do vôo e nome do passageiro devem ser guardados  em arquivo texto (“vendas.txt”), 
     // um voucher por linha.
}

// função que lista os voos cadastrados
void listaVoos(tListaEnc *l){
	if(vaziaVoo(l)){
		printf("\n\nLista Vazia, cadastre voo(s)!");
		fflush(stdin);
		getchar();
		return;
	}
    system("cls");
    printf("\t\tVOOS CADASTRADOS\n");
    printf("------------------------------------------------\n\n");
	imprimeVoo(l);
	fflush(stdin);
	getchar();
}


// lerArquivo: le os dados do arquivo
// e carrega na lista
void lerArquivo(tListaEnc *l){
	FILE *fp;
	tVoo voo;
	fp = fopen("voos.bin","rb");	

	if(fp == NULL)
		printf("\n\t\tErro ao tentar ler o arquivo.");
	else
		while(fread(&voo,sizeof(tVoo),1,fp))
			insereVoo(voo,l);
}

// gerarArquivo: gera o arquivo preenchendo com os
// voos que estão na lista l
void gerarArquivo(tListaEnc *l){
	FILE *fp;
	fp = fopen("voos.bin","wb");
	tVoo voo;
	if(fp == NULL)
		printf("\n\t\tErro ao tentar gerar o arquivo.");
	else{
		tCelula *celula = l->primeiro;
		while(!vaziaVoo(l)){
			retiraVoo(celula, l, &voo);
			fwrite(&voo, sizeof(tVoo), 1, fp);
		}
		printf("\n\t\tArquivo atualizado!");
	}
	fflush(stdin);
	getchar();
}

//função que exibe as cidades que estão cadastradas no arquivo txt.
void exibeCidades(){
	char c[40];
	int i = 0;
	system("cls");
	printf("Cidade(s): ");
    FILE * fp = fopen("cidades.txt","r");
    if(!fp){
		printf("Erro na abertura do arquivo texto!\n");
		fflush(stdin);
		getchar();
       exit(1);
    }
	while (fgets(c, 40, fp)){
		printf("\n\t\t%d. %s", ++i, c);
	}
    fclose(fp);
	fflush(stdin);
    getchar();
}

// ************* OPERAÇÕES OCULTAS

void zeraCodVoo(){
    FILE * fp = fopen("codVoo.txt","w");
    fprintf(fp,"%d", 0);
    printf("\n\nOPERACAO OCULTA REALIZADA, codVoo.txt zerado com sucesso !");
	fclose(fp);
}

void zeraArqVoos(){
    FILE * fb = fopen("voos.bin","wb+");
    if(!fb){
        printf("Erro na abertura do arquivo binario!\n");
        getchar();
        exit(1);
    }
	fclose(fb);
}

void main(){
	int op;
	tListaEnc l;
	inicializaVoo(&l);
	lerArquivo(&l);
	do{
		op = menu();
		switch (op){
			case 1:	cadastrarVoo(&l);			break;
			case 2:	alteraVoo(&l);				break;
			case 3:	excluiVoo(&l);				break;
			case 4: ativaVoo(&l);				break;
			case 5:	listaVoos(&l);				break;
			case 6:	vendaPassagem(&l);			break;
			case 7:	imprimePassageirosVoo(&l);	break;
			case 8: exibeCidades();				break;
			case 9:	gerarArquivo(&l);			break;
			case 50:zeraCodVoo();				break;
			case 51:zeraArqVoos();				break;
			default: printf("\n\n\t\tOpcao invalida!");fflush(stdin);getchar();
		}		
	} while(op != 9);
}