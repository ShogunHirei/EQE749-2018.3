#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
    @shogunhirei
    EQE749 - Métodos Numéricos
    3ª Lista de Exercícios - Questão 1

    Obs.: Fixarei a variação do tempo em dT1 = 20, dT2 = 5, dT3 = 1.25, dT4 = 0.3125

    ter 18 dez 2018 18:17:13 -02
*/

#define tempo_total 50.0 // Restrição temporal imposta 
#define T0 2500
#define Ta 250
#define alpha 4E-12

int main(int argc, char** argv)
{
    int i, j, k, m; // Contadores diversos 
    double passos_temp[4] = {20.0, 5.0, 1.25, 0.3125};
    
    printf("******************** Item a *******************\n");

    double Tn;
    int num_passos;
    // Para plotar os dados em gráfico
    double dados[160]; // Usando o maior quantidade de passos para todos os sistemas

    for ( i = 0; i < sizeof(passos_temp); i++)
    {
        // Respeitando a restrição do tempo de 0 a 50 segundos 
        num_passos = abs(tempo_total/passos_temp[i]);

        for(j = 0; j < num_passos; j++)
        {
            
        }
        


    }

    

     
}
