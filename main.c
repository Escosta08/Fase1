#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ll.h"
#include <locale.h>
#pragma region "Variaveis"
/// <summary>
/// Declaração das listas ligadas 
/// </summary>
ListElem ClientList = NULL;
ListElem GestorList = NULL;
ListElem MeiosList = NULL;
ListElem HistOpera = NULL;
ListElem HistAlug = NULL;

char UserFile[] = "Documentos/UsersFile.txt";
char FileMeios[] = "Documentos/MeiosFile.txt";
char HistOper[] = "Documentos/HistOpera.txt";
char HistAluger[] = "Documentos/HistAluger.txt";
char FileRout[] = "Documentos/RoutFile.txt";
char FileLocal[] = "Documentos/Locais.txt";
//Registar utlizador que fez loggin
char utilizador[50] = "";
char email_utilizador[100] = "";
char NIF_utilizador[10] = "";
char morada_utilizador[100] = "";
float saldo_utilizador = 0.00;
char password_utilizador[100] = "";
int permissões_utilizador = 0;

char nome_AUX[50] = "";
char email_AUX[100] = "";
char NIF_AUX[10] = "";
char morada_AUX[100] = "";
float saldo_AUX = 0.00;
char password_AUX[100] = "";
int lastop_AUX;
int lastid_AUX;
int permissões_AUX = 0;
int lastoperacao;
int lastid;

char tipo_AUX[50];
int id_AUX;
int capacidade_bateria_AUX = 0;
int autonomia_AUX = 0;
float custo_aluger_AUX = 0;
char localizacao_AUX[100] = "";
#define VERTICES 40
float Matriz[VERTICES][VERTICES];
int Veiculoscompoucabateria[100][3];
int vertices[VERTICES];
#define MAX 40
#define INFINITY 9999


#pragma endregion
#pragma region "Estruturas"

/// <summary>
/// Estrutura onde irão ser guardados o valor do vertice mais proximo
/// </summary>
typedef struct reg
{
	int valor;
	struct reg* seguinte;
} *Pilha;
/// <summary>
/// Lista ligada onde é armazenada o peso dos caminhos entre vertices
/// </summary>
typedef struct registo
{
	int id;
	float peso;
	
	struct registo* seguinte;
} Lista, * Adjacentes;

/// /// <summary>
/// Estrutura de registo dos alugeres, onde irão ser colocados os dados do respectivo aluger
/// </summary>

typedef struct HistAluger
{
	char utilizador[50];
	char NIF[10];
	int identificador;
	char tipo[50];
	char localizacao[100];
	float custo;
	
}*Historicoaluger;

/// <summary>
/// Estrutura de Históricos de Operação, sera registado sempre que o utilizador faça um pagamento ou uma adição de saldo
/// </summary>
typedef struct HistOp
{
	char utilizador[50];
	char NIF[10];
	char Operacao[150];
	float Quantia;
}*Historicoopera;

/// <summary>
/// Estruturas de veiculos, onde é guardado o tipo, o identificador, a bateria, a autonomia, o custo do aluger, a localização e a disponibilidade
/// </summary>
typedef struct veiculos
{
	char tipo_de_veiculo[50];          //Tipo de Veículo
	int identificador;                //Identificador do Veículo
	int capacidade_bateria;          //Percentagem de Bateria 
	int autonomia;                  //Autonomia do Veículo 
	float custo_aluger;            //Custo de Aluger
	char localizacao[100];        //Geolocalização 3 palavras separadas por pontos		
	int disponibilidade;
}*mobilidade;
/// <summary>
/// Estrutura de Clientes, é guardado dados como o nome, o email, o nif, o email, a morada, o saldo, a password, as permissões,a ultima operação(aluger ou devolução) e o veiculo em questão
/// </summary>
typedef struct utilizadores
{
	char nome_cliente[50];          // Nome do Cliente
	char email_cliente[50];        // Email do Cliente
	char NIF[10];				  // NIF DO Cliente
	char morada[150];            // Morada 
	float saldo;						//  saldo
	char password[100];				  // Palavra-chave
	int permissoes;					 // Tipo de permissoes
	int ultimaoperacao;              //
	int identificador_ultima_operacao; //
}*Clientes;
/// <summary>
/// Estrutura equivalente à dos clientes, apenas respectiva aos gestores dos programas.
/// </summary>

typedef struct gestores
{
	char nome_gestor[50];         // Nome do Cliente
	char email_gestor[50];
	char NIF[10];					  // NIF DO Cliente
	char morada[150];            // Morada 
	float saldo;                //  saldo
	char password[100];        // Palavra-chave
	int permissoes;			  // Tipo de permissoes
	int ultimaoperacao;              //
	int identificador_ultima_operacao;//
}*Gestores;


#pragma endregion
#pragma region "Clientes".

/// <summary>
/// Função do tipo Void, recebe como variaveis de entrada os dados das listas ligadas e um inteiro, que seleciona o que vai ser mostrado na consola.
/// </summary>
/// <param name="data"></param>
/// <param name="op"></param>
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
	case 6:
	{	
		mobilidade v = (mobilidade)data;
		if ((v != NULL) && (v->disponibilidade == 1))
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
	default:
		break;
	}
}

/// <summary>
/// Função para limpeza dos ficheiros txt que armazenam os dados utilizados pela aplicação.
/// </summary>
/// <param name="txt"></param>
void cleantxt(char txt[])
{
	FILE* UserFiles;
	UserFiles = fopen(txt, "w");
	fprintf(UserFiles, "");
	fclose(UserFiles);

}


/// <summary>
/// Função para escrever conteudo das listas ligadas em ficheiros de texto, recebe como argumentos de entrada o conteudo das listas ligadas e a operacao a executar
/// </summary>
/// <param name="data"></param>
/// <param name="op"></param>
int writetxt(void* data, int op)
{
	switch (op) {
	case 1:
	{
		Clientes j = (Clientes)data;
		if (j != NULL)
		{
			FILE* UserFiles;
			UserFiles = fopen(UserFile, "a+");
			fprintf(UserFiles, "%s %s %s %s %f %s %d %d %d\n", j->nome_cliente, j->email_cliente, j->NIF, j->morada, j->saldo, j->password, j->permissoes, j->ultimaoperacao,j->identificador_ultima_operacao);
			fclose(UserFiles);
		
		}
		break;
	}
	case 2:
	{
		Gestores j = (Gestores)data;
		if (j != NULL)
		{
			FILE* UserFiles;
			UserFiles = fopen(UserFile, "a+");
			fprintf(UserFiles, "%s %s %s %s %f %s %d %d %d\n", j->nome_gestor, j->email_gestor, j->NIF, j->morada, j->saldo, j->password, j->permissoes,j->ultimaoperacao, j->identificador_ultima_operacao);
			fclose(UserFiles);
		}
		break;
	}

	case 3:
	{
		mobilidade k = (mobilidade)data;
		FILE* MeiosFile;
		if (k !=NULL)
		{ 
		MeiosFile = fopen(FileMeios, "a+");
		fprintf(MeiosFile, "%s %d %d %d %f %s %d\n", k->tipo_de_veiculo, k->identificador, k->capacidade_bateria, k->autonomia, k->custo_aluger, k->localizacao, k->disponibilidade);
		fclose(MeiosFile);
		}
	}		
	default:
		break;
	}
}

