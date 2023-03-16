#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ll.h"
#include <locale.h>
#pragma region "Variaveis"
ListElem ClientList = NULL;
ListElem GestorList = NULL;
ListElem MeiosList = NULL;
ListElem HistOpera = NULL;
ListElem HistAlug = NULL;

char UserFile[] = "C:/Users/EduardoSousaCosta/Desktop/Fase1/UsersFile.txt";
char FileMeios[] = "C:/Users/EduardoSousaCosta/Desktop/Fase1/MeiosFile.txt";
char HistOper[] = "C:/Users/EduardoSousaCosta/Desktop/Fase1/HistOpera.txt";
char HistAluger[] = "C:/Users/EduardoSousaCosta/Desktop/Fase1/HistAluger.txt";

//Registar utlizador que fez loggin
char utilizador[50] = "";
char email_utilizador[100] = "";
char NIF_utilizador[10] = "";
char morada_utilizador[100] = "";
float saldo_utilizador = 0.00;
char password_utilizador[100] = "";
int permissões_utilizador = 0;

#pragma endregion
#pragma region "Estruturas"

typedef struct HistAluger
{
	char utilizador[50];
	char NIF[10];
	int identificador;
	char tipo[50];
	char localizacao[100];
	float custo;
	
}*Historicoaluger;

typedef struct HistOp
{
	char utilizador[50];
	char NIF[10];
	char Operacao[150];
	float Quantia;
}*Historicoopera;
typedef struct veiculos
{
	char tipo_de_veiculo[50];          //Tipo de Veículo
	int identificador;                //Identificador do Veículo
	int capacidade_bateria;          //Percentagem de Bateria 
	int autonomia;                  //Autonomia do Veículo 
	float custo_aluger;            //Custo de Aluger
	char localizacao[100];        //Geolocalização 3 palavras separadas por pontos		
}*mobilidade;

typedef struct utilizadores
{
	char nome_cliente[50];          // Nome do Cliente
	char email_cliente[50];        // Email do Cliente
	char NIF[10];				  // NIF DO Cliente
	char morada[150];            // Morada 
	float saldo;						//  saldo
	char password[100];				  // Palavra-chave
	int permissoes;					 // Tipo de permissoes
}*Clientes;

typedef struct gestores
{
	char nome_gestor[50];         // Nome do Cliente
	char email_gestor[50];
	char NIF[10];					  // NIF DO Cliente
	char morada[150];            // Morada 
	float saldo;                //  saldo
	char password[100];        // Palavra-chave
	int permissoes;			  // Tipo de permissoes
}*Gestores;

#pragma endregion
#pragma region "Clientes"

void Show(void* data, int op)
{
	switch (op) {
	case 1:
	{
		Clientes j = (Clientes)data;
		if (j != NULL)
		{
			printf("Nome do Cliente: %s \n", j->nome_cliente);
			printf("Numero de Identificação Fiscal: %s \n", j->NIF);
			printf("Email: %s \n", j->email_cliente);
			printf("Saldo: %f \n", j->saldo);
			printf("Morada: %s \n", j->morada);
			printf("Password: %s \n", j->password);
			printf("Nivel de Permissoes: %d \n", j->permissoes);
			printf("\n");
		}
		break;
	}
	case 2:
	{
		Gestores j = (Gestores)data;
		if (j != NULL)
		{
			printf("Nome do Gestor: %s \n", j->nome_gestor);
			printf("Numero de Identificação Fiscal: %s \n", j->NIF);
			printf("Email: %s \n", j->email_gestor);
			printf("Saldo: %f \n", j->saldo);
			printf("Morada: %s \n", j->morada);
			printf("Password: %s \n", j->password);
			printf("Nivel de Permissoes: %d \n", j->permissoes);
			printf("\n");
		}
		break;
	}
	case 3:
	{
		mobilidade v = (mobilidade)data;
		if (v != NULL)
		{
			printf("Tipo de Veiculo: %s \n", v->tipo_de_veiculo);
			printf("Identificador: %d \n", v->identificador);
			printf("Capacidade Bateria: %d \n", v->capacidade_bateria);
			printf("Autonomia: %d \n", v->autonomia);
			printf("Custo de Aluger: %f \n", v->custo_aluger);
			printf("Localização: %s\n", v->localizacao);
			printf("\n");
		}
		break;
	}
	case 4:
	{
		Historicoaluger h = (Historicoaluger)data;
		if (h != NULL)
		{
			if (strcmp(h->NIF,NIF_utilizador)==0)
			{ 
			printf("Tipo de Veiculo: %s \n", h->tipo);
			printf("Identificador: %d \n", h->identificador);
			printf("Localização: %s \n", h->localizacao);
			printf("Custo do Aluger: %f \n", h->custo);
			printf("*********************************");
			printf("\n");
			}

		}
		break;
	}
	case 5:
	{
		Historicoopera h = (Historicoopera)data;
		if (h != NULL)
		{
			if (strcmp(h->NIF, NIF_utilizador) == 0)
			{
				printf("Operação: %s \n", h->Operacao);
				printf("Montante: %f \n", h->Quantia);
				printf("*********************************");
				printf("\n");
			}

		}
		break;
	}
	default:
		printf("Opção Inválida! \n");
		break;
	}
}





