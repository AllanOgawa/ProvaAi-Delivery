#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

FILE *arq;
bool leituradaloja=false,leituradamoto=false,leituradocli=false;
int qntloja=0, qntmoto=0, qntcli=0;
int x,y;


struct structdados{
	char nome[55],telefone[15];
	char cpf[15], cep[10], cnpj[21], cnh[12];
};


struct structclientes{
	struct structdados dados;
	char estado[10], cidade[50], rua[55];
}   cliente[100];


struct structmotorista{	
	struct structdados dados;
	char placa[9], renavam[12], ano[5], veiculo[51];
} 	moto[100];


struct structloja{ 
	struct structdados dados;
	char empresa[51];
}   loja[100];


//--- MENU ------------------------------------------------------
void caixa(char* a);
void MenuPrincipal();

//--- CLIENTE ---------------------------------------------------
void leituracli();
void menucli();
void tabelacli();
void salvacli();
int cadcli();
int editcli();
int delcli();

//--- MOTORISTA -------------------------------------------------
void leituramoto();
void menumoto();
void tabelamoto();
void salvamoto();
int cadmoto();
int editmoto();
int delmoto();

//--- LOJA ------------------------------------------------------
void leituraloja();
void menuloja();
void tabelaloja();
void salvaloja();
int cadloja();
int editloja();
int delloja();

//--- CLASSIFICAÇÃO ---------------------------------------------
void troca(char* aa,char*bb);
void classificacao(int cont, int tipo);


int main(){
	leituracli();
	leituramoto();
	leituraloja();
	
	if(leituradamoto==false||leituradaloja==false||leituradocli==false){
		printf("\n ERRO NO CARREGAMENTO DA TABELA \n");
		printf("\n ARQUIVO CLIENTE  : %s\n", leituradocli ? "true" : "false");
		printf(" ARQUIVO MOTORISTA: %s\n", leituradamoto ? "true" : "false");
		printf(" ARQUIVO LOJA     : %s\n", leituradaloja ? "true" : "false");
	}
	else{
		MenuPrincipal();
		return(0);
	}
}


//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-
//---- MENU -----------------------------------------------------------------------------------------------------------------
void caixa(char* a){
	printf("    ");
	for(x=0;x<28;x++)
		printf("=");
		
	for(x=0;x<3;x++){
		if(x!=1){
			printf("\n%5c",'=');
			printf("%27c",'=');}
		else 
			printf("\n%5c%20s%7c",'=',a,'=');	
	}
	
	printf("\n    ");
	for(x=0;x<28;x++)
		printf("=");
	printf("\n");
}

void MenuPrincipal(){
	int opcao=999, saida=0;
	do{
		system("cls");
		caixa("MENU     ");
		printf("\n    1 - CLIENTE");
		printf("\n    2 - ENTREGADOR");
		printf("\n    3 - LOJA");
		printf("\n    0 - SAIR");
		printf("\n\n    DIGITE O QUE QUER FAZER: ");
		scanf("%d",&opcao);
		fflush(stdin);
		
		switch(opcao){			
			case 0:
				saida=1;
				break;
			case 1:
				menucli();
				break;
			case 2:
				menumoto();
				break;
			case 3:
				menuloja();
				break;	
		}
	}while(saida!=1);
}


//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-
//---- CLIENTE --------------------------------------------------------------------------------------------------------------
void leituracli(){
	arq=fopen("CLIENTE.txt","r");
  	if (arq==NULL)
  		leituradocli=false;
  	else{ 
  		leituradocli=true;
		while(!feof(arq)){
			fseek(arq,0,SEEK_CUR);
			fgets(cliente[qntcli].dados.cpf, 15, arq); 
			cliente[qntcli].dados.cpf[strlen(cliente[qntcli].dados.cpf)]='\0';
			
			fseek(arq,2,SEEK_CUR);
			fgets(cliente[qntcli].dados.telefone, 15, arq); 
			cliente[qntcli].dados.telefone[strlen(cliente[qntcli].dados.telefone)]='\0';

			fseek(arq,2,SEEK_CUR);
			fgets(cliente[qntcli].dados.nome, 51, arq);
			while(cliente[qntcli].dados.nome[strlen(cliente[qntcli].dados.nome)-1]=='.')
				cliente[qntcli].dados.nome[strlen(cliente[qntcli].dados.nome)-1]='\0';
			cliente[qntcli].dados.nome[strlen(cliente[qntcli].dados.nome)-1]='\0';
			
			fseek(arq,2,SEEK_CUR);
			fgets(cliente[qntcli].dados.cep, 10, arq); 
			cliente[qntcli].dados.cep[strlen(cliente[qntcli].dados.cep)]='\0';
			
			fseek(arq,1,SEEK_CUR);
			fgets(cliente[qntcli].estado, 3, arq); 
			cliente[qntcli].estado[strlen(cliente[qntcli].estado)]='\0';
			
			fseek(arq,1,SEEK_CUR);
			fgets(cliente[qntcli].cidade, 31, arq); 
			while(cliente[qntcli].cidade[strlen(cliente[qntcli].cidade)-1]=='.')
				cliente[qntcli].cidade[strlen(cliente[qntcli].cidade)-1]='\0';
			cliente[qntcli].cidade[strlen(cliente[qntcli].cidade)-1]='\0';
			
			fseek(arq,1,SEEK_CUR);
			fgets(cliente[qntcli].rua, 53, arq); 
			while(cliente[qntcli].rua[strlen(cliente[qntcli].rua)-2]=='.')
				cliente[qntcli].rua[strlen(cliente[qntcli].rua)-1]='\0';
			cliente[qntcli].rua[strlen(cliente[qntcli].rua)-2]='\0';
			qntcli++;
		}
		qntcli--;
		fclose(arq);	
	}
}