/// <summary>
/// Verifica Existencia dos clientes, caso exista passa os dados da lista ligada para variaveis auxliares para posterior edição das mesmas
/// </summary>
/// <param name="data"></param>
/// <param name="nif"></param>
/// <returns></returns>
int verificarexistenciacliente(void* data, char* nif) {
	Clientes j = (Clientes)data;

	if (strcmp(j->NIF, nif) == 0) {
		strcpy(nome_AUX, j->nome_cliente);
		strcpy(email_AUX, j->email_cliente);
		strcpy(NIF_AUX, j->NIF);
		strcpy(morada_AUX, j->morada);
		strcpy(password_AUX, j->password);
		saldo_AUX = j->saldo;
		permissões_AUX = j->permissoes;
		return 1;
	}
	else return 0;

}
/// <summary>
/// Verifica loggin dos clientes, caso exista passa os dados da lista ligada para variaveis do utilizador
/// </summary>
/// <param name="data"></param>
/// <param name="email"></param>
/// <param name="password"></param>
/// <returns></returns>
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
		permissões_utilizador = j->permissoes;
		lastoperacao = j->ultimaoperacao;
		lastid = j->identificador_ultima_operacao;
		
		return 1; //retorna loggin com sucesso
	}
	else return 0;
}


/// <summary>
/// Função de alterar dados dos veiculos, recebe como variaveis de entrada da lista ligada, o identificador do veiculo a alterar, recebe uma string, um inteiro e um float
/// consoante o valor do inteiro da operação, esta função reescreve na lista ligada a informação que foi alterada.
/// </summary>
/// <param name="data"></param>
/// <param name="identificador"></param>
/// <param name="string"></param>
/// <param name="inteiro"></param>
/// <param name="custo"></param>
/// <param name="op"></param>
/// <returns></returns>

int alterardadosveiculos(void* data, int identificador, char string[], int inteiro, float custo, int op)
{
	mobilidade j = (mobilidade)data;

	if (j->identificador == identificador)
	{
		if (op == 1)
		{
			j->capacidade_bateria = inteiro;
		}
		if (op == 2)
		{
			j->autonomia = inteiro;
		}
		if (op == 3)
		{
			j->custo_aluger = custo;

		}
		if (op == 4)
		{
			strcpy(j->localizacao, string);

		}
		if (op == 5)
		{
			j->disponibilidade = inteiro;
				
		}
		return 1;

	}
	else return 0;
}