int verificarexistenciacliente(void* data, char* nif) {
	Clientes j = (Clientes)data;

	if (strcmp(j->NIF, nif) == 0) {
		return 1; // Retorna 1 se a string existe na lista
	}
	else return 0;

}
int verificarlogginclientes(void* data, char email[50], char password[15])
{
	Clientes j = (Clientes)data;

	if ((strcmp(j->email_cliente, email) == 0) && (strcmp(j->password, password) == 0)) {

		strcpy(utilizador, j->nome_cliente);
		strcpy(email_utilizador, j->email_cliente);
		strcpy(NIF_utilizador, j->NIF);
		strcpy(morada_utilizador, j->morada);
		strcpy(password_utilizador, j->password);
		saldo_utilizador = j->saldo;
		permissões_utilizador == j->permissoes;
		
		return 1; //retorna loggin com sucesso
	}
	else return 0;
}


int compararclientes(void* data1, void* data2)
{
	Clientes d1 = (Clientes)data1;
	Clientes d2 = (Clientes)data2;
	return(-strcmp(d1->NIF, d2->NIF));
}
int comparar(void* data1, void* data2)
{
	Clientes d1 = (Clientes)data1;
	Clientes d2 = (Clientes)data2;
	if (d1->NIF < d2->NIF) return(1);
	else if (d1->NIF > d2->NIF) return(-1);
	else return(0);
}

int igual(void* data1, void* data2)
{
	mobilidade d1 = (mobilidade)data1;
	mobilidade d2 = (mobilidade)data2;
		if (d1->identificador == d2->identificador) return 1;
		else return 0;

}
#pragma endregion
#pragma region "Gestores"

int verificarexistenciagestor(void* data, char* nif) {
	Gestores j = (Gestores)data;

	if (strcmp(j->NIF, nif) == 0) {
		return 1; // Retorna 1 se a string existe na lista
	}
	else return 0;

}
int comparargestores(void* data1, void* data2)
{
	Gestores d1 = (Gestores)data1;
	Gestores d2 = (Gestores)data2;
	return(-strcmp(d1->NIF, d2->NIF));
}
int verificarloggingestores(void* data, char email[50], char password[15])
{
	Gestores j = (Gestores)data;

	if ((strcmp(j->email_gestor, email) == 0) && (strcmp(j->password, password) == 0)) {

		strcpy(utilizador, j->nome_gestor);
		strcpy(email_utilizador, j->email_gestor);
		strcpy(NIF_utilizador,j->NIF);
		strcpy(morada_utilizador,j->morada);
		strcpy(password_utilizador,j->password);
		saldo_utilizador = j->saldo;
		permissões_utilizador==j->permissoes ;

		return 1; //retorna loggin com sucesso
	}
	else return 0;
}

#pragma endregion

#pragma region "Veiculos"

int verificarexistenciaveiculo(void* data, int* identificador) {
	mobilidade v = (mobilidade)data;

	if (v->identificador == identificador) {
		return 1; // Retorna 1 se a string existe na lista
	}
	else return 0;



}
int compararveiculos(void* data1, void* data2)
{
		mobilidade v1 = (mobilidade)data1;
		mobilidade v2 = (mobilidade)data2;
		return(-strcmp(v1->tipo_de_veiculo, v2->tipo_de_veiculo));
}


