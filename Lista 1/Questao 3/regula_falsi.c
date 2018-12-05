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

void regula_falsi(double A, double B, int def)
{
    double conv_crit = 0.000001;
    double results[2];
    double k;
    double g; 
    double c;
    int n = 0; //COntrole de loop

    function(def, A, B, results); 
    //Cálculo de F(a) e F(b) para determinar qual a direção de aumento da função
    printf("F(a): %f ; F(b): %f\n",results[0], results[1]);

    if(results[0] > results[1]) // Mudando valores de intervalo para evitar problemas com sinais
    {
        printf("Passou por aqui! \n");
        k = A;
        A = B;
        B = k;
    }
    printf("A: %f, B: %f\nf(A): %f f(B): %f\n", A, B, results[0], results[1]);

    while ( fabs(results[0]) >= conv_crit)
    {
        function(def, A, B, results); // Cálculo de F(a) e F(b)
        g = (results[1] - results[0])/(B - A); //Determinação do ponto que passa a nova reta  
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

}

int main(int argc, char** argv)
{
     
    double A, B;
    int def;

    // Letra A 
    A = -3.5;
    B = 2.5;
    def = 1;

    regula_falsi( A,  B,  def);

    // Letra B
    A = 0.0;
    B = 1.0;
    def = 0;

    regula_falsi( A,  B,  def);
    

    return(EXIT_SUCCESS);


}