void menucli(){
	int opcao=999, saida=0;
	do{
		system("cls");
		caixa("CLIENTE    ");
		printf("\n    1 - Cadastrar Cliente");
		printf("\n    2 - Editar Cliente");
		printf("\n    3 - Excluir Cliente");
		printf("\n    4 - Consultar lista de Clientes");
		printf("\n    0 - VOLTAR");
		printf("\n\n    DIGITE O QUE QUER FAZER: ");
		scanf("%d",&opcao);
		fflush(stdin);
		switch(opcao){			
			case 0:
				saida=1;
				break;
			case 1:
				cadcli();
				break;
			case 2:
				editcli();
				break;
			case 3:
				delcli();
				break;
			case 4:
				system("cls");
				tabelacli();
				system("pause");
				break;
		}
	}
	while(saida!=1);
}

int cadcli(){
	char nnome[100], ncpf[50], ntelefone[50], nrua[100], nestado[10], ncidade[50], ncep[50];
	int retorno;
	system("cls");
	caixa("NOVO CLIENTE  ");
	printf("    Insira 0 no Nome caso deseje retornar ao menu\n");
	printf("\n    Nome: ");
	gets(nnome);
	nnome[strlen(nnome)]='\0';
	retorno=strcmp(nnome,"0");
	if(retorno==0)
		return 0;
	nnome[0]=toupper(nnome[0]);
	
	printf("    CPF(XXX.XXX.XXX-XX): ");
	gets(ncpf);
	ncpf[strlen(ncpf)]='\0';
	
	printf("    TELEFONE( (XX)XXXXX-XXXX ): ");
	gets(ntelefone);
	ntelefone[strlen(ntelefone)]='\0';
	
	printf("    CEP(XXXXX-XXX): ");
	gets(ncep);
	ncep[strlen(ncep)]='\0';
	
	printf("    ESTADO(ex:PR): ");
	gets(nestado);
	nestado[strlen(nestado)]='\0';
	
	printf("    CIDADE: ");
	gets(ncidade);
	ncidade[strlen(ncidade)]='\0';
	
	printf("    ENDERECO: ");
	gets(nrua);
	nrua[strlen(nrua)]='\0';
	
	printf("\n    CADASTRADO COM SUCESSO, ");
	strcpy(cliente[qntcli].dados.nome,nnome);
	strcpy(cliente[qntcli].dados.cpf,ncpf);
	strcpy(cliente[qntcli].dados.telefone,ntelefone);
	strcpy(cliente[qntcli].dados.cep,ncep);
	strcpy(cliente[qntcli].cidade,ncidade);
	strcpy(cliente[qntcli].estado,nestado);
	strcpy(cliente[qntcli].rua,nrua);
	qntcli++;
	salvacli();
	system("pause");
	return 0;
}

