

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
        else{
        
	//calculando a distancia entre as datas

	//contabilizar meses
	dma.qtdMeses = (12 - dataInicialQ.iMes) + dataFinalQ.iMes;
	if(dataInicialQ.iMes == dataFinalQ.iMes && dataInicialQ.iAno == dataFinalQ.iAno){//caso a diferênca seja só em dias de um mesmo mês
	    dma.qtdMeses = 0;
	}
	//contabilizar anos e atualizar meses
	if(dma.qtdMeses >= 12 && dataFinalQ.iAno > dataInicialQ.iAno){ //caso sejam contabilizados mais de 12 meses, e o ano final seja diferente do inicial VERIFICAR!!!!!!!!
	    dma.qtdMeses = dma.qtdMeses - 12;
	    dma.qtdAnos = dataFinalQ.iAno - dataInicialQ.iAno;
	}
	else{
	    dma.qtdAnos = 0;
	}

	//Verificação se o ano é bissexto

	int d1A = dataInicialQ.iAno % 10;
    int d2A = (dataInicialQ.iAno % 100) / 10;

	//contabilizar Dias

	if(dataFinalQ.iAno == dataInicialQ.iAno && dataFinalQ.iMes == dataInicialQ.iMes){ //caso a diferença de dias seja no mesmo mês
		dma.qtdDias = dataFinalQ.iDia - dataInicialQ.iDia; //calculo da diferença de dias
	}


	else{  // caso o mês ou o ano sejam diferentes
		int bissexto = 0;//armazena se o ano é bissexto (1 para sim e 0 para não)
        int diasRestantes = 0;
	
        if((d1A == 0 && d2A == 0 && dataInicialQ.iAno %400 == 0)||((d1A != 0 || d2A != 0) && dataInicialQ.iAno %4 == 0)){ //testa se o ano é bissexto
            bissexto = 1;
        }
    
        if(dataInicialQ.iMes == 1 || dataInicialQ.iMes == 3 || dataInicialQ.iMes == 5 || dataInicialQ.iMes == 7 || dataInicialQ.iMes == 8 || dataInicialQ.iMes == 10 || dataInicialQ.iMes == 12){
            diasRestantes = 31 - dataInicialQ.iDia;
        }
        else if(dataInicialQ.iMes == 4 || dataInicialQ.iMes == 6 || dataInicialQ.iMes == 9 || dataInicialQ.iMes == 11){
            diasRestantes = 30 - dataInicialQ.iDia;
        }
        else if(bissexto == 0 && dataInicialQ.iMes == 2){
            diasRestantes = 28 - dataInicialQ.iDia;
        }
        else if(bissexto == 1 && dataInicialQ.iMes == 2){
            diasRestantes = 29 - dataInicialQ.iDia;
        }

        if (dataInicialQ.iDia > dataInicialQ.iDia){
            dma.qtdDias = diasRestantes + (dataFinalQ.iDia - dataInicialQ.iDia); //calculo da diferença de dias
        }
        else{
            dma.qtdDias = diasRestantes + dataFinalQ.iDia;
        }
	}
   
	      
	dma.retorno = 1;
      	return dma;
      }

    }
    
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
    printf("\n Q2\n\n");
    testQ2();
    /*testQ3();
    testQ4();
    testQ5();
    testQ6();*/
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