/// <summary>
/// Alteração dos valores da lista lgiada de ultima operação e de ultimo identificador usado pelo utilizador.
/// </summary>
/// <param name="data"></param>
/// <param name="NIF"></param>
/// <param name="numero"></param>
/// <param name="op"></param>
/// <param name="perm"></param>
/// <returns></returns>
int alterarlastopid(void* data, char NIF[10],int numero, int op, int perm)
{

	if (perm == 1)
	{
		Gestores i = (Gestores)data;
		if (strcmp(i->NIF, NIF) == 0) {
			if (op == 1)
			{
				i->ultimaoperacao = numero;

			}
			if (op == 2)
			{
				i->identificador_ultima_operacao = numero;

			}
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
				i->ultimaoperacao = numero;

			}
			if (op == 2)
			{
				i->identificador_ultima_operacao = numero;
				
			}
			return 1;
		}
		else return 0;
	}

}
/// <summary>
/// Função de alterar dados, recebe como entrada os dados da lista ligada, o nif do utilizador e a alteração.
/// Os inteiros que recebem de seguida indicam de que tipo de operação e do tipo de utilizador.
/// </summary>
/// <param name="data"></param>
/// <param name="NIF"></param>
/// <param name="string"></param>
/// <param name="op"></param>
/// <param name="perm"></param>
/// <returns></returns>
int alterardados(void* data, char NIF[10], char string[], int op, int perm)
{
	
	if (perm == 1)
	{
		Gestores i = (Gestores)data;
		if (strcmp(i->NIF, NIF) == 0) {
			if (op == 1)
			{
				strcpy(i->email_gestor, string);
			
			}
			if (op == 2)
			{
				strcpy(i->morada, string);

			}
			if (op == 3)
			{
				strcpy(i->password, string);
			}

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
				strcpy(i->email_cliente, string);

			}
			if (op == 2)
			{
				
				strcpy(i->morada, string);
			}
			if (op == 3)
			{
				strcpy(i->password, string);

			}


			return 1;
		}
		else return 0;
	}

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
int igual_clientes(void* data1, void* data2)
{
	Clientes d1 = (Clientes)data1;
	Clientes d2 = (Clientes)data2;
	if (strcmp(d1->NIF , d2->NIF)==0) return 1;
	else return 0;

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
/// <summary>
/// Verifica a existencia do gestor na lista ligada, recebe apenas como variaveis de entrada os dados da lista ligada e o nif do utlizador em questão.
/// Caso este esteja inserido dentro da lista ligada, copia os dados do mesmo para variaveis auxiliares para posterior alteração
/// </summary>
/// <param name="data"></param>
/// <param name="nif"></param>
/// <returns></returns>
int verificarexistenciagestor(void* data, char* nif) {
	Gestores j = (Gestores)data;

	if (strcmp(j->NIF, nif) == 0) {
		strcpy(nome_AUX, j->nome_gestor);
		strcpy(email_AUX, j->email_gestor);
		strcpy(NIF_AUX, j->NIF);
		strcpy(morada_AUX, j->morada);
		strcpy(password_AUX, j->password);
		saldo_AUX = j->saldo;
		permissões_AUX = j->permissoes;


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


/// <summary>
/// Função para verificar loggin dos gestores, esta função recebe como entrada a lista lgiada, os dados de e-mail e a password
/// caso ele exista dentro da lista ligada e a password for igual a registada na lista ligada
/// os dados do gestor são copiados para as variaveis de utilizador.
/// </summary>
/// <param name="data"></param>
/// <param name="email"></param>
/// <param name="password"></param>
/// <returns></returns>
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
		permissões_utilizador=j->permissoes ;
		lastoperacao = j->ultimaoperacao;
		lastid = j->identificador_ultima_operacao;

		return 1; //retorna loggin com sucesso
	}
	else return 0;
}

#pragma endregion

#pragma region "Veiculos"
/// <summary>
/// Verifica a existencia de veiculo na lista ligada, copiando de seguida os dados do mesmo, se existir, para variaveis auxiliares para posterior alteração se for necessário.
/// </summary>
/// <param name="data"></param>
/// <param name="identificador"></param>
/// <returns></returns>
int verificarexistenciaveiculo(void* data, int identificador) {
	mobilidade v = (mobilidade)data;
	if (v->identificador == identificador) {
		id_AUX = identificador;
		strcpy(tipo_AUX, v->tipo_de_veiculo);
		capacidade_bateria_AUX = v->capacidade_bateria;
		 autonomia_AUX = v->autonomia;
		 custo_aluger_AUX = v->custo_aluger;
		strcpy(localizacao_AUX, v->localizacao);
		return 1; 
	}
	else return 0;
}

int verificarexistenciapoucabateira(void* data, int i) {
	mobilidade v = (mobilidade)data;
	int vertice;
	char localizacao[100] = "";
	if (v->capacidade_bateria <= 50) {
		FILE* LocaisDoc;
		LocaisDoc = fopen(FileLocal, "r");
		while (fscanf(LocaisDoc, "%d %s", &vertice, localizacao) != EOF) {

			if (strcmp(v->localizacao,localizacao) == 0)
			{
				Veiculoscompoucabateria[i][0] = vertice;
				Veiculoscompoucabateria[i][1] = v->identificador;
				Veiculoscompoucabateria[i][2] = 0;
				Veiculoscompoucabateria[i+1][0] = 0;
				Veiculoscompoucabateria[i+1][1] = 0;
				Veiculoscompoucabateria[i+2][2] = 0;
				fclose(LocaisDoc);
				return 1;
			}
		}
		fclose(LocaisDoc);


		return 0;
	}
	else return 0;
}





int compararveiculos(void* data1, void* data2)
{
		mobilidade v1 = (mobilidade)data1;
		mobilidade v2 = (mobilidade)data2;
		return(-strcmp(v1->tipo_de_veiculo, v2->tipo_de_veiculo));
}

/// <summary>
/// Regista dentro da lista ligada por ordem decrescente
/// </summary>
/// <param name="tipo_de_veiculo"></param>
/// <param name="identificador"></param>
/// <param name="capacidade_bateria"></param>
/// <param name="autonomia"></param>
/// <param name="custo_aluger"></param>
/// <param name="localizacao"></param>
/// <param name="disponibilidade"></param>
void registarveiculo(char tipo_de_veiculo[50], int identificador, int capacidade_bateria, int autonomia, float custo_aluger, char localizacao[100],int disponibilidade)
{
	mobilidade v;
	v = (mobilidade)malloc(sizeof(struct veiculos));
	strcpy(v->tipo_de_veiculo, tipo_de_veiculo);
	v->identificador = identificador;
	v->capacidade_bateria = capacidade_bateria;
	v->autonomia = autonomia;
	v->custo_aluger = custo_aluger;
	v->disponibilidade = disponibilidade;
	strcpy(v->localizacao, localizacao);
	MeiosList = addItemOrderedIterative(MeiosList, v, &compararveiculos);
}


/// <summary>
/// Apaga veiculo da lista ligada
/// </summary>
/// <param name="identificador"></param>
void apagarveiculo(int identificador)
{
	mobilidade v;
	v = (mobilidade)malloc(sizeof(struct veiculos));
	v->identificador = identificador;
	MeiosList = removeItemIterative(MeiosList, v, &igual);
	cleantxt(FileMeios);
	rewritefile(MeiosList, 1, &writetxt);
}
/// <summary>
/// Escreve o meio no txt respectivo.
/// </summary>
/// <param name="tipo_de_veiculo"></param>
/// <param name="identificador"></param>
/// <param name="capacidade_bateria"></param>
/// <param name="autonomia"></param>
/// <param name="custo_aluger"></param>
/// <param name="localizacao"></param>
/// <param name="disponibilidade"></param>
void writeveiculo(char tipo_de_veiculo[50], int identificador, int capacidade_bateria, int autonomia, float custo_aluger, char localizacao[100], int disponibilidade)
{
	FILE* MeiosFile;
	MeiosFile = fopen(FileMeios, "a+");
	fprintf(MeiosFile, "%s %d %d %d %f %s %d\n", tipo_de_veiculo, identificador, capacidade_bateria, autonomia, custo_aluger, localizacao,disponibilidade);
	fclose(MeiosFile);
}
#pragma endregion

#pragma region "Funções conjuntas"
/// <summary>
/// Apaga utilizador da lista ligada, seja ele cliente ou gestor, reescrevendo de seguida os ficheiros de texto com a informação
/// </summary>
/// <param name="NIF"></param>
/// <param name="op"></param>
void apagaruser(char NIF[], int op)
{
	if (op == 1)
	{
		Clientes i;
		i = (Clientes)malloc(sizeof(struct utilizadores));
		strcpy(i->NIF, NIF);
		ClientList = removeItemIterative(ClientList, i, &igual_clientes);
	}
	else
	{
		Gestores i;
		i = (Gestores)malloc(sizeof(struct gestores));
		strcpy(i->NIF, NIF);
		GestorList = removeItemIterative(GestorList, i, &igual_clientes);
	}

	cleantxt(UserFile);
	rewritefile(ClientList, 1, &writetxt);
	rewritefile(GestorList, 2, &writetxt);
}

int compararal(void* data1, void* data2)
{
	Historicoaluger d1 = (Historicoaluger)data1;
	Historicoaluger d2 = (Historicoaluger)data2;
	return(-strcmp(d1->NIF, d2->NIF));
}
/// <summary>
/// Função de registar aluger na lista ligada-
/// </summary>
/// <param name="nome"></param>
/// <param name="NIF"></param>
/// <param name="ident"></param>
/// <param name="tipo"></param>
/// <param name="localizacao"></param>
/// <param name="custo"></param>
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

/// <summary>
/// Escreve no ficheiro de texto o aluger que foi previamente registado na lista ligada
/// </summary>
/// <param name="nome"></param>
/// <param name="NIF"></param>
/// <param name="ident"></param>
/// <param name="tipo"></param>
/// <param name="localizacao"></param>
/// <param name="custo"></param>
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


/// <summary>
/// Adiciona ao ficheiro de texto dos utilizadores o utilizador que foi registado novo
/// </summary>
/// <param name="nome"></param>
/// <param name="email"></param>
/// <param name="NIF"></param>
/// <param name="morada"></param>
/// <param name="saldo"></param>
/// <param name="password"></param>
/// <param name="permissoes"></param>
/// <param name="lastop"></param>
/// <param name="lastid"></param>
void WriteuserFile(char nome[50], char email[50], char NIF[10], char morada[50], float saldo, char password[50], int permissoes, int lastop, int lastid)
{	
	FILE* UserFiles;
	UserFiles = fopen(UserFile, "a+");
	fprintf(UserFiles, "%s %s %s %s %f %s %d %d %d\n", nome, email, NIF, morada, saldo,password, permissoes,lastop,lastid);
	fclose(UserFiles);
}


/// <summary>
/// Regista a operação (pagamento ou carregamento) na lista ligada
/// </summary>
/// <param name="nome"></param>
/// <param name="NIF"></param>
/// <param name="operacao"></param>
/// <param name="quantia"></param>
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

/// <summary>
/// Regista no ficheiro de Texto a operação que foi declarada anteriormente na lista ligada.
/// </summary>
/// <param name="nome"></param>
/// <param name="NIF"></param>
/// <param name="operacao"></param>
/// <param name="quantia"></param>
void writeope(char nome[50],char NIF[10],char operacao[20], float quantia)
{
	FILE* HistOP;

	HistOP = fopen(HistOper, "a+");
	fprintf(HistOP, "%s %s %s %f\n", nome, NIF,operacao, quantia);
	fclose(HistOP);

	registarop(nome, NIF, operacao, quantia);
}

void writecaminho(int vertice1,int vertice2,  float distancia)
{
	FILE* RouteFile;

	RouteFile = fopen(FileRout, "a+");
	fprintf(RouteFile, "%d %d %f \n", vertice1, vertice2, distancia);
	fclose(RouteFile);

}



/// <summary>
/// Função de alterar saldo dentro das listas ligadas, caso seja para alterar positivamente ou negativamenete, registando esta operação na lista ligada do historico de operações
/// Tambem regista no ficheiro de texto das operações.
/// </summary>
/// <param name="data"></param>
/// <param name="NIF"></param>
/// <param name="quantia"></param>
/// <param name="op"></param>
/// <param name="perm"></param>
/// <returns></returns>
int altsaldo(void* data,char NIF[10],float *quantia,int op, int perm)
{

	char operacao[20] = "";
	if (perm == 1)
	{	
	Gestores i = (Gestores)data;	
	if (strcmp(i->NIF, NIF) == 0) {
		if (op == 1)
		{ 
		i->saldo = i->saldo + *quantia;
		strcpy(operacao,"Carregamento");
		}
		if (op == 2)
		{
			i->saldo = i->saldo - *quantia;
			strcpy(operacao, "Pagamento");
		}
		writeope(i->nome_gestor, i->NIF, operacao, *quantia);
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
				i->saldo = i->saldo + *quantia;
				strcpy(operacao, "Carregamento");
			}
			if (op == 2)
			{
				i->saldo = i->saldo - *quantia;
				strcpy(operacao, "Pagamento");
			}
			saldo_utilizador = i->saldo;
			writeope(i->nome_cliente, i->NIF, operacao, *quantia);
			return 1;
		}
		else return 0;
	}

}
/// <summary>
/// Função de registar clientes e gestores, recebe os dados a registar para dentro das listas ligadas.
/// </summary>
/// <param name="nome"></param>
/// <param name="email"></param>
/// <param name="NIF"></param>
/// <param name="morada"></param>
/// <param name="saldo"></param>
/// <param name="password"></param>
/// <param name="permissoes"></param>
/// <param name="lastop"></param>
/// <param name="lastid"></param>
void registar(char nome[], char email[], char NIF[], char morada[], float saldo, char password[], int permissoes,int lastop,int lastid)
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
		j->ultimaoperacao = lastop;
		j->identificador_ultima_operacao = lastid;
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
		i->ultimaoperacao = lastop;
		i->identificador_ultima_operacao = lastid;
		GestorList = addItemOrderedIterative(GestorList, i, &comparargestores);
	}
}
/// <summary>
/// Função inicial de ler os ficheiros de texto e colocar os dados registados para dentro das listas ligadas.
/// </summary>
/// <param name="Users"></param>
/// <param name="meios"></param>





