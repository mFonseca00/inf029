

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

int somar(int x, int y); //função utilizada para testes
int fatorial(int x); //função utilizada para testes
int q1(char data[]);
DiasMesesAnos q2(char datainicial[], char datafinal[]);
int q3(char *texto, char c, int isCaseSensitive);
int q4(char *strTexto, char *strBusca, int posicoes[30]);
int q5(int num);
int q6(int numerobase, int numerobusca);
DataQuebrada quebraData(char data[]);

void testSomar();    //função utilizada para testes
void testFatorial(); //função utilizada para testes
void testQ1();
void testQ2();
void testQ3();
void testQ4();
void testQ5();
void testQ6();

DataQuebrada quebraData(char data[]);

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
        else{
        
	//calculando a distancia entre as datas

	//contabilizar meses
	dma.qtdMeses = (12 - dataInicialQ.iMes) + dataFinalQ.iMes;
	if(dataInicialQ.iMes == dataFinalQ.iMes && dataInicialQ.iAno == dataInicialQ.iAno){//caso a diferênca seja só em dias de um mesmo mês
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

	if(dataFinalQ.iAno == dataInicialQ.iAno && dataFinalQ.iAno == dataInicialQ.iAno){ //caso a diferença de dias seja no mesmo mês
		dma.qtdDias = dataFinalQ.iDia - dataInicialQ.iDia; //calculo da diferença de dias
	}


	else{  // caso o mês ou o ano sejam diferentes
		int bissexto = 0;//armazena se o ano é bissexto (1 para sim e 0 para não)
	
        if((d1A == 0 && d2A == 0 && dataInicialQ.iDia %400 == 0)||((d1A != 0 || d2A != 0) && dataInicialQ.iDia %4 == 0)){ //testa se o ano é bissexto
            bissexto = 1;
        }
    
        if(dataInicialQ.iMes == 1 || dataInicialQ.iMes == 3 || dataInicialQ.iMes == 5 || dataInicialQ.iMes == 7 || dataInicialQ.iMes == 8 || dataInicialQ.iMes == 10 || dataInicialQ.iMes == 12){
            dma.qtdDias = 31 - dataInicialQ.iDia; //calculo da diferença de dias
        }
        else if(dataInicialQ.iMes == 4 || dataInicialQ.iMes == 6 || dataInicialQ.iMes == 9 || dataInicialQ.iMes == 11){
            dma.qtdDias = 30 - dataInicialQ.iDia; //calculo da diferença de dias
        }
        else if(bissexto == 0 && dataInicialQ.iMes == 2){
            dma.qtdDias = 28 - dataInicialQ.iDia; //calculo da diferença de dias
        }
        else if(bissexto == 1 && dataInicialQ.iMes == 2){
            dma.qtdDias = 29 - dataInicialQ.iDia; //calculo da diferença de dias
        }
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
    int qtdOcorrencias = -1;

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
        posicoes[0] = 13;
        posicoes[1] = 16;
        Observe que o índice da posição no texto deve começar ser contado a partir de 1.
        O retorno da função, n, nesse caso seria 1;

 */
int q4(char *strTexto, char *strBusca, int posicoes[30])
{
    int qtdOcorrencias = -1;

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

    return num;
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
    int qtdOcorrencias;
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
    //testSomar();
    //testFatorial();
    printf("\n Q1\n\n");
    testQ1();
    printf("\n Q2\n\n");
    testQ2();
    /*testQ3();
    testQ4();
    testQ5();
    testQ6();*/
}

void testSomar()
{
    printf("%d\n", somar(3, 4) == 7);
    printf("%d\n", somar(-1, -3) == -4);
    printf("%d\n", somar(-6, 6) == 0);
    printf("%d\n", somar(74, 9) == 83);
    printf("%d\n", somar(30, -9) == 21);
    printf("%d\n", somar(-2, 8) == 6);
    printf("%d\n", somar(1000, 99) == 1099);

}

void testFatorial()
{
    printf("%d\n", fatorial(3) == 6);
    printf("%d\n", fatorial(1) == 1);
    printf("%d\n", fatorial(5) == 120);
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

void testQ4()
{
    char strTexto[250];
    char strBusca[50];
    int posicoes[30];
    int i;
    for (i = 0; i < 30; i++)
    {
        posicoes[i] = -1;
    }
    strcpy(strTexto, "Laboratorio de programacao: para ratos de programação");
    strcpy(strBusca, "rato");
    printf("%d\n", q4(strTexto, strBusca, posicoes) == 2);
    printf("%d\n", posicoes[0] == 5);
    printf("%d\n", posicoes[1] == 8);
    printf("%d\n", posicoes[2] == 34);
    printf("%d\n", posicoes[3] == 37);

    for (i = 0; i < 30; i++)
    {
        posicoes[i] = -1;
    }
    strcpy(strTexto, "Olá, o mundo é muito grande. Tem muitas pessoas, e muitos problemas");
    strcpy(strBusca, "mui");
    printf("%d\n", q4(strTexto, strBusca, posicoes) == 3);
    printf("%d\n", posicoes[0] == 16);
    printf("%d\n", posicoes[1] == 18);
    printf("%d\n", posicoes[2] == 34);
    printf("%d\n", posicoes[3] == 36);
    printf("%d\n", posicoes[4] == 52);
    printf("%d\n", posicoes[5] == 54);
}

void testQ5()
{
    printf("%d\n", q5(345) == 543);
    printf("%d\n", q5(78) == 87);
    printf("%d\n", q5(3) == 3);
    printf("%d\n", q5(5430) == 345);
}

void testQ6()
{
    printf("%d\n", q6(34567368, 3) == 2);
    printf("%d\n", q6(34567368, 4576) == 0);
    printf("%d\n", q6(3539343, 3) == 4);
    printf("%d\n", q6(3539343, 39) == 1);
}