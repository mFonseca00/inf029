

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
            
            //separa os dois ultimos dígitos do ano
            int d1A = dataq.iAno % 10;
            int d2A = (dataq.iAno % 100) / 10;

            int bissexto = 0;//armazena se o ano é bissexto (1 para sim e 0 para não)
            if((d1A == 0 && d2A == 0 && dataq.iAno %400 == 0)||((d1A != 0 || d2A != 0) && dataq.iAno %4 == 0)){ //testa se o ano é bissexto
		
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
        return dma;
    }else if (q1(datafinal) == 0){
        dma.retorno = 3;
        return dma;
    }else{
        DataQuebrada dataFinalQ, dataInicialQ; //variáveis tipo DataQuebrada que irão armazenar os valores separados
        dataInicialQ = quebraData(datainicial); //chamada da função quebraData para quebrar data em dia, mês e ano
        dataFinalQ = quebraData(datafinal); //chamada da função quebraData para quebrar data em dia, mês e ano
        //verificando se a data final não é menor que a data inicial
        if(dataFinalQ.iAno < dataInicialQ.iAno || ( dataFinalQ.iAno >= dataInicialQ.iAno && dataFinalQ.iMes < dataInicialQ.iMes) || ( dataFinalQ.iAno >= dataInicialQ.iAno && dataFinalQ.iMes >= dataInicialQ.iMes && dataFinalQ.iDia < dataInicialQ.iDia )){
            dma.retorno = 4;
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

            //Diferença de dias - Validado

            dma.qtdDias = dataFinalQ.iDia - dataInicialQ.iDia; // contabiliza o número de dias
            if(bissextoInicial==1 && dataInicialQ.iMes<=2 && dataInicialQ.iDia<29 && bissextoFinal == 0 && dataFinalQ.iMes>2){//aumenta em 1 a quantidade de dias caso o ano inicial seja bissexto e a data inicial seja antes do fim de fevereiro
                dma.qtdDias++;
            }
            if(bissextoFinal==1 && dataFinalQ.iMes>2 && dma.qtdDias !=0){//reduz em 1 a quantidade de dias caso o ano Final seja bissexto e a data Final seja após do fim de fevereiro
                dma.qtdDias--;
            }
            if(dma.qtdDias<0){//caso a diferença seja negativa (dia final < dia inicial), retira o sinal negativo
                dma.qtdDias= (-1)*dma.qtdDias;
            }

            //Diferença de meses - Validado

            dma.qtdMeses = dataFinalQ.iMes - dataInicialQ.iMes; // contabiliza o número de meses
            if(dataInicialQ.iDia>dataFinalQ.iDia && dma.qtdMeses==1){//exclui casos onde o mês é diferente entre as datas, mas não se completou um mês de diferença
                dma.qtdMeses = 0;
            }

            if(dma.qtdMeses<0){//caso a diferença seja negativa (mês final < mês inicial), retira o sinal negativo
                dma.qtdMeses= (-1)*dma.qtdMeses;
            }

            //Diferença de anos - Validado

            dma.qtdAnos = dataFinalQ.iAno - dataInicialQ.iAno; // contabilizando o número de anos
            if(dataInicialQ.iAno>dataFinalQ.iAno && dma.qtdAnos==1){//exclui casos onde o ano é diferente entre as datas, mas não se completou um ano de diferença
                dma.qtdAnos = 0;
            }

            if(dma.qtdAnos<0){//caso a diferença seja negativa (ano final < ano inicial), retira o sinal negativo
                dma.qtdAnos = 0;
            }

            dma.retorno = 1;
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
    else{       //considerar diferenças entre maiúsculo e minúsculo
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

    // printf("\n Q1\n\n");
    // testQ1();
    // printf("\n Q2\n\n");
    // testQ2();
    printf("\n Q3\n\n");
    testQ3();
    // testQ4();
    // testQ5();
    // testQ6();
}



void testQ1()
{
    char str[11];
    strcpy(str, "29/02/2015");
    printf("%d\n", q1(str) == 0);
    strcpy(str, "29/02/2012");
    printf("%d\n", q1(str) == 1);
    strcpy(str, "9/13/2014");
    printf("%d\n", q1(str) == 0);
    strcpy(str, "45/4/2014");
    printf("%d\n", q1(str) == 0);
    strcpy(str, "/9/2014");
    printf("%d\n", q1(str) == 0);
}

void testQ2()
{
    char datainicial[11], datafinal[11];
    int qtdDias, qtdMeses, qtdAnos;
    DiasMesesAnos dma;

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

    strcpy(datainicial, "01/30/2015");
    strcpy(datafinal, "01/06/2016");
    dma = q2(datainicial, datafinal);
    printf("%d\n", dma.retorno == 2);

    strcpy(datainicial, "01/3/2015");
    strcpy(datafinal, "40/06/2016");
    dma = q2(datainicial, datafinal);
    printf("%d\n", dma.retorno == 3);

    strcpy(datainicial, "01/06/2016");
    strcpy(datafinal, "01/06/2015");
    dma = q2(datainicial, datafinal);
    printf("%d\n", dma.retorno == 4);

    //teste 3
    qtdDias = -1;
    qtdMeses = -1;
    qtdAnos = -1;

    strcpy(datainicial, "06/06/2017");
    strcpy(datafinal, "07/07/2017");
    dma = q2(datainicial, datafinal);
    printf("%d\n", dma.retorno == 1);
    printf("%d\n", dma.qtdDias == 1);
    printf("%d\n", dma.qtdMeses == 1);
    printf("%d\n", dma.qtdAnos == 0);
}

void testQ3()
{
    char str[250];
    strcpy(str, "Renato Lima Novais");
    printf("%d\n", q3(str, 'a', 0) == 3);
    printf("%d\n", q3(str, 'b', 0) == 0);
    printf("%d\n", q3(str, 'l', 1) == 0);
    printf("%d\n", q3(str, 'l', 0) == 1);
    printf("%d\n", q3(str, 'L', 0) == 1);
}

