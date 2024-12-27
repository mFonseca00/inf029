#include <stdio.h>
#include <stdlib.h>

// Lista simplesmente encadeada
/*  Uma Lista/lista encadeada/Lista simplesmente encadeada é uma sequência de elementos encadeados, um após o outro,
    onde cada elemento contém um ponteiro para o próximo elemento da lista*/
/* É uma estrutura mais genéria e flexível que as pilhas e filas, posi não especifica onde os elementos serão inseridos ou removidos.*/

// Lista encadeada com cabeçote
/* Uma Lista encadeada com cabeçote é uma lista simplesmente encadeada, com um cabeçote, o primeiro elemento da lista.
O cabeçote contém um ponteiro para o primeiro elemento da lista, e um ponteiro para o fim da lista.*/

/* A diferença principal entre as duas versões da lista encadeada e se da na inicialização da lista e, por consequência, na inserção de elementos.
 (no caso com cabeçote, considerar a função de inicialização e a inserção de elementos como  head->next = newNode,
 enquanto no caso sem, como head = newNode ou seja, enquanto o cabeçote aponta para o primeiro elemento na versão com cabeçote,
 na versão sem cabeçote, a lista inicia direto com o primeiro elemento inserido)*/


typedef struct no{
    int valor;
    struct no *prox;
}No;

// Procedimento (função) para inserir um elemento no inicio da lista
void inserir_no_inicio(No **inicio, int insert){ // *inicio = ponteiro para o inicio da lista (**inicio = ponteiro para ponteiro para o inicio da lista)
    No *novo = malloc(sizeof(No)); // Aloca memória para o novo no
    if(novo == NULL){
        printf("Erro ao alocar memória\n");
        return;
    }

    novo->valor = insert; // Insere o valor
    novo->prox = *inicio; // Insere o ponteiro para o proximo elemento (elemento apontado pelo inicio da lista)
    *inicio = novo; // Atualiza o ponteiro para o inicio da lista para o novo no
}

// Procedimento (função) para inserir um elemento no fim da lista
void inserir_no_fim(No **inicio, int insert){
    No *novo = malloc(sizeof(No)); // Aloca memória para o novo no
    if(novo == NULL){
        printf("Erro ao alocar memória\n");
        return;
    }

    novo->valor = insert; // Insere o valor
    novo->prox = NULL; // Insere o ponteiro para o proximo elemento (elemento nulo, pois nao aponta para nenhum elemento)

    // É o primeiro elemento da lista? Adiciona o nó como o inicio da lista
    if(*inicio == NULL){
        novo->prox = NULL; // Insere o ponteiro para o proximo elemento (elemento nulo, pois nao aponta para nenhum elemento)
        *inicio = novo; // Se sim, atualiza o ponteiro para o inicio da lista para o novo no
        return;
    }

    // Não é o primeiro elemento da lista? Adiciona o nó como ultimo elemento da lista
    else{
        No *aux = *inicio; // Cria um ponteiro auxiliar para percorrer a lista
        while(aux->prox != NULL){ // Enquanto o proximo elemento nao for nulo, percorre a lista
            aux = aux->prox; // Atualiza o ponteiro auxiliar para o proximo elemento
        }
        aux->prox = novo; // Insere o ponteiro para o proximo elemento (elemento apontado pelo inicio da lista)
    }
}

// Procedimento (função) para inserir um elemento no meio ou outra posicao da lista
void inserir_no_meio(No **inicio, int insert, int anterior){
    No *novo = malloc(sizeof(No)); // Aloca memória para o novo no
    if(novo == NULL){
        printf("Erro ao alocar memória\n");
        return;
    }

    novo->valor = insert; // Insere o valor
    // é o primeiro elemento da lista? Adiciona o nó como o inicio da lista
    if(*inicio == NULL){
        novo->prox = NULL; // Insere o ponteiro para o proximo elemento (elemento nulo, pois nao aponta para nenhum elemento)
        *inicio = novo; // Se sim, atualiza o ponteiro para o inicio da lista para o novo no
    }

    // Nao é o primeiro elemento da lista? Adiciona o nó com base no parâmetro anterior
    else{
        No *aux = *inicio; // Cria um ponteiro auxiliar para percorrer a lista
        while(aux->valor != anterior && aux->prox != NULL){ // Enquanto o valor do auxiliar for diferente do anterior e o proximo elemento nao for nulo, percorre a lista
            aux = aux->prox; // Atualiza o ponteiro auxiliar para o proximo elemento
        }
        novo->prox = aux->prox; // Insere o ponteiro para o proximo elemento (elemento apontado pelo inicio da lista)
        aux->prox = novo; // Insere o ponteiro para o proximo elemento (elemento apontado pelo inicio da lista)
    }
}

// Procedimento (função) para imprimir a lista
void imprimir_lista(No *no){
    printf("\n\tLista: ");
    while(no != NULL){
        printf("%d ", no->valor); // Imprime o valor do no
        no = no->prox; // Atualiza o ponteiro para o proximo no
    }
    printf("\n\n");
}

// Lista duplamente encadeada
/* Em uma lista duplamente encadeada, cada elemento contém um ponteiro para o elemento anterior e um ponteiro para o próximo elemento da lista.*/

// Lista circular
/* Uma lista circular é uma lista simplesmente encadeada em que o ultimo elemento aponta para o primeiro elemento*/


int main(void) {

    int opcao=1, valor;
    No *lista=NULL;

    printf("\n\n\t***Lista simplesmente encadeada***\n\n");
    do{
        printf("\n\t1 - Inserir no inicio\n\t2 - Inserir no meio\n\t3 - Inserir no fim\n\t4 - Imprimir lista\n\t0 - Sair\n\n\tOpcao: ");
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                printf("\n\tDigite o valor a ser inserido: ");
                scanf("%d", &valor);
                inserir_no_inicio(&lista, valor);
                break;
            case 2:
                printf("\n\tDigite o valor a ser inserido: ");
                scanf("%d", &valor);
                int anterior;
                printf("\n\tDigite o elemento de referência a ser considerado como anterior: ");
                scanf("%d", &anterior);
                inserir_no_meio(&lista, valor, anterior);
                break;
            case 3:
                printf("\n\tDigite o valor a ser inserido: ");
                scanf("%d", &valor);
                inserir_no_fim(&lista, valor);
                break;
            case 4:
                imprimir_lista(lista);
                break;
            case 0:
                printf("\n\tSaindo...\n\n");
                break;
            default:
                printf("\n\tOpcao invalida\n");
                break;
        }

    } while(opcao != 0);



    return 0;
}