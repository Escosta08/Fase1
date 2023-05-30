#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ll.h"  // header file

ListElem addItemLastIterative(ListElem head, void *data) {
	ListElem aux, prev;

	aux = (ListElem)malloc(sizeof(SListElem));
	aux->data = data;
	aux->next = NULL;

	if (head == NULL) {	
		return aux;
	}

	for(prev = head; prev->next != NULL; prev = prev->next) ;

	prev->next = aux;

	return head;
}


void showListIterative(ListElem head, int op, void (*show)(void *data, int op)) {
	
	while(head != NULL) {
		show(head->data,op);
		head = head->next;
	}
	
}

int alteraraluger(ListElem head, char NIF[10], int numero, int op, int perm, int (*alterar)(void* data, char nif[10], int numero, int op, int perm)) {

	while (head != NULL) {
		if ((alterar(head->data, NIF, numero, op, perm) == 1)) {
			return 1;
			break;
		}
		else
			head = head->next;
	}
	return 0;
}

int alterar(ListElem head, char NIF[10], char string[], int op, int perm, int (*alterar)(void* data, char nif[10], char string[], int op, int perm)) {

	while (head != NULL) {
		if ((alterar(head->data, NIF, string, op, perm) == 1)) {
			return 1;
			break;
		}
		else
			head = head->next;
	}
	return 0;
}
int alterarveiculos(ListElem head, int identificador, char string[], int inteiro, float custo, int op, int (*alterar)(void* data, int identificador, char string[], int inteiro, float custo, int op)) {

	while (head != NULL) {
		if ((alterar(head->data, identificador, string, inteiro, custo, op) == 1)) {
			return 1;
			break;
		}
		else
			head = head->next;
	}
	return 0;
}
int alterarsaldo(ListElem head,char NIF[10],float *saldo,int op, int perm, int (*addsaldo)(void* data, char nif[10], float *quantia, int op, int perm)) {

	while (head != NULL) {
		if ((addsaldo(head->data, NIF, saldo,op,perm) == 1)) {
			return 1;
			break;
		}
		else
			head = head->next;
	}
	return 0;
}

int rewritefile(ListElem head,int op, int (*write)(void* data,int op)) {

	while (head != NULL) {
		if ((write(head->data,op) == 1)) {
			return 1;
		}
		else
			head = head->next;
	}
	return 0;
}
int verificarmeios(ListElem head, int id, int (*verificar)(void* data, int id)) {

	while (head != NULL) {


		if ((verificar(head->data, id) == 1)) {
			return 1;
		}
		else
			head = head->next;
	}
	return 0;
}

void verificarpoucabat(ListElem head, int (*verificar)(void* data , int i)) {
	int i = 0;
	while (head != NULL) {
		if ((verificar(head->data, i) == 1)) {
			i++;
			head = head->next;
		}
		else
			head = head->next;
	}
	
}


int verificarproximidade(ListElem head, char localizacao[100], int (*verificar)(void* data, char localizacao[100])) {

	while (head != NULL) {
		if ((verificar(head->data, localizacao) == 1)) {
			head = head->next;
		}
		else
			head = head->next;
	}
	return 0;
}

int verificarusers(ListElem head,char num[10], int (*verificar)(void* data , char nif[10])) {

	while (head != NULL) {
		if ((verificar(head->data, num) == 1)) {
			return 1;
		}
		else
		head = head->next;
	}
	return 0;
}

int loggin(ListElem head, char email[50], char password[15], int (*verificar)(void* data, char email[50], char password[15]))
{
	while (head != NULL) {
		if ((verificar(head->data, email,password) == 1)) {
			return 1;
		}
		else
			head = head->next;
	}
	 return 0;

}

ListElem removeItemIterative(ListElem head, void* data, int (*compare)(void* data1, void* data2)) {
	ListElem aux, prev;

	// List is empty
	if (head == NULL)
		return NULL;

	// Element to remove is on the head of the list
	if (compare(head->data, data) == 1) {
		aux = head->next;
		free(head);
		return aux;
	}

	// Element to remove is in the tail of the list
	for (prev = head; prev->next != NULL; prev = prev->next)
	{
		if (compare(prev->next->data, data) == 1) {
			aux = prev->next;
			prev->next = prev->next->next;
			free(aux);
			break;
		}
	}

	return head;
}


ListElem addItemOrderedIterative(ListElem head, void *data, int (*compare)(void *data1, void *data2)) {
	ListElem n, aux;
	
	n = (ListElem) malloc(sizeof(SListElem));
	n->data = data;
	n->next = NULL;
	
	if(head == NULL || compare(data, head->data) < 0) {
		n->next = head;
		return n;
		return n;
	}
	
	for(aux = head; aux->next != NULL; aux = aux->next) {
		if(compare(data, aux->next->data) < 0) {
			n->next = aux->next;
			aux->next = n;
			return head;
		}
	}
	
	aux->next = n;
	return head;
}

#pragma region "Menus"
int menuinicial()
{
	int operacao = 0;
	system("cls");
	printf("************************************************\n");
	printf("***************MOBILIDADE ELETRICA**************\n");
	printf("************************************************\n");
	printf("**      Qual a opção que pretende excutar:    **\n");
	printf("**		Fechar Aplicação -> 0         **\n");
	printf("**		Fazer loggin -> 1             **\n");
	printf("**		Registar-me -> 2              **\n");	
	printf("************************************************\n");
	printf("************************************************\n");
	scanf("%d", &operacao);

	return(operacao);
}
void menulocalizacao(char FileLocal[])
{
	int id;
	char localizacao[100];
	printf("******************************************************************\n");
	FILE* LocaisDoc;
	LocaisDoc = fopen(FileLocal, "r");
	while (fscanf(LocaisDoc, "%d %s ", &id, localizacao) != EOF) {
		printf("* %d - %s \n", id, localizacao);
	}
	printf("******************************************************************\n");
	fclose(LocaisDoc);
}
#pragma endregion



