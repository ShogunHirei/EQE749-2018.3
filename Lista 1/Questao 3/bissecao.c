#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*
    @shogunhirei
    EQE749 - Métodos Numéricos 
    Resolução da Questão 3 - Letra A e B parte 1

    Implementação do Método da Bisseção
    
    Processo:
    -> 'Definir Intervalo (a,b)
    -> 'Definir média de intervalo c
    -> 'Verificar se f(a)*f(c) é maior ou menor que 0
    -> 'Verificar critério de convergência 
    -> 'Começar novo ciclo
    qua 21 nov 2018 13:31:09 -02
*/

void function(int def, double A, double B, double interval[2])
{
    if(def != 1)
    {
        interval[0] = exp(A) -  sin(M_PI*A/3);
        interval[1] = exp(B) -  sin(M_PI*B/3);
    } 
    else 
    {
        interval[0] = pow(A,3.0) - 2*pow(A,2) - 2*A + 1;
        interval[1] = pow(B,3.0) - 2*pow(B,2) - 2*B + 1;
    }
}

void bissecao(double A, double B, int def, double conv_crit)
{
    int n = 0; 
    double interval[2];
    double c; 
    
    c = (A + B)/2.0 ;

    do {
        function(def, A, c, interval);

        if(interval[0]*interval[1] < 0)
        {
            B = c;
            c = (A + B)/2;
        }
        else
        {
            A = c;
            c = (A + B)/2 ;
        }
        if(n > 300)
        {
            printf("Não convergiu para esse intervalo!\n Número de it = %d",n);
            break;
        }
        n++;
    }while (fabs(interval[0]) > conv_crit );

        printf("Convergiu!\n Numéro de it: %d\n Raiz: %f\n f(Raiz): %f\n (A - B): %f\n Conv_crit: %f\n", n, c, interval[0],fabs(A - B),conv_crit);
}


int main(int argc, char** argv)
{
    double A, B;  //Intervalo de busca da raiz
    double c; //Ponto médio do intervalo
    int def;
    double conv_crit = 0.000001; //Critério de Convergência 
    int n = 0; // Contador de loop...

    // Letra A 
    A = -3.5;
    B = 2.5;
    def = 0;

    bissecao( A,  B,  def,  conv_crit);

    // Letra B
    A = 0.0;
    B = 1.0;
    def = 1;

    bissecao( A,  B,  def,  conv_crit);
    
    return(EXIT_SUCCESS);

}