int editcli(){
	int indice,opcao,retorno;
	char cpfi[100],novo[200];
	system("cls");
	caixa("EDITAR CLIENTE");
	printf("    Insira 0 caso deseje retornar ao menu\n\n");
	printf("    Informe o CPF(XXX.XXX.XXX-XX): ");
	gets(cpfi);
	retorno=strcmp(cpfi,"0");
	if(retorno==0)
		return 0;
	cpfi[strlen(cpfi)]='\0';
	for(x=0;x<qntcli;x++){
		retorno=strcmp(cpfi,cliente[x].dados.cpf);
		if(retorno==0){
			indice=x;
			break;
		}
	}
	
	system("cls");
	caixa("EDITAR CLIENTE");
	printf("    Insira 0 caso deseje retornar ao menu\n\n");
	printf("    1 - Nome:     %s",cliente[indice].dados.nome);
	printf("\n    2 - Telefone: %s",cliente[indice].dados.telefone);
	printf("\n    3 - Endereco: %s  %s - %s",cliente[indice].dados.cep,cliente[indice].estado,cliente[indice].cidade);
	printf("\n                  %s",cliente[indice].rua);
	printf("\n\n    QUAL OPCAO DESEJA EDITAR: ");
	scanf("%d",&opcao);
	fflush(stdin);
	if(opcao==0)
		return 0;
		
	system("cls");
	caixa("EDITAR CLIENTE");
	if(opcao==1){
		printf("\n    Nome: %s",cliente[indice].dados.nome);
		printf("\n    Novo NOME: ");
		gets(novo);
		novo[strlen(novo)]='\0';
		novo[0]=toupper(novo[0]);
		strcpy(cliente[indice].dados.nome,novo);
	}
	
	if(opcao==2){
		printf("\n    Telefone: %s",cliente[indice].dados.telefone);
		printf("\n    Novo TELEFONE( (XX)XXXXX-XXXX ): ");
		gets(novo);
		novo[strlen(novo)]='\0';
		strcpy(cliente[indice].dados.telefone,novo);
	}
	
	if(opcao==3){
		printf("\n    Endereco: %s  %s - %s",cliente[indice].dados.cep,cliente[indice].estado,cliente[indice].cidade);
		printf("\n              %s",cliente[indice].rua);
		
		printf("\n    Novo CEP(XXXXX-XXX): ");
		gets(novo);
		novo[strlen(novo)]='\0';
		
		strcpy(cliente[indice].dados.cep,novo);
		printf("    Novo ESTADO(ex. PR): ");
		gets(novo);
		novo[strlen(novo)]='\0';
		
		strcpy(cliente[indice].estado,novo);
		printf("    Nova CIDADE: ");
		gets(novo);
		novo[strlen(novo)]='\0';
		
		strcpy(cliente[indice].cidade,novo);
		printf("    Nova RUA: ");
		gets(novo);
		novo[strlen(novo)]='\0';
		strcpy(cliente[indice].rua,novo);
	}
	
	salvacli();
	printf("\n\n    EDITADO COM SUCESSO,");
	system("pause");
	return 0;	
}

int delcli(){
	int indice,opcao,retorno;
	char cpfi[100];
	system("cls");
	caixa("EXCLUIR CLIENTE");
	printf("    Insira 0 caso deseje retornar ao menu\n\n");
	printf("    Informe o CPF(XXX.XXX.XXX-XX): ");
	gets(cpfi);
	retorno=strcmp(cpfi,"0");
	if(retorno==0)
		return 0;
	cpfi[strlen(cpfi)]='\0';
	for(x=0;x<qntcli;x++){
		retorno=strcmp(cpfi,cliente[x].dados.cpf);
		if(retorno==0){
			indice=x;
			break;
		}
	}
	
	system("cls");
	caixa("EXCLUIR CLIENTE");
	printf("    Insira 0 caso deseje retornar ao menu\n\n");
	printf("    CPF:      %s",cliente[indice].dados.cpf);
	printf("\n    Nome:     %s",cliente[indice].dados.nome);
	printf("\n    Telefone: %s",cliente[indice].dados.telefone);
	printf("\n    Endereco: %s  %s - %s",cliente[indice].dados.cep,cliente[indice].estado,cliente[indice].cidade);
	printf("\n              %s",cliente[indice].rua);
	printf("\n\n    DESEJA MESMO EXCLUIR CLIENTE(1=SIM / 0=NAO): ");
	scanf("%d",&opcao);
	fflush(stdin);
	if(opcao==0)
		return 0;
		
	else if(opcao==1){
		qntcli--;
		strcpy(cliente[indice].dados.nome,cliente[qntcli].dados.nome);
		strcpy(cliente[indice].dados.telefone,cliente[qntcli].dados.telefone);
		strcpy(cliente[indice].dados.cep,cliente[qntcli].dados.cep);
		strcpy(cliente[indice].dados.cpf,cliente[qntcli].dados.cpf);
		strcpy(cliente[indice].cidade,cliente[qntcli].cidade);
		strcpy(cliente[indice].estado,cliente[qntcli].estado);
		strcpy(cliente[indice].rua,cliente[qntcli].rua);
		salvacli();
		printf("\n    ITEM DELETADO, ");
		system("pause");
		return 0;
	}
}

void tabelacli(){
	for(x=0;x<qntcli;x++){
		printf("%3d %-50s CPF:%-20s TELEFONE:%s\n",x+1,cliente[x].dados.nome,cliente[x].dados.cpf,cliente[x].dados.telefone);
		printf("    ENDERECO:%-41s CEP:%-20s CIDADE:%s-%s \n",cliente[x].rua,cliente[x].dados.cep,cliente[x].cidade,cliente[x].estado);
		for(y=0;y<110;y++)
			printf("_");
		printf("\n");
	}
}

