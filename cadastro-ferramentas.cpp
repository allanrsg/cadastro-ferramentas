#include<stdio.h>
#include<conio.c>
#include<string.h>
#include<locale.h>

void incluir();
void alterar();
void remover();
void listar();
void cadastrosecundario();

void transacao();
void commit();
void rollback();

struct ferramenta{
	int cod;
	char prod[20], confirmar;
}reg;

struct commit{
	int codi;
	char produ[20];
}com;

FILE *log;
FILE *arq;
FILE *arquivo;
FILE *mem;

char resposta;
int testecommit, teste, tr=0;

main(){
char opcao;
	listar();
do{
	listar();
   	gotoxy(19,3);printf("---BANCO DE DADOS---");
   	gotoxy(10,19);	printf("1 - NOVA TRANSAÇÃO");
	gotoxy(35,19);	printf("2 - CHECKPOINT");//não esta em uso no momento
	gotoxy(15,21);	printf("3 -  EXISTE DEADLOCK?");//não esta em uso no momento
	gotoxy(25, 23);	printf("4 - Sair! ");
	gotoxy(25,25);	printf("Opção: ");
	gotoxy(32,25);	opcao=getche();

	switch(opcao){
		case '9':cadastrosecundario();
		case '1':transacao();break;
		case '2':listar();break;
		//case '3':();break;
		case '4':clrscr();
			gotoxy(10,10);	printf("Programa encerrado");
			gotoxy(12,12);	printf("Tecle algo para sair");
			break;
			default:
   			gotoxy(35,25);printf("Opção Inválida.");
			getch();
		}
}while(opcao!='4');

}
void transacao(){
	char opcao;
	log=fopen("log.txt","at");
	tr=tr+1;
	fprintf(log,"Iniciou T""%i \n",tr);
	fclose(log);
	do{
	clrscr();
	listar();
	gotoxy(19,3);printf("---BANCO DE DADOS---");
	listar();
	gotoxy(10,19);printf("1-INSERIR");
	gotoxy(22,19);printf("2-ALTERAR");
	gotoxy(34,19);printf("3-REMOVER");
	gotoxy(15, 21);printf("4-COMMIT");
	gotoxy(26, 21);printf("5-ROLLBACK");//não esta em uso no momento
	gotoxy(25,25);printf("Opção: ");
	gotoxy(32,25);opcao=getche();
	switch(opcao){
		case '1':incluir();break;
		case '2':alterar();break;
		case '3':remover();break;
		case '4':commit();break;
		case '5':clrscr();
			gotoxy(12,12);	printf("Tecle algo para retornar!");  getch();clreol();
			break;
		default:gotoxy(10,15);printf("Opção Inválida.");
				gotoxy(12,17);printf("Escolha uma opção válida.");
				getch();
		}
}while(opcao!='5');
}

void incluir(){
	char confirmar;
	resposta='S';
	arq=fopen("mem.txt","ab");

	if(arq){
		while(resposta=='S' || resposta=='s'){

			clrscr();
			gotoxy(10,3);	printf("Cadastro ferramenta");
			gotoxy(10,7);	printf("Código da ferramenta......: ");
				scanf("%i", &reg.cod);
			gotoxy(10,8);	printf("Descrição da ferramenta...: ");
				fflush(stdin);
				fgets(reg.prod,20,stdin);
			//gotoxy(10,10);	printf("Confirmar? ");
				//confirmar=getche();
				//clrscr();
			//if(confirmar=='S'|| confirmar=='s'){
				teste=fwrite(&reg,sizeof(struct commit), 1, arq);
				fclose(arq);
			//	if(teste){
					gotoxy(10,14);
					printf("Registro gravado com sucesso!");

			//	}


			gotoxy(10,20);	printf("Deseja continuar?");
			resposta=getche();
		}
		fclose(arq);
	}
}



