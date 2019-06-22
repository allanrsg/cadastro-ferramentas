#include<stdio.h>
#include<conio.c>
#include<string.h>
#include<locale.h>

void incluir();
void alterar();
void remover();
void listar();

int transacao();
void commit();
void rollback();
void copia();


struct copy{
	int comparac,codc,bloqueioc;	char prodc[30] ;
}cp;

struct ferramenta{
	int  compara,cod, bloqueio; 	char prod[30];//confirmar O COMPARA NUMERA FIXO UM PRODUDO 
}reg;



FILE *log;	//somente log 
FILE *arq;   //ferramenta.txt
FILE *arquivo;
FILE *mem;    //memoria.txt
FILE *altrem;

char resposta;
int numprod, teste, tr=0, controle;

int main(){
char opcao;

do{
clrscr();
	tr++;
	setlocale(LC_ALL, "Portuguese");
	
   	gotoxy(19,3);printf("---BANCO DE DADOS---");
   	gotoxy(10,9);	printf("1 - NOVA TRANSAÇÃO");
	gotoxy(10,10);	printf("2 - CHECKPOINT");//não esta em uso no momento
	gotoxy(10,11);	printf("3 - EXISTE DEADLOCK?");
	gotoxy(10,12);	printf("4 - LISTAR BANCO");//não esta em uso no momento
	gotoxy(10,13);	printf("5 - Sair! ");
	gotoxy(10,15);	printf("Opção: ");
	gotoxy(17,15);	opcao=getche();
	

	switch(opcao){
	
		case '1':transacao();break;
		case '2':listar(); ;break;
		//case '3':();break;
		case'4':listar();break;
		case '5':clrscr();
			gotoxy(10,10);	printf("Programa encerrado");
			gotoxy(12,12);	printf("Tecle algo para sair");
			log=fopen("log.txt", "ab");	fprintf(log,"Programa encerrado!\n");fclose(log);
			break;
			default:
   			gotoxy(35,25);printf("Opção Inválida.");
			getch();
		}
}while(opcao!='5');

}
int transacao(){
	char opcao;
	copia();

	log=fopen("log.txt","ab");	fprintf(log,"Iniciou T""%i \n",tr);fclose(log);
	
	do{	
	clrscr();

	gotoxy(19,3);printf("---TRANSAÇÃO %i---controle = %i", tr, controle);
	gotoxy(10,9);printf("1 - INCLUIR");
	gotoxy(10,10);printf("2 - ALTERAR");
	gotoxy(10,11);printf("3 - REMOVER");
	gotoxy(10,12);printf("4 - COMMIT");
	gotoxy(10, 13);printf("5 - ROLLBACK");
	gotoxy(10,14);printf("6 - VOLTAR MENU PRINCIPAL");
	gotoxy(10,15);printf("7 - ATUALIZA MEMORIA");
	gotoxy(10,16);printf("Opção: ");
	gotoxy(17,16);opcao=getche();
	switch(opcao){
		case '1':incluir();break;
		case '2':alterar();break;
		case '3':remover();break;
		case '4':commit();break;
		case '5':rollback();break;
		case '6':clrscr();
		case '7':copia();break;
		log=fopen("log.txt", "ab");
		fprintf(log," T%i saiu \n",tr);
			fclose(log);
			break;
		default:gotoxy(17,16);printf("Opção Inválida.");
				getch();
		}
}while(opcao!='6');
return tr;
}


void incluir(){
	char confirmar;
	resposta='S';
	log=fopen("log.txt", "wb");	
	arq=fopen("incluir.txt","ab");
	if(arq){
		while(resposta=='S' || resposta=='s'){
		
			clrscr();
			gotoxy(10,3);	printf("---Incluir ferramenta---");
			gotoxy(10,7);	printf("Código da ferramenta......: ");
				reg.compara=controle;
				scanf("%i", &reg.cod);
			gotoxy(10,8);	printf("Descrição da ferramenta...: ");
				fflush(stdin);
				fgets(reg.prod,30,stdin);
				reg.bloqueio=0;
				teste=fwrite(&reg,sizeof(struct ferramenta), 1, arq);
				
				fprintf(log,"T%i incluiu Cod %i Produto %s \n",tr, reg.cod, reg.prod);
				gotoxy(10,14);
				printf("Registro gravado com sucesso!");
				
			gotoxy(10,20);	printf("Pressione algo para continuar?");
			resposta=getche();
			controle++;
		}}
		fclose(log);fclose(arq);
}