#pragma endregion


#pragma region Fase2

/// <summary>
/// Função para registo de arestas do grafo na lista ligada
/// </summary>
/// <param name="Grafo"></param> Grafo ao qual vai ser adicionado a aresta
/// <param name="v1"></param> vertice inicial
/// <param name="v2"></param> vertice final
/// <param name="p"></param> distancia do caminho
/// <returns></returns>
int inserirAresta(Adjacentes Grafo[], int v1, int v2, float p)
{
	Adjacentes novo;
	if ((v1 >= 0) && (v1 < VERTICES) && (v2 >= 0) && (v2 < VERTICES) &&
		(p >= 0)
		)
	{
		novo = (Adjacentes)malloc(sizeof(struct registo));
		novo->id = v2;
		novo->peso = p;
		novo->seguinte = Grafo[v1];
		Grafo[v1] = novo;

		return(1);
	}
	else return(0);
}

/// <summary>
/// Função que inicia o grafo, coloca todas as distancias em zero
/// </summary>
/// <param name="Grafo"></param> Grafo a ser inicializado
void inicializarGrafo(Adjacentes Grafo[])
{
	int i;
	for (i = 0; i < VERTICES; i++) Grafo[i] = NULL;
}

/// <summary>
/// Função que transforma o grafo recebido por parametro, numa matriz de adjacencia, primeiramente é escrita a matriz com valores nullos e de seguida é preenchida com o peso da adjacencia de cada vertice
/// </summary>
/// <param name="Grafo"></param> Grafo a ser convertido
/// <param name="Matriz"></param> Matriz na qual é escrita a matriz adjacencia
void converter(Adjacentes Grafo[], float Matriz[][VERTICES])
{
	int i, j;
	Adjacentes aux;
	for (i = 0; i < VERTICES; i++)
		for (j = 0; j < VERTICES; j++)
			Matriz[i][j] = 0;
	for (i = 0; i < VERTICES; i++)
	{
		aux = Grafo[i];
		while (aux != NULL)
		{
			Matriz[i][aux->id] = aux->peso;
			aux = aux->seguinte;
		}
	}
}
/// <summary>
/// 
/// </summary>
/// <param name="sequencia"></param>
/// <param name="pos"></param>
/// <param name="id"></param>
/// <returns></returns>
int visitado(int sequencia[], int pos, int id)
{
	int i;
	for (i = 0; i < pos; i++) if (sequencia[i] == id) return(1);
	return(0);
}
/// <summary>
/// Função escreve na consola os detalhes do veiculo, presentes na lista ligada caso estes entrem nos parametros de localização e disponibilidade
/// </summary>
/// <param name="data"></param> Espaço de memoria onde esta alocada a informação relativa ao veiculo
/// <param name="localizacao"></param> localização para a qual tem de coincidir os veiculos para serem apresentados
/// <returns></returns>
int mostrarveiculosnasproximidades(void* data, char localizacao[100])
{
	mobilidade v = (mobilidade)data;
	if ((strcmp(v->localizacao, localizacao) == 0) && (v->disponibilidade == 1)) {

		printf("	Tipo de Veiculo: %s \n", v->tipo_de_veiculo);
		printf("	Identificador: %d \n", v->identificador);
		printf("	Capacidade Bateria: %d /100 \n", v->capacidade_bateria);
		printf("	Autonomia: %d Km \n", v->autonomia);
		printf("	Custo de Aluger: %f euros \n", v->custo_aluger);
		printf("\n");
		return 1;
	}
}
/// <summary>
///  Função de leitura de ficheiro de texto, que recebe por parametro, o id do vertice e um inteiro op, esta função irá ler o ficheiro de texto e comparar com o id de entrada da função e realizará outra função consoante o op
/// </summary>
/// <param name="id_read"></param> ID de descodificação do vertice
/// <param name="op"></param> Simbolo da operação que realizará após leitura do verticve
void devolverlocalizacao(int id_read, int op)
{
	char localizacao[100];
	int id;
	FILE* LocaisDoc;
	LocaisDoc = fopen(FileLocal, "r");
	while (fscanf(LocaisDoc, "%d %s", &id, localizacao) != EOF) {
		if (id == id_read)
		{
			if (op == 1)
			{
				printf("Em: %s \n", localizacao);
				verificarproximidade(MeiosList, localizacao, &mostrarveiculosnasproximidades);
			}
			if (op == 2)
			{
				alterarveiculos(MeiosList, id_AUX, localizacao, 0, 0.00, 4, &alterardadosveiculos);
			}
			break;
		}
	}
	fclose(LocaisDoc);
}


