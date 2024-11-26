#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define maxPessoas  3
#define tamData 11

typedef struct pessoa{
    char nome[50];
    int idade;
}pessoa;

void lerDados(pessoa pessoas[]){
    for(int i=0; i<maxPessoas; i++){
        printf("Digite o nome da %d pessoa: ", i+1);
        fgets(pessoas[i].nome,50,stdin);
        printf("Digite a idade da %d pessoa: ", i+1);
        scanf("%d",&pessoas[i].idade);
        getchar();// limpando buffer
    }
}

void imprimirDados(pessoa pessoas[]){
    //ordenação de menor para maior idade (selection sort)
    for(int i=0; i<maxPessoas-1; i++){
        int menorIdx = i;
        for(int j = i+1; j<maxPessoas; j++){
            if(pessoas[j].idade < pessoas[menorIdx].idade){
                menorIdx = j;
            }
        }
        pessoa temp = pessoas[i];
        pessoas[i] = pessoas[menorIdx];
        pessoas[menorIdx] = temp;
    }

    //impressão das pessoas
    for(int i=0; i < maxPessoas; i++){
        printf("Nome: %s | Idade: %d", pessoas[i].nome, pessoas[i].idade);
    }
}

void inverterData(char dataOriginal[], char dataInvertida[]){
    int len = tamData-1;
    for(int i = 0; i < len; i++){
        dataInvertida[(len-1)-i] = dataOriginal[i];
    }
    dataInvertida[tamData] = '\0';
}

int main(void){
    
    setlocale(LC_ALL, "portuguese");

    // Q1
    // pessoa pessoas[maxPessoas];
    // lerDados(pessoas);
    // imprimirDados(pessoas);

    // Q2
    // char dataOriginal[tamData], dataInvertida[tamData];
    // inverterData(dataOriginal,dataInvertida);
    // printf("Data Original: %s | Data Invertida: %s", dataOriginal, dataInvertida);

    // Q3
    




    return 0;
}