void salvacli(){
	char tmprua[100];
	char tmpnome[100];
	char tmpcid[100];
	classificacao(qntcli,1);
	arq=fopen("CLIENTE.txt","w");
	for(x=0;x<qntcli;x++){
		
		for(y=0;y<100;y++){
			tmprua[y]='\0';
			tmpnome[y]='\0';
			tmpcid[y]='\0';
		}
		
		strcpy(tmprua,cliente[x].rua);
		strcpy(tmpnome,cliente[x].dados.nome);
		strcpy(tmpcid,cliente[x].cidade);
		
		tmprua[strlen(tmprua)]=' ';
		tmpnome[strlen(tmpnome)]=' ';
		tmpcid[strlen(tmpcid)]=' ';
		
		for(y=0;y<55;y++){
			tmprua[strlen(tmprua)]='.';
			tmpnome[strlen(tmpnome)]='.';
			tmpcid[strlen(tmpcid)]='.';
		}
		
		tmprua[50]='\0';
		tmpnome[50]='\0';
		tmpcid[30]='\0';
		
		fprintf(arq,"%s  %s  %s  %s %s %s %s\n",cliente[x].dados.cpf,cliente[x].dados.telefone,tmpnome,cliente[x].dados.cep,cliente[x].estado,tmpcid,tmprua);
	}
	fclose(arq);	
}


//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-
//---- MOTORISTA ------------------------------------------------------------------------------------------------------------
void leituramoto(){
	arq=fopen("MOTORISTA.txt","r");
  	if (arq==NULL)
  		leituradamoto=false;
  	else{ 
  		leituradamoto=true;
		while(!feof(arq)){
			fseek(arq,0,SEEK_CUR);
			fgets(moto[qntmoto].dados.cpf, 15, arq); 
			moto[qntmoto].dados.cpf[strlen(moto[qntmoto].dados.cpf)]='\0';
			
			fseek(arq,2,SEEK_CUR);
			fgets(moto[qntmoto].dados.telefone, 15, arq); 
			moto[qntmoto].dados.telefone[strlen(moto[qntmoto].dados.telefone)]='\0';
			
			fseek(arq,2,SEEK_CUR);
			fgets(moto[qntmoto].dados.cnh, 12, arq); 
			moto[qntmoto].dados.cnh[strlen(moto[qntmoto].dados.cnh)]='\0';
			
			fseek(arq,2,SEEK_CUR);
			fgets(moto[qntmoto].placa, 9, arq); 
			moto[qntmoto].placa[strlen(moto[qntmoto].placa)]='\0';
			
			fseek(arq,2,SEEK_CUR);
			fgets(moto[qntmoto].renavam, 12, arq); 
			moto[qntmoto].renavam[strlen(moto[qntmoto].renavam)]='\0';
			
			fseek(arq,2,SEEK_CUR);
			fgets(moto[qntmoto].ano, 5, arq); 
			moto[qntmoto].ano[strlen(moto[qntmoto].ano)]='\0';
			
			fseek(arq,2,SEEK_CUR);
			fgets(moto[qntmoto].veiculo, 51, arq); 
			while(moto[qntmoto].veiculo[strlen(moto[qntmoto].veiculo)-1]=='.')
				moto[qntmoto].veiculo[strlen(moto[qntmoto].veiculo)-1]='\0';
			moto[qntmoto].veiculo[strlen(moto[qntmoto].veiculo)-1]='\0';
			
			fseek(arq,2,SEEK_CUR);
			fgets(moto[qntmoto].dados.nome, 53, arq);
			while(moto[qntmoto].dados.nome[strlen(moto[qntmoto].dados.nome)-2]=='.')
				moto[qntmoto].dados.nome[strlen(moto[qntmoto].dados.nome)-1]='\0';
			moto[qntmoto].dados.nome[strlen(moto[qntmoto].dados.nome)-2]='\0';
		
			qntmoto++;
		}
		qntmoto--;
		fclose(arq);
	}
}

void menumoto(){
	int opcao=999, saida=0;
	do{
		system("cls");
		caixa("ENTREGADOR  ");
		printf("\n    1 - Cadastrar Entregador");
		printf("\n    2 - Editar Entregador");
		printf("\n    3 - Excluir Entregador");
		printf("\n    4 - Consultar lista de Entregadores");
		printf("\n    0 - VOLTAR");
		printf("\n\n    DIGITE O QUE QUER FAZER: ");
		scanf("%d",&opcao);
		fflush(stdin);
		switch(opcao){			
			case 0:
				saida=1;
				break;
			case 1:
				cadmoto();
				break;
			case 2:
				editmoto();
				break;
			case 3:
				delmoto();
				break;	
			case 4:
				system("cls");
				tabelamoto();
				system("pause");
				break;
		}
	}
	while(saida!=1);
}