/// <summary>
///  Recebe como entrada uma Matriz, onde vão estar escritos os vertices adjacentes recolhidos e os pesos, e vai returnar a sua saída o vertice em que o caminho é menor
/// </summary>
/// <param name="Matriz"></param>
/// <returns></returns> Retorna vertice que o caminho é menor
int devolvermenor(float Matriz[VERTICES][2])
{
	int i = 0;
	int id = 0;
	float menor = Matriz[0][1];
	for (i = 0; Matriz[i][1] != 0; i++)
		if (Matriz[i][1] < menor) {
			menor = Matriz[i][1];
			id = i;
		}
	return(id);
}
/// <summary>
/// Função que lista os vertices adjacentes presentes num grafo do vertice escolhido, após isso faz a serleção dos vertices que estão até ao raio escolhido pelo utilizador
/// Chama depois a função que para apresentar os veiculos em
/// </summary>
/// <param name="Grafo"></param> Grafo a procurar vertices adjacentes
/// <param name="vertice"></param> Vertice ao qual vamos procurar os adjacentes
/// <param name="raiomaximo"></param> Raio máximo admitida percorrer pelo cliente
void listar_(Adjacentes Grafo[], int vertice, int raiomaximo)
{
	Adjacentes aux;
	int i = 0, j = 0;
	float Matriz[VERTICES][2];
	int id, id_read;
	char localizacao[100];
	aux = Grafo[vertice];
	;

	while (aux != NULL)
	{
		Matriz[i][0] = aux->id;
		Matriz[i][1] = aux->peso;
		i++; 
		aux = aux->seguinte;
	}
	Matriz[i][0] = 0;
	Matriz[i][1] = 0;	
	printf("Veiculos nas suas proximidades: \n\n");
	for (j = 0; j < i; j++)
	{
		id = devolvermenor(Matriz);
		id_read = Matriz[id][0];	
		if (Matriz[id][1] <= raiomaximo)
		{
			printf("Distancia: %2f \n", Matriz[id][1]);
			devolverlocalizacao(id_read,1);
		}
		Matriz[id][1] = 9999;
	}
}
/// <summary>
/// Função que recebe por parametro a matriz adjacencia, o numero de vertices e o vertice inicial
/// Verifica qual o vertice mais perto na lista de vertices ao qual é necessário e apaga o vertice que está mais perto da lista
/// Apresenta por ultimo o caminho mais curto para o vertice mais perto.
/// </summary>
/// <param name="G"></param> Matriz adjacencia
/// <param name="n"></param> Numero de Vertices
/// <param name="startnode"></param> Vertice inicial para verificar o mais perto
/// <returns></returns>
int dijkstra(float G[VERTICES][VERTICES], int n, int startnode)
{

	int cost[VERTICES][VERTICES], distance[VERTICES], pred[VERTICES];
	int visited[VERTICES], count, mindistance, nextnode, i, j, k;
	int verticelista, menor = 9999;
	int verticemaisperto;
	char localizacao[100];

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			if (G[i][j] == 0)
				cost[i][j] = INFINITY;
			else
				cost[i][j] = G[i][j];
	
	for (i = 0; i < n; i++)
	{
		distance[i] = cost[startnode][i];
		pred[i] = startnode;
		visited[i] = 0;
	}
	distance[startnode] = 0;
	visited[startnode] = 1;
	count = 1;
	int distanciamenor = 9999;
	while (count < n - 1)
	{
		mindistance = INFINITY;
		
		for (i = 0; i < n; i++)
			if (distance[i] < mindistance && !visited[i])
			{
				mindistance = distance[i];
				nextnode = i;
			}
		
		visited[nextnode] = 1;
		for (i = 0; i < n; i++)
			if (!visited[i])
				if (mindistance + cost[nextnode][i] < distance[i])
				{
					distance[i] = mindistance + cost[nextnode][i];
					pred[i] = nextnode;
				}
		count++;
	}

	for (i = 0; i < n; i++){
		verticelista = vertices[i];
	
		if (distance[verticelista] < menor)
		{
			menor = distance[verticelista];
			verticemaisperto = verticelista;
			k = i;
		}
	}

	for (j = k; j < i - 1; j++) {
		vertices[j] = vertices[j + 1];
	}


	if (i != startnode)
		{	
		FILE* LocaisDoc;
		LocaisDoc = fopen(FileLocal, "r");
		while (fscanf(LocaisDoc, "%d %s", &verticelista, localizacao) != EOF) {
			if (verticelista == verticemaisperto)
			{
				break;
			}
		}
		fclose(LocaisDoc);
			printf("\n\nPercorra uma distancia de %d  km ate %s \n",distance[verticemaisperto], localizacao);
			printf("Caminho mais perto para %s \n", localizacao);
			j = verticemaisperto;
			i = 0;
			do
			{
				j = pred[j];

				LocaisDoc = fopen(FileLocal, "r");
				while (fscanf(LocaisDoc, "%d %s", &verticelista, localizacao) != EOF) {
					if (verticelista == j)
					{
						printf("				^\n");
						printf("				^\n");
						printf("				^\n");
						printf("			%s\n",localizacao);					
						break;
					}					
				}
				fclose(LocaisDoc);
				
			} while (j != startnode);
			return(verticemaisperto);
		}		
}

#pragma endregion

/// <summary>
/// Importa dos ficheiros de texto os valores todos de utilização
/// </summary>
void importsfromtxt()
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
	int lastid;
	int lastop;
	int disponibilidade;
	int vertice;
	int id_local;
	char nome_local[] = "";

	FILE* UsersFile;
	UsersFile = fopen(UserFile, "r");
	while (fscanf(UsersFile, "%s %s %s %s %f %s %d %d %d", nome, email, NIF, morada, &saldo, password, &permissoes, &lastop, &lastid) != EOF) {
		registar(nome, email, NIF, morada, saldo, password, permissoes, lastop, lastid);
	}

	fclose(UsersFile);

	FILE* MeiosFile;
	MeiosFile = fopen(FileMeios, "r");
	while (fscanf(MeiosFile, "%s %d %d %d %f %s %d", tipo, &identificador, &capacidade_bateria, &autonomia, &custo_aluger, localizacao, &disponibilidade) != EOF) {
		registarveiculo(tipo, identificador, capacidade_bateria, autonomia, custo_aluger, localizacao, disponibilidade);
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
	while (fscanf(Histal, "%s %s %d %s %s %f", nome, NIF, &identificador, tipo, localizacao, &custo_aluger) != EOF) {

		registaral(nome, NIF, identificador, tipo, localizacao, custo_aluger);
	}
	fclose(Histal);


	
}

