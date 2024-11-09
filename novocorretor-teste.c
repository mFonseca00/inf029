

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct DQ
{
    int iDia; 
    int iMes;
    int iAno;
    int valido; // 0 se inválido, e 1 se válido 

} DataQuebrada;

typedef struct Qtd
{
    int qtdDias;
    int qtdMeses;
    int qtdAnos;
    int retorno;

} DiasMesesAnos;


int q1(char data[]);
DiasMesesAnos q2(char datainicial[], char datafinal[]);

DataQuebrada quebraData(char data[]);


void testQ1();
void testQ2();
void testQ3();


DataQuebrada quebraData(char data[]);



int q1(char data[])
{
    int datavalida = 0;
    //quebrar a string data em strings sDia, sMes, sAno
    DataQuebrada dataq; //variável tipo DataQuebrada que irá armazenar os valores separados
    if(strlen(data) <= 10){ //testa se o tamanho da string e menor ou igual a 10 (máximo tamanho para a data conforme enunciado)
        dataq = quebraData(data); //chamada da função quebraData que veio pronta no código para quebrar data em dia, mês e ano
        if(dataq.valido == 1 && dataq.iMes >= 1 && dataq.iMes <= 12){ //testa se a data é valida após função de quebrar data

            if(dataq.iAno<100){//testa se o ano tem dois dígitos
                dataq.iAno = dataq.iAno+2000;
            }


            int bissexto = 0;//armazena se o ano é bissexto (1 para sim e 0 para não)
            if(dataq.iAno %400 == 0||(dataq.iAno % 4 == 0 && dataq.iAno % 100 != 0)){ //testa se o ano é bissexto

                bissexto = 1;
            }

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

    if (q1(datainicial) == 0){
        dma.retorno = 2;
        printf("data inicial: %s | data final: %s\n", datainicial, datafinal);
        printf("Retorno = %d\n",dma.retorno);
        return dma;
    }else if (q1(datafinal) == 0){
        dma.retorno = 3;
        printf("data inicial: %s | data final: %s\n", datainicial, datafinal);
        printf("Retorno = %d\n",dma.retorno);
        return dma;
    }else{
        DataQuebrada dataFinalQ, dataInicialQ; //variáveis tipo DataQuebrada que irão armazenar os valores separados
        dataInicialQ = quebraData(datainicial); //chamada da função quebraData para quebrar data em dia, mês e ano
        dataFinalQ = quebraData(datafinal); //chamada da função quebraData para quebrar data em dia, mês e ano
        //verificando se a data final é menor que a data inicial
        if(dataInicialQ.iAno > dataFinalQ.iAno || (dataInicialQ.iAno == dataFinalQ.iAno && dataInicialQ.iMes > dataFinalQ.iMes) || (dataInicialQ.iAno == dataFinalQ.iAno && dataInicialQ.iMes == dataFinalQ.iMes && dataInicialQ.iDia > dataFinalQ.iDia)){
            dma.retorno = 4;
            printf("data inicial: %s | data final: %s\n", datainicial, datafinal);
            printf("Retorno = %d\n",dma.retorno);

            return dma;
        }
        else{//calculando a distancia entre as datas
            int bissextoInicial = 0, bissextoFinal = 0;
            if(dataInicialQ.iAno %400 == 0||(dataInicialQ.iAno %4 == 0 && dataInicialQ.iAno %100 !=0)){ //testa se o ano inicial é bissexto
                bissextoInicial = 1;
            }
            if(dataFinalQ.iAno %400 == 0||(dataFinalQ.iAno %4 == 0 && dataFinalQ.iAno %100 !=0)){ //testa se o ano inicial é bissexto
                bissextoFinal = 1;
            }

            //Diferença de anos - 

            dma.qtdAnos = dataFinalQ.iAno - dataInicialQ.iAno; // contabilizando o número de anos
            if(dataFinalQ.iMes < dataInicialQ.iMes || (dataFinalQ.iMes == dataInicialQ.iMes && dataFinalQ.iDia < dataInicialQ.iDia)){
            dma.qtdAnos--; // Ajusta o número de anos se o mês ou o dia final ainda não completaram um ano completo
            }

            //Diferença de meses - 

            dma.qtdMeses = dataFinalQ.iMes - dataInicialQ.iMes; // contabiliza o número de meses

            
            if(dma.qtdMeses<0){
                dma.qtdMeses += 12; //ajuista a quantidade de meses para um valor positivo ()
            }

            //Diferença de dias - melhor até agora (só dois casos deu erro)
            dma.qtdDias = dataFinalQ.iDia - dataInicialQ.iDia; // contabiliza a diferença de dias
            if (dma.qtdDias < 0) {
                int diasNoMesAnterior = 0;
                if(dataFinalQ.iMes==4 || dataFinalQ.iMes==6 || dataFinalQ.iMes==9 ||dataFinalQ.iMes==11){
                    diasNoMesAnterior = 30;
                }
                else if(dataFinalQ.iMes==2 && bissextoFinal==0){
                    diasNoMesAnterior = 28;
                }
                else if(dataFinalQ.iMes==2 && bissextoFinal==1){
                    diasNoMesAnterior = 29;
                }
                else{
                    diasNoMesAnterior = 31;
                }

                if((dataFinalQ.iMes>2 && bissextoFinal==1)||(bissextoInicial==1 && (dataInicialQ.iMes==1 ||(dataInicialQ.iMes==2 && dataInicialQ.iDia< 29 )))){
                    dma.qtdDias--;
                }
                
                diasNoMesAnterior--;//subtrai 1 dia do mês anterior
                dma.qtdDias+=diasNoMesAnterior; // ajusta a quantidade de dias para um valor positivo referente a data no mês anterior
                dma.qtdMeses--; // subtrai um mês para ajustar a quantidade de meses
            }

            
           
            dma.retorno = 1;
            printf("data inicial: %s | data final: %s\n", datainicial, datafinal);
            printf("%d anos, %d meses, %d dias, retorno = %d\n", dma.qtdAnos,dma.qtdMeses,dma.qtdDias, dma.retorno);
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
    if(isCaseSensitive != 1){     //não considerar diferenças entre maiúsculo e minúsculo
        if(c>64 && c<91){       //transforma o caractere para minúsculo, caso seja letra
            c = c + 32;
        }
        for(int i=0;i<=strlen(texto);i++){      //transforma todas as letras do texto para minúsculo
            if(texto[i]>64 && texto[i]<91 ){
                texto[i]=texto[i]+32;
            }
        }
        //verificação dos caracteres (função)
        for(int i=0; i<=strlen(texto);i++){
            if(c==texto[i]){
                qtdOcorrencias++;
            }
        }
    }
    else{       //considerar diferenças entre maiúsculo e minúsculo   ERRO NO TESTE
        // verificação dos caracteres (função)
        for(int i=0; i<=strlen(texto);i++){
            if(c==texto[i]){
                qtdOcorrencias++;
            }
        }
    }
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

int main()
{

    printf("\n Q1\n\n");
    testQ1();
    printf("\n Q2\n\n");
    testQ2();
    // printf("\n Q3\n\n");
    // testQ3();
    // testQ4();
    // testQ5();
    // testQ6();
}



void testQ1(){
    char str[11];
    strcpy(str,"29/02/2015");
    printf("%d\n",q1(str) == 0);
    strcpy(str,"29/02/2012");
    printf("%d\n",q1(str) == 1);
    strcpy(str,"9/13/2014");
    printf("%d\n",q1(str) == 0);
    strcpy(str,"45/4/2014");
    printf("%d\n",q1(str) == 0);
    strcpy(str,"12/1/15");
    printf("%d\n",q1(str) == 1);
    strcpy(str,"1/9/2016");
    printf("%d\n",q1(str) == 1);
    strcpy(str,"//2016");
    printf("%d\n",q1(str) == 0);
    strcpy(str,"1//20");
    printf("%d\n",q1(str) == 0);
    strcpy(str,"1/R/2016");
    printf("%d\n",q1(str) == 0);
    strcpy(str,"1/12/19");
    printf("%d\n",q1(str) == 1); 

}

void testQ2(){
    char datainicial[11], datafinal[11];
    int qtdDias, qtdMeses, qtdAnos;
    DiasMesesAnos dma;
    int retorno;

    //teste 1
    qtdDias = -1;
    qtdMeses = -1;
    qtdAnos = -1;

    strcpy(datainicial, "01/06/2015");
    strcpy(datafinal, "01/06/2016");
    dma = q2(datainicial, datafinal);
    printf("%d\n", dma.retorno == 1);
    printf("%d\n", dma.qtdDias == 0);
    printf("%d\n", dma.qtdMeses == 0);
    printf("%d\n", dma.qtdAnos == 1);

    //teste 2 - retornos
    qtdDias = -1;
    qtdMeses = -1;
    qtdAnos = -1;

    strcpy(datainicial,"01/30/2015");
    strcpy(datafinal,"01/06/2016");
    dma = q2(datainicial, datafinal);
    printf("%d\n",dma.retorno == 2);

    strcpy(datainicial,"01/3/2015");
    strcpy(datafinal,"40/06/2016");
    dma = q2(datainicial, datafinal);
    printf("%d\n",dma.retorno == 3);

    strcpy(datainicial,"01/06/2016");
    strcpy(datafinal,"01/06/2015");
    dma = q2(datainicial, datafinal);
    printf("%d\n",dma.retorno == 4);

    //teste 3
    qtdDias = -1;
    qtdMeses = -1;
    qtdAnos = -1;

    strcpy(datainicial,"06/06/2017");
    strcpy(datafinal,"07/07/2017");
    dma = q2(datainicial, datafinal);
    printf("%d\n",dma.retorno == 1);
    printf("%d\n",dma.qtdDias == 1);
    printf("%d\n",dma.qtdMeses == 1);
    printf("%d\n",dma.qtdAnos == 0);

    //teste 4
    qtdDias = -1;
    qtdMeses = -1;
    qtdAnos = -1;

    strcpy(datainicial,"06/06/2017");
    strcpy(datafinal,"05/07/2018");
    dma = q2(datainicial, datafinal);
    printf("%d\n",dma.retorno == 1);
    printf("%d\n",dma.qtdDias == 29);
    printf("%d\n",dma.qtdMeses == 0);
    printf("%d\n",dma.qtdAnos == 1);

    //teste 5
    qtdDias = -1;
    qtdMeses = -1;
    qtdAnos = -1;

    strcpy(datainicial,"26/07/2017");
    strcpy(datafinal,"25/08/2017");
    dma = q2(datainicial, datafinal);
    printf("%d\n",dma.retorno == 1);
    printf("%d\n",dma.qtdDias == 30);
    printf("%d\n",dma.qtdMeses == 0);
    printf("%d\n",dma.qtdAnos == 0);

    //teste 6
    qtdDias = -1;
    qtdMeses = -1;
    qtdAnos = -1;

    strcpy(datainicial,"26/06/2017");
    strcpy(datafinal,"26/07/2017");
    dma = q2(datainicial, datafinal);
    printf("%d\n",dma.retorno == 1);
    printf("%d\n",dma.qtdDias == 0);
    printf("%d\n",dma.qtdMeses == 1);
    printf("%d\n",dma.qtdAnos == 0);

    //teste 8
    qtdDias = -1;
    qtdMeses = -1;
    qtdAnos = -1;

    strcpy(datainicial,"27/02/2016");
    strcpy(datafinal,"03/03/2017");
    dma = q2(datainicial, datafinal);
    printf("%d\n",dma.retorno == 1);
    printf("%d\n",dma.qtdDias == 4);
    printf("%d\n",dma.qtdMeses == 0);
    printf("%d\n",dma.qtdAnos == 1);

    //teste 9
    qtdDias = -1;
    qtdMeses = -1;
    qtdAnos = -1;

    strcpy(datainicial,"27/02/2015");
    strcpy(datafinal,"03/03/2016");
    dma = q2(datainicial, datafinal);
    printf("%d\n",dma.retorno == 1);
    printf("%d\n",dma.qtdDias == 5);
    printf("%d\n",dma.qtdMeses == 0);
    printf("%d\n",dma.qtdAnos == 1);

    //teste 10
    qtdDias = -1;
    qtdMeses = -1;
    qtdAnos = -1;

    strcpy(datainicial,"28/01/2016");
    strcpy(datafinal,"29/02/2016");
    dma = q2(datainicial, datafinal);
    printf("%d\n",dma.retorno == 1);
    printf("%d\n",dma.qtdDias == 1);
    printf("%d\n",dma.qtdMeses == 1);
    printf("%d\n",dma.qtdAnos == 0);

}

void testQ3(){
    char str[250];
    strcpy(str,"Renato Lima Novais");
    printf("%d\n",q3(str, 'a', 0) == 3);
    printf("%d\n",q3(str, 'b', 0) == 0);
    printf("%d\n",q3(str, 'l', 1) == 0);
    printf("%d\n",q3(str, 'l', 0) == 1);
    printf("%d\n",q3(str, 'L', 0) == 1);

    strcpy(str,"Letícia, signifiCa fEliCIdADE");
    printf("%d\n",q3(str, 'c', 0) == 3);
    printf("%d\n",q3(str, 'C', 0) == 3);
    printf("%d\n",q3(str, 'c', 1) == 1);
    printf("%d\n",q3(str, 'C', 1) == 2);
    printf("%d\n",q3(str, 'R', 0) == 0);
    printf("%d\n",q3(str, 'e', 0) == 3);
    printf("%d\n",q3(str, 'E', 1) == 2);
    printf("%d\n",q3(str, 'S', 1) == 0);


}

// void testQ4(){
//     char strTexto[250];
//     char strBusca[50];
//     int posicoes[30];
//     int i;
//     for (i = 0; i<30; i++){
//         posicoes[i] = -1;
//     }
//     strcpy(strTexto,"Laboratorio de programacao: para ratos de programação");
//     strcpy(strBusca,"rato");
//     printf("%d\n",q4(strTexto, strBusca, posicoes) == 2);
//     printf("%d\n",posicoes[0]==5);
//     printf("%d\n",posicoes[1]==8);
//     printf("%d\n",posicoes[2]==34);
//     printf("%d\n",posicoes[3]==37);


//     for (i = 0; i<30; i++){
//         posicoes[i] = -1;
//     }
//     strcpy(strTexto,"Ola, o mundo e muito grande. Tem muitas pessoas, e muitos problemas");
//     strcpy(strBusca,"mui");
//     printf("%d\n",q4(strTexto, strBusca, posicoes) == 3);
//     printf("%d\n",posicoes[0]==16);
//     printf("%d\n",posicoes[1]==18);
//     printf("%d\n",posicoes[2]==34);
//     printf("%d\n",posicoes[3]==36);
//     printf("%d\n",posicoes[4]==52);
//     printf("%d\n",posicoes[5]==54);

//     for (i = 0; i<30; i++){
//         posicoes[i] = -1;
//     }
//     strcpy(strTexto,"Programar é legal?");
//     strcpy(strBusca,"sim");
//     printf("%d\n",q4(strTexto, strBusca, posicoes) == 0);

//     for (i = 0; i<30; i++){
//         posicoes[i] = -1;
//     }
//     strcpy(strTexto,"maraaaavilha, meu prograaaama funcionou");
//     strcpy(strBusca,"aa");
//     printf("%d\n",q4(strTexto, strBusca, posicoes) == 4);
//     printf("%d\n",posicoes[0]==4);
//     printf("%d\n",posicoes[1]==5);
//     printf("%d\n",posicoes[2]==6);
//     printf("%d\n",posicoes[3]==7);
//     printf("%d\n",posicoes[4]==24);
//     printf("%d\n",posicoes[5]==25);
//     printf("%d\n",posicoes[6]==26);
//     printf("%d\n",posicoes[7]==27);

// }


// void testQ5(){
//     printf("%d\n",q5(345) == 543);
//     printf("%d\n",q5(78) == 87);
//     printf("%d\n",q5(3) == 3);
//     printf("%d\n",q5(5430) == 345);
//     printf("%d\n",q5(1000) == 1);
//     printf("%d\n",q5(0) == 0);
//     printf("%d\n",q5(707) == 707);
//     printf("%d\n",q5(80) == 8);
//     printf("%d\n",q5(8) == 8);
//     printf("%d\n",q5(1234) == 4321);
// }

// void testQ6(){
//     printf("%d\n",q6(34567368, 3) == 2);
//     printf("%d\n",q6(34567368, 4576) == 0);
//     printf("%d\n",q6(3539343, 3) == 4);
//     printf("%d\n",q6(3539343, 39) == 1);
//     printf("%d\n",q6(5444, 44) == 1);
//     printf("%d\n",q6(54444, 44) == 2);
//     printf("%d\n",q6(1234562354, 23) == 2);
//     printf("%d\n",q6(1234, 13) == 0);
//     printf("%d\n",q6(544444, 4) == 5);
//     printf("%d\n",q6(1234562354, 32) == 0);

// }

