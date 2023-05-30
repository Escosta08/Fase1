/// <summary>
/// Estrutura de lista ligada, no primeiro campo sera guardada a informação e no campo next será guardado o endereço do proximo elemento da lista ligada
/// </summary>
typedef struct sListElem {
	void *data; // endereço de memória remetendo para o(s) dado(s)
		    // a representar
	struct sListElem *next;
} *ListElem, SListElem;

// Applies show function to all elements on the list, iteratively
void showListIterative(ListElem head, int op, void (*show)(void *data, int op));

int verificarusers(ListElem head, char num[10], int (*verificar)(void* data, char nif[10]));

// Insert a new element with *data in last position of the list, iteratively
// *data must point to storage in the heap
ListElem addItemLastIterative(ListElem head, void *data);

// Insert a new element with *data in the list according to the order defined by function compare, iteratively
// *data must point to storage in the heap
ListElem addItemOrderedIterative(ListElem head, void *data, int (*compare)(void *data1, void *data2));


// Removes the first item on the list that compares positively with *data through function compare, iteratively 
ListElem removeItemIterative(ListElem head, void *data, int (*compare)(void *data1, void *data2));

int menuinicial();

int alteraraluger(ListElem head, char NIF[10], int numero, int op, int perm, int (*alterar)(void* data, char nif[10], int numero, int op, int perm));

int alterar(ListElem head, char NIF[10], char string[], int op, int perm, int (*alterar)(void* data, char nif[10], char string[], int op, int perm));

int alterarveiculos(ListElem head, int identificador, char string[], int inteiro, float custo, int op, int (*alterar)(void* data, int identificador, char string[], int inteiro, float custo, int op));

int alterarsaldo(ListElem head, char NIF[10], float* saldo, int op, int perm, int (*addsaldo)(void* data, char nif[10], float* quantia, int op, int perm));

int rewritefile(ListElem head, int op, int (*write)(void* data, int op));

int verificarproximidade(ListElem head, char localizacao[100], int (*verificar)(void* data, char localizacao[100]));