void alterar(){
 char nomepesq[30];	int achei, apontador;
resposta='s';
arq=fopen("ferramenta.txt", "rb+");
if(arq){
			 while (resposta=='s' || resposta=='S'){
			   achei=0;
				clrscr();
				gotoxy(10,3);	printf("Alterar produto");
				gotoxy(10,7); 	printf("Nome do Produto: ");
				fflush(stdin); 	fgets(nomepesq,20,stdin);
				rewind(arq);
				apontador=0;
				while(!feof(arq) && achei ==0){
						teste=fread(&reg,sizeof(struct ferramenta), 1,arq);
						apontador++;
						if(teste){
							if(strcmp(reg.prod,nomepesq)==0){

								gotoxy(10,13);	printf("Código..: %i", reg.cod);
								gotoxy(10,14);	printf("Nome....: %s", reg.prod);

								achei=1;
								gotoxy(40,10);	printf("Editar Produto...");
								gotoxy(40,13);	printf("Código: " );	scanf("%i",&reg.cod);
								gotoxy(40,14);	printf("Nome: ");		fflush(stdin);
																		fgets(reg.prod,20,stdin);
								gotoxy(40,20);	printf("Confirma a edição? S/N");
								gotoxy(63,20);  resposta=getche();
								if(resposta=='s' || resposta=='S'){
									apontador--;
									fseek(arq,apontador * sizeof(struct ferramenta), SEEK_SET);
									teste=fwrite(&reg,sizeof(struct ferramenta), 1, arq);
									if(teste){
										gotoxy(40,20);
										printf("Registro editado com sucesso");
		                           	}
								}
							}
						}
					if(achei==0){
						gotoxy(10,12);	printf("Registro não encontrado.");
					}
		gotoxy(10,22);		printf("Deseja continuar? S/N");
		resposta=getche();
		fclose(arq);
					}
			 }
		}
		else{
				clrscr();
				gotoxy(10,8);	printf("Arquivo Vazio.");
				gotoxy(10,10);	printf("Tecle algo para voltar");
				getch();
		}
}









