#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define maxTam 10 //Tamanho máximo do vetor de caracteres

typedef struct {
    int posAtual;
    char vetor[maxTam];
    int repeticoes[maxTam];
    char retorno[100];
    char caractereTrocado;
}vetorChar;

void inserirCaractere(vetorChar caracteres){
    if(caracteres.posAtual < maxTam){
        printf("Digite o caractere a ser adicionado no vetor: ");
        scanf("%c", &caracteres.vetor[caracteres.posAtual]);
        caracteres.posAtual++;
        strcpy(caracteres.retorno,"Caractere inserido\n");
    }
    else{
        strcpy(caracteres.retorno,"O caractere nao pode ser inserido\n");
    }
}

int trocarCaractere(vetorChar caracteres){
    char novo;
    printf("Informe o novo caractere, para realizar a troca: ");
    scanf("%c",&novo);
    for(int i=0; i < caracteres.posAtual+1; i++){
        if(caracteres.vetor[i]>novo){
            caracteres.caractereTrocado = caracteres.vetor[i];
            caracteres.vetor[i]=novo;
            strcpy(caracteres.retorno, "Caractere alterado\n");
            return 1;
        }
    }
    strcpy(caracteres.retorno, "O caractere nao pode ser alterado\n");
    return 0;
}

void removerCaractere(vetorChar caracteres){
    caracteres.posAtual--;
    strcpy(caracteres.retorno, "Caractere removido\n");
}

void listarCaracteres(vetorChar caracteres){
    printf("Lista de caracteres: ");
    for(int i=0; i < maxTam; i++){
        printf("%c",caracteres.vetor[i]);
        if(i<maxTam-1){
            printf(", ");
        }
    }
    printf("\n");
}

void listarDistintos(vetorChar caracteres){
    vetorChar Distintos;
    int contagem;
    Distintos.posAtual=0;

    for(int i=0; i < maxTam; i++){
        //Verificação se o caracter já se encontra listado como distinto
        bool naoListado=true;
        int listados = strlen(Distintos.vetor);
        for(int j=0; j<listados ;j++){
            if(caracteres.vetor[i]==Distintos.vetor[j]){
                naoListado=false;
            }
        }
        //Caso não esteja listado, contabilizar repetições no vetor base e adicionar como distinto
        if(naoListado){
            contagem=0;
            for(int j=0; j < maxTam; j++){
                if(caracteres.vetor[j]==caracteres.vetor[i]){
                    contagem++;
                }
            }
            Distintos.repeticoes[Distintos.posAtual] = contagem;
            Distintos.vetor[Distintos.posAtual]=caracteres.vetor[i];
            Distintos.posAtual++;
            Distintos.vetor[Distintos.posAtual]='\0';
        }
    }
    
    //Listagem do vetor contentdo todos os caracteres distintos
    printf("Lista de caracteres distintos: ");
    for(int i=0; i<Distintos.posAtual-1; i++){
        printf("%c: %d",Distintos.vetor[i],Distintos.repeticoes[i]);
        if(i<Distintos.posAtual-1){
            printf(", ");
        }
    }
    printf("\n");
}

int main(void){

    vetorChar caracteres;
    caracteres.posAtual=0;
    caracteres.vetor[1]='\0';
    int opcao=0;
    
    printf("Digite a opcao desejada:\n'1' - inserir caractere\n'2' - trocar caractere\n'3' - remover caracteres\n"
    "'4' - listar todos os caracteres\n'5' - listar caracteres distintos\n'6' - Sair\n");
    while(opcao!=6){
        scanf("%d",&opcao);
        switch (opcao){
            case 1:{
                inserirCaractere(caracteres);
                printf("%s",caracteres.retorno);
                break;
            }
            case 2:{
                int trocou = 0;
                trocou=trocarCaractere(caracteres);
                printf("%s",caracteres.retorno);
                if(trocou == 1){
                    printf("Caractere removido: %c", caracteres.caractereTrocado);
                }
                break;
            }
            case 3:{
                removerCaractere(caracteres);
                printf("%s",caracteres.retorno);
                break;
            }
            case 4:{
                listarCaracteres(caracteres);
                break;
            }
            case 5:{
                listarDistintos(caracteres);
                break;
            }
            case 6:{
                opcao = 6;
                break;
            }
            default:{
                printf("Opção inválida, tente novamente.\n");
                break;
            }
        }
    }

    return 0;
}
