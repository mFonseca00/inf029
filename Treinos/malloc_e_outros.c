#include <stdio.h>
#include <stdlib.h>

int main(void) {

    //Malloc

    int *x = malloc(sizeof(int)); // aloca na memória o espaço indicado como parâmetro. retorna um ponteiro casa seja possível alocar e caso não, retorna NULL
    if(x == NULL){
        printf("Não foi possível alocar memória!");
    }
    else{
        printf("Memória alocada");
        *x=50;
        printf("&y = %p", x);
        printf("x = %d", *x);
    }

    //Calloc

    int *y = calloc(1, sizeof(int)); // funciona de maneria semelhante ao malloc, porém permite alocar para uma quantidade de elementos para alocação de memória (útil para arrays)
    if(y == NULL){
        printf("Não foi possível alocar memória!");
    }
    else{
        printf("Memória alocada");
        *y=50;
        printf("&y = %p", y);
        printf("y = %d", *y);
    }

    return 0;
}