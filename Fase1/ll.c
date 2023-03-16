#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ll.h"  // header file

ListElem addItemHead(ListElem head, void *data) {
	ListElem aux;
	
	if((aux = (ListElem) malloc(sizeof(SListElem))) == NULL)
		return head;
	
	aux->data = data;
	aux->next = head;
	
	return aux;
}

ListElem addItemLastRecursive(ListElem head, void *data) {
	ListElem aux;
	
	if(head == NULL) {
		aux = (ListElem) malloc(sizeof(SListElem));
		aux->data = data;
		aux->next = NULL;
		return aux;
	}
	
	head->next = addItemLastRecursive(head->next, data);
	
	return head;
}

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


void showListIterative(ListElem head, int op, void (*show)(void *data)) {
	
	while(head != NULL) {
		show(head->data,op);
		head = head->next;
	}
	
}

int alterarsaldo(ListElem head,char NIF[10],int saldo,int op, int perm, int (*addsaldo)(void* data, char nif[10], float quantia, int op, int perm)) {

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




int verificar(ListElem head,char num[10], int (*verificar)(void* data , char nif[10])) {

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


void showListRecursive(ListElem head, void (*show)(void *data)) {
	if(head != NULL) {
		show(head->data);
		showListRecursive(head->next, show);
	}
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

ListElem removeItemRecursive(ListElem head, void *data, int (*compare)(void *data1, void *data2)) {
	ListElem aux;
	
	if(head == NULL)
		return NULL;
	
	if(compare(head->data, data) == 1) {
		aux = head->next;
		free(head);
		return aux;
	} else {
		head->next = removeItemRecursive(head->next, data, compare);
		return head;
	}
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

ListElem addItemOrderedRecursive(ListElem head, void *data, int (*compare)(void *data1, void *data2)) {
	ListElem aux;
	
	if(head == NULL || compare(data, head->data) < 0) {
		aux = (ListElem) malloc(sizeof(SListElem));
		aux->data = data;
		aux->next = head;
		return aux;
	}
	
	head->next = addItemOrderedRecursive(head->next, data, compare);
	return head;
}

#pragma region "Menus"
int menuinicial()
{
	int operacao = 0;
	printf("************************************************\n");
	printf("***************MOBILIDADE ELETRICA***************\n");
	printf("************************************************\n \n \n");
	printf("Qual a opção que pretende excutar:\n");
	printf("Fechar Aplicação -> 0 \n");
	printf("Fazer loggin -> 1\n");
	printf("Registar-me -> 2 \n");	
	printf("************************************************\n");
	printf("************************************************\n");
	scanf("%d", &operacao);

	return(operacao);
}
#pragma endregion



