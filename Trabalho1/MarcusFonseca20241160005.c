// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  Cada aluno deve renomear esse arquivo para Aluno<MATRICULA>.c
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome: Marcus Vinicius Silva da Fonseca
//  email: mv070900@gmail.com
//  Matrícula: 20241160005
//  Semestre: 2024.2

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016

// #################################################

#include <stdio.h>
#include "MarcusFonseca20241160005.h" // Substitua pelo seu arquivo de header renomeado
#include <stdlib.h>
#include <string.h>

DataQuebrada quebraData(char data[]);



int verificarBissexto(int ano){ // função utilizada para verificar se ano informado é bissexto
    if(ano<100){//testa se o ano tem dois dígitos
        ano = ano+2000;
    }
    if((ano%4==0 && ano%100!=0) || ano%400==0){
        return 1;   //retorna 1 se o ano é bissexto
    }
    else{
        return 0;   //retorna 0 se o ano não é bissexto
    }
}

// Função para contabilizar o número de dias em um mês considerando anos bissextos
int diasNoMes(int mes, int ano){
    if(mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12){
        return 31;
    }
    else if(mes == 4 || mes == 6 || mes == 9 || mes == 11){
        return 30;
    }
    else if(mes == 2 && verificarBissexto(ano)==1){
        return 29;
    }
    else if(mes == 2 && verificarBissexto(ano)==0){
        return 28;
    }
    else{
        return 0;
    }
}


/*
## função utilizada para testes  ##

 somar = somar dois valores
@objetivo
    Somar dois valores x e y e retonar o resultado da soma
@entrada
    dois inteiros x e y
@saida
    resultado da soma (x + y)
 */
int somar(int x, int y)
{
    int soma;
    soma = x + y;
    return soma;
}

/*
## função utilizada para testes  ##

 fatorial = fatorial de um número
@objetivo
    calcular o fatorial de um número
@entrada
    um inteiro x
@saida
    fatorial de x -> x!
 */
int fatorial(int x)
{ //função utilizada para testes
    int i, fat = 1;

    for (i = x; i > 1; i--)
        fat = fat * i;

    return fat;
}

int teste(int a)
{
    int val;
    if (a == 2)
        val = 3;
    else
        val = 4;

    return val;
}

/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa,
    onde dd = dia, mm = mês, e aaaa, igual ao ano.
    dd em mm podem ter apenas um digito, e aaaa podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
 @restrições
    Não utilizar funções próprias de string (ex: strtok)   
    pode utilizar strlen para pegar o tamanho da string
 */
int q1(char data[])
{
    int datavalida = 0;
    //quebrar a string data em strings sDia, sMes, sAno
    DataQuebrada dataq; //variável tipo DataQuebrada que irá armazenar os valores separados
    if(strlen(data) <= 10){ //testa se o tamanho da string e menor ou igual a 10 (máximo tamanho para a data conforme enunciado)
        dataq = quebraData(data); //chamada da função quebraData que veio pronta no código para quebrar data em dia, mês e ano
        if(dataq.valido == 1 && dataq.iMes >= 1 && dataq.iMes <= 12){ //testa se a data é valida após função de quebrar data

            int bissexto = verificarBissexto(dataq.iAno);    //verifica se o ano é bissexto

            if((dataq.iMes == 1 || dataq.iMes == 3 || dataq.iMes == 5 || dataq.iMes == 7 || dataq.iMes == 8 || dataq.iMes == 10 || dataq.iMes == 12) && dataq.iDia >= 1 && dataq .iDia <= 31){
                datavalida = 1;
            }
            else if((dataq.iMes == 4 || dataq.iMes == 6 || dataq.iMes == 9 || dataq.iMes == 11) && dataq.iDia >= 1 && dataq .iDia <= 30){
                datavalida = 1;
            }
            else if(bissexto == 0 && dataq.iMes == 2 && dataq.iDia >= 1 && dataq .iDia <= 28){
                datavalida = 1;
            }
            else if(bissexto == 1 && dataq.iMes == 2 && dataq.iDia >= 1 && dataq .iDia <= 29){
                datavalida = 1;
            }
        }
        else{
            datavalida = 0;
        }
    }

    // printf("%s\n", data);

    if (datavalida)
        return 1;
    else
        return 0;
}



/*
 Q2 = diferença entre duas datas
 @objetivo
    Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
    uma string datainicial, uma string datafinal. 
 @saida
    Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis valores abaixo
    1 -> cálculo de diferença realizado com sucesso
    2 -> datainicial inválida
    3 -> datafinal inválida
    4 -> datainicial > datafinal
    Caso o cálculo esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos com os valores correspondentes.
 */
