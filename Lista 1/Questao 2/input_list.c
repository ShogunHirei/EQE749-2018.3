/*#ifndef helper_funtions.h*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
/*
    @shogunhirei
    Criação de header para evitar declaração repetidas de funções 
    qua 05 dez 2018 10:31:35 -02
*/

void pivotamento(int n_lines, int indice_linha, double matriz[n_lines][n_lines], double vetor[n_lines])
{ /*
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
    for (int k = 0; k < n; k++)
    {
        soma = 0; 

        for (int s = 0; s < n; s++) // Somatorio das elementos das linhas 
        {
            soma += mat[k][s];
        }

        soma = fabs(soma - mat[k][k]); // Retirando a diagonal principal
        
        for (int i = k + 1; i < n ; i++)
        {

            if(fabs(mat[k][k]) <= soma)
            {
               // Verificando se as outras linhas seriam diagonais dominantes 
               // nessa diagonal (k) de refereência
               soma2 = 0;

               for (int col = 0; col < n; col++) 
               {
                   soma2 += mat[i][col];
               }
               // Usando a coluna de referencia como valor que seria da diagonal
               soma2 = fabs(soma2 - mat[i][k]);

               if(mat[i][k] >= soma2)
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
                   for (int lin = 0; lin < n; ++lin) {
                       for (int col = 0; col < n; ++col) {
                           printf("A%d%d: %f, ", lin, col, mat[lin][col]);
                       }
                       printf("Linhas alteradas %d com %d \n", i, k);
                   }
               }
               else
               {
                   printf("A linha %d não seria dominante no lugar da linha %d\n", i, k);
               }
            }
            printf("Já tem a diagonal dominante L%d\n ",k);
        }
    }
}

int main(int argc, char** argv)
{
    int i,j,k;
    double mat[3][3] = { {0,3,3},{2,5,3},{7, 1, 0} };
    double vet[3] = { 3, 2, 1}; 

    pivotamento(3,0, mat, vet);
    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            printf("A%d%d: %f, ",i + 1, j + 1, mat[i][j]);
        }
        printf("b%d: %f ", i, vet[i]);
        printf("\n");
    }

    diag_domin(3, mat, vet);
    
    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            printf("A%d%d: %f, ",i + 1, j + 1, mat[i][j]);
        }
        printf("b%d: %f ", i, vet[i]);
        printf("\n");
    }
    return(EXIT_SUCCESS);
}


/*#endif*/
