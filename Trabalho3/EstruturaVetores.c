#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#define TAM 10

#include "EstruturaVetores.h"

//estrutura para armazenar cada estrutura auxiliar, a posição atual a ser escrita e seu tamanho total
typedef struct estrutura{ 
    int *vet;
    int posAtual;
    int tamanho;
}estrutura;

estrutura *vetorPrincipal;//vetor de ponteiro que aponta para as estruturas auxiliares

/*
Objetivo: inicializa o programa. deve ser chamado ao inicio do programa 
*/
void inicializar()
{
    const char *save = "dados.txt"; // ponteiro para armazenar o nome do arquivo
    FILE *fp; // ponteiro para apontar para o arquivo
    fp = fopen(save, "r"); // Abre o arquivo no modo leitura para verificar se existe
    if(fp == NULL){
        printf("Arquivo '%s' não encontrado. Criando um novo arquivo.\n", save);
        fopen(save, "w"); // Abre o arquivo no modo escrita para criar ele
        if (fp == NULL) {
            perror("Erro ao criar o arquivo");
            return 1;
        }
        printf("Arquivo '%s' criado com sucesso.\n", save);
    }
    fclose(fp); // Fecha o arquivo aberto

    vetorPrincipal = malloc(sizeof(estrutura) * TAM); // Aloca o espaço de memória para o vetor principal

    // Inicializa todos os ponteiros de estruturas auxiliares com estruturas vazias (NULL), a posição atual com 0 (inicial) e o tamanho com 0 (já que ainda não foi alocada)
    for(int i = 0; i < TAM; i++){
        vetorPrincipal[i].vet = NULL;
        vetorPrincipal[i].posAtual = 0;
        vetorPrincipal[i].tamanho = 0;
    }

    lerArquivo(save);
}

// Função para trocar dois elementos de posição em um vetor
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Função para particionar o vetor
int partition(int arr[], int low, int high) {
    // Escolhe o último elemento como pivô
    int pivot = arr[high];
    
    // Índice do menor elemento
    int i = (low - 1);

    // Percorre o vetor, comparando cada elemento com o pivô
    for (int j = low; j <= high - 1; j++) {
        // Se o elemento atual for menor ou igual ao pivô
        if (arr[j] <= pivot) {
            i++; // Incrementa o índice do menor elemento
            swap(&arr[i], &arr[j]); // Troca o elemento atual com o elemento do índice do menor
        }
    }
    // Troca o pivô com o elemento do índice do menor
    swap(&arr[i + 1], &arr[high]); 
    return (i + 1); // Retorna o índice do pivô
}