int cadmoto(){
	char nnome[100], ncpf[50], ntelefone[50], nveiculo[100], nano[10], nplaca[50], ncnh[50], nrenavam[50];
	int retorno;
	system("cls");
	caixa("NOVO ENTREGADOR");
	printf("    Insira 0 no Nome caso deseje retornar ao menu\n");
	printf("\n    Nome: ");
	gets(nnome);
	nnome[strlen(nnome)]='\0';
	retorno=strcmp(nnome,"0");
	if(retorno==0)
		return 0;
	nnome[0]=toupper(nnome[0]);
	
	printf("    CPF(XXX.XXX.XXX-XX): ");
	gets(ncpf);
	ncpf[strlen(ncpf)]='\0';
	
	printf("    TELEFONE( (XX)XXXXX-XXXX ): ");
	gets(ntelefone);
	ntelefone[strlen(ntelefone)]='\0';
	
	printf("    CNH: ");
	gets(ncnh);
	ncnh[strlen(ncnh)]='\0';
	
	printf("    VEICULO: ");
	gets(nveiculo);
	nveiculo[strlen(nveiculo)]='\0';
	
	printf("    ANO: ");
	gets(nano);
	nano[strlen(nano)]='\0';
	
	printf("    PLACA: ");
	gets(nplaca);
	nplaca[strlen(nplaca)]='\0';
	
	printf("    RENAVAM: ");
	gets(nrenavam);
	nrenavam[strlen(nrenavam)]='\0';
	
	printf("\n    CADASTRADO COM SUCESSO, ");
	strcpy(moto[qntmoto].dados.nome,nnome);
	strcpy(moto[qntmoto].dados.cpf,ncpf);
	strcpy(moto[qntmoto].dados.telefone,ntelefone);
	strcpy(moto[qntmoto].dados.cnh,ncnh);
	strcpy(moto[qntmoto].ano,nano);
	strcpy(moto[qntmoto].placa,nplaca);
	strcpy(moto[qntmoto].renavam,nrenavam);
	strcpy(moto[qntmoto].veiculo,nveiculo);
	
	qntmoto++;
	salvamoto();
	system("pause");
	return 0;
}

int editmoto(){
	int indice,opcao,retorno;
	char cpfi[100],novo[200];
	system("cls");
	caixa("EDITAR ENTREGADOR");
	printf("    Insira 0 caso deseje retornar ao menu\n\n");
	printf("    Informe o CPF(XXX.XXX.XXX-XX): ");
	gets(cpfi);
	retorno=strcmp(cpfi,"0");
	if(retorno==0)
		return 0;
		
	cpfi[strlen(cpfi)]='\0';
	for(x=0;x<qntmoto;x++){
		retorno=strcmp(cpfi,moto[x].dados.cpf);
		if(retorno==0){
			indice=x;
			break;
		}
	}
	
	system("cls");
	caixa("EDITAR ENTREGADOR");
	printf("    Insira 0 caso deseje retornar ao menu\n\n");
	printf("    1 - Nome:     %s",moto[indice].dados.nome);
	printf("\n    2 - Telefone: %s",moto[indice].dados.telefone);
	printf("\n    3 - Veiculo:  %s  %s",moto[indice].ano,moto[indice].placa);
	printf("\n                  %s",moto[indice].veiculo);
	printf("\n         RENAVAM: %s",moto[indice].renavam);
	printf("\n\n    QUAL OPCAO DESEJA EDITAR: ");
	scanf("%d",&opcao);
	fflush(stdin);
	if(opcao==0)
		return 0;
		
	system("cls");
	caixa("EDITAR ENTREGADOR");
	
	if(opcao==1){
		printf("\n    Nome: %s",moto[indice].dados.nome);
		printf("\n    Novo NOME: ");
		gets(novo);
		novo[strlen(novo)]='\0';
		novo[0]=toupper(novo[0]);
		strcpy(moto[indice].dados.nome,novo);
	}
	
	if(opcao==2){
		printf("\n    Telefone: %s",moto[indice].dados.telefone);
		printf("\n    Novo TELEFONE( (XX)XXXXX-XXXX ): ");
		gets(novo);
		novo[strlen(novo)]='\0';
		strcpy(moto[indice].dados.telefone,novo);
	}
	
	if(opcao==3){
		printf("\n    Veiculo: %s  %s",moto[indice].ano,moto[indice].placa);
		printf("\n             %s",moto[indice].veiculo);
		printf("\n    RENAVAM: %s",moto[indice].renavam);
		
		printf("\n    Novo Veiculo: ");
		gets(novo);
		novo[strlen(novo)]='\0';
		strcpy(moto[indice].veiculo,novo);
		
		printf("    ANO: ");
		gets(novo);
		novo[strlen(novo)]='\0';
		strcpy(moto[indice].ano,novo);
		
		printf("    PLACA: ");
		gets(novo);
		novo[strlen(novo)]='\0';
		strcpy(moto[indice].placa,novo);
		
		printf("    RENAVAM: ");
		gets(novo);
		novo[strlen(novo)]='\0';
		strcpy(moto[indice].renavam,novo);
	}
	
	salvamoto();
	printf("\n    EDITADO COM SUCESSO,");
	system("pause");
	return 0;	
}

