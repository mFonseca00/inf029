#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // Varioáveis: armazenam dados
    // int, float, char, struct, etc
    // tipo_variável nome_variável
    int x = 10;

    // Ponteiros: armazenam endereços de memória
    //tipo_ponteiro *nome_ponteiro
    // int *x;

    // ponteiros são inicializados apontado para um lugar indefinido na memória
    // é possível inicializa-lo com o valor NULL para evitar lixo de memória
    int *p = NULL; // Está apontado para uma região da memória que não existe
    // Eles também podem ser inicializados apontando para um local específico na memória
    p = &x; // Está apontando para o endereço de memória da variável x (não está recebendo o valor da variável e sim o endereço dela na memória)

    printf("x = %d\n", x); // Imprime o valor da variável x 
    printf("&x = %p\n", &x); // Imprime o endereço de memória da variável x
    printf("p = %p\n", p); // Imprime o endereço de memória apontado pelo ponteiro (endereço de memória da variável x)
    printf("*p = %d\n", *p); // Imprime o valor apontado pelo ponteiro (desreferenciando o endereço de memória apontado pelo ponteiro)
    printf("\n");

    // Escrevendo no endereço apontado pelo ponteiro
    *p = 20; // Atribui o valor 20 ao endereço de memória apontado pelo ponteiro (modifica o valor da variável x de forma indireta)
    printf("x = %d\n", x); // Imprime o valor da variável x
    printf("p = %p\n", p); // Imprime o endereço de memória apontado pelo ponteiro (endereço de memória da variável x)
    printf("*p = %d\n", *p); // Imprime o valor apontado pelo ponteiro (desreferenciando o endereço de memória apontado pelo ponteiro)
    printf("\n");

    // Operações com ponteiros	

    // Ponteiros só podem receber o endereço de uma variável do mesmo tipo dele
    int *p1, *p2, y = 50;
    float z = 20.0;
    p1 = &y;
    printf("*p1 = %d\n", *p1);
    p2 = p1;
    printf("*p2 = %d\n", *p2);
    // p = &z; Não é uma operação possivel, pois z é do tipo float e p1 é do tipo int
    printf("\n");
    // Só é possivel realizar operações de soma e subtração com valores inteiros com ponteiros
    p2 = 0X5DC; //1500
    printf("p2 = %d\n", p2);
    p2++;
    printf("p2 = %d\n", p2);
    p2 -= 2;
    printf("p2 = %d\n", p2);
    // O resultado da operação varia de acordo com o tamanho do tipo do ponteiro
    char *p3 = 1600;
    printf("p3 = %d\n", p3);
    p3++;
    printf("p3 = %d\n", p3);
    // É possivel realizar operações de comparação entre ponteiros, comparando o endereço
    if(p3 > p2) {
        printf("p3 > p2\n");
    }
    printf("\n");
    
    // Ponteiros genéricos
    // Tipo especial de ponteiro que pode apontar para qualquer endereço de memória
    // void *nome_ponteiro
    void *p4;
    int i = 10, *pint;
    pint = &i;
    p4 = &i;
    printf("p4 = %p\n", p4);
    p4 = &pint;
    printf("p4 = %p\n", p4);
    p4 = pint;
    printf("p4 = %p\n", p4);
    // Antes de acessar o conteúdo de um ponteiro genérico, é necessário converte-lo para o tipo desejado. Sem isso, é considerado apenas um byte
    printf("conteúdo de pint = %d\n", *(int*)p4); // conversão para inteiro: (int*)p4 - para acessar os 4 primeiros bytes do ponteiro
    // O mesmo vale para as operações a serem realizadas

    // Ponteiros e Arrays
    int array[5]; // Um array é um ponteir que indica a primeira posição do conjunto de elementos
    int *point = array; // o ponteiro aponta para a posição do array
    for(int i=0; i<5; i++){
        printf("%d\n",p[i]); // aponta para cada posição do array, apontado pelo ponteiro (acessa o valor da posição referente ao array)
        printf("%d\n",*(p+i)); // também pode ser acessado desse modo (p é a posição inicial do array -  o * serve para desreferenciar o valor dentro do endereço apontado)
        printf("&p[i] = %d\n", &p[i]); //indica o endereço
        printf("&p[i] = %d\n", (p+i)); //indica o endereço
    }

    // Array de ponteiros
    int  *vetorPoint[5]; //array de ponteiros (este exemplo é um array com 5 ponteiros para inteiros)
    // ex de uso:
    int *coords[2];
    int x=10, y[2] = (20,30);
    coords[0]= &x;
    coords[1]=y;

    printf("coords[0]= %p\n", coords[0]); //&x
    printf("coords[1]= %p\n", coords[1]); //&y[0]

    printf("coords[0]= %p\n", *coords[0]); //x
    printf("coords[1][1]= %p\n", coords[1][1]); //y[1]

    //Ponteiro para ponteiro
    int num=10;
    int *pointer = &num;
    int **pPointer = &pointer;

    printf("pPointer = %d\n", pPointer); // &pointer
    printf("*pPointer = %d\n", *pPointer); // &num
    printf("**pPointer = %d\n", pPointer); // num (desreferencia duas vezes)


    return 0;
}