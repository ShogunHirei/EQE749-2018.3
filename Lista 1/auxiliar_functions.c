#include <stdio.h>
#include <math.h>
#include "auxiliar_functions.h"

/*
    @shogunhirei
    Criação de header para evitar declaração repetidas de funções 

    Sumário:
    1 --> pivotamento:  Função de Pivotamento Matricial
    2 --> diag_domim: Função para tornar diagonal da matriz dominante 
    3 --> input_listing:  Inserção de Dados
    4 --> print_matriz: Mostrar matriz e vetor reposta formatados
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

// Função para inserção de dados, evitar declaração
double* input_listing(int ar_len, double input[ar_len]){

    for(int i = 0; i < ar_len; i++)
    {
        scanf("%lf,",&input[i]);
    }
    return input;

}

void print_matriz(int n_lin, double matriz[n_lin][n_lin], double vet_b[n_lin]){
        printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        for (int y = 0; y < n_lin; ++y) {
            for (int g = 0; g < n_lin ; ++g) {
                printf(" A%d%d: %f,", y, g, matriz[y][g]);
            }
            printf(" B%d: %f \n", y, vet_b[y]);
        }
        printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
}

