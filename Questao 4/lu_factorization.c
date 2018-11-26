#include <stdio.h>
#include <stdlib.h>

/*
    @shogunhirei
    EQE749 - Métodos Numéricos
    Implementação do Método de Fatorização LU (Doolitle)

    Processo:
    Inserir matrizes (fixadas, por enquanto)
    Decomposição em Matriz L e U, para resolver sistemas L*b' = b e U*X = b'
    Encontrar variáveis do vetor b'
    Depois usá-las para encontrar o vetor solução X;

    qui 22 nov 2018 18:08:15 -02
*/
void print_matriz(int n_lin, double matriz[n_lin][n_lin], double vet_b[n_lin]){
        printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        for (int y = 0; y < n_lin; ++y) {
            for (int g = 0; g < n_lin ; ++g) {
                printf(" a%d%d: %f,", y, g, matriz[y][g]);
            }
            printf(" b%d: %f \n", y, vet_b[y]);
        }
        printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
}

int main(int argc, char** argv)
{
   /*double mat[3][3] = {  {1, -2, 1},{2, 1, 2}, {-1, 1, 3} };*/
   double mat[3][3] = { {2, 3, 5}, {3, 1,-2}, {1, 3, 4} }; // LETRA B
   /*double vet_b[3] = { -1, 3, 8};*/
   double vet_b[3] = {0, -2, -3};// LETRA B
   int i, j, k;
   int n_lin = 3;
   double L[n_lin][n_lin];
   double U[n_lin][n_lin]; 
   double mult;
   double b_prime[n_lin];
   double soma = 0; 
   double sols[n_lin];

   for(i = 0; i < n_lin; i++)
   {
        U[0][i] = mat[0][i];
   }

   for (k = 0; k < n_lin ; ++k) {
       for ( i = k+1; i < n_lin; ++i) {
          L[k][k] = 1;
          mult = mat[i][k]/mat[k][k];
          L[i][k] = mult;
          U[i][k] = 0;
          for (j = 0; j < n_lin; j++)
          {
              mat[i][j] = mat[i][j] - mult * mat[k][j];
              U[i][j] = mat[i][j];
          }
       }
   }

       //TODO: Necessário Inserir Pivoteamento
       //@shogunhirei 
       //qui 22 nov 2018 19:45:41 -02


   L[n_lin - 1][n_lin - 1] = 1;
   printf("Matriz L\n");
   print_matriz(n_lin, L, vet_b);
   printf("Matriz U\n");
   print_matriz(n_lin, U, vet_b);

   /*
       @shogunhirei
       Resolução de Sistemas Lineares L e U
       1º -> Encontrar valores de b_prime
       2º -> Encontrar valores para X_n (sols)
       qui 22 nov 2018 20:00:53 -02
   */
   b_prime[0] = vet_b[0];
   
   // Forward Substituition
   for (k =1; k < n_lin; ++k) {
       b_prime[k] = vet_b[k];
       for (i = 0; i < k; ++i) {
           b_prime[k] = b_prime[k] - L[k][i] * b_prime[i];
       }
   }
   for (i = 0; i < n_lin; ++i) {
       printf("b'_%d: %f ", i, b_prime[i]);
   }

   //Backwards Substituition
   sols[n_lin - 1] = b_prime[n_lin - 1] / U[n_lin - 1][n_lin - 1];

    for (int n = n_lin - 2; n >= -1; --n)
    {
        soma = 0;
        for (int m = n_lin - 1; m > n; --m)
        {
            soma += U[n][m]*sols[m];
        }
        printf("Som= %f \n",soma);
        sols[n]=(vet_b[n] - soma)/U[n][n];
    }

    for (i=0; i<n_lin; i++)
    {
        printf("Variavel X_%d: %f \n" , i, sols[i]);
    }

   return(EXIT_SUCCESS);


}