#pragma region "Principal"
int main()
{
	Pilha p = NULL;


	int operacao = 0;
	// Declaração de Variaveis para inserção aquando do registo do cliente
	char passwordrep[50] ="";
	char nome[50];           
	char email[50];       
	char NIF[10];		
	char morada[150];            
	float saldo = 0.00;						
	char password[100] = "";
	int permissoes = 0;	
	int verticecliente;
	//Declaração de Variaveis para inserção de meios
	char tipo[50] = "";
	int identificador = 0;
	int capacidade_bateria = 0;         
	int autonomia = 0;
	float custo_aluger = 0;
	char localizacao[100] = "";
	int disponibilidade;
	//Declaração de Variaveis para saldo
	char cartao[50];
	char nome_titular[100];
	char validade[10];
	int codigoseguranca = 0;
	float quantia = 0;
	int c;
	int ponto1;
	int ponto2;
	float distancia;
	int raiomaximo;
	int max;

	importsfromtxt();
	FILE* RoutFile;
	RoutFile = fopen(FileRout, "a+");
	Adjacentes Grafo1[VERTICES];
	inicializarGrafo(Grafo1);
	while (fscanf(RoutFile, "%d %d %f", &ponto1, &ponto2, &distancia) != EOF) {

		inserirAresta(Grafo1, ponto1, ponto2, distancia);
	}
	fclose(RoutFile);


	

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
			if (lastoperacao == 1)printf("Alugar veiculo -> 1\n");
			if (lastoperacao ==2) printf("Devolver veiculo -> 1\n");			
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
				if (lastoperacao == 1)
				{
					system("cls");
					menulocalizacao(FileLocal);
					printf("Qual a sua localização:\n");
					scanf("%d", &verticecliente);
					printf("Qual o raio máximo:\n");
					scanf("%d", &raiomaximo);
					system("cls");
					devolverlocalizacao(verticecliente,1);
					listar_(Grafo1, verticecliente, raiomaximo);
					printf("Qual o veículo que pretende alugar:");
					scanf("%d", &identificador);
					if (verificarmeios(MeiosList, identificador, &verificarexistenciaveiculo) == 1) {
						if (saldo_utilizador >= custo_aluger_AUX)
						{			
						alterarveiculos(MeiosList, identificador, " ", 0, 0.00, 5, &alterardadosveiculos);
						writeal(utilizador, NIF_utilizador, identificador, tipo_AUX, localizacao_AUX, custo_aluger_AUX);
						alterarsaldo(ClientList, NIF_utilizador, &custo_aluger_AUX, 2, 2, &altsaldo);
						alteraraluger(ClientList, NIF_utilizador, 2, 1, 2, &alterarlastopid);
						alteraraluger(ClientList, NIF_utilizador, identificador, 2, 2, &alterarlastopid);
						lastoperacao = 2;
						cleantxt(UserFile);
						rewritefile(ClientList, 1, &writetxt);
						rewritefile(GestorList, 2, &writetxt);
						cleantxt(FileMeios);
						rewritefile(MeiosList, 3, &writetxt);
						lastid = identificador;
						goto cliente;
						}
						else
						{
							printf("Não foi possivel alugar devido ao seu saldo! Prima Enter para continuar");
							while ((c = getchar()) != '\n' && c != EOF) {}
							getchar();
							goto cliente;
						}
					}


				}
				if (lastoperacao == 2)
				{
					if (verificarmeios(MeiosList, lastid, &verificarexistenciaveiculo) == 1) {
						system("cls");
						printf("************************************************\n");
						printf("****************Devolver Veículo******************\n");
						printf("************************************************\n \n \n");
						menulocalizacao(FileLocal);
						printf("Qual a sua localização:");
						scanf("%d", &verticecliente);
						printf("Qual a bateria:");
						scanf("%d", &capacidade_bateria_AUX);
						devolverlocalizacao(verticecliente, 2);
						alterarveiculos(MeiosList, identificador, " ", capacidade_bateria_AUX, 0.00, 1, &alterardadosveiculos);
						alterarveiculos(MeiosList, lastid, " ", 1, 0.00, 5, &alterardadosveiculos);
						alteraraluger(ClientList, NIF_utilizador, 1, 1, 2, &alterarlastopid);
						lastoperacao = 1;
					}

				}
				cleantxt(UserFile);
				rewritefile(ClientList, 1, &writetxt);
				rewritefile(GestorList, 2, &writetxt);
				cleantxt(FileMeios);
				rewritefile(MeiosList, 3, &writetxt);
				goto cliente;
			case 2:
				system("cls");
				printf("************************************************\n");
				printf("****************Carregar Saldo******************\n");
				printf("************************************************\n \n \n");
				printf("Neste momento o saldo da sua conta é de %f\n", saldo_utilizador);
				printf("\nQual a quantia que deseja adicionar:");
				scanf("%f", &quantia);
				printf("Para carregar insira abaixo os dados do seu cartão:\n");
				printf("\nO Número do Cartão:");
				scanf("%s", cartao);
				printf("\nO Titular do Cartão:");
				scanf("%s", nome_titular);
				printf("\nA Validade do Cartão:");
				scanf("%s", validade);
				printf("\nO Código de Segurança do Cartão:");
				scanf("%d", &codigoseguranca);
				alterarsaldo(ClientList, NIF_utilizador,&quantia, 1, 2, &altsaldo);
				cleantxt(UserFile);
				rewritefile(ClientList, 1, &writetxt);
				rewritefile(GestorList, 2, &writetxt);
				goto cliente;
			case 3:
				system("cls");
				printf("************************************************\n");
				printf("****************Alterar Dados*******************\n");
				printf("************************************************\n \n \n");			
				printf("E-mail -> 1\n");
				printf("Morada -> 2\n");
				printf("Password -> 3\n");
				printf("Voltar -> 0\n");
				printf("Qual os dados que deseja alterar:");
				scanf("%d", &operacao);
				switch (operacao)
				{
				case 1:
					system("cls");
					printf("O seu e-mail atual é: %s\n", email_utilizador);
					printf("Digite o seu novo e-mail: ");
					scanf("%s", email_utilizador);
					alterar(ClientList, NIF_utilizador, email_utilizador,1,2,&alterardados);
					break;
				case 2:
					system("cls");
					printf("A sua morada atual é: %s\n", morada_utilizador);
					printf("Digite a sua nova morada: ");
					scanf("%s", morada_utilizador);
					alterar(ClientList, NIF_utilizador, morada_utilizador, 2, 2, &alterardados);
					break;
				case 3:
					system("cls");
					printf("Digite a sua palavra passe atual:");
					scanf("%s", password);
					if (strcmp(password, password_utilizador) == 0)
					{
						printf("Digite a sua palavra passe nova:");
						scanf("%s", password);
						printf("Reescreva a sua palavra passe nova:");
						scanf("%s", passwordrep);
						if (strcmp(password, passwordrep) == 0)
						{
							strcpy(password_utilizador, password);
							alterar(ClientList, NIF_utilizador, password_utilizador, 3, 2, &alterardados);
						}
						else 
						{ 
							printf("Novas passwords nao correspondem, prima Enter para continuar.");
							while ((c = getchar()) != '\n' && c != EOF) {}
							getchar();
							goto cliente;
						}
					}
					else
					{
						printf("Passwords nao correspondem, prima Enter para continuar.");
						while ((c = getchar()) != '\n' && c != EOF) {}
						getchar();
						goto cliente;
					}
					break;
				case 0:
					goto cliente;
				default:
					break;
				}
				cleantxt(UserFile);
				rewritefile(ClientList, 1, &writetxt);
				rewritefile(GestorList, 2, &writetxt);
				goto cliente;
			
			case 4:
				showListIterative(HistOpera, 5, &Show);
				printf("\nPara voltar ao menu inicial prima enter");
				while ((c = getchar()) != '\n' && c != EOF) {} 
				getchar();
				goto cliente;
			case 5: 
				showListIterative(HistAlug, 4, &Show);
				printf("\nPara voltar ao menu inicial prima enter");
				while ((c = getchar()) != '\n' && c != EOF) {}
				getchar();
				goto cliente;
			case 6:
				goto inicio;
			default:
				goto cliente;		
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
				if (lastoperacao == 1)printf("Alugar veiculo -> 1\n");
				if (lastoperacao == 2) printf("Devolver veiculo -> 1\n");
				printf("Carregar Saldo -> 2 \n");
				printf("Histórico Transações -> 3\n");
				printf("Histórico Aluger -> 4 \n");
				printf("Adicionar Veiculo -> 5 \n");
				printf("Alterar Veículo -> 6 \n");
				printf("Remover Veículo -> 7 \n");
				printf("Consultar lista de Veículos -> 8 \n");
				printf("Consultar lista de Clientes -> 9 \n");
				printf("Consultar lista de Gestores -> 10 \n");
				printf("Adicionar gestor -> 11\n");
				printf("Alterar dados de Clientes ou de Gestores -> 12\n");
				printf("Remover Clientes ou Gestores -> 13\n");
				printf("Adicionar caminhos -> 14\n");
				printf("Recolher Véiculos -> 15\n");
				printf("Terminar sessão-> 16\n");
				printf("************************************************\n");
				printf("************************************************\n");
				scanf("%d", &operacao);
				switch (operacao)
				{
				case 1: //Alugar Veiculo
					if (lastoperacao == 1)
					{
						system("cls");
						menulocalizacao(FileLocal);
						printf("Qual a sua localização:\n");
						scanf("%d", &verticecliente);
						printf("Qual o raio máximo:\n");
						scanf("%d", &raiomaximo);
						system("cls");
						devolverlocalizacao(verticecliente, 1);
						listar_(Grafo1, verticecliente, raiomaximo);
						printf("Qual o veículo que pretende alugar:");
						scanf("%d", &identificador);
						if (verificarmeios(MeiosList, identificador, &verificarexistenciaveiculo) == 1) {
							if (saldo_utilizador >= custo_aluger_AUX)
							{
								alterarveiculos(MeiosList, identificador, " ", 0, 0.00, 5, &alterardadosveiculos);
								writeal(utilizador, NIF_utilizador, identificador, tipo_AUX, localizacao_AUX, custo_aluger_AUX);
								alterarsaldo(GestorList, NIF_utilizador, &custo_aluger_AUX, 2, 1, &altsaldo);
								alteraraluger(GestorList, NIF_utilizador, 2, 1, 1, &alterarlastopid);
								alteraraluger(GestorList, NIF_utilizador, identificador, 2, 1, &alterarlastopid);
								lastoperacao = 2;
								cleantxt(UserFile);
								rewritefile(ClientList, 1, &writetxt);
								rewritefile(GestorList, 2, &writetxt);
								cleantxt(FileMeios);
								rewritefile(MeiosList, 3, &writetxt);
								lastid = identificador;
								goto gestor;
							}
							else
							{
								printf("Não foi possivel alugar devido ao seu saldo! Prima Enter para continuar");
								while ((c = getchar()) != '\n' && c != EOF) {}
								getchar();
								goto gestor;
							}
						}


					}
					if (lastoperacao == 2)
					{
						if (verificarmeios(MeiosList, lastid, &verificarexistenciaveiculo) == 1) {
							system("cls");
							printf("************************************************\n");
							printf("****************Devolver Veículo******************\n");
							printf("************************************************\n \n \n");
							menulocalizacao(FileLocal);
							printf("Qual a sua localização:");
							scanf("%d", &verticecliente);
							printf("Qual a bateria:");
							scanf("%d", &capacidade_bateria_AUX);
							devolverlocalizacao(verticecliente, 2);
							alterarveiculos(MeiosList, lastid, " ", 1, 0.00, 5, &alterardadosveiculos);
							alteraraluger(GestorList, NIF_utilizador, 1, 1, 1, &alterarlastopid);
							lastoperacao = 1;
						}

					}

					cleantxt(UserFile);
					rewritefile(ClientList, 1, &writetxt);
					rewritefile(GestorList, 2, &writetxt);
					cleantxt(FileMeios);
					rewritefile(MeiosList, 3, &writetxt);
					goto gestor;

				case 2://Adicionar Saldo
					system("cls");
					printf("************************************************\n");
					printf("****************Carregar Saldo******************\n");
					printf("************************************************\n \n \n");
					printf("Neste momento o saldo da sua conta é de %f\n",saldo_utilizador);

					printf("\nQual a quantia que deseja adicionar:");
					scanf("%f", &quantia);
					printf("Para carregar insira abaixo os dados do seu cartão:\n");
					printf("\nO Número do Cartão:");
					scanf("%s", cartao);
					printf("\nO Titular do Cartão:");
					scanf("%s", nome_titular); 
					printf("\nA Validade do Cartão:");
					scanf("%s", validade);
					printf("\nO Código de Segurança do Cartão:");
					scanf("%d", &codigoseguranca);					
					alterarsaldo(GestorList,NIF_utilizador,&quantia,1 ,1,&altsaldo);
					cleantxt(UserFile);
					rewritefile(ClientList, 1, &writetxt);
					rewritefile(GestorList, 2, &writetxt);
					
					goto gestor;

				case 3:					
					showListIterative(HistOpera, 5, &Show);
					while ((c = getchar()) != '\n' && c != EOF) {}
					getchar();
					goto gestor;
			

				case 4:
					showListIterative(HistAlug, 4, &Show);
					while ((c = getchar()) != '\n' && c != EOF) {}
					getchar();

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
					printf("\nQual a sua Dispobilidade?:");
					printf("\n1-> Disponivel // 2-> Indisponivel");
					scanf("%d", &disponibilidade);

					if (verificarmeios(MeiosList, identificador, &verificarexistenciaveiculo) != 1) {

						registarveiculo(tipo, identificador, capacidade_bateria, autonomia, custo_aluger, localizacao,disponibilidade);
						writeveiculo(tipo, identificador, capacidade_bateria, autonomia, custo_aluger, localizacao, disponibilidade);
						printf("Véiculo adicionado");
						getchar();
						goto gestor;

					}
					else
					{
						printf("Véiculo com esse identificador já se encontra registado");
						while ((c = getchar()) != '\n' && c != EOF) {}
						getchar();
						goto gestor;
					}

				case 6:
					system("cls");
					printf("************************************************\n");
					printf("****************Alterar Veiculos*******************\n");
					printf("************************************************\n \n \n");
					showListIterative(MeiosList, 3, &Show);
					printf("Digite o numero do identificador do veiculo:\n");
					scanf("%d", &identificador);
					if (verificarmeios(MeiosList, identificador, &verificarexistenciaveiculo) == 1)
					{
						printf("Bateria -> 1\n");
						printf("Autonomia -> 2\n");
						printf("Custo Aluger -> 3\n");
						printf("Localização -> 4\n");
						printf("Voltar -> 0\n");
						printf("Qual os dados que deseja alterar:");
						scanf("%d", &operacao);
						switch (operacao)
						{
						case 0:
							goto gestor;
						case 1:
							system("cls");
							printf("A Capacidade atual é: %d\n", capacidade_bateria_AUX);
							printf("Digite a nova capacidade: ");
							scanf("%d", &capacidade_bateria);
							alterarveiculos(MeiosList, identificador, " ", capacidade_bateria, 0.00, 1, &alterardadosveiculos);
							cleantxt(FileMeios);
							rewritefile(MeiosList, 3, &writetxt);
							goto gestor;
						case 2:
							system("cls");
							printf("A Autonomia atual é: %d\n", autonomia_AUX);
							printf("Digite a nova autonomia: ");
							scanf("%d", &autonomia);
							alterarveiculos(MeiosList, identificador, " ", autonomia, 0.00, 2, &alterardadosveiculos);
							cleantxt(FileMeios);
							rewritefile(MeiosList, 3, &writetxt);
							goto gestor;
						case 3:
							system("cls");
							printf("O Custo de Aluger atual é: %f\n", custo_aluger_AUX);
							printf("Digite a nova capacidade: ");
							scanf("%f", &custo_aluger);
							alterarveiculos(MeiosList, identificador, " ", 0, custo_aluger_AUX, 3, &alterardadosveiculos);
							cleantxt(FileMeios);
							rewritefile(MeiosList, 3, &writetxt);
							goto gestor;
						case 4:
							system("cls");
							printf("A localização atual é: %s\n", localizacao_AUX);
							menulocalizacao(FileLocal);
							printf("Digite a nova localização: ");
							scanf("%d", &verticecliente);
							devolverlocalizacao(verticecliente, 2);
							cleantxt(FileMeios);
							rewritefile(MeiosList, 3, &writetxt);
							goto gestor;
						default:
							break;
						}
					}
					goto gestor;
				case 7: 
					system("cls");
					showListIterative(MeiosList,6,&Show);
					printf("\n");
					printf("Por favor digite o identificador do veiculo que quer remover:");
					scanf("%d", &identificador);
					apagarveiculo(identificador);
					goto gestor;
				case 8:
					system("cls");
					showListIterative(MeiosList, 3, &Show);		
					while ((c = getchar()) != '\n' && c != EOF) {}
					getchar();
					goto gestor;
				case 9:
					system("cls");
					showListIterative(ClientList, 1, &Show);
					while ((c = getchar()) != '\n' && c != EOF) {}
					getchar();
					goto gestor;
				case 10:
					system("cls");
					showListIterative(GestorList, 2, &Show);
					while ((c = getchar()) != '\n' && c != EOF) {}
					getchar();
					goto gestor;
				case 11:

					system("cls");
					printf("************************************************\n");
					printf("****************Alterar Permissões*******************\n");
					printf("************************************************\n \n \n");
					printf("Digite o NIF do utlizador que pretende admitir como gestor:\n");
					scanf("%s", NIF);
					if (verificarusers(ClientList, NIF, &verificarexistenciacliente) == 1)
					{
						apagaruser(NIF, 1);
						registar(nome_AUX, email_AUX, NIF_AUX, morada_AUX, saldo_AUX, password_AUX, 1, lastop_AUX,lastid_AUX);
						cleantxt(UserFile);
						rewritefile(ClientList, 1, &writetxt);
						rewritefile(GestorList, 2, &writetxt);
					}

					goto gestor;
				case 12:
					system("cls");
					printf("************************************************\n");
					printf("****************Alterar Dados*******************\n");
					printf("************************************************\n \n \n");
					printf("Digite o NIF do utlizador que alterar dados:\n");
					scanf("%s", NIF);
					if (verificarusers(ClientList, NIF, &verificarexistenciacliente) == 1)
					{
						printf("E-mail -> 1\n");
						printf("Morada -> 2\n");
						printf("Voltar -> 0\n");
						printf("Qual os dados que deseja alterar:");
						scanf("%d", &operacao);
						switch (operacao)
						{
						case 1:
							system("cls");
							printf("O  e-mail atual é: %s\n", email_AUX);
							printf("Digite o novo e-mail: ");
							scanf("%s", email_AUX);
							alterar(ClientList, NIF_AUX, email_AUX, 1, 2, &alterardados);
							break;
						case 2:
							system("cls");
							printf("A  morada atual é: %s\n", morada_AUX);
							printf("Digite a nova morada: ");
							scanf("%s", morada_AUX);
							alterar(ClientList, NIF_AUX, morada_AUX, 2, 2, &alterardados);
							break;
						default:
							break;
						}
						cleantxt(UserFile);
						rewritefile(ClientList, 1, &writetxt);
						rewritefile(GestorList, 2, &writetxt);
						goto gestor;
					}
					if (verificarusers(GestorList, NIF, &verificarexistenciagestor) == 1)
					{
						printf("E-mail -> 1\n");
						printf("Morada -> 2\n");
						printf("Voltar -> 0\n");
						printf("Qual os dados que deseja alterar:");
						scanf("%d", &operacao);
						switch (operacao)
						{
						case 1:
							system("cls");
							printf("O  e-mail atual é: %s\n", email_AUX);
							printf("Digite o novo e-mail: ");
							scanf("%s", email_AUX);
							alterar(GestorList, NIF_AUX, email_AUX, 1, 1, &alterardados);
							break;
						case 2:
							system("cls");
							printf("A  morada atual é: %s\n", morada_AUX);
							printf("Digite a nova morada: ");
							scanf("%s", morada_AUX);
							alterar(GestorList, NIF_AUX, morada_AUX, 2, 1, &alterardados);
							break;
						default:
							break;
						}

						cleantxt(UserFile);
						rewritefile(ClientList, 1, &writetxt);
						rewritefile(GestorList, 2, &writetxt);
						goto gestor;
					}

					goto gestor;
				case 13:
					system("cls");
					printf("************************************************\n");
					printf("****************Remover Users*******************\n");
					printf("************************************************\n \n \n");
					printf("Digite o NIF do utlizador que pretende apagar:\n");
					scanf("%s", NIF);
					if (verificarusers(ClientList, NIF, &verificarexistenciacliente) == 1)
					{
						apagaruser(NIF, 1);
						cleantxt(UserFile);
						rewritefile(ClientList, 1, &writetxt);
						rewritefile(GestorList, 2, &writetxt);
					}
					if (verificarusers(GestorList, NIF, &verificarexistenciagestor) == 1)
					{
						apagaruser(NIF, 2);
						cleantxt(UserFile);
						rewritefile(ClientList, 1, &writetxt);
						rewritefile(GestorList, 2, &writetxt);
					}

					goto gestor;

				case 14:
					system("cls");
					printf("************************************************\n");
					printf("****************Adicionar caminhos*******************\n");
					printf("************************************************\n \n \n");
					menulocalizacao(FileLocal);
					printf("Qual a primeira localidade:\n");
					scanf("%d", &ponto1);
					printf("Qual a segunda localidade:\n");
					scanf("%d", &ponto2);
					printf("Qual a distancia:");
					scanf("%f", &distancia);
					inserirAresta(Grafo1,ponto1, ponto2, distancia);
					writecaminho(ponto1, ponto2, distancia);
					goto gestor;

				case 15: //Recolher Véiculos
				
					system("cls");
					printf("************************************************\n");
					printf("****************Recolher Veículos***************\n");
					printf("************************************************\n \n \n");
					int proximovertice = 21;
					int j = 0;
					verificarpoucabat(MeiosList, &verificarexistenciapoucabateira);

					for (int i = 0; Veiculoscompoucabateria[i][0] != 0; i++) {	
						if (Veiculoscompoucabateria[i][2] != 1)
						{ 
							printf("\nNo Vertice :%d  \n *Veículo: %d ",Veiculoscompoucabateria[i][0], Veiculoscompoucabateria[i][1]);	
							Veiculoscompoucabateria[i][2] = 1;
							for (int j = i+1; Veiculoscompoucabateria[j][0] != 0; j++) {
								if (Veiculoscompoucabateria[i][0] == Veiculoscompoucabateria[j][0])
								{
									printf("%d ", Veiculoscompoucabateria[j][1]);
									Veiculoscompoucabateria[j][2] = 1;
								}
							}		
							
							vertices[j] = Veiculoscompoucabateria[i][0];
							j++;
							vertices[j] = 0;
							
							printf("\n_________________");
						}
						max = i+1;
						
					}
					printf("\nNo total existe %d  veiculos com bateria abaixo de 50/100", max);
					
					converter(Grafo1, Matriz);


					for (int i = 0; i < j; i++) {

						proximovertice = dijkstra(Matriz, VERTICES, proximovertice);


					}
					vertices[0] = 21;
					proximovertice = dijkstra(Matriz, VERTICES, proximovertice);


					while ((c = getchar()) != '\n' && c != EOF) {}
					getchar();


					goto gestor;
				case 16:
					goto inicio;
				default:
					goto gestor;
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
			if ((verificarusers(ClientList, NIF, &verificarexistenciacliente) != 1) && (verificarusers(GestorList, NIF,&verificarexistenciagestor)) != 1) {
				registar(nome, email, NIF, morada, saldo, password, permissoes,1,0);
				WriteuserFile(nome, email, NIF, morada, saldo, password, permissoes,1,0);
				system("cls");
				printf("Registado com sucesso!\n");
				goto cliente;
			}
			else
			{
				system("cls");
				printf("O utilizador já se encontra registado!\n");
				while ((c = getchar()) != '\n' && c != EOF) {}
				getchar();
			}
		}
		else
		{
			system("cls");
			printf("As palavras passes não correspondem, registo não efectuado!\n");
			while ((c = getchar()) != '\n' && c != EOF) {}
			getchar();
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

