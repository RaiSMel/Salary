#include <stdio.h>
#include <stdlib.h>

double AliINSS(double salario){
    if(salario <= 1751.81){
        return 8;
    }else if(salario <= 2919.72){
        return 9;
    }else if(salario <= 5839.45){
        return 11;
    }else{
        return 0;
    }
}

double ValINSS(double salario, double alins){

    if(alins != 0) return salario * (alins/100);
    else return 642.34;
}

double BaseIR(double salario, double valins){
    return salario - valins ;
}

double AliqIR(double baseir){
    if(baseir <= 1903.98) return 0;
    else if(baseir <= 2826.65) return 7.5;
    else if(baseir <= 3751.05) return 15;
    else if(baseir <= 4664.68) return 22.5;
    else return 27.5;
}

double ValIR(double baseir, double aliqir){
    double deducao, valir;
    if(aliqir == 7.5) deducao = 142.80;
    else if(aliqir == 15) deducao = 354.80;
    else if(aliqir == 22.5) deducao = 636.13;
    else if(aliqir == 27.5) deducao = 869.39;
    else return 0;

    valir = baseir * (aliqir)/100 - deducao;

    if (valir <= 10)
    {
        return 0;
    } 
    return valir;
}

int main() {

    char n1[] = "Rai da Silva Mello RA: 0020482312017",
    n2[] = "Giulio Gabriel Monteiro Arantes RA: 0020482312043",
    n3[] = "Mariana De Santis Del Colletto  RA: 0020482312027"
    ;

    printf("\n\nProjeto Programa 1 – Cálculo de Salários – arq. salarios.c\n\n           Criado por:\n\n%s \n\n%s\n\n%s\n\n", n1, n2, n3);

    FILE *Salarios, *Calculos;
    int Tam = 0;
    double  salario, *contaSalarios = NULL;
    
    Salarios = fopen("salario.txt", "r");

    while (fscanf(Salarios, "%lf\n", &salario) != EOF)
    {
        Tam++;
        contaSalarios = (double *)realloc(contaSalarios, sizeof(double) * Tam);
        contaSalarios[Tam-1] = salario;
    }
    fclose(Salarios);


    for(int i=0; i < Tam; i++){
        double changer = 0;
        for(int j = i + 1; j < Tam; j++){
            if(contaSalarios[j] < contaSalarios[i]){
                changer = contaSalarios[j];
                contaSalarios[j] = contaSalarios[i];
                contaSalarios[i] = changer;
                
            }
        }
    }
    Calculos = fopen("calculos.txt", "w");

    fprintf(Calculos, "Projeto Programa 1  Calculo de Salarios arq. salarios.c\n\n           Criado por:\n\n%s\n\n%s\n\n%s\n\n", n1, n2, n3);

    fprintf(Calculos,"    Bruto      AliqINSS      Val.INSS       Base I.R.     AliqIR     Val.IR     Liquido\n");
    for(int i=0; i < Tam; i++)
    {
        double Alins= AliINSS(contaSalarios[i]);
        double valins = ValINSS(contaSalarios[i], Alins);
        double baseir = BaseIR(contaSalarios[i], valins);
        double aliqir = AliqIR(baseir);
        double valir = ValIR(baseir, aliqir);
        double salarioliq = baseir - valir;
        fprintf(Calculos, "%10.2lf %12.1lf %13.2lf %15.2lf %10.2lf %10.2lf %11.2lf\n", contaSalarios[i], Alins, valins, baseir, aliqir, valir, salarioliq);
    }
    fclose(Calculos);

    system("pause");
    
    return 0;
}