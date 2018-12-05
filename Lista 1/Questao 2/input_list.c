#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/*
    @shogunhirei
    Function to insert data more easily, because, seriously, element-wise its a pain in the ass

    Process:
    -> Input string;
    -> Read string;
    -> identify marker (",")
    -> Identify elements between markers (data)
    -> Create array with the length equal to the numbers of marks + 1
    ->         Problem: Converts string of text to number
    ->         Inicial solution: convert element-wise char and sum them up
    -> Do this for every markers + 1, 
    -> End: Return array
    sáb 10 nov 2018 12:39:52 -02
*/

void pivotamento(int n_lines, int indice_linha, double matriz[n_lines][n_lines], double vetor[n_lines])
{
     /*
         @shogunhirei
         Função para pivotamento de de matriz 

         O pivoteamento consiste na técnica de mudança de linhas e colunas 
         para manter o elemento de maior modulo como elemento inicial da linha
         ou de forma que ele seja conveniente à operação sendo realizada.

         Processo (Pivoteamento de linhas):
         --> Para a linha indicada:
            --> Verificar se existem outros elementos com maior módulo na mesma coluna:
            -->     Caso sim, mudar linha atual com linha da coluna indicada, incluindo termo fonte
            --> Verificar se existem valores maiores na linha:
            -->     Caso sim, trocar as colunas de lugar, e mudar o vet solução;

         *Vou me abster do pivoteamento de colunas por enquanto
         ter 04 dez 2018 22:52:59 -02
     */
    // Pivoteamento de Linhas
    // Matriz -> Matriz que será pivoteada
    // Vetor -> pode ser termo-fonte ou vetor solução, depende do pivot 
    int i, j, k; // Contadores genéricos
    double troca1; // Para substituição de valores entre linhas 

    i = indice_linha;
    for (j = indice_linha + 1; j < n_lines; j++)
    {

        printf("A%d%d: %f, A%d%d: %f, \n",i + 1, i + 1, matriz[i][i],i + 1, j + 1, matriz[j][i]);
        if(fabs(matriz[i][i]) < fabs(matriz[j][i]))
        {
            // Etapa de troca de elementos das matriz e vetor
            for (k = indice_linha; k < n_lines; k++)
            {
                troca1 = matriz[i][k];
                matriz[i][k] = matriz[j][k];
                matriz[j][k] = troca1;
            }
            troca1 = vetor[indice_linha];
            vetor[indice_linha] = vetor[j];
            vetor[j] = troca1;
        }
    }
    
}
int main(int argc, char** argv)
{
    int i,j,k;
    double mat[3][3] = { {0,3,2},{2,5,3},{7, 1, 0} };
    double vet[3] = { 3, 2, 1}; 

    pivotamento(3,1, mat, vet);
    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            printf("A%d%d: %f, ",i + 1, j + 1, mat[i][j]);
        }
        printf("\n");
    }
    return(EXIT_SUCCESS);
}
