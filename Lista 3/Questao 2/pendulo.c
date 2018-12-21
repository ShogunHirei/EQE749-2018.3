#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
    @shogunhirei
    EQE749 - Métodos Numéricos 
    3ª Lista de Exercícios - Questão 2. Oscilação de Pêndulo

    qui 20 dez 2018 10:37:19 -02
*/

#define g 9.80665

void euler_explicit(double teta_prev[2], double dT, double L, int type, double Teta_next[2]);

int main(int argc, char** argv)
{
    int i, j, k; // Contadores diversos
    double Comprim[3] = {0.1, 1.0, 10.0}; // Comprimentos da corda do pendulo 
    double passos_tempo[4] = {1.25, 0.3125, 0.078125, 0.02};

    //Array com as condições iniciais apresentadas no corpo da questão 
    // Primeiro Item:
    //      Resolver a EDO aproximada para as condição de contorno Teta0 = 0.1 radianos 
    //      utilizando comprimento de 0.1, 1e 10 m
    // Segundo Item:
    //      Resolver a EDO aproximada para as condição de contorno Teta0 = 0.5 radianos 
    //      utilizando comprimento de 0.1, 1e 10 m
    double teta0;
    double Teta_next[2];
    double abs_error;
    double rel_error;
    double Teta_prev[2];
    double dT;
    double Temp_acum; // Para plotar gráfico com tempo acumulado
    double num_passos;
    double L;
    double tempo;  // Valor maximo de tempo observado
    FILE *file;
    
    file = fopen("Q2_letraC.txt", "w");

    printf("Insira o tempo máximo de observação: ");
    scanf("%lf",&tempo);

    printf("Insira o deslocamento inicial, Teta0(0), em radianos:  ");
    scanf("%lf",&teta0);

    double Teta_zero[2] = {teta0, 0.0}; 

    for (i = 0; i < sizeof(passos_tempo)/sizeof(double); i++)
    {
        dT = passos_tempo[i];

        for (j = 0; j < 3; j++)
        {
            Teta_prev[0] = Teta_zero[0];
            Teta_prev[1] = Teta_zero[1];

            L = Comprim[j];
            
            num_passos = tempo / dT;

            fprintf(file, "------- Passo de tempo:  %f e Comprimento: %f, Teta0 = %f, \n",
                        dT, L, Teta_prev[0]); 

            fprintf(file, "Passo \t Tempo(s) \t Euler Explíc. \t Err. Abs. \t Err. Rel.\n");

            abs_error = 0;
            rel_error = 0;
            Temp_acum = 0;

            for (k = 0; k < num_passos; k++)
            {
                fprintf(file, "%d \t %f \t %f \t %f \t %f\n",k, Temp_acum, Teta_prev[0],abs_error, rel_error);
                euler_explicit(Teta_prev, dT, L, 1, Teta_next);
                abs_error = fabs(Teta_prev[0] - Teta_next[0]);
                rel_error = fabs( (Teta_prev[0] - Teta_next[0])/Teta_prev[0] * 100);
                Teta_prev[0] = Teta_next[0];
                Teta_prev[1] = Teta_next[1];
                Temp_acum += dT;
                
            }
            fprintf(file, "--------------------------------------------\n\n");
        }
    }
    fclose(file); // Fim da Letra C, 

    // O mesmo processo para a Letra D
    file = fopen("Q2_letraD.txt", "w");

    for (i = 0; i < sizeof(passos_tempo)/sizeof(double); i++)
    {
        dT = passos_tempo[i];

        for (j = 0; j < 3; j++)
        {

            Teta_prev[0] = Teta_zero[0];
            Teta_prev[1] = Teta_zero[1];

            L = Comprim[j];
            
            num_passos = tempo / dT;

            fprintf(file, "------- Passo de tempo:  %f e Comprimento: %f, Teta0 = %f, \n",
                        dT, L, Teta_prev[0]); 

            fprintf(file, "Passo \t Tempo(s) \t Euler Explíc. \t Err. Abs. \t Err. Rel.\n");

            abs_error = 0;
            rel_error = 0;
            Temp_acum = 0;

            for (k = 0; k < num_passos; k++)
            {
                fprintf(file, "%d \t %f \t %f \t %f \t %f\n",k, Temp_acum, Teta_prev[0],abs_error, rel_error);
                euler_explicit(Teta_prev, dT, L, 0, Teta_next);
                abs_error = fabs(Teta_prev[0] - Teta_next[0]);
                rel_error = fabs( (Teta_prev[0] - Teta_next[0])/Teta_prev[0] * 100);
                Teta_prev[0] = Teta_next[0];
                Teta_prev[1] = Teta_next[1];
                
            }
            fprintf(file, "---------------------------------------------\n\n");
        }
    }
    fclose(file); // Fim da Letra D, 


    return(EXIT_SUCCESS);
}


void euler_explicit(double teta_prev[2], double dT, double L, int type, double Teta_next[2])
{
    // Função para avaliar o valor de Euler Explicito para 
    // as funções aproximada (letra C) e não-aproximada (letra D)
    //  Se tipo == 0 é a edo não aproximada 
    //  se tipo diferente de 0 é a edo aproximada sin y ~= y
    
    if (type == 0 ) 
    {
        Teta_next[1] = teta_prev[1] + dT * ((-g/L) * sin(teta_prev[0]));
        Teta_next[0] = teta_prev[0] + dT * (Teta_next[1]);
    }
    else
    {
        Teta_next[1] = teta_prev[1] + dT * ((-g/L) * teta_prev[0]);
        Teta_next[0] = teta_prev[0] + dT * (Teta_next[1]);
    }

}