int delmoto(){
	int indice,opcao,retorno;
	char cpfi[100],novo[200];
	system("cls");
	caixa("EXCLUIR ENTREGADOR");
	printf("    Insira 0 caso deseje retornar ao menu\n\n");
	printf("    Informe o CPF(XXX.XXX.XXX-XX): ");
	gets(cpfi);
	retorno=strcmp(cpfi,"0");
	if(retorno==0)
		return 0;
		
	cpfi[strlen(cpfi)]='\0';
	for(x=0;x<qntmoto;x++){
		retorno=strcmp(cpfi,moto[x].dados.cpf);
		if(retorno==0){
			indice=x;
			break;
		}
	}
	
	system("cls");
	caixa("EXCLUIR ENTREGADOR");
	printf("    Insira 0 caso deseje retornar ao menu\n\n");
	printf("    Nome:     %s",moto[indice].dados.nome);
	printf("\n    Telefone: %s",moto[indice].dados.telefone);
	printf("\n    Veiculo:  %s  %s",moto[indice].ano,moto[indice].placa);
	printf("\n              %s",moto[indice].veiculo);
	printf("\n     RENAVAM: %s",moto[indice].renavam);
	printf("\n\n    DESEJA MESMO EXCLUIR ENTREGADOR(1=SIM / 0=NAO): ");
	scanf("%d",&opcao);
	fflush(stdin);
	if(opcao==0)
		return 0;
		
	else if(opcao==1){
		qntmoto--;
		strcpy(moto[indice].dados.nome,moto[qntmoto].dados.nome);
		strcpy(moto[indice].dados.telefone,moto[qntmoto].dados.telefone);
		strcpy(moto[indice].dados.cpf,moto[qntmoto].dados.cpf);
		strcpy(moto[indice].dados.cnh,moto[qntmoto].dados.cnh);
		strcpy(moto[indice].ano,moto[qntmoto].ano);
		strcpy(moto[indice].veiculo,moto[qntmoto].veiculo);
		strcpy(moto[indice].placa,moto[qntmoto].placa);
		strcpy(moto[indice].renavam,moto[qntmoto].renavam);
		
		salvamoto();
		printf("\n    ITEM DELETADO, ");
		system("pause");
		return 0;
	}
}

void tabelamoto(){
	for(int x=0;x<qntmoto;x++){
		printf("%3d %-50s CPF:%-20s TELEFONE:%s\n",x+1,moto[x].dados.nome,moto[x].dados.cpf,moto[x].dados.telefone);
		printf("    VEICULO:%-42s ANO:%-20s PLACA:%s\n",moto[x].veiculo,moto[x].ano,moto[x].placa);
		printf("    CNH:%-46s RENAVAM:%s\n",moto[x].dados.cnh,moto[x].renavam);
		for(y=0;y<110;y++)
			printf("_");
		printf("\n");
	}
}

void salvamoto(){
	char tmpveiculo[100];
	char tmpnome[100];
	classificacao(qntmoto,2);
	arq=fopen("MOTORISTA.txt","w");
	for(x=0;x<qntmoto;x++){
		
		for(y=0;y<100;y++){
			tmpveiculo[y]='\0';
			tmpnome[y]='\0';
		}
		
		strcpy(tmpveiculo,moto[x].veiculo);
		strcpy(tmpnome,moto[x].dados.nome);
		tmpveiculo[strlen(tmpveiculo)]=' ';
		tmpnome[strlen(tmpnome)]=' ';
		
		for(y=0;y<55;y++){
			tmpveiculo[strlen(tmpveiculo)]='.';
			tmpnome[strlen(tmpnome)]='.';
		}
		
		tmpveiculo[50]='\0';
		tmpnome[50]='\0';
		
		fprintf(arq,"%s  %s  %s  %s  %s  %s  %s  %s\n",moto[x].dados.cpf,moto[x].dados.telefone,moto[x].dados.cnh,moto[x].placa,moto[x].renavam,moto[x].ano,tmpveiculo,tmpnome);
	}
	fclose(arq);
}


