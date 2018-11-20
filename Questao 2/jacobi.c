#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
    @shogunhirei
    Script for implementation of Jacobi Method

    Process:
        --> Insert number of equations
        --> insert coefficients
        --> Insert guesses
        --> Insert convergence criteria
        --> Determine R_i for every line
        --> Determine individually x_i (if attended to the convergence criteria)
    sáb 10 nov 2018 20:34:31 -02
*/

double* input_listing(int ar_len, double input[ar_len]){

    for(int i = 0; i < ar_len; i++)
    {
        scanf("%lf,",&input[i]);
    }
    return input;

}

int main(int argc, char** argv)
{
    int n_lin, i, j, n_solutions; //I'm gonna use the n_solutions to determine individuals solutions
    double conv_cri;
    int limite = 300;

    printf("Insira a ordem do sistema: ");
    scanf("%d",&n_lin);

    n_solutions = n_lin;

    /*
        @shogunhirei
        Parte inserção de dados na matriz, coefficientes e chutes iniciais
        sáb 10 nov 2018 20:45:49 -02
    */

    double matriz[n_lin][n_lin];
    double vet_b[n_lin];

    for (i = 0; i < n_lin; ++i) {
        printf("Insira os coeficientes da linha %d ",i); 
        input_listing(n_lin, matriz[i]);
        printf("Insira o vetor b%d ",i);
        scanf("%lf",&vet_b[i]);
    }

    double gues[n_solutions];
    printf("Insira os palpites agora, cara... ");
    input_listing(n_solutions, gues);

    printf("Insira o critério de convergência: ");
    scanf("%lf",&conv_cri);
    /*
        @shogunhirei
        Iniciando parte numérica do código
        Determinar R_i e x_i baseado no palpite inicial (gues[i])
        sáb 10 nov 2018 20:59:01 -02
    */
    double soma;
    double soma_res = 5;
    double residuo[n_lin];
    int n = 0;
    
    for(i = 0; i < n_lin; ++i){
        for (j = 0; j < n_lin; ++j) {
            printf("a%d%d: %f", i, j, matriz[i][j]);
        }
        printf(" b%d: %f Guess_%d: %f\n", i, vet_b[i], i, gues[i]);
    }

    while (soma_res > conv_cri)
    {
        soma_res = 0;
        for (i = 0; i < n_lin; ++i) {
            soma = 0;
            for (j = 0; j < n_lin; ++j)
            {
                soma += matriz[i][j]*gues[j];                      
            }
            residuo[i] = vet_b[i] - soma;
            printf("Residuo[%d]: %f \n ", i, residuo[i]);
            soma_res += fabs(residuo[i]/(matriz[i][i]*gues[i]));
            gues[i] = gues[i] + residuo[i]/matriz[i][i];
        }
        printf("Soma res: %f\n",soma_res);
        printf("Dif de %d: %f\n",i,(residuo[i]/matriz[i][i]));
        /*for(i = 0; i < n_lin; ++i)*/
        /*{*/
            /*if(soma_res > conv_cri)*/
            /*{*/
            /*}*/
            /*else*/
            /*{*/
                /*n_solutions -= 1;*/
            /*}*/
        /*}*/
            if(n > limite)
            {
                printf("Limite de operações atingido\n");
                break;
            }
        n++; 
    }


    for (i = 0; i < n_lin; ++i) {
        printf("X_%d: %f\n", i, gues[i]);
    }
    return(EXIT_SUCCESS);
}