void alterar(){
	char nomepesq[30];
	int achei, apontador, codant;
	resposta='s';
	arq=fopen("bdproduto.txt", "rb+");
	mem=fopen("copiabanco.txt", "rb+"); 
	log=fopen("log.txt", "ab");
	if(arq){
		while (resposta=='s' || resposta=='S'){
			achei=0;
			clrscr();
			gotoxy(10,3);	printf("---Editar produto---");
			gotoxy(10,5);	printf("============================");
			gotoxy(10,7);
			printf("Produto a ser pesquisado: ");
			fflush(stdin);
			fgets(nomepesq,30,stdin);
			rewind(mem);
			rewind(arq);
			apontador=0;
			while(!feof(arq) && achei ==0){
				teste=fread(&reg,sizeof(struct ferramenta), 1,arq);
				apontador++;
				if(teste){
						
					if(strcmp(reg.prod,nomepesq)==0 && reg.bloqueio==0){
						apontador--;
						reg.bloqueio=1;
							fseek(arq,apontador * sizeof(struct ferramenta), SEEK_SET);
							teste=fwrite(&reg,sizeof(struct ferramenta), 1, arq);fclose(arq);
							apontador++;
						
						gotoxy(10,13);	printf("Código..: %i", reg.cod);
						gotoxy(10,14);	printf("Nome....: %s", reg.prod);	
						achei=1;
						codant=reg.cod;
						
						gotoxy(40,10);	printf("Editando o registro...");
						gotoxy(40,13);	printf("Código: " );	scanf("%i",&cp.codc);
						gotoxy(40,14);	printf("Produto: ");		fflush(stdin);
																fgets(cp.prodc,20,stdin);
						
						gotoxy(40,20);	printf("Confirma a edição? S/N  ");
						gotoxy(63,20);  resposta=getche();
						
						if(resposta=='s' || resposta=='S'){
							log=fopen("log.txt", "ab");fprintf(log," T%i alterou cod %i  produto %s para cod %i produto %s \n",tr,codant, nomepesq, cp.codc, cp.prodc);fclose(log);
							apontador--;
							arq=fopen("bdproduto.txt", "rb+");
							reg.bloqueio=0;
							fseek(mem,apontador * sizeof(struct copy), SEEK_SET);
							teste=fwrite(&cp,sizeof(struct copy), 1, mem);
							if(teste){	gotoxy(40,20);	printf("Registro editado com sucesso");	}					
						}
						else{
							arq=fopen("bdproduto.txt", "rb+");
							apontador--;
							reg.bloqueio=0;
							fseek(arq,apontador * sizeof(struct ferramenta), SEEK_SET);
							teste=fwrite(&reg,sizeof(struct ferramenta), 1, arq);
						}
						
					}			
				}
			}
			if(achei==0){
				gotoxy(10,12);	printf("Registro não encontrado.");			
			}
			gotoxy(10,22);		printf("Deseja continuar? S/N");			
			resposta=getche();
		}
		fclose(arq);
	}
	else{
		clrscr();
		gotoxy(10,8);	printf("Arquivo Vazio.");
		gotoxy(10,10);	printf("Tecle algo para voltar");
		getch();
	}
}

