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


void pivotamento(int n_lines, int indice_linha, double matriz[n_lines][n_lines], double vetor[n_lines]);
void diag_domin(int n, double mat[n][n], double vetor[n]); 

#define n_lin 3 // Número de Linhas 

int main(int argc, char** argv)
{
    int i, j; // Contadores Diversos
    int n = 0; // Contador de Loop;
    int limite = 30; // Máximo de iterações
    double soma;
    double soma_res ; 
    double residuo[n_lin];
    double conv_cri = 0.000000001;
    // Matriz A
    //double matriz[n_lin][n_lin] = {{1, -2, 1}, {2, 1, 2}, {-1, 1, 3}}; 
    //double vet_b[n_lin] = {-1, 3, 8};
    // Matriz B
    double matriz[n_lin][n_lin] = {{2, 3, 5}, {3, 1, -2}, {1, 3, 4}}; 
    double vet_b[n_lin] = {0, -2, -3};
    double gues[n_lin] = {0, 0, 0};
    /*
        @shogunhirei
        Iniciando parte numérica do código
        Determinar R_i e x_i baseado no palpite inicial (gues[i])
        sáb 10 nov 2018 20:59:01 -02
    */
    

    for (int i = 0; i < n_lin; i++)
    {
        for (int j = 0; j< n_lin; j++)
        {
            printf("A%d%d: %f, ", i+1, j+1, matriz[i][j]);
        }
        printf("b%d:  %f \n",i+1, vet_b[i]);
    }

    printf("Depois da diagonalização \n");

    diag_domin(n_lin, matriz, vet_b); 

    for(i = 0; i < n_lin; ++i){
        for (j = 0; j < n_lin; ++j) {
            printf("a%d%d: %f", i, j, matriz[i][j]);
        }
        printf(" b%d: %f Guess_%d: %f\n", i, vet_b[i], i, gues[i]);
    }

    do
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

        if(n > limite)
        {
            printf("Limite de operações atingido\n");
            break;
        }
        n++; 
    }while (soma_res > conv_cri);


    for (i = 0; i < n_lin; ++i) {
        printf("X_%d: %f\n", i, gues[i]);
    }
    return(EXIT_SUCCESS);
}


void diag_domin(int n, double mat[n][n], double vetor[n]) // n ->  número de linhas; ordem da matriz
{
    /*
        @shogunhirei
        PIvotamento - Limitações observadas 
        -> Por causa da definção de i = (k+1) o código não verifica se as linhas 
        ->      anteriores seriam diagonais dominantes no lugar dessa
        ter 27 nov 2018 00:02:09 -02
    */
    double soma = 0; // Para verificar se a diagonal atual é dominante 
    double soma2 = 0;// Verficar se as outras linhas seriam diagonais dominantes
    double subs; // substituir elemento por elemento;
    for (int k = n - 1; k > -1; k--)
    {
        soma = 0; 

        for (int s = 0; s < n; s++) // Somatorio das elementos das linhas 
        {
            soma += fabs(mat[k][s]);
        }

        soma = soma - fabs(mat[k][k]); // Retirando a diagonal principal
        
        for (int i = n - 1; i > -1 ; i--)
        {

            if(fabs(mat[k][k]) <= soma)
            {
               // Verificando se as outras linhas seriam diagonais dominantes 
               // nessa diagonal (k) de refereência
               soma2 = 0;

               for (int col = 0; col < n; col++) 
               {
                   soma2 += fabs(mat[i][col]);
               }
               // Usando a coluna de referencia como valor que seria da diagonal
               soma2 = soma2 - fabs(mat[i][k]);

               if(fabs(mat[i][k]) >= soma2)
               {
                   for (int el = 0; el < n; el++) // Etapa de troca de diagonal
                   {
                       subs = mat[k][el];
                       mat[k][el] = mat[i][el];
                       mat[i][el] = subs;
                   }
                   subs = vetor[k];
                   vetor[k] = vetor[i];
                   vetor[i] = subs;
               }
            }
        }
    }
}

