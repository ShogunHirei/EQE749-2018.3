#include <stdio.h>
#include <stdlib.h>

/*
    @shogunhirei
    EQE749 - Métodos Numéricos
    Questão 5 - Gerar método para resolver matrizes Pentadiagonais baseadas no Algoritmo de 
    Thomas (Questão 2)

    Processo:
    De acordo com a literatura abordada o método opera de forma similar à
    eliminação gaussiana, basicamente difere pela redução dos usos computacionais

    Etapas:
    -> Inserir Matriz dos valores da Pentadiagonal 
    -> Inserir vetores (todos de uma vez)
    -> Encontrar Mult_1
    -> Encontrar A_lin3
    -> Encontrar A_linh2
    -> Encontrar Mult_2
    -> Encontrar A_lin_i-1,4
    -> Encontrar A_i_3

    ter 20 nov 2018 18:28:14 -02
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
   int n_lin;
   int i, j, k, m; // Contadores diversos
   double mult1;
   double mult2;
   double mat[8][5] = {{0 , 0,  2, 1, 3},
                       {0, 1, 2, 1, 3},
                       { 3, 1, 2, 1, 3},
                       { 3, 1, 2, 1, 4},
                       { 3, 1, 5, 1, 3},
                       { 1, 1, 2, 1, 3},
                       { 3, 1, 2, 1, 0.0},
                       { 3, 1, 2, 0.0 , 0.0}};
   double vet_b[8] = {1, 1, 1, 1, 1, 1, 1, 100};
   double sols[8]; 
   /*printf("Insira a quantidade de linhas da Matriz pentadiagonal: ");*/
   /*scanf("%lf",&n_lin);*/
   
   /*double mat[n_lin][5];*/

   /*for (i = 0; i < n_lin; i++)*/
   /*{*/
       /*printf("Insira os coeficientes da linha %d: ", i );*/
       /*input_listing(5, mat[i]);*/
   /*}*/

   /*printf("Insira os coeficientes das matriz: ");*/
   /*input_listing(n_lin, vet_b);*/

   mat[1][2] = mat[1][2] - (mat[1][1]/mat[0][2]) * mat[0][3];
   mat[1][3] = mat[1][3] - (mat[1][1]/mat[0][2]) * mat[0][4];
   vet_b[1] = vet_b[1] - (mat[1][1]/mat[0][2]) * vet_b[0];

       /*@shogunhirei*/
       /*Iniciando eliminação de acordo com as etapas descritas anteriormente*/
       /*definidos os valores necessários para a23 (diagonal principal) e a24 (superdiagonal 1) */
       /*ter 20 nov 2018 19:09:38 -02*/

   for (i = 2; i < 8; i++)
   {
       //Nova tentativa 
       // Encontrar a'_2
       mat[i][1] = mat[i][1] - (mat[i][0]/mat[i-2][2]) * mat[i-2][3];

       // Encontrae a'i3
       mat[i][2] = mat[i][2] - (mat[i][0]/mat[i-2][2]) * mat[i-2][4];

       //Encontrar a"_i3
       mat[i][2] = mat[i][2] - (mat[i][1]/mat[i-1][2]) * mat[i-1][3];

       // Encontrar a"_i4
       mat[i][3] = mat[i][3] - (mat[i][1]/mat[i-1][2]) * mat[i-1][4];

       // Encontrar o valor de vetor b com as mesmas trasnformações efetuadas na linha 
       vet_b[i] = vet_b[i] - (mat[i][0]/mat[i-2][2])* vet_b[i-2] - (mat[i][1]/mat[i-1][2]) * vet_b[i-1];
   }
   for (i = 0; i < 8; ++i) {
       for (j = 0; j < 5; ++j) {
            printf(" a%d%d => %f |", i, j, mat[i][j]);
       }
       printf("b%d => %f \n", i, vet_b[i]);
   }

   // Como não existem valores nos últimos elementos da superdiagonal 1 e 2 (colunas 4 e 5)
   //  é necessário definir a solução X_(n - 1) e X_n manualmente
   sols[7] = vet_b[7]/mat[7][2];
   sols[6] = (vet_b[6] - mat[6][3] * sols[7])/mat[6][2];

   // Para encontrar as outras soluções 
   for (j = 5 ; j > -1; j--)
   {
       sols[j] = (1/mat[j][2])*(vet_b[j] - mat[j][3]*sols[j+1] - mat[j][4]*sols[j+1]);
   }

   for (i = 0; i < 8; ++i) {
       printf("X_%d - > %f \n", i, sols[i]);
   }

   return(EXIT_SUCCESS);
}
