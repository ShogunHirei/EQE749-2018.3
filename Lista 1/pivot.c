#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*
    @shogunhirei
    EQE749 - Métodos Numéricos
    Inserindo função de pivotamento de matriz

    Processo:
    Input será o indice da linha e coluna
    Matriz também será argumento da função 
    Função genérica para que possa ser integrada aos outros códigos
    *Possível mudança para header
    
    **Tentar utilizar ponteiros;

    ***Verificar função para diagonal dominante 
    seg 26 nov 2018 18:40:28 -02
*/
void pivot_mat(int i, int n, double mat[n][n])
{
    // O processo de pivotamento é baseado no julgamento 
    // de que aquela linha não é adequada para a eliminação 
    // pretendida, pois contém zeros nas colunas posteriores
    // à coluna analisada;
    // Para a eliminação Gaussiana e Fatorização LU verificar 
    //  zeros acima da diagonal principal 
    double subs1[n];
    double subs2[n];

    for (int k = i; k < n; k++)
    {
        for (int j = k + 1; j < n; j++)
        {
           // COmeçando da linha especificada pela entrada 
           // Avaliar os valores das linhas abaixo dela
           // começando da próxima, pivotando a diagonal apenas(?)
           //
           if(fabs(mat[k][k]) < fabs(mat[j][k]))
           {
               for(int s = k; s < n; s++)
               {
                   subs1[s] = mat[k][s];
                   mat[k][s] = mat[j][s];
                   mat[j][s] = subs1[s];

               }
           } 
        }

    }
     
}
void diag_domin(int n, double mat[n][n])
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
                   for (int el = 0; el < n; el++)
                   {
                       subs = mat[k][el];
                       mat[k][el] = mat[i][el];
                       mat[i][el] = subs;
                   }
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
   //double mat[3][3] = {  {1, -2, 1},{2, 1, 2}, {-1, 1, 3} };
   double mat[3][3] = { {2, 3, 5}, {3, 1,-2}, {1, 3, 4} }; // LETRA B
   //double vet_b[3] = { -1, 3, 8};
   double vet_b[3] = {0, -2, -3};// LETRA B
   int n_lin = 3;
   int i, j, k;
   
   //pivot_mat(0, n_lin, mat);
   diag_domin(n_lin, mat);
   for (i = 0; i < n_lin; ++i) {
       for (j = 0; j < n_lin; ++j) {
           printf("A%d%d: %f, ", i, j, mat[i][j]);
       }
       printf("\n");
   }

   return(EXIT_SUCCESS);
}