//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-
//---- LOJA -----------------------------------------------------------------------------------------------------------------
void leituraloja(){
	arq=fopen("LOJA.txt","r");
  	if (arq==NULL)
  		leituradaloja=false;
  	else{ 
  		leituradaloja=true;
		while(!feof(arq)){
			fseek(arq,0,SEEK_CUR);
			fgets(loja[qntloja].dados.cnpj, 19, arq); 
			loja[qntloja].dados.cnpj[strlen(loja[qntloja].dados.cnpj)]='\0';
			
			fseek(arq,2,SEEK_CUR);
			fgets(loja[qntloja].empresa,51, arq);
			while(loja[qntloja].empresa[strlen(loja[qntloja].empresa)-1]=='.')
				loja[qntloja].empresa[strlen(loja[qntloja].empresa)-1]='\0';
			loja[qntloja].empresa[strlen(loja[qntloja].empresa)-1]='\0';
			
			fseek(arq,2,SEEK_CUR);
			fgets(loja[qntloja].dados.nome, 52, arq);
			while(loja[qntloja].dados.nome[strlen(loja[qntloja].dados.nome)-2]=='.')
				loja[qntloja].dados.nome[strlen(loja[qntloja].dados.nome)-1]='\0';
			loja[qntloja].dados.nome[strlen(loja[qntloja].dados.nome)-2]='\0';
			
			qntloja++;
		}
		qntloja--;
		fclose(arq);
	}
}

void menuloja(){
	int opcao=999, saida=0;
	do{
		system("cls");
		caixa("LOJA     ");
		printf("\n    1 - Cadastrar Loja");
		printf("\n    2 - Editar Loja");
		printf("\n    3 - Excluir Loja");
		printf("\n    4 - Consultar lista de Lojas");
		printf("\n    0 - VOLTAR");
		printf("\n\n    DIGITE O QUE QUER FAZER: ");
		scanf("%d",&opcao);
		fflush(stdin);
		switch(opcao){			
			case 0:
				saida=1;
				break;
			case 1:
				cadloja();
				break;
			case 2:
				editloja();
				break;
			case 3:
				delloja();
				break;	
			case 4:
				system("cls");
				tabelaloja();
				system("pause");
				break;
		}
	}
	while(saida!=1);
}

int cadloja(){
	char nloja[51], ncnpj[21], ntitular[55];
	int retorno;
	system("cls");
	caixa("NOVA LOJA   ");
	printf("    Insira 0 no nome da loja caso deseje retornar ao menu\n");
	printf("\n    Nome da Loja: ");
	gets(nloja);
	retorno=strcmp(nloja,"0");
	if(retorno==0)
		return 0;
		
	nloja[strlen(nloja)]='\0';
	nloja[0]=toupper(nloja[0]);
	
	printf("    Nome do Titular da Empresa: ");
	gets(ntitular);
	ntitular[strlen(ntitular)]='\0';
	ntitular[0]=toupper(ntitular[0]);
	
	printf("    CNPJ(XX.XXX.XXX/XXXX-XX): ");
	gets(ncnpj);
	ncnpj[strlen(ncnpj)]='\0';
	
	printf("\n    CADASTRADO COM SUCESSO, ");
	strcpy(loja[qntloja].empresa,nloja);
	strcpy(loja[qntloja].dados.nome,ntitular);
	strcpy(loja[qntloja].dados.cnpj,ncnpj);
	qntloja++;
	salvaloja();
	
	system("pause");
	return 0;
}

int editloja(){
	int indice,opcao;
	char novo[100];
	system("cls");
	caixa("EDITAR LOJA  ");
	printf("    Insira 0 caso deseje retornar ao menu\n\n");
	tabelaloja();
	printf("\nESCOLHA O NUMERO DA LOJA (1 a %d): ",qntloja);
	scanf("%d",&indice);
	fflush(stdin);
	if(indice==0)
		return 0;
	indice--;
	
	system("cls");
	caixa("EDITAR LOJA  ");
	printf("    Insira 0 no nome da loja caso deseje retornar ao menu\n");
	printf("\n    1- TITULAR: %s",loja[indice].dados.nome);
	printf("\n    2- LOJA:    %s",loja[indice].empresa);
	printf("\n    3- CNPJ:    %s",loja[indice].dados.cnpj);
	printf("\n\n    ESCOLHA A OPCAO: ");
	scanf("%d",&opcao);
	fflush(stdin);
	if(opcao==0)
		return 0;
		
	system("cls");
	caixa("EDITAR LOJA");
	if(opcao==1){
		printf("\n    TITULAR: %s",loja[indice].dados.nome);
		printf("\n    NOVO TITULAR: ");
		gets(novo);
		novo[0]=toupper(novo[0]);
		strcpy(loja[indice].dados.nome,novo);
	}
	
	else if(opcao==2){
		printf("\n    LOJA: %s",loja[indice].empresa);
		printf("\n    NOVO NOME DE LOJA: ");
		gets(novo);
		novo[0]=toupper(novo[0]);
		strcpy(loja[indice].empresa,novo);
	}
	
	else if(opcao==3){
		printf("\n    CNPJ: %s",loja[indice].dados.cnpj);
		printf("\n    NOVO CNPJ (XX.XXX.XXX/XXXX-XX): ");
		gets(novo);
		strcpy(loja[indice].dados.cnpj,novo);
	}
	
	salvaloja();
	printf("\n\n    EDITADO COM SUCESSO,");
	system("pause");
	return 0;
}