// Função principal do Quicksort (recursiva)
void quickSort(int arr[], int low, int high) {
    // Verifica se o índice baixo é menor que o índice alto para evitar chamadas recursivas desnecessárias
    if (low < high) {
        // Encontra o índice do pivô, elementos menores que o pivô são movidos para a esquerda, e os maiores para a direita
        int pi = partition(arr, low, high);

        // Ordena recursivamente os elementos antes e depois do pivô
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

/*
Objetivo: criar estrutura auxiliar na posição 'posicao'.
com tamanho 'tamanho'
Rertono (int)
    SUCESSO - criado com sucesso
    JA_TEM_ESTRUTURA_AUXILIAR - já tem estrutura na posição
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    SEM_ESPACO_DE_MEMORIA - Sem espaço de memória
    TAMANHO_INVALIDO - o tamanho deve ser maior ou igual a 1
*/
int criarEstruturaAuxiliar(int posicao, int tamanho)
{
    // Verifica se a posição é válida (entre 1 e 10)
    if(posicao < 1 || posicao > 10){
        return POSICAO_INVALIDA;
    }

    // Verifica se o tamanho é válido (>= 1)
    if(tamanho < 1){
        return TAMANHO_INVALIDO;
    }
    
    // Verifica no vetor principal se a posição já está ocupada
    if(vetorPrincipal[posicao-1].vet != NULL){
        return JA_TEM_ESTRUTURA_AUXILIAR;
    }

    // Aloca o espaço de memória
    vetorPrincipal[posicao-1].vet = malloc(sizeof(int) * tamanho);

    // Verifica se o tamanho é muito grande (capacidade da memória) - se não for possível alocar, o retorno de malloc será NULL
    if(vetorPrincipal[posicao-1].vet == NULL){
        // printf("Sem espaco de memoria\n"); // DEBUG
        return SEM_ESPACO_DE_MEMORIA;
    }

    vetorPrincipal[posicao-1].posAtual = 0;
    vetorPrincipal[posicao-1].tamanho = tamanho;
   
    return SUCESSO;
}

/*
Objetivo: inserir número 'valor' em estrutura auxiliar da posição 'posicao'
Rertono (int)
    SUCESSO - inserido com sucesso
    SEM_ESPACO - não tem espaço
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
CONSTANTES
*/
int inserirNumeroEmEstrutura(int posicao, int valor)
{
    if (posicao < 1 || posicao > 10){
        // printf("Posição inválida\n"); //Debug
        return POSICAO_INVALIDA;
    }
    else
    {
        // testar se existe estrutura auxiliar na posição informada
        if (vetorPrincipal[posicao - 1].vet != NULL)
        {
            // testar se a estrutura auxiliar tem espaço para inserir
            if(vetorPrincipal[posicao - 1].posAtual == vetorPrincipal[posicao - 1].tamanho)
            {
                // printf("Sem espaco disponivel na posicao %d da estrutura principal\n", posicao); //Debug
                return SEM_ESPACO;
            }

            else // caso haja espaco, insere o valor na posição atual da estrutura auxilixar
            {
                // printf("inserindo %d na posicao %d da estrutura principal...\n", valor, posicao); //Debug
                vetorPrincipal[posicao - 1].vet[vetorPrincipal[posicao - 1].posAtual] = valor;
                // printf("Valor %d inserido com sucesso na posicao %d da estrutura principal\n",*(vetorPrincipal[posicao - 1].vet + vetorPrincipal[posicao - 1].posAtual), posicao); //Debug
                vetorPrincipal[posicao - 1].posAtual++;
                return SUCESSO;
            }
        }
        else
        {
            // printf("Nao ha estrutura auxiliar na posicao %d\n", posicao); //Debug
            return SEM_ESTRUTURA_AUXILIAR;
        }
    }
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar no final da estrutura.
ex: suponha os valores [3, 8, 7, 9,  ,  ]. Após excluir, a estrutura deve ficar da seguinte forma [3, 8, 7,  ,  ,  ].
Obs. Esta é uma exclusão lógica

Rertono (int)
    SUCESSO - excluido com sucesso
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int excluirNumeroDoFinaldaEstrutura(int posicao)
{
    if(posicao < 1 || posicao > 10){
        // printf("Posicao invalida\n"); //Debug
        return POSICAO_INVALIDA;
    }

    if(vetorPrincipal[posicao-1].vet == NULL){
        // printf("Nao ha estrutura auxiliar na posicao %d\n", posicao); //Debug
        return SEM_ESTRUTURA_AUXILIAR;
    }

    if(vetorPrincipal[posicao-1].posAtual == 0){
        // printf("Estrutura auxiliar vazia\n"); //Debug
        return ESTRUTURA_AUXILIAR_VAZIA;
    }  

    // printf("Excluindo %d...\n", vetorPrincipal[posicao-1].vet[vetorPrincipal[posicao-1].posAtual-1]);  //Debug
    vetorPrincipal[posicao-1].posAtual--;

    return SUCESSO;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar da posição 'posicao'.
Caso seja excluido, os números posteriores devem ser movidos para as posições anteriores
ex: suponha os valores [3, 8, 7, 9,  ,  ] onde deve ser excluido o valor 8. A estrutura deve ficar da seguinte forma [3, 7, 9,  ,  ,  ]
Obs. Esta é uma exclusão lógica
Rertono (int)
    SUCESSO - excluido com sucesso 'valor' da estrutura na posição 'posicao'
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    NUMERO_INEXISTENTE - Número não existe
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar

*/
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor)
{
    if(posicao < 1 || posicao > 10){
        // printf("Posicao invalida\n"); //Debug
        return POSICAO_INVALIDA;
    }

    if(vetorPrincipal[posicao-1].vet == NULL){
        // printf("Nao ha estrutura auxiliar na posicao %d\n", posicao); //Debug
        return SEM_ESTRUTURA_AUXILIAR;
    }

    if(vetorPrincipal[posicao-1].posAtual == 0){    
        // printf("Estrutura auxiliar vazia\n"); //Debug
        return ESTRUTURA_AUXILIAR_VAZIA;
    }

    // Mover o valor para o final da estrutura auxiliar

    int busca = 0;
    bool encontrou = false;

    for(busca = 0; busca < vetorPrincipal[posicao-1].posAtual; busca++){
        if(vetorPrincipal[posicao-1].vet[busca] == valor){ // Busca a primeira ocorrência do valor na estrutura auxiliar
            vetorPrincipal[posicao-1].vet[vetorPrincipal[posicao-1].posAtual] = vetorPrincipal[posicao-1].vet[busca]; // Move o valor para o final da estrutura auxiliar
            encontrou = true;
            break; // Para a busca
        }
    }

    if(!encontrou){
        // printf("Valor nao encontrado\n"); //Debug
        return NUMERO_INEXISTENTE;
    }
    else{
        for(int i = busca; i < vetorPrincipal[posicao-1].posAtual; i++){
        vetorPrincipal[posicao-1].vet[i] = vetorPrincipal[posicao-1].vet[i+1]; // Move os demais valores para a trás, rearranjando a estrutura auxiliar a partir da posição onde foi encontrado o valor
        }

        // Excluir ultimo valor (valor buscado e movido para o final da estrutura auxiliar)
        vetorPrincipal[posicao-1].posAtual--;
        return SUCESSO;
    }  
}

/*
Objetivo: retorna os números da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Retorno (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    if(posicao < 1 || posicao > 10){
        // printf("Posicao invalida\n"); //Debug
        return POSICAO_INVALIDA;
    }

    if(vetorPrincipal[posicao-1].vet == NULL){
        // printf("Nao ha estrutura auxiliar na posicao %d\n", posicao); //Debug
        return SEM_ESTRUTURA_AUXILIAR;
    }
    
    // printf("\nListando dados da estrutura auxiliar da posicao %d\n", posicao); //Debug
    // Copia os dados da estrutura auxiliar para o vetorAux
    for(int i = 0; i < vetorPrincipal[posicao-1].posAtual; i++){
        vetorAux[i] = vetorPrincipal[posicao-1].vet[i];
        // printf("%d\t", vetorAux[i]); //Debug
    }
    // printf("\n\n"); //Debug
    return SUCESSO;
}

/*
Objetivo: retorna os números ordenados da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao (1..10)'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    if(posicao < 1 || posicao > 10){
        // printf("Posicao invalida\n"); //Debug
        return POSICAO_INVALIDA;
    }

    if(vetorPrincipal[posicao-1].vet == NULL){
        // printf("Nao ha estrutura auxiliar na posicao %d\n", posicao); //Debug
        return SEM_ESTRUTURA_AUXILIAR;
    }

    // printf("\nListando dados da estrutura auxiliar da posicao %d em ordem crescente \n", posicao); //Debug
    // Copia os dados da estrutura auxiliar para o vetorAux
    for(int i = 0; i < vetorPrincipal[posicao-1].posAtual; i++){
        vetorAux[i] = vetorPrincipal[posicao-1].vet[i];
        // printf("%d\t", vetorAux[i]); //Debug
    }

    // Ordena o vetorAux
    quickSort(vetorAux, 0, vetorPrincipal[posicao-1].posAtual-1);

    return SUCESSO;
}

/*
Objetivo: retorna os números de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int contaVazias = 0; // contabiliza o número de estruturas auxiliares vazias
    int elemento = 0; // contabiliza o número de elementos armazenados no vetorAux
    
    for(int i = 0; i < TAM; i++){ // Varre o vetor principal
        if(vetorPrincipal[i].posAtual == 0){
                contaVazias++;
                // printf("Estrutura auxiliar %d vazia\n", i+1); // Debug
                continue;
            }
        // printf("\nListando dados da estrutura auxiliar %d\n", i+1); // Debug
        int j = 0;
        for(j = 0; j < vetorPrincipal[i].posAtual; j++){// varre cada estrutura auxiliar
            vetorAux[j + elemento] = vetorPrincipal[i].vet[j]; // Copia os dados da estrutura auxiliar para o vetorAux
            // printf("%d\t", vetorAux[j + elemento]); // Debug
        }
        // printf("\n\n"); // Debug
        elemento += j; // Incrementa o número de elementos armazenados no vetorAux para próxima inserção (próxima estrutura auxiliar)
    }  
    if(contaVazias == TAM){
        // printf("Todas as estruturas auxiliares estao vazias\n"); // Debug
        return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;    
    }
    else{
        return SUCESSO;
    }
}

/*
Objetivo: retorna os números ordenados de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int contaVazias = 0; // contabiliza o número de estruturas auxiliares vazias
    int elemento = 0; // contabiliza o número de elementos armazenados no vetorAux
    
    for(int i = 0; i < TAM; i++){ // Varre o vetor principal
        if(vetorPrincipal[i].posAtual == 0){
                contaVazias++;
                // printf("Estrutura auxiliar %d vazia\n", i+1); // Debug
                continue;
            }
        // printf("\nListando dados da estrutura auxiliar %d\n", i+1); // Debug
        int j = 0;
        for(j = 0; j < vetorPrincipal[i].posAtual; j++){// varre cada estrutura auxiliar
            vetorAux[j + elemento] = vetorPrincipal[i].vet[j]; // Copia os dados da estrutura auxiliar para o vetorAux
            // printf("%d\t", vetorAux[j + elemento]); // Debug
        }
        // printf("\n\n"); // Debug
        elemento += j; // Incrementa o número de elementos armazenados no vetorAux para próxima inserção (próxima estrutura auxiliar)
    }  
    if(contaVazias == TAM){
        // printf("Todas as estruturas auxiliares estao vazias\n"); // Debug
        return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;    
    }
    else{
        // printf("Ordenando dados das estruturas auxiliares\n"); // Debug
        quickSort(vetorAux, 0, elemento - 1);
        return SUCESSO;
    }
}

/*
Objetivo: modificar o tamanho da estrutura auxiliar da posição 'posicao' para o novo tamanho 'novoTamanho' + tamanho atual
Suponha o tamanho inicial = x, e novo tamanho = n. O tamanho resultante deve ser x + n. Sendo que x + n deve ser sempre >= 1

Rertono (int)
    SUCESSO - foi modificado corretamente o tamanho da estrutura auxiliar
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    NOVO_TAMANHO_INVALIDO - novo tamanho não pode ser negativo
    SEM_ESPACO_DE_MEMORIA - erro na alocação do novo valor
*/
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho) // concluir
{
    if(posicao < 1 || posicao > TAM){
        return POSICAO_INVALIDA;
    }

    if(vetorPrincipal[posicao-1].vet == NULL){
        return SEM_ESTRUTURA_AUXILIAR;
    }

    int tamNovo = vetorPrincipal[posicao-1].tamanho + novoTamanho; // Calcula o novo tamanho
    // printf("Novo tamanho: %d\n", tamNovo); // Debug

    if(tamNovo < 1){
        return NOVO_TAMANHO_INVALIDO;
    }

    vetorPrincipal[posicao-1].tamanho = tamNovo; // Atualiza o tamanho registrado para estrutura auxiliar
    vetorPrincipal[posicao-1].vet = realloc(vetorPrincipal[posicao-1].vet, sizeof(int) * vetorPrincipal[posicao-1].tamanho); // Realoca o espaço de memória para o novo tamanho
    while(vetorPrincipal[posicao-1].posAtual > vetorPrincipal[posicao-1].tamanho){ // Garante que os elementos preenchidos além do novo tamanho da estrutura auxiliar sejam desconsiderados
        vetorPrincipal[posicao-1].posAtual--;
    }
    
    if(vetorPrincipal[posicao-1].vet == NULL){
        return SEM_ESPACO_DE_MEMORIA;
    }

    return SUCESSO;
}

/*
Objetivo: retorna a quantidade de elementos preenchidos da estrutura auxiliar da posição 'posicao'.

Retorno (int)
    POSICAO_INVALIDA - posição inválida
    SEM_ESTRUTURA_AUXILIAR - sem estrutura auxiliar
    ESTRUTURA_AUXILIAR_VAZIA - estrutura auxiliar vazia
    Um número int > 0 correpondente a quantidade de elementos preenchidos da estrutura
*/
int getQuantidadeElementosEstruturaAuxiliar(int posicao)
{
    if(posicao < 1 || posicao > TAM){
        return POSICAO_INVALIDA;
    }

    if(vetorPrincipal[posicao-1].vet == NULL){
        return SEM_ESTRUTURA_AUXILIAR;
    }

    if(vetorPrincipal[posicao-1].posAtual == 0){
        return ESTRUTURA_AUXILIAR_VAZIA;
    }
    
    // printf("Quantidade de elementos: %d\n", vetorPrincipal[posicao-1].posAtual); // Debug
    return vetorPrincipal[posicao-1].posAtual;
}

// Fução para inserir no fim da lista encadeada com cabeçote
void inserir_no_fim(No **cabecote, int valor){
    No *novo = (No*)malloc(sizeof(No));// Aloca memória para o novo no
    if(novo == NULL){
        printf("Erro ao alocar memória\n");
        return;
    }

    novo->conteudo = valor; // Insere o valor
    novo->prox = NULL; // Insere o ponteiro para o proximo elemento (elemento nulo, pois será o ultimo elemento)

    // É o primeiro elemento da lista? Adiciona o nó como o inicio da lista
    if((*cabecote) == NULL){
        (*cabecote) = novo; // Atualiza o ponteiro para o inicio da lista para o novo nó (cabeçote aponta para nó criado)
        return;
    }

    // Nao é o primeiro elemento da lista? Adiciona o nó como ultimo elemento da lista
    else{
        No *aux = *cabecote; // Cria um ponteiro auxiliar para percorrer a lista
        while(aux->prox != NULL){ // Enquanto o proximo elemento nao for nulo, percorre a lista
            aux = aux->prox; // Atualiza o ponteiro auxiliar para o proximo elemento
        }
        aux->prox = novo; // Insere o ponteiro para o proximo elemento (elemento criado)
        return;
    }
}

/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes em todas as estruturas.

Retorno (No*)
    NULL, caso não tenha nenhum número nas listas
    No*, ponteiro para o início da lista com cabeçote
*/
No *montarListaEncadeadaComCabecote()
{
    No *cabecote = NULL; // Inicializa o cabeçote como NULL, caso não encontre nenhum elemento, irá retornar NULL

    // Criando cabeçote
    cabecote = (No*)malloc(sizeof(No));
    if(cabecote == NULL){
        printf("Erro ao alocar memória\n");
        return NULL;
    }
    cabecote->prox = NULL;
    cabecote->conteudo = -1;

    // Percorrendo as estruturas auxiliares
    for(int i = 0; i < TAM; i++){
        if(vetorPrincipal[i].vet != NULL){ // Verifica se existe um vetor auxiliar nessa posição
            for(int j = 0; j < vetorPrincipal[i].posAtual; j++){ // Percorre o vetor auxiliar
                inserir_no_fim(&cabecote, vetorPrincipal[i].vet[j]); // Insere o elemento no fim da lista
            }
        }
    }
    return cabecote;
}

/*
Objetivo: retorna os números da lista enceada com cabeçote armazenando em vetorAux.
Retorno void
*/
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[]) // (Listagem dos elementos da lista montada com cabeçote)
{
    int i = 0;
    No *aux = inicio->prox; // Inicializa a variável auxiliar para percorrer a lista encadeada desconsiderando o cabeçote
    while(aux != NULL){ // Enquanto o elemento da lista nao apontar para NULL
        vetorAux[i] = aux->conteudo; // Insere o elemento no vetor
        aux = aux->prox; // Atualiza o ponteiro auxiliar para o proximo elemento
        i++;
    }
}

/*
Objetivo: Destruir a lista encadeada com cabeçote a partir de início.
O ponteiro inicio deve ficar com NULL.

Retorno 
    void.
*/
void destruirListaEncadeadaComCabecote(No **inicio)
{
    No *aux = *inicio; // Cria um ponteiro auxiliar para percorrer a lista
    while(aux != NULL){ // Enquanto o ponteiro auxiliar nao for nulo, percorre a lista
        No *temp = aux; // Cria um ponteiro auxiliar para armazenar o ponteiro auxiliar atual
        aux = aux->prox; // Atualiza o ponteiro auxiliar para o proximo elemento
        free(temp); // Libera a memória do ponteiro auxiliar
    }
    *inicio = NULL; // Atualiza o ponteiro para o inicio da lista para NULL (não existe nenhum elemento na lista)
}

/* 
Objetivo: Funções para a leitura e escrita no 
arquivo de salvamento das estruturas

Retorno
    -2  -ERRO na leitura
    -1  -ERRO ao abrir
    0   -Nenhum valor registrado (estrutura principal vazia)
    1   -Sucesso na operação

*/

//VERIFICAR SE DEVE SER USADO . ou -> (estou usando . , cnoforme funções anteriores)

int lerArquivo(const char *filename){ //Main não esta lendo - aparentemente não esta criando as estruturas auxiliares
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo para leitura\n");
        return -1;
    }

    int index, qtdElementos, tamanho, valor, retAux;

    while (fscanf(fp, "%d %d %d", &index, &qtdElementos, &tamanho)==3){
        index++;
        if(index<0 || index>TAM){
            printf("Índice inválido\n"); // DEBUG
            fclose(fp);
            return -2;
        }

        // Criação da estrutura auxiliar do atual index
        if(tamanho>0){ //add
            printf("Criando estrutura auxiliar com tamanho %d na posição %d...\n", tamanho, index); // DEBUG
            retAux = criarEstruturaAuxiliar(index, tamanho);//incrementando 1 no index, criou
            if(retAux != SUCESSO){ // Verifica se a estrutura auxiliar foi criada com sucesso
                printf("Erro ao criar estrutura auxiliar: \t"); // DEBUG
                if(retAux == JA_TEM_ESTRUTURA_AUXILIAR){
                    printf("já tem estrutura na posição\n");
                }
                else if(retAux == POSICAO_INVALIDA){
                    printf("Posição inválida para estrutura auxiliar\n");
                }
                else if(retAux == SEM_ESPACO_DE_MEMORIA){
                    printf("Sem espaço de memória\n");
                }
                else if(retAux == TAMANHO_INVALIDO){
                    printf("o tamanho deve ser maior ou igual a 1\n");
                }
            }
            // Salvando valores do atual index na estrutura auxiliar
            if(qtdElementos>0){
                printf("Inserindo %d elementos na estrutura auxiliar da posição %d...\n", qtdElementos, index); // DEBUG
                for(int i=0; i<qtdElementos;i++){
                    if(fscanf(fp, "%d",&valor) != 1){ // Verifica se foi armazenado o valor
                        printf("Erro ao ler %d° valor da estrutura auxiliar de posição %d\n", i, index); // DEBUG
                    }
                    retAux = inserirNumeroEmEstrutura(index, valor);
                    if(retAux != SUCESSO){ // Verifica se o valor foi inserido
                        printf("Erro ao inserir %d° valor (%d) na estrutura auxiliar de posição %d\n", i, valor, index); // DEBUG
                    }
                }
            }
            else{
                printf("Não há elementos para inserir na estrutura auxiliar.\n"); // DEBUG
            }
        }

        
    }

    fclose(fp);

    return 1;

}

