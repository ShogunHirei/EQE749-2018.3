#include <stdio.h>
#include <stdlib.h>

/*
    @shogunhirei
    EQE749 - Métodos Numéricos
    Implementação do Algoritmo de Thomas;

    Processo:
    --> Considerar Inserção de apenas matrizes tridiagonais
    --> Adquirir matriz A' através das equações
    --> Adquirir vetor B' através das equações
    Processo de retorno: 
    -> Critério de Resolução: diagonal A' dominante
    -> Usar equação do livro
    dom 11 nov 2018 20:57:32 -02
*/

double* input_listing(int ar_len, double input[ar_len]){

    for(int i = 0; i < ar_len; i++)
    {
        scanf("%lf,",&input[i]);
    }
    return input;

}
void print_matriz(int n_lin, double matriz[n_lin][n_lin], double vet_b[n_lin])
{
        printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        for (int y = 0; y < n_lin; ++y) 
        {
            for (int g = 0; g < n_lin ; ++g) 
            {
                printf(" a%d%d: %f,", y, g, matriz[y][g]);
            }
            printf(" b%d: %f \n", y, vet_b[y]);
        }
        printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
}

int main(int argc, char** argv)
{
    int n_lin, i;
    
    printf("Insira a ordem do sistema TRIDIAGONAL: ");
    scanf("%d",&n_lin);

    double vet_b[n_lin];
    double matriz[n_lin][n_lin];
    double matriz_linha[n_lin][3];
    double sols[n_lin];
    double m; //multiplicador

    for (i = 0; i < n_lin; ++i) {
        printf("Insira os elementos da linha %d ->",i);
        input_listing(n_lin, matriz[i]);
        printf("Insira o vetor b%d ",i);
        scanf("%lf",&vet_b[i]);
    }
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


    for (i = 0; i < n_lin; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            printf("a%d%d: %f ", i, j, matriz_linha[i][j]);
        }
        printf("b%d: %f\n", i, vet_b[i]);
    }

    for (i = 1; i < n_lin; ++i) {
        m = (matriz_linha[i][0]/matriz_linha[i-1][1]);
        matriz_linha[i][1] = matriz_linha[i][1] - m*matriz_linha[i-1][2];
        vet_b[i] = vet_b[i] - m*vet_b[i-1];
    }

    sols[n_lin - 1] = vet_b[n_lin - 1]/matriz_linha[n_lin-1][1];

    for (i = n_lin - 2; i >= 0; i-- )
    {
        sols[i] = (vet_b[i] - matriz_linha[i][2]*sols[i+1])/matriz_linha[i][1];
    }

    printf("Matriz_linha alterada \n");

    for (i = 0; i < n_lin; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            printf("a%d%d: %f ", i, j, matriz_linha[i][j]);
        }
        printf("b%d: %f\n", i, vet_b[i]);
    }
    for (i = 0; i < n_lin; ++i) 
    {
        printf("X_%d: %f\n", i, sols[i]);
    }

    return(EXIT_SUCCESS);

}