/*void alterar(){
	char nomepesq[30];
	int achei, apontador, codant;
						
	resposta='s';
	
	mem=fopen("bdproduto.txt", "ab");
	arq=fopen("copiabanco.txt", "ab+"); 
	log=fopen("log.txt", "ab");
	
	if(arq){
		while (resposta=='s' || resposta=='S'){
			achei=0;
			clrscr();
			gotoxy(10,3);	printf("---Editar produto---");
			gotoxy(10,5);	printf("============================");
			gotoxy(10,7);
			printf("Produto a ser pesquisado: ");
			fflush(stdin);
			fgets(nomepesq,30,stdin);
			
			rewind(arq);
			apontador=0;
			while(!feof(arq) && achei ==0){
				teste=fread(&reg,sizeof(struct ferramenta), 1,arq);
				//apontador++;
				if(teste){
						
					if(strcmp(reg.prod,nomepesq)==0 && reg.bloqueio==0){
						apontador--;rewind(mem);
						reg.bloqueio=1;
							fseek(mem,apontador * sizeof(struct ferramenta), SEEK_SET);
							teste=fwrite(&reg,sizeof(struct ferramenta), 1, mem);fclose(mem);
							apontador++;
						
						gotoxy(10,13);	printf("Código..: %i", reg.cod);
						gotoxy(10,14);	printf("Nome....: %s", reg.prod);	
						achei=1;
						codant=reg.cod;
						
						
						gotoxy(40,10);	printf("Editando o registro...");
						
						gotoxy(40,13);	printf("Código: " );	scanf("%i",&cp.codc);
						gotoxy(40,14);	printf("Produto: ");		fflush(stdin);
																fgets(cp.prodc,20,stdin);
						
						

						
						gotoxy(40,20);	printf("Confirma a edição? S/N  ");
						gotoxy(63,20);  resposta=getche();
						
						
						if(resposta=='s' || resposta=='S'){
							log=fopen("log.txt", "ab");fprintf(log," T%i alterou cod %i  produto %s para cod %i produto %s \n",tr,codant, nomepesq, cp.codc, cp.prodc);fclose(log);
							apontador--;
							reg.bloqueio=0;
							fseek(arq,apontador * sizeof(struct copy), SEEK_SET);
							teste=fwrite(&cp,sizeof(struct copy), 1, arq);
							if(teste){
								gotoxy(40,20);
								printf("Registro editado com sucesso");
							}					
						}
						else{
							apontador--;
							reg.bloqueio=0;
							fseek(arq,apontador * sizeof(struct ferramenta), SEEK_SET);
							teste=fwrite(&reg,sizeof(struct ferramenta), 1, arq);
						}
						
					}			
				}
			}
			if(achei==0){
				gotoxy(10,12);	printf("Registro não encontrado.");			
			}
			gotoxy(10,22);		printf("Deseja continuar? S/N");			
			resposta=getche();
		}
		fclose(arq);
	}
	else{
		clrscr();
		gotoxy(10,8);	printf("Arquivo Vazio.");
		gotoxy(10,10);	printf("Tecle algo para voltar");
		getch();
	}
}*/