void registarveiculo(char tipo_de_veiculo[50], int identificador, int capacidade_bateria, int autonomia, float custo_aluger, char localizacao[100])
{
	mobilidade v;
	v = (mobilidade)malloc(sizeof(struct veiculos));
	strcpy(v->tipo_de_veiculo, tipo_de_veiculo);
	v->identificador = identificador;
	v->capacidade_bateria = capacidade_bateria;
	v->autonomia = autonomia;
	v->custo_aluger = custo_aluger;
	strcpy(v->localizacao, localizacao);
	MeiosList = addItemOrderedIterative(MeiosList, v, &compararveiculos);
}
void apagarveiculo(int identificador)
{
	mobilidade v;
	v = (mobilidade)malloc(sizeof(struct veiculos));
	v->identificador = identificador;
	MeiosList = removeItemIterative(MeiosList, v, &igual);
}
void writeveiculo(char tipo_de_veiculo[50], int identificador, int capacidade_bateria, int autonomia, float custo_aluger, char localizacao[100])
{
	FILE* MeiosFile;
	MeiosFile = fopen(FileMeios, "a+");
	fprintf(MeiosFile, "%s %d %d %d %f %s\n", tipo_de_veiculo, identificador, capacidade_bateria, autonomia, custo_aluger, localizacao);
	fclose(MeiosFile);
}
#pragma endregion

#pragma region "Funções conjuntas"
int compararal(void* data1, void* data2)
{
	Historicoaluger d1 = (Historicoaluger)data1;
	Historicoaluger d2 = (Historicoaluger)data2;
	return(-strcmp(d1->NIF, d2->NIF));
}

void registaral(char nome[50], char NIF[10], int ident, char tipo[50], char localizacao[100], float custo)
{
	Historicoaluger al;
	al = (Historicoaluger)malloc(sizeof(struct HistAluger));
	strcpy(al->utilizador, nome);
	strcpy(al->NIF, NIF);
	strcpy(al->tipo, tipo);
	strcpy(al->localizacao, localizacao);
	al->identificador = ident;
	al->custo = custo;

	HistAlug = addItemOrderedIterative(HistAlug, al, &compararal);

}
void writeal(char nome[50], char NIF[10],int ident,char tipo[50],char localizacao[100],float custo)
{
	FILE* Histalu;

	Histalu = fopen(HistAluger, "a+");
	fprintf(Histalu, "%s %s %d %s %s %f\n", nome, NIF, ident, tipo,localizacao,custo);
	fclose(Histalu);

	registaral(nome, NIF, ident, tipo, localizacao, custo);
}

int compararhist(void* data1, void* data2)
{
	Historicoopera d1 = (Historicoopera)data1;
	Historicoopera d2 = (Historicoopera)data2;
	return(-strcmp(d1->NIF, d2->NIF));
}

void WriteuserFile(char nome[50], char email[50], char NIF[10], char morada[50], float saldo, char password[50], int permissoes)
{	
		FILE* Clientsfile;
		Clientsfile = fopen(UserFile, "a+");
		fprintf(Clientsfile, "%s %s %s %s %f %s %d\n", nome, email, NIF, morada, saldo, password, permissoes);
		fclose(Clientsfile);
}	


void registarop(char nome[50], char NIF[10], char operacao[10], float quantia)
{
	Historicoopera op;
	op = (Historicoopera)malloc(sizeof(struct HistOp));
	strcpy(op->utilizador, nome);
	strcpy(op->NIF, NIF);
	strcpy(op->Operacao, operacao);
	op->Quantia = quantia;

	HistOpera = addItemOrderedIterative(HistOpera, op, &compararhist);

}
void writeope(char nome[50],char NIF[10],char operacao[20], float quantia)
{
	FILE* HistOP;

	HistOP = fopen(HistOper, "a+");
	fprintf(HistOP, "%s %s %s %f\n", nome, NIF,operacao, quantia);
	fclose(HistOP);

	registarop(nome, NIF, operacao, quantia);
}

