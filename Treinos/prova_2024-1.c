#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define maxPessoas = 3;

typedef struct pessoa{
    char nome[50];
    int idade;
}pessoa;

void lerDados(pessoa pessoas[maxPessoas]){
    for(int i=0; i<maxPessoas; i++){
        printf("Digite o nome da %d pessoa: ", i+1);
        fgets(pessoas[i].nome,50,stdin);
        printf("Digite a idade da %d pessoa: ", i+1);
        scanf("%d",&pessoas[i].idade);
    }
}

void impirmirDados(pessoa pessoas)
