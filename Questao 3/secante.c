#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
    @shogunhirei
    EQE749 Métodos Numéricos
    Método da Secante - Questão 3 Letras E, F;

    Processo:
    Definir função g = (F(Xi) - F(X0))/(Xi - X0) ; 
    Definir novo valor pra X0 
    qui 22 nov 2018 10:39:52 -02
*/

void function(int def, double X0, double Xi, double interval[2]) 
{
    if(def != 0)
    {
        interval[0] = exp(X0) -  sin(M_PI*X0/3);
        interval[1] = exp(Xi) -  sin(M_PI*Xi/3);
    } 
    else 
    {
        interval[0] = pow(X0,3.0) - 2*pow(X0,2) - 2*X0 + 1;
        interval[1] = pow(Xi,3.0) - 2*pow(Xi,2) - 2*Xi + 1;
    }
}


int main(int argc, char** argv)
{
    int def, n = 0;
    double Xi, X0, k;
    double results[2];
    double conv_crit;
    double g;

    printf("insira o valor inicial (X0, Xi): ");
    scanf("%lf, %lf",&X0, &Xi);

    printf("insira a função (1 ou 0): ");
    scanf("%d",&def);

    printf("insira o critério de convergência: ");
    scanf("%lf",&conv_crit);

    do
    {
        function(def, X0, Xi, results);
        g = (results[1] - results[0])/(Xi - X0); 
        k = Xi;
        Xi = X0 - results[0]/g;
        X0 = k;

        if(n > 300)
        {
            printf("Não convergiu ainda!\n It: %d",n);
            break;
        }
        n++;
    }while(fabs(Xi - X0) > conv_crit);
    printf("\n Convergiu!\n It: %d; Raiz: %f\n f(Raiz): %f\n", n, Xi, results[1]);

    return(EXIT_SUCCESS);
}