int altsaldo(void* data,char NIF[10],float quantia,int op, int perm)
{

	char operacao[20] = "";
	if (perm == 1)
	{	
	Gestores i = (Gestores)data;	
	if (strcmp(i->NIF, NIF) == 0) {
		if (op == 1)
		{ 
		i->saldo = i->saldo + quantia;
		strcpy(operacao,"Carregamento");
		}
		if (op == 2)
		{
			i->saldo = i->saldo - quantia;
			strcpy(operacao, "Pagamento");
		}
		writeope(i->nome_gestor, i->NIF, operacao, quantia);
		saldo_utilizador = i->saldo;
		return 1;
	}
	else return 0;
	}
	if (perm == 2)
	{
		Clientes i = (Clientes)data;
		if (strcmp(i->NIF, NIF) == 0) {
			if (op == 1)
			{
				i->saldo = i->saldo + quantia;
				strcpy(operacao, "Carregamento");
			}
			if (op == 2)
			{
				i->saldo = i->saldo - quantia;
				strcpy(operacao, "Pagamento");
			}
			saldo_utilizador = i->saldo;
			writeope(i->nome_cliente, i->NIF, operacao, quantia);
			return 1;
		}
		else return 0;
	}

}
void registar(char nome[], char email[], char NIF[], char morada[], float saldo, char password[], int permissoes)
{
	if (permissoes == 0)
	{
		Clientes j;
		j = (Clientes)malloc(sizeof(struct utilizadores));
		strcpy(j->nome_cliente, nome);
		strcpy(j->email_cliente, email);
		strcpy(j->NIF, NIF);
		strcpy(j->morada, morada);
		strcpy(j->password, password);
		j->saldo = saldo;
		j->permissoes = permissoes;
		ClientList = addItemOrderedIterative(ClientList, j, &compararclientes);
	}
	if (permissoes == 1)
	{
		Gestores i;
		i = (Gestores)malloc(sizeof(struct gestores));
		strcpy(i->nome_gestor, nome);
		strcpy(i->email_gestor, email);
		strcpy(i->NIF, NIF);
		strcpy(i->morada, morada);
		strcpy(i->password, password);
		i->saldo = saldo;
		i->permissoes = permissoes;
		GestorList = addItemOrderedIterative(GestorList, i, &comparargestores);
	}
}

void importsfromtxt(char Users[], char meios[])
{
	char nome[50];          // Nome do Cliente
	char email[50];        // Email do Cliente
	char NIF[10];				  // NIF DO Cliente
	char morada[150];            // Morada 
	float saldo;  
	float quantia;              //  saldo
	char password[100];        // Palavra-chave
	int permissoes;
	char tipo[50] = "";
	int identificador = 0;
	int capacidade_bateria = 0;
	int autonomia = 0;
	float custo_aluger = 0;
	char localizacao[100] = "";
	char operacao[20];
	

	FILE* UsersFile;
	UsersFile = fopen(Users, "r");
	while (fscanf(UsersFile, "%s %s %s %s %f %s %d", nome, email, NIF, morada, &saldo, password, &permissoes) != EOF) {
		registar(nome, email, NIF, morada, saldo, password, permissoes);
	}

	fclose(UsersFile);

	FILE* MeiosFile;
	MeiosFile = fopen(meios, "r");
	while (fscanf(MeiosFile, "%s %d %d %d %f %s", tipo, &identificador, &capacidade_bateria, &autonomia, &custo_aluger, localizacao) != EOF) {
		registarveiculo(tipo, identificador, capacidade_bateria, autonomia, custo_aluger, localizacao);
	}
	fclose(MeiosFile);


	FILE* Histop;
	Histop = fopen(HistOper, "a+");
	while (fscanf(Histop, "%s %s %s %f", nome, NIF, operacao, &quantia) != EOF) {

		registarop(nome, NIF, operacao, quantia);
	}
	fclose(Histop);

	FILE* Histal;
	Histal = fopen(HistAluger, "a+");
	while (fscanf(Histal, "%s %s %d %s %s %f", nome, NIF,&identificador,tipo, localizacao, &custo_aluger) != EOF) {

		registaral(nome, NIF, identificador, tipo, localizacao, custo_aluger);
	}
	fclose(Histal);
}


void changesaldointxt(char Users[], char nif[], float saldo)
{
	char nome[50] = "";          // Nome do Cliente
	char email[50] = "";        // Email do Cliente
	char NIF[10] = "";				  // NIF DO Cliente
	char morada[150] = "";            // Morada 
	float Saldo = 0;
	char password[100] = "";        // Palavra-chave
	int permissoes = 0;
	int tamanho = 0;

	FILE* UsersFile;
	UsersFile = fopen(Users, "r+");
	while (fscanf(UsersFile, "%s %s %s %s %f %s %d", nome, email, NIF, morada, &Saldo, password, &permissoes) != EOF) {

		if (strcmp(NIF, nif) == 0) {
			tamanho = snprintf(NULL, 0, "%s %s %s %s %.2f %s %d\n", nome, email, NIF, morada, saldo, password, permissoes);
			fseek(UsersFile, -tamanho, SEEK_CUR);
			fprintf(UsersFile, "%s %s %s %s %.2f %s %d", nome, email, NIF, morada, saldo, password, permissoes);
			break;
		}
	}
	fclose(UsersFile);
}


#pragma endregion