DiasMesesAnos q2(char datainicial[], char datafinal[])
{

    //calcule os dados e armazene nas três variáveis a seguir
    DiasMesesAnos dma;

    //inicialização dos campos da estrutura DiasMesesAnos com zero
    dma.qtdAnos = 0;
    dma.qtdMeses = 0;
    dma.qtdDias = 0;

    if (q1(datainicial) == 0){
        dma.retorno = 2;
        return dma;
    }else if (q1(datafinal) == 0){
        dma.retorno = 3;
        return dma;
    }else{
        DataQuebrada Final, Inicial; //variáveis tipo DataQuebrada que irão armazenar os valores separados
        Inicial = quebraData(datainicial); //chamada da função quebraData para quebrar data em dia, mês e ano
        Final = quebraData(datafinal); //chamada da função quebraData para quebrar data em dia, mês e ano
        //verificando se a data final não é menor que a data inicial
        
        if(Final.iAno < Inicial.iAno || ( Final.iAno == Inicial.iAno && Final.iMes < Inicial.iMes) || ( Final.iAno == Inicial.iAno && Final.iMes == Inicial.iMes && Final.iDia < Inicial.iDia )){
            dma.retorno = 4;
            return dma;
        }
            
        else{//calculando a distancia entre as datas
            dma.retorno=1;
            
            // Verifica a diferença entre os anos
            dma.qtdAnos = Final.iAno - Inicial.iAno;

            //Verifica a diferença de meses
            dma.qtdMeses = Final.iMes - Inicial.iMes;
            if(dma.qtdMeses<0){ // casos em que a diferença resulta em menos de um ano
                dma.qtdMeses += 12;
                dma.qtdAnos--;
            }

            //Verifica a quantidade de dias
            dma.qtdDias = Final.iDia - Inicial.iDia;
            if(dma.qtdDias<0){
                dma.qtdDias += diasNoMes(Inicial.iMes, Inicial.iAno);
                if(verificarBissexto(Inicial.iAno) && Inicial.iMes==2){
                    dma.qtdDias--;//verificar
                }
                dma.qtdMeses--;
            }
            if(((verificarBissexto(Inicial.iAno) && Inicial.iMes == 1) || 
                (verificarBissexto(Inicial.iAno) && Inicial.iMes == 2 && Inicial.iDia == 29)) &&
                ((Inicial.iAno == Final.iAno && Final.iMes !=2) ||
                (Inicial.iAno < Final.iAno && Final.iMes < 2)))
            {
                dma.qtdDias++;
            }
            // if(Inicial.iAno != Final.iAno && verificarBissexto(Final.iAno) &&
            //     (Final.iMes > 2 || (Final.iMes == 2 && Final.iDia == 29))){
            //     dma.qtdDias++;
            // }

             // printf("Data inicial: %d/%d/%d\n", Inicial.iDia, Inicial.iMes, Inicial.iAno);
             // printf("Data final: %d/%d/%d\n", Final.iDia, Final.iMes, Final.iAno);
             // printf("Diferenca em anos: %d\n", dma.qtdAnos);
             // printf("Diferenca em meses: %d\n", dma.qtdMeses);
             // printf("Diferenca em dias: %d\n", dma.qtdDias);
             // código correto, primeiro teste do novo corretor apresenta um erro (pede 0 dias,
             // mas por 2016 ser bissexto, o certo seria 1 dia)

            
            
            return dma;
        }

    }

}

/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar diferenças entre maiúsculos e minúsculos.
        Se isCaseSensitive != 1, a pesquisa não deve  considerar diferenças entre maiúsculos e minúsculos.
 @saida
    Um número n >= 0.
 */
int q3(char *texto, char c, int isCaseSensitive)
{
    int qtdOcorrencias = 0;

    //cópia do texto para uma string temporária
    
    int tamTexto = strlen(texto);
    char textoTemp[tamTexto+1];
    
    for(int i=0; i<tamTexto; i++){
        textoTemp[i] = texto[i];
    }
    textoTemp[tamTexto+1] = '\0'; 
       
    if(isCaseSensitive != 1){

        //Converte caracteres de busca maiúsculos para minúsculos
        if(c >= 'A' && c <= 'Z'){
            c = c + 32;
        }
        //Varre a string texto convertendo as letras miúsculas em minúsculas
        for(int i = 0; i < tamTexto; i++){
            if(textoTemp[i]>='A' && textoTemp[i]<='Z'){
                textoTemp[i] = textoTemp[i] + 32;
            }
        }
    }
    
    for (int i=0; i<strlen(texto); i++){
        if(textoTemp[i] == c){
            qtdOcorrencias++;
        }
    }
    
    // printf("Texto original: %s\n", texto);
    // printf("Texto ajustado: %s - quantidade de ocorrências de %c: %i\n", textoTemp, c, qtdOcorrencias);
    // printf("Resultado: ");


    return qtdOcorrencias;
}