int delloja(){
	int indice,opcao;
	system("cls");
	caixa("EXCLUIR LOJA ");
	printf("    Insira 0 caso deseje retornar ao menu\n\n");
	tabelaloja();
	printf("\nESCOLHA O NUMERO DA LOJA (1 a %d): ",qntloja);
	scanf("%d",&indice);
	fflush(stdin);
	if(indice==0)
		return 0;
	indice--;
	
	system("cls");
	caixa("EXCLUIR LOJA ");
	printf("\n");
	printf("\n    TITULAR: %s",loja[indice].dados.nome);
	printf("\n    LOJA:    %s",loja[indice].empresa);
	printf("\n    CNPJ:    %s",loja[indice].dados.cnpj);
	printf("\n\n    TEM CERTEZA QUE DESEJA REMOVER (1=SIM / 0=NAO): ");
	scanf("%d",&opcao);
	fflush(stdin);
	if(opcao==0)
		return 0;
		
	else{
		qntloja--;
		strcpy(loja[indice].dados.nome,loja[qntloja].dados.nome);
		strcpy(loja[indice].empresa,loja[qntloja].empresa);
		strcpy(loja[indice].dados.cnpj,loja[qntloja].dados.cnpj);
		salvaloja();
		
		printf("\n    ITEM DELETADO, ");
		system("pause");
		return 0;
	}
}

void tabelaloja(){
	printf("%3s %-50s %-40s %s\n"," ","TITULAR","EMPRESA","CNPJ");
	for(x=0;x<120;x++)
		printf("_");
	printf("\n");
	for(x=0;x<qntloja;x++)
		printf("%3d %-50s %-40s %s\n",x+1,loja[x].dados.nome,loja[x].empresa,loja[x].dados.cnpj);
}

void salvaloja(){
	char tmpempresa[100];
	char tmpnome[100];
	classificacao(qntloja,3);
	arq=fopen("LOJA.txt","w");
	for(x=0;x<qntloja;x++){
		
		for(y=0;y<100;y++){
			tmpempresa[y]='\0';
			tmpnome[y]='\0';
		}
		
		strcpy(tmpempresa,loja[x].empresa);
		strcpy(tmpnome,loja[x].dados.nome);
		tmpempresa[strlen(tmpempresa)]=' ';
		tmpnome[strlen(tmpnome)]=' ';
		
		for(y=0;y<55;y++){
			tmpempresa[strlen(tmpempresa)]='.';
			tmpnome[strlen(tmpnome)]='.';
		}
		
		tmpempresa[50]='\0';
		tmpnome[50]='\0';
		
		fprintf(arq,"%s  %s  %s\n",loja[x].dados.cnpj,tmpempresa,tmpnome);
	}		
	fclose(arq);
}


//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-
//---- CLASSIFICAÇÃO --------------------------------------------------------------------------------------------------------
void troca(char* aa,char*bb){
	char tmpc[200];
	strcpy(tmpc,aa);
	strcpy(aa,bb);
	strcpy(bb,tmpc);
}

void classificacao(int cont, int tipo){
	int tmp;
	for(x=0;x<cont-1;x++)
		for(y=x+1;y<cont;y++){
			if(tipo==1){
				tmp=strcmp(cliente[x].dados.nome,cliente[y].dados.nome);
				if(tmp==1){
					troca(cliente[x].dados.nome,    cliente[y].dados.nome);
					troca(cliente[x].dados.cpf,     cliente[y].dados.cpf);
					troca(cliente[x].dados.telefone,cliente[y].dados.telefone);
					troca(cliente[x].dados.cep,     cliente[y].dados.cep);
					troca(cliente[x].estado,        cliente[y].estado);
					troca(cliente[x].cidade,        cliente[y].cidade);
					troca(cliente[x].rua,           cliente[y].rua);
				}
			}
			
			if(tipo==2){
				tmp=strcmp(moto[x].dados.nome,moto[y].dados.nome);
				if(tmp==1){
					troca(moto[x].dados.nome,    moto[y].dados.nome);
					troca(moto[x].dados.cpf,     moto[y].dados.cpf);
					troca(moto[x].dados.telefone,moto[y].dados.telefone);
					troca(moto[x].dados.cnh,     moto[y].dados.cnh);
					troca(moto[x].ano,           moto[y].ano);
					troca(moto[x].renavam,       moto[y].renavam);
					troca(moto[x].placa,         moto[y].placa);
					troca(moto[x].veiculo,       moto[y].veiculo);
				}
			}
			
			if(tipo==3){
				tmp=strcmp(loja[x].dados.nome,loja[y].dados.nome);
				if(tmp==1){
					troca(loja[x].dados.nome, loja[y].dados.nome);
					troca(loja[x].dados.cnpj, loja[y].dados.cnpj);
					troca(loja[x].empresa,    loja[y].empresa);
				}
			}
		}
}