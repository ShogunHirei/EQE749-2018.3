#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
    @shogunhirei
    EQE749 - Métodos Numéricos
    Método de Newthon-Raphson 

    Processo:
    Definir funções e derivadas
    Definir chute inicial
    Definir novo valor
    Definir Critério de Convergência
    Repetir interação
    qui 22 nov 2018 09:48:15 -02
*/


void function(int def, double X0, double interval[2]) 
{
    if(def != 0)
    {
        interval[0] = exp(X0) -  sin(M_PI*X0/3);
        interval[1] = exp(X0) - (M_PI/3)*cos(M_PI*X0/3);
    } 
    else 
    {
        interval[0] = pow(X0,3.0) - 2*pow(X0,2) - 2*X0 + 1;
        interval[1] = 3*pow(X0,2.0) + 4*X0 - 2; 
    }
}

int main(int argc, char** argv)
{
    int def, n = 0;
    double X0;
    double conv_crit;
    double results[2];

    printf("insira o valor inicial (x0): ");
    scanf("%lf", &X0);

    printf("insira a função (1 ou 0): ");
    scanf("%d",&def);

    printf("insira o critério de convergência: ");
    scanf("%lf",&conv_crit);


    do
    {

        function(def, X0, results);
        X0 = X0 - results[0]/results[1];

        if(n > 450)
        {
            printf("Não convergiu ainda!\n It: %d", n);
            break;
        }
        n++;
    }
    while (fabs(results[0]) > conv_crit);
    printf("Convergiu!\n Iterações: %d \n Raiz: %f\n f(Raiz): %f\n", n, X0, results[0]);

    return(EXIT_SUCCESS);
}

