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
    vetorPrincipal = malloc(sizeof(estrutura) * TAM);

    // Inicializa todos os ponteiros de estruturas auxiliares com estruturas vazias
    for(int i = 0; i < TAM; i++){
        vetorPrincipal[i].vet = NULL;
        vetorPrincipal[i].posAtual = 0;
        vetorPrincipal[i].tamanho = 0;
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
    // Mover o valor para o final da estrutura auxiliar

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
        // Excluir ultimo valor
        vetorPrincipal[posicao-1].posAtual--;
        return SUCESSO;
    }  
}

// // se posição é um valor válido {entre 1 e 10}
// int ehPosicaoValida(int posicao)
// {
//     int retorno = 0;
//     if (posicao < 1 || posicao > 10)
//     {
//         retorno = POSICAO_INVALIDA;
//     }
//     else
//         retorno = SUCESSO;

//     return retorno;
// }
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

    int retorno = 0;

    return retorno;
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

    int retorno = 0;

    
    return retorno;
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

    int retorno = 0;
    return retorno;
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

    int retorno = 0;
    return retorno;
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
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho)
{

    int retorno = 0;
    return retorno;
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

    int retorno = 0;

    return retorno;
}

/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes em todas as estruturas.

Retorno (No*)
    NULL, caso não tenha nenhum número nas listas
    No*, ponteiro para o início da lista com cabeçote
*/
No *montarListaEncadeadaComCabecote()
{

    return NULL;
}

/*
Objetivo: retorna os números da lista enceada com cabeçote armazenando em vetorAux.
Retorno void
*/
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[])
{

}

/*
Objetivo: Destruir a lista encadeada com cabeçote a partir de início.
O ponteiro inicio deve ficar com NULL.

Retorno 
    void.
*/
void destruirListaEncadeadaComCabecote(No **inicio)
{

}

/*
Objetivo: finaliza o programa. deve ser chamado ao final do programa 
para poder liberar todos os espaços de memória das estruturas auxiliares.
*/
void finalizar()
{

}