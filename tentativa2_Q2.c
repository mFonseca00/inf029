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
        //verificando se a data final é menor que a data inicial
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

            //Diferença de anos - 

            dma.qtdAnos = dataFinalQ.iAno - dataInicialQ.iAno; // contabilizando o número de anos
            if(dataFinalQ.iAno < dataInicialQ.iMes || (dataFinalQ.iMes == dataInicialQ.iMes && dataFinalQ.iDia < dataInicialQ.iDia)){
            dma.qtdAnos--; // Ajusta o número de anos se o mês ou o dia final ainda não completaram um ano completo
            }

            //Diferença de meses - 

            dma.qtdMeses = dataFinalQ.iMes - dataInicialQ.iMes; // contabiliza o número de meses
            if(dma.qtdMeses<0){
                dma.qtdMeses += 12; //ajuista a quantidade de meses para um valor positivo ()
            }

            //Diferença de dias - 

            dma.qtdDias = dataFinalQ.iDia - dataInicialQ.iDia; // contabiliza o número de dias
            if (dma.qtdDias < 0) {
                int diasNoMesAnterior = 31;
                if(dataFinalQ.iMes==4 || dataFinalQ.iMes==6 || dataFinalQ.iMes==9 ||dataFinalQ.iMes==11){
                    diasNoMesAnterior = 30;
                }
                if(dataFinalQ.iMes==2 && bissextoFinal==0){
                    diasNoMesAnterior = 28;
                }
                if(dataFinalQ.iMes==2 && bissextoFinal==1){
                    diasNoMesAnterior = 29;
                }
                diasNoMesAnterior--;//subtrai 1 dia do mês anterior
                dma.qtdDias+=diasNoMesAnterior; // ajusta a quantidade de dias para um valor positivo referente a data no mês anterior
                dma.qtdMeses--; // subtrai um mês para ajustar a quantidade de meses
            }

            if (dma.qtdMeses < 0) { //torna o mês um valor positivo e ajusta a quantidade de anos, subtraindo um ano
                dma.qtdMeses += 12;
                dma.qtdAnos--;
            }

            dma.retorno = 1;
            return dma;
        }

    }

}