#pragma region "Principal"
int main()
{
	int operacao = 0;
	// Declaração de Variaveis para inserção aquando do registo do cliente
	char passwordrep[50];
	char nome[50];           
	char email[50];       
	char NIF[10];		
	char morada[150];            
	float saldo = 0.00;						
	char password[100];				 
	int permissoes = 0;	
	//Declaração de Variaveis para inserção de meios
	char tipo[50] = "";
	int identificador = 0;
	int capacidade_bateria = 0;         
	int autonomia = 0;
	float custo_aluger = 0;
	char localizacao[100] = "";
	//Declaração de Variaveis para saldo
	char cartao[50];
	char nome_titular[100];
	char validade[10];
	int codigoseguranca = 0;
	int quantia = 0;

	importsfromtxt(UserFile, FileMeios);
inicio:
	switch (menuinicial())
	{
	case 1:
		system("cls");
		printf("************************************************\n");
		printf("*******************Loggin**********************\n");
		printf("************************************************\n \n \n");		
		printf("E-mail:");
		scanf("%s", email);
		printf("Password:");
		scanf("%s", password);

		if (loggin(ClientList, email, password, &verificarlogginclientes) == 1)
		{
		cliente:
			system("cls");
			printf("************************************************\n");
			printf("***************MOBILIDADE ELETRICA***************\n");
			printf("************************************************\n \n \n");
			printf("Bem-vindo(a), %s!\n", utilizador);
			printf("O seu saldo é de %f", saldo_utilizador);
			printf("Qual a opção que pretende excutar:\n");
			printf("Alugar veiculo -> 1\n");
			printf("Carregar Saldo -> 2 \n");
			printf("Alterar dados -> 3 \n");
			printf("Histórico Operações -> 4 \n");
			printf("Histórico Alugeres -> 5 \n");
			printf("Terminar sessão-> 6\n");
			printf("************************************************\n");
			printf("************************************************\n");
			scanf("%d", &operacao);

			switch (operacao)
			{
			case 1:


			case 2:
				system("cls");
				printf("************************************************\n");
				printf("****************Carregar Saldo******************\n");
				printf("************************************************\n \n \n");
				printf("Neste momento o saldo da sua conta é de %f\n", saldo_utilizador);
				printf("\nQual a quantia que deseja adicionar:");
				scanf("%d", &quantia);
				printf("Para carregar insira abaixo os dados do seu cartão:\n");
				printf("\nO Número do Cartão:");
				scanf("%s", cartao);
				printf("\nO Titular do Cartão:");
				scanf("%s", nome_titular);
				printf("\nA Validade do Cartão:");
				scanf("%s", validade);
				printf("\nO Código de Segurança do Cartão:");
				scanf("%d", &codigoseguranca);
				alterarsaldo(ClientList, NIF_utilizador, quantia, 1, 2, &altsaldo);
				savechangeintxt(UserFile, NIF_utilizador, saldo_utilizador);
				goto cliente;
			case 3:

			
			case 4:
				showListIterative(HistOpera, 5, &Show);
				goto cliente;
			case 5: 
				showListIterative(HistAlug, 4, &Show);
				goto cliente;
			case 6:
				goto inicio;
			default:
				break;
			}
		}
		else
		{
			if (loggin(GestorList, email, password, &verificarloggingestores) == 1)
			{
			gestor:
				system("cls");
				printf("************************************************\n");
				printf("***************MOBILIDADE ELETRICA***************\n");
				printf("************************************************\n \n \n");
				printf("Bem-vindo(a), %s!\n", utilizador);
				printf("O seu saldo é de %f\n", saldo_utilizador);
				printf("Qual a opção que pretende excutar:\n");
				printf("Alugar veiculo -> 1\n");
				printf("Carregar Saldo -> 2 \n");
				printf("Histórico Transações -> 3\n");
				printf("Histórico Aluger -> 4 \n");
				printf("Adicionar Veiculo -> 5 \n");
				printf("Remover Veículo -> 6 \n");
				printf("Consultar lista de Veículos -> 7 \n");
				printf("Consultar lista de Clientes -> 8 \n");
				printf("Consultar lista de Gestores -> 9 \n");
				printf("Adicionar gestor -> 10\n");
				printf("Alterar dados de Cliente -> 11\n");
				printf("Terminar sessão-> 12\n");
				printf("************************************************\n");
				printf("************************************************\n");
				scanf("%d", &operacao);
				switch (operacao)
				{
				case 1: //Alugar Veiculo

				case 2://Adicionar Saldo
					system("cls");
					printf("************************************************\n");
					printf("****************Carregar Saldo******************\n");
					printf("************************************************\n \n \n");
					printf("Neste momento o saldo da sua conta é de %f\n",saldo_utilizador);

					printf("\nQual a quantia que deseja adicionar:");
					scanf("%d", &quantia);
					printf("Para carregar insira abaixo os dados do seu cartão:\n");
					printf("\nO Número do Cartão:");
					scanf("%s", cartao);
					printf("\nO Titular do Cartão:");
					scanf("%s", nome_titular); 
					printf("\nA Validade do Cartão:");
					scanf("%s", validade);
					printf("\nO Código de Segurança do Cartão:");
					scanf("%d", &codigoseguranca);

					
					alterarsaldo(GestorList,NIF_utilizador,quantia,1 ,1,&altsaldo);
					changesaldointxt(UserFile, NIF_utilizador, saldo_utilizador);
					goto gestor;

				case 3:					
					showListIterative(HistOpera, 5, &Show);

					goto gestor;
			

				case 4:
					showListIterative(HistAlug, 4, &Show);

					goto gestor;
				case 5: //Adicionar Veiculo
					system("cls");
					printf("************************************************\n");
					printf("**************Registo de Veiculos***************\n");
					printf("************************************************\n \n \n");
					printf("Qual o tipo de veículo que quer adicionar:");
					scanf("%s", tipo);
					printf("\nNumero de Identificação:");
					scanf("%d", &identificador);
					printf("\nQual a percentagem de bateria:");
					scanf("%d", &capacidade_bateria);
					printf("\nQual a autonomia:");
					scanf("%d", &autonomia);
					printf("\nQual o custo do seu aluger:");
					scanf("%f", &custo_aluger);
					printf("\nQual a sua localização?:");
					scanf("%s", localizacao);

					if (verificar(MeiosList, identificador, &verificarexistenciaveiculo) != 1) {

						registarveiculo(tipo, identificador, capacidade_bateria, autonomia, custo_aluger, localizacao);
						writeveiculo(tipo, identificador, capacidade_bateria, autonomia, custo_aluger, localizacao);
						printf("Véiculo adicionado");
						getchar();
						goto gestor;

					}
					else
					{
						printf("Véiculo com esse identificador já se encontra registado");
						getchar();
						goto gestor;
					}



				case 6: 
					system("cls");
					showListIterative(MeiosList,3 ,&Show);
					printf("\n");
					printf("Por favor digite o identificador do veiculo que quer remover:");
					scanf("%d", &identificador);
					apagarveiculo(identificador);
					goto gestor;
				case 7:
					system("cls");
					showListIterative(MeiosList, 3, &Show);				
					goto gestor;
				case 8:
					system("cls");
					showListIterative(ClientList, 1, &Show);
					goto gestor;
				case 9:
					system("cls");
					showListIterative(GestorList, 2, &Show);
					goto gestor;
				case 10:

				case 11:

				case 12:
					goto inicio;
				default:
					break;
				}
			}
			else
			{
				system("cls");
				printf("Por favor tente novamente! \n");
				goto inicio;
			}

		}
		
	case 2:
		system("cls");
		printf("************************************************\n");
		printf("*******************Registo**********************\n");
		printf("************************************************\n \n \n");
		printf("Coloque o seu nome:");
		scanf("%s", nome);
		printf("\nNumero de Identificação Fiscal:");
		scanf("%s", NIF);
		printf("\nMorada:");
		scanf("%s", morada);
		printf("\nColoque o seu e-mail:");
		scanf("%s", email);
		printf("\nCrie a sua password:");
		scanf("%s", password);
		printf("\nColoque novamente a sua password:");
		scanf("%s", passwordrep);

		if ((strcmp(password, passwordrep) == 0))
		{
			if ((verificar(ClientList, NIF, &verificarexistenciacliente) != 1) && (verificar(GestorList, NIF,&verificarexistenciagestor)) != 1) {
				registar(nome, email, NIF, morada, saldo, password, permissoes);
				WriteuserFile(nome, email, NIF, morada, saldo, password, permissoes);
				system("cls");
				printf("Registado com sucesso!\n");
				goto cliente;
			}
			else
			{
				system("cls");
				printf("O utilizador já se encontra registado!\n");
			}
		}
		else
		{
			system("cls");
			printf("As palavras passes não correspondem, registo não efectuado!\n");
		}

		goto inicio;

	case 0:
		return 0;
	default:
		break;
	}
	return 0;
}
#pragma endregion

