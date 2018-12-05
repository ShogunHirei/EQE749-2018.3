#include <stdio.h>
#include <stdlib.h>

/*
    @shogunhirei
    EQE749 - Métodos Numéricos
    Implementação do Algoritmo de Thomas;
    Considerando os elementos da tridiagonal juntos

    Processo:
    --> Considerar Inserção de apenas matrizes tridiagonais
    --> Adquirir matriz A' através das equações
    --> Adquirir vetor B' através das equações
    Processo de retorno: 
    -> Critério de Resolução: diagonal A' dominante
    -> Usar equação do livro
    dom 11 nov 2018 20:57:32 -02
*/

#define n_lin 4

void print_matriz(int n_line, double matriz[n_line][n_line], double vet_b[n_line]);

int main(int argc, char** argv)
{
    int i;
    double matriz_linha[n_lin][3];
    double sols[n_lin];
    double m; //multiplicador
    double matriz[n_lin][n_lin] = {{-2, 1, 0, 0}, {1,-2, 1, 0}, {0, 1, -2, 1}, {0, 0, 1, -2}};
    double vet_b[n_lin] = {1, 2, -7, -1}; 
    /*
        @shogunhirei
        Inserir matriz normalmente, agora realizar transformação para matriz nx3 
        dom 11 nov 2018 21:34:28 -02
    */

    matriz_linha[0][1] = matriz[0][0]; // Diagonal Principal;
    matriz_linha[0][2] = matriz[0][1];

    matriz_linha[n_lin - 1][0] = matriz[n_lin - 1][n_lin - 2];
    matriz_linha[n_lin - 1][1] = matriz[n_lin - 1][n_lin - 1];

    for (i = 1; i < (n_lin - 1); ++i) {
        matriz_linha[i][0] = matriz[i][i-1];
        matriz_linha[i][1] = matriz[i][i];
        matriz_linha[i][2] = matriz[i][i+1];
    }

    // Mostrando a matriz para conferir coeficientes 

    print_matriz(n_lin, matriz, vet_b);

    for (i = 1; i < n_lin; ++i) {
        // Operação de Eliminação, Li - M * Lj
        m = (matriz_linha[i][0]/matriz_linha[i-1][1]);
        matriz_linha[i][1] = matriz_linha[i][1] - m * matriz_linha[i-1][2];
        vet_b[i] = vet_b[i] - m  * vet_b[i-1];
    }
    /*Inicio de processo de retorno */
    // Especificando o último valor do conjunto de soluções 
    sols[n_lin - 1] = vet_b[n_lin - 1]/matriz_linha[n_lin-1][1];

    for (i = n_lin - 2; i >= 0; i-- )
    {
        sols[i] = (vet_b[i] - matriz_linha[i][2]*sols[i+1])/matriz_linha[i][1];
    }

    // Mostrando matriz final e soluções
    printf("Matriz_linha alterada \n");

    for (i = 0; i < n_lin; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            printf("a%d%d: %f ", i, j, matriz_linha[i][j]);
        }
        printf("b%d: %f\n", i, vet_b[i]);
    }
    // Mostrando resultados do conjunto solução 
    for (i = 0; i < n_lin; ++i) 
    {
        printf("X_%d: %f\n", i, sols[i]);
    }

    return(EXIT_SUCCESS);

}

void print_matriz(int n_line, double matriz[n_line][n_line], double vet_b[n_line])
{
        printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        for (int y = 0; y < n_line; ++y) 
        {
            for (int g = 0; g < n_line ; ++g) 
            {
                printf(" a%d%d: %f,", y, g, matriz[y][g]);
            }
            printf(" b%d: %f \n", y, vet_b[y]);
        }
        printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
}
