#include<stdio.h>
#include<conio.c>
#include<string.h>
#include<locale.h>

void incluir();
void alterar();
void remover();
void listar();
void usuario();
void confincluir();
void cp();
//teste teste2
struct ferramenta{
	int cod;
	char prod[20];
	char confirmar;
}reg;

struct user{	
	char nome[30];
}regi;
	
FILE *log;
FILE *arq;
FILE *arquivo;					

char resposta, login[15] = "Admin", login1[15]; 
int senha =1234, senha1, teste;

main(){
	setlocale(LC_ALL,"Portuguese");
char opcao;

usuario();
do{	
	arquivo=fopen("log.txt","ab");
	fprintf(arquivo, "MENU \n");
	fclose(arquivo);
	clrscr();
	gotoxy(10,3);printf("---MENU FERRAMENTA---");
	gotoxy(10,4);printf("=================");
	gotoxy(10,6);printf("1 - Incluir ferramenta");
	gotoxy(10,7);printf("2 - Alterar produtos");//
	gotoxy(10,8);printf("3 - Excluir produto");
	gotoxy(10,9);printf("4 - Listar");
	gotoxy(10,11);printf("5 - Sair");
	gotoxy(10,13);printf("Opção: ");
		gotoxy(18,13);opcao=getche();		
		switch(opcao){	
		case '1':incluir();break;
		case '2':alterar();break;
		case '3':remover();break;
		case '4':listar(); break;
		case '5':clrscr();
			gotoxy(10,10);	printf("Programa encerrado");
				arquivo=fopen("log.txt","ab");
				fprintf(arquivo, "PROGRAMA ENCERRADO \n");
				fclose(arquivo);
			gotoxy(12,12);	printf("Tecle algo para sair");
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
	arq=fopen("ferramenta.txt","ab");
			
	if(arq){						
		while(resposta=='S' || resposta=='s'){
					arquivo=fopen("log.txt","ab");
					fprintf(arquivo, "INCLUIR  FERRAMENTA \n");
					fclose(arquivo);
			clrscr();
			gotoxy(10,3);	printf("Cadastro ferramenta");
			gotoxy(10,7);	printf("Código da ferramenta......: ");	
				scanf("%i", &reg.cod);
			gotoxy(10,8);	printf("Descrição da ferramenta...: ");	
				fflush(stdin);
				fgets(reg.prod,20,stdin);

		cp();
			gotoxy(10,10);	printf("Confirmar? ");
				confirmar=getche();
				clrscr();
			if(confirmar=='S'|| confirmar=='s'){
				teste=fwrite(&reg,sizeof(struct ferramenta), 1, arq);
			
				if(teste){
					gotoxy(10,14);
					printf("Registro gravado com sucesso!");
					confincluir();
				}
			}
			else{
					arquivo=fopen("log.txt","ab");
					fprintf(arquivo, "INCLUSÃO DE FERRAMENTA CANCELADA \n");
					fclose(arquivo);
			}
			gotoxy(10,20);	printf("Deseja continuar?");
			resposta=getche();
		}
		fclose(arq);		
	}
}

void alterar(){
	char nomepesq[30];
	int achei, apontador;
	resposta='s';
	arq=fopen("ferramenta.txt", "rb+"); 
	if(arq){
		while (resposta=='s' || resposta=='S'){
		arquivo=fopen("log.txt","ab");
		fprintf(arquivo, "ALTERAR \n");
		fclose(arquivo);
			achei=0;
			clrscr();
			gotoxy(10,3);	printf("Alterar produto");
			gotoxy(10,7);
			printf("Nome do Produto: ");
			fflush(stdin);
			fgets(nomepesq,20,stdin);
			
			rewind(arq);
			apontador=0;
			while(!feof(arq) && achei ==0){
				teste=fread(&reg,sizeof(struct ferramenta), 1,arq);
				apontador++;
				if(teste){
					if(strcmp(reg.prod,nomepesq)==0){
						arquivo=fopen("log.txt","ab");
						fprintf(arquivo, "PRODUTO ENCONTRADO \n");
						fclose(arquivo);
						gotoxy(10,13);	printf("Código..: %i", reg.cod);
						gotoxy(10,14);	printf("Nome....: %s", reg.prod);
							
						achei=1;
						gotoxy(40,10);	printf("Editar Produto...");
						gotoxy(40,13);	printf("Código: " );	scanf("%i",&reg.cod);
						gotoxy(40,14);	printf("Nome: ");		fflush(stdin);
																fgets(reg.prod,20,stdin);
						
						gotoxy(40,20);	printf("Confirma a edição? S/N");
						cp();
						gotoxy(63,20);  resposta=getche();
						if(resposta=='s' || resposta=='S'){
							apontador--;
							fseek(arq,apontador * sizeof(struct ferramenta), SEEK_SET);
							teste=fwrite(&reg,sizeof(struct ferramenta), 1, arq);
							if(teste){
								gotoxy(40,20);
								printf("Registro editado com sucesso");
									arquivo=fopen("log.txt","ab");
									fprintf(arquivo, "PRODUTO ALTERADO! \n");
									fclose(arquivo);
						
												
						}
							}
							else{
							arquivo=fopen("log.txt","ab");
							fprintf(arquivo, "PRODUTO NÃO ALTERADO! \n");
							fclose(arquivo);
							}
					
					}	
								
				}

			}
			if(achei==0){
				gotoxy(10,12);	printf("Registro não encontrado.");
						arquivo=fopen("log.txt","ab");
						fprintf(arquivo, "PRODUDO NÃO ENCONTRADO \n");
						fclose(arquivo);			
			}
			gotoxy(10,22);		printf("Deseja continuar? S/N");
			resposta=getche();
		}
		fclose(arq);

	}
	else{
		clrscr();
		gotoxy(10,8);	printf("Arquivo Vazio.");
						arquivo=fopen("log.txt","ab");
							fprintf(arquivo, "ERRO - ARQUIVO VAZIO! \n");
							fclose(arquivo);
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
		while(!feof(arq)&& achei==0){
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
				
				cp();
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

void usuario(){
	clrscr();
	do{
		clrscr();
		gotoxy(5,8);
		printf("LOGIN: ");scanf ("%s",login1);
		gotoxy(5,10); 
		printf("SENHA:");scanf("%i", &senha1);
		if (strcmp(login, login1) == 0 && senha == senha1)
		{
			printf("Logado como Administrador");
			arquivo=fopen("log.txt","ab");
			fprintf(arquivo, "Logado como Administrador \n");
			fclose(arquivo);
		}
		else
		{		
			printf("Erro no login");
			arquivo=fopen("log.txt","ab");
			fprintf(arquivo, "Erro no login \n");
			fclose(arquivo);
		}
	}while(strcmp(login, login1) != 0 || senha != senha1);	
}

void listar(){
int linha=9;
arq=fopen("ferramenta.txt","rb");
	arquivo=fopen("log.txt","ab");
	fprintf(arquivo, "LISTAR PRODUTOS \n");
	fclose(arquivo);					
	clrscr();
	if(arq){		
	gotoxy(10,3);	printf("PRODUTOS");
	gotoxy(10,4);	printf("Código  Produto             Quantidade");
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
		gotoxy(10,22); 	printf("Listagem concluida.");
		arquivo=fopen("log.txt","ab");
		fprintf(arquivo, "LISTAGEM CONCLUIDA \n");
		fclose(arquivo);
		gotoxy(10,23);	printf("Tecle algo para volta ao menu...");
		getch();
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
void confincluir(){
	clrscr();
	gotoxy(10,10);	printf("Ferramenta Incluida com sucesso!");
	arquivo=fopen("log.txt","ab");
	fprintf(arquivo, "INCLUSÃO DE FERRAMENTA CONCLUIDA \n");
	fclose(arquivo);
	getche();	
}

void cp(){
	arquivo=fopen("log.txt","ab");
	fprintf(arquivo, "checkpoint(precisa confirmar tarefa...) \n");
	fclose(arquivo);
}