int salvarArquivo(const char *filename){
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo para escrita\n");
        return -1;
    }

    int cont=0;

    for(int i=0; i<TAM; i++){ // Varre o array da estrutura principal
        // if(vetorPrincipal[i]!=NULL){
            fprintf(fp, "%d %d %d ", i, vetorPrincipal[i].posAtual, vetorPrincipal[i].tamanho); // registra a posição da estrutura auxiliar, a quantidade de elementos e o tamanho dela
            for(int j=0; j<vetorPrincipal[i].posAtual; j++){ // Varre cada estrutura auxiliar
                fprintf(fp, "%d ", vetorPrincipal[i].vet[j]); // Salva os valores presentes na estrutura auxiliar
            }
            fprintf(fp,"\n");
            cont++;
        // }
    }
    if(cont==0){ // Verifica se algo foi salvo no arquivo
        printf("Nenhum valor foi registrado, estrutura principal vazia\n"); // DEBUG
        return 0;
    }
    
    printf("Valores registrados\n"); // DEBUG
    fclose(fp);

    return 1;
}

/*
Objetivo: finaliza o programa. deve ser chamado ao final do programa 
para poder liberar todos os espaços de memória das estruturas auxiliares.
*/
void finalizar()
{
    // ***Salvamento dos dados no arquivo***
    ret = salvarArquivo(save);
    if(ret == 1){
        printf("Arquivo salvo com sucesso\n");
    }
    else{
        printf("Erro ao salvar\n");
    }

    for(int i = 0; i < TAM; i++){
        if(vetorPrincipal[i].vet != NULL){
            free(vetorPrincipal[i].vet); // Libera a memória do vetor auxiliar
            vetorPrincipal[i].vet = NULL; // Atualiza o ponteiro para o vetor auxiliar para NULL
        }
    }
    free(vetorPrincipal); // Libera a memória do vetor principal
    vetorPrincipal = NULL; // Atualiza o ponteiro para o vetor principal para NULL
}