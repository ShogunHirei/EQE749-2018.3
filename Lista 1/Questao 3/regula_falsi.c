#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
    @shogunhirei
    EQE749 - Métodos Numéricos 
    Implementação do Metodo da Regula Falsi

    Questão 3 - A e B

    Processo 
    Linearização com Intervalo
    Verificar se em qual intervalo a raiz da função não-linear está
    Novo Intervalo
    Repetir processo até atingir convergência
    
    qua 21 nov 2018 15:16:36 -02
*/


void function(int def, double A, double B, double interval[2])
{
    if(def != 0)
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

int main(int argc, char** argv)
{
     
    double A, B;
    double c;
    double results[2];
    double g;
    double conv_crit;
    double k; // Para transferir valores entre variaveis
    int def;
    int n = 0; // Segurança contra Loop Infinito

    printf("Insira o intervalo A,B: ");
    scanf("%lf, %lf",&A, &B);

    printf("A: %f, B: %f \n", A, B);
    printf("Insira a função (1 ou 0): ");
    scanf("%d",&def);

    printf("Insira o critério de convergência: ");
    scanf("%lf",&conv_crit);

    function(def, A, B, results);
    printf("F(a): %f ; F(b): %f\n",results[0], results[1]);
    if(results[0] > results[1])
    {
        printf("Passou por aqui! \n");
        k = A;
        A = B;
        B = k;
    }
    printf("A: %f, B: %f\nf(A): %f f(B): %f\n", A, B, results[0], results[1]);


    while ( fabs(results[0]) >= conv_crit)
    {

        function(def, A, B, results);
        g = (results[1] - results[0])/(B - A);
        c = B - results[1]/g;
        A = c;
        if( n > 300)
        {
            printf("Não convergiu!");
            break;
        }
        n++;

    }

    printf("\n Numéro de it: %d\n Raiz: %f\n f(Raiz): %f\n (A - B): %f\n Conv_crit: %f\n", n, c, results[0],fabs(A - B),conv_crit);

    return(EXIT_SUCCESS);


}