void remover(){

	char nomepesq[30];
	int achei, apontador;
	resposta='S';
	arq=fopen("ferramenta.txt","rb+");
if(arq)	{
	while(resposta=='S'||resposta=='s'){
		arquivo=fopen("log.txt","ab");
							fprintf(arquivo, "EXCLUIR PRODUTO \n");
							fclose(arquivo);
		achei=0;
		clrscr();
		gotoxy(10,3);	printf("Exclui Produto");
		gotoxy(10,7);
		printf("Qual o nome do produto: ");
		fflush(stdin);
		fgets(nomepesq,20,stdin);

		rewind(arq);
		apontador=0;
		while(!feof(arq)&& achei==0)
		{
			teste=fread(&reg,sizeof(struct ferramenta),1,arq);
			apontador++;
			if(teste){

				if(strcmp(reg.prod,nomepesq)==0){

					gotoxy(10,8);	printf("Pesquisa realizada com sucesso");
					arquivo=fopen("log.txt","ab");
							fprintf(arquivo, "PRODUTO PESQUISADO \n");
							fclose(arquivo);
					gotoxy(10,12);	printf("Codigo..: %i", reg.cod);
					gotoxy(10,13);	printf("Descrição....: %s", reg.prod);

					achei=1;


					reg.cod=0;
					strcpy(reg.prod," ");


					gotoxy(10,19);	printf("Confirma a exclusão? S/N");



					gotoxy(35,19);	resposta=getche();


						if(resposta=='s' || resposta=='S'){
							apontador--;
							fseek(arq, apontador * sizeof(struct ferramenta), SEEK_SET);
							teste=fwrite(&reg, sizeof(struct ferramenta),1, arq );
							if(teste){
								gotoxy(10,19);
								printf("Registro excuido com sucesso.");
								arquivo=fopen("log.txt","ab");
								fprintf(arquivo, "PRODUTO PESQUISADO EXCLUIDO \n");
								fclose(arquivo);
							}

						}
							else{
								arquivo=fopen("log.txt","ab");
									fprintf(arquivo, "EXCLUSÃO CANCELADA! \n");
									fclose(arquivo);
							}


				}
			}
		}
					if(achei==0){
						gotoxy(10,12);
						printf("Registro não encontrado.");
						arquivo=fopen("log.txt","ab");
							fprintf(arquivo, "ERRO - PRODUTO NÃO ENCONTRADO! \n");
							fclose(arquivo);
					}
					gotoxy(10,22);
					printf("Deseja continuar? S/N");
					resposta=getche();
				}
				fclose(arq);
		}
		else{
			clrscr();
			gotoxy(10,8);	printf("Arquivo vazio.");
			arquivo=fopen("log.txt","ab");
							fprintf(arquivo, "ERRO - ARQUIVO VAZIO! \n");
							fclose(arquivo);
			gotoxy(10,10);	printf("Tecle algo para voltar ao menu..");
			getch();
		}
	}

 void listar(){
int linha=5;
arq=fopen("ferramenta.txt","rb");
	arquivo=fopen("log.txt","ab");
	fprintf(arquivo, "LISTAR PRODUTOS \n");
	fclose(arquivo);
	clrscr();
	if(arq){
	gotoxy(10,4);	printf("Código  Produto");
		while(!feof(arq))
		{
		teste=fread(&reg, sizeof(struct ferramenta), 1,arq);
		if(teste && strcmp(reg.prod, ""))
		{
		gotoxy(10,linha);	printf("%04i", reg.cod);
		gotoxy(15,linha);	puts(reg.prod);


			if(linha<17)
			linha++;
				else{
				gotoxy(10,22);
				printf("Tecle ENTER para continuar exibindo os registros.");
				getch();
				gotoxy(10,9);	delline();
					gotoxy(10,17);	insline();
				}
		}
		}
		fclose(arq);
	}
		else{
			gotoxy(10,19);	printf("Arquivo vazio.");
				arquivo=fopen("log.txt","ab");
				fprintf(arquivo, "ERROR - ARQUIVO VAZIO \n");
				fclose(arquivo);
			gotoxy(10,10);	printf("Tecle algo para voltar ao menu...");
			getch();
		}
}


void commit(){
int *ptrcodcom;
char *ptrprodcom;
		int apontador;char apontacommit;
 		apontador++;
		mem=fopen("mem.txt","r");
		fseek(arq,apontacommit *  sizeof(struct commit),SEEK_SET)  ;
		testecommit=fread(&reg, sizeof(struct commit), 1,mem);
		reg.cod==com.codi;
		reg.prod==com.produ;
	   	arq=fopen("commit.txt","ab");
		fseek(arq,apontacommit *  sizeof(struct commit),SEEK_END)  ;
  		teste=fwrite(&reg,sizeof(struct ferramenta), 1, arq);
		fclose(arq);
 }



void cadastrosecundario(){
	char confirmar;
	resposta='S';
	arq=fopen("ferramenta.txt","ab");

	if(arq){
		while(resposta=='S' || resposta=='s'){

			clrscr();
			gotoxy(10,3);	printf("Cadastro ferramenta");
			gotoxy(10,7);	printf("Código da ferramenta......: ");
				scanf("%i", &reg.cod);
			gotoxy(10,8);	printf("Descrição da ferramenta...: ");
				fflush(stdin);
				fgets(reg.prod,20,stdin);



			gotoxy(10,10);	printf("Confirmar? ");
				confirmar=getche();
				clrscr();
			if(confirmar=='S'|| confirmar=='s'){
				teste=fwrite(&reg,sizeof(struct ferramenta), 1, arq);

				if(teste){
					gotoxy(10,14);
					printf("Registro gravado com sucesso!");

				}
			}

			gotoxy(10,20);	printf("Deseja continuar?");
			resposta=getche();
		}
		fclose(arq);
	}
}