/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros (posicoes) que irá guardar as posições de início e fim de cada ocorrência da palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída correspondente. Por exemplo, se tiver uma única ocorrência, a posição 0 do vetor deve ser preenchido com o índice de início do texto, e na posição 1, deve ser preenchido com o índice de fim da ocorrencias. Se tiver duas ocorrências, a segunda ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente. Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera". Como há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da seguinte forma:
        posicoes[0] = 13; - posição da primeira letra
        posicoes[1] = 16; - posição da ultima letra
        Observe que o índice da posição no texto deve começar ser contado a partir de 1.
        O retorno da função, n, nesse caso seria 1;

 */
int q4(char *strTexto, char *strBusca, int *posicoes) {
    int qtdOcorrencias = 0;  // Contador de ocorrências
    
    // Debug:
    // printf("Texto base: %s\n", strTexto);
    // printf("Palavra de busca: %s\n", strBusca);
    
    int tamTexto = strlen(strTexto);
    int tamBusca = strlen(strBusca);

    // Percorre o texto base
    for (int i = 0; i <= tamTexto - tamBusca; i++) {
        int encontrou = 1; // Assume que encontrou a palavra

        // Verifica correspondência da palavra
        for (int j = 0; j < tamBusca; j++) {
            if (strTexto[i + j] != strBusca[j]) {
                encontrou = 0; // Quebra se a correspondência falhar
                break;
            }
        }

        // Se a palavra foi encontrada
        if (encontrou) {
            int posInicio = i + 1;           
            int posFim = i + tamBusca;       

            posicoes[qtdOcorrencias * 2] = posInicio;
            posicoes[qtdOcorrencias * 2 + 1] = posFim;

            qtdOcorrencias++; 
            i += tamBusca - 1; 
        }
    }

    return qtdOcorrencias;
}

/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
 */

int q5(int num)
{
    int inverso = 0;
    // printf("Número original: %d\n", num);

    for(int i=0; num>0; i++){
        inverso = inverso*10 + num%10;
        num /= 10;
    }

    // printf("Número invertido: %d\n", inverso);
    return inverso;
}

/*
 Q6 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base
 */

int q6(int numerobase, int numerobusca)
{

    // printf("Número base: %d\n", numerobase);
    // printf("Número de busca: %d\n", numerobusca);
    
    int qtdOcorrencias = 0;
    int mult10 = 1; //multiplos de dez (potência de 10 equivalente ao numero de dígitos do númerobusca)
    int tempBusca = numerobusca; //variável temporária para armazenar o número de busca e verificar o número de dígitos

    while(tempBusca>0){
        mult10 *= 10;
        tempBusca /= 10;
    }

    // printf("%d\n", mult10);

    while(numerobase > 0){
        if(numerobase % mult10 == numerobusca){ //verifica se o número de busca está contido no número base
            numerobase -= numerobusca; //remove o número de busca do número base, para que o primeiro dígito não seja verificado novamente
            qtdOcorrencias++;
        }
        numerobase /= 10; //remoção do ultimo dígito
    }
    // printf("Quantidade de vezes que número de busca ocorre em número base: %d\n", qtdOcorrencias);    
    return qtdOcorrencias;
}




DataQuebrada quebraData(char data[]){
  DataQuebrada dq;
    char sDia[3];
  char sMes[3];
  char sAno[5];
  int i; 

  for (i = 0; data[i] != '/'; i++){
    sDia[i] = data[i];	
  }
  if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
    sDia[i] = '\0';  // coloca o barra zero no final
  }else {
    dq.valido = 0;
    return dq;
    }  


  int j = i + 1; //anda 1 cada para pular a barra
  i = 0;

  for (; data[j] != '/'; j++){
    sMes[i] = data[j];
    i++;
  }

  if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
    sMes[i] = '\0';  // coloca o barra zero no final
  }else {
    dq.valido = 0;
    return dq;
  }


  j = j + 1; //anda 1 cada para pular a barra
  i = 0;

  for(; data[j] != '\0'; j++){
    sAno[i] = data[j];
    i++;
  }

  if(i == 2 || i == 4){ // testa se tem 2 ou 4 digitos
    sAno[i] = '\0';  // coloca o barra zero no final
  }else {
    dq.valido = 0;
    return dq;
  }

  dq.iDia = atoi(sDia);
  dq.iMes = atoi(sMes);
  dq.iAno = atoi(sAno); 

  dq.valido = 1;

  return dq;
}