void remover(){

	char nomepesq[30], remprod[30];
	int achei, apontador, remcod=0;
	resposta='S';
	arq=fopen("copiabanco.txt","rb+");
	mem=fopen("bdproduto.txt","rb+");
if(arq)	{
	while(resposta=='S'||resposta=='s'){			
		achei=0;
		clrscr();
		gotoxy(10,3);	printf("---Exclui Produto---");
		gotoxy(10,7);
		printf("Qual o nome do produto: ");
		fflush(stdin);
		fgets(nomepesq,30,stdin);
		rewind(arq);
		apontador=0;
		while(!feof(arq)&& achei==0)
		{
			teste=fread(&reg,sizeof(struct ferramenta),1,arq);
			apontador++;
			if(teste && reg.bloqueio!=1){
				if(strcmp(reg.prod,nomepesq)==0 && reg.bloqueio==0){
						apontador--;
						reg.bloqueio=1;
							fseek(mem,apontador * sizeof(struct ferramenta), SEEK_SET);
							teste=fwrite(&reg,sizeof(struct ferramenta), 1, mem);fclose(mem);
							apontador++;
					
					gotoxy(10,8);	printf("Pesquisa realizada com sucesso");
									gotoxy(10,12);	printf("Codigo..: %i", reg.cod);
									remcod=reg.cod;
					gotoxy(10,13);	printf("Descrição....: %s", reg.prod);
					achei=1;
					
					gotoxy(10,19);	printf("Confirma a exclusão? S/N");
					gotoxy(35,19);	resposta=getche();
						if(resposta=='s' || resposta=='S'){
							apontador--;
							reg.cod=0;
							strcpy(reg.prod," ");
							reg.bloqueio=3;
							fseek(arq, apontador * sizeof(struct ferramenta), SEEK_SET);
							teste=fwrite(&reg, sizeof(struct ferramenta),1, arq );
							
							if(teste){
								gotoxy(10,19);
								printf("Registro excuido com sucesso.");
								log=fopen("log.txt", "ab");fprintf(log,"T%i removeu %i   %s \n",tr, remcod, nomepesq);fclose(log);	
							}

						}
						else{
							apontador--;
							reg.bloqueio=0;
							fseek(arq, apontador * sizeof(struct ferramenta), SEEK_SET);
							teste=fwrite(&reg, sizeof(struct ferramenta),1, arq );
						
							}


				}
				
			}
			else{
			clrscr();gotoxy(10,10);printf("BLOQUEADO PARA EXCLUSÃO");}
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
			gotoxy(10,10);	printf("Tecle algo para voltar ao menu..");
			getch();
		}
	}

void listar(){
int linha=5;
	tr--;
arq=fopen("bdproduto.txt","rb");
	clrscr();
	if(arq){
	gotoxy(19,3);printf("---BANCO DE DADOS---");
	gotoxy(10,4);	printf("Código  Produto  Bloqueio");
		while(!feof(arq))
		{
		teste=fread(&reg, sizeof(struct ferramenta), 1,arq);
		if(teste && strcmp(reg.prod, ""))
		{
		gotoxy(10,linha);	printf("%04i", reg.cod);
		gotoxy(18,linha);	puts(reg.prod);
		gotoxy(27,linha);	printf("%i", reg.bloqueio);
		gotoxy(37,linha);	printf("%i", reg.compara);
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
		fclose(arq);gotoxy(10, linha+5); printf("Tecle algo para voltar...");
	}
		else{
			gotoxy(10,19);	printf("Arquivo vazio.");
			gotoxy(10,10);	printf("Tecle algo para voltar ao menu...");
			getch();
		}
		getch();
}

void commit(){
	clrscr();
	mem=fopen("incluir.txt", "rb");
	arquivo=fopen("bdproduto.txt", "ab");
	altrem=fopen("copiabanco","rb");
	if(mem){
		while(!feof(mem)){	
		
			fread(&reg, sizeof(struct ferramenta), 1,mem);
			fseek(arquivo, sizeof(struct ferramenta),SEEK_END);	
			fwrite(&reg,sizeof(struct ferramenta), 1, arquivo);	
							
		}		

	}
	else	{		printf("Erro na copia... arquivo origem não existe...");		getche();	}
	mem=fopen("incluir.txt", "w");
	altrem=fopen("copiabanco","w");
	feof(mem);feof(arquivo);
	gotoxy(10,10);	printf("Dados commitado! Tecle algo para voltar ao menu...");
	getch();
}

void rollback(){
	clrscr();
	mem=fopen("incluir.txt", "rb");
	altrem=fopen("copiabanco","rb");
	mem=fopen("incluir.txt", "w");
	altrem=fopen("copiabanco","w");
	feof(mem);feof(arquivo);
	gotoxy(10,10);	printf("Dados não commitados! Tecle algo para voltar ao menu...");
	getch();
}

void copia(){
	clrscr();
	controle=0;
	mem=fopen("bdproduto.txt", "rb");
	arquivo=fopen("copiabanco.txt", "wb"); 
	if(mem){
		while(!feof(mem)){	
			controle++;
			fread(&reg, sizeof(struct ferramenta), 1,mem);
			fseek(arquivo, sizeof(struct ferramenta),SEEK_END);	
			fwrite(&reg,sizeof(struct ferramenta), 1, arquivo);	
							
		}		

	}
	else	{		printf("Erro na copia... arquivo origem não existe...");		getche();	}
	feof(mem);feof(arquivo);
}

