#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
    @shogunhirei
    EQE749 Métodos Numéricos
    Método de Gauss-Seidel de Resolução de Sistemas lineares

    Processo:
    --> Similar ao Jacobi...
    --> Mudança nas etapas de do próximo Xi da iteração
    --> Residuo também é alterado
    --> As mudanças nas variaveis são feitas assim que determinadas
        as aproximações
    dom 11 nov 2018 12:39:22 -02
*/

void print_matriz(int n_line, double matriz[n_line][n_line], double vet_b[n_line]);

void diag_domin(int n, double mat[n][n], double vetor[n]); 

#define n_lin 3 

int main(int argc, char** argv)
{
    int i, j; // Contadores Diversos
    int n = 0; // Contador de Loop;
    int limite = 300; // Máximo de iterações
    double soma;
    double soma_res ; 
    double soma_antes;
    double soma_depois;
    double residuo[n_lin];
    double conv_cri = 0.000000001;
    double gues[n_lin] = {0, 0, 0};
    // Matriz A
    double matriz[n_lin][n_lin] = {{1, -2, 1}, {2, 1, 2}, {-1, 1, 3}}; 
    double vet_b[n_lin] = {-1, 3, 8};
    // Matriz B
    //double matriz[n_lin][n_lin] = {{2, 3, 5}, {3, 1, -2}, {1, 3, 4}}; 
    //double vet_b[n_lin] = {0, -2, -3};

    /*
        @shogunhirei
        Iniciando parte numérica do código
        Determinar R_i e x_i baseado no palpite inicial (gues[i])
        sáb 10 nov 2018 20:59:01 -02
    */
    

    print_matriz(n_lin, matriz, vet_b);

    printf("Depois da diagonalização \n");
    
    diag_domin(n_lin, matriz, vet_b); 

    print_matriz(n_lin, matriz, vet_b);

    do
    {
        soma_res = 0;
        for (i = 0; i< n_lin; i++)
        {
            soma_antes = 0;
            soma_depois = 0;
            for (j = 0; j < n_lin; ++j) 
            {
                if(j < i)
                {
                    soma_antes +=matriz[i][j]*gues[j];
                }
                else
                {
                    soma_depois += matriz[i][j]*gues[j];
                }
            }

            residuo[i] = vet_b[i] - soma_antes - soma_depois;
            soma_res += fabs(residuo[i]/matriz[i][i]);
            printf("Gues_ant%d = %f; Soma_antes%d = %f; Soma_depois%d = %f; Residuo%d  = %f\n", i, gues[i], i, soma_antes, i, soma_depois, i, residuo[i]);
            gues[i] = gues[i] + residuo[i]/matriz[i][i];
            printf("Soma_res: %f; g_%d: %f\n",soma_res, i, gues[i]);

        }
        if(n > limite)
        {
            printf("Limite de operações atingido\n");
            break;
        }
    }while (soma_res > conv_cri);
    for (i = 0; i < n_lin; ++i) {
        printf("X_%d: %f\n", i, gues[i]);
    }
}

void print_matriz(int n_line, double matriz[n_line][n_line], double vet_b[n_line]){
        printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        for (int y = 0; y < n_line; ++y) {
            for (int g = 0; g < n_line ; ++g) {
                printf(" A%d%d: %f,", y, g, matriz[y][g]);
            }
            printf(" B%d: %f \n", y, vet_b[y]);
        }
        printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
}

void diag_domin(int n, double mat[n][n], double vetor[n]) // n ->  número de linhas; ordem da matriz
{
    /*
        @shogunhirei
        -> Por causa da definção de i = (k+1) o código não verifica se as linhas 
        ->      anteriores seriam diagonais dominantes no lugar dessa
        ter 27 nov 2018 00:02:09 -02
    */
    double soma = 0; // Para verificar se a diagonal atual é dominante 
    double soma2 = 0;// Verficar se as outras linhas seriam diagonais dominantes
    double subs; // substituir elemento por elemento;
    /*
        @shogunhirei
        Os critérios de diagonalidade dominante podem ser divididos em:
            Estritamente diagonal (matrizes não singulares)
            Fracamente diagonal (matrizes não singulare)
            Fracamente diagonal acorrentada (matrizes singulares e não singulares)*
        Para garantir que a matriz não seja singular, ela deve ser pelo menos fracamente diagonal
        acorrentada (ou seja, o último elemento deve ter diagonal dominante)

        *Tradução livre
        qua 05 dez 2018 14:25:21 -02
    */
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

