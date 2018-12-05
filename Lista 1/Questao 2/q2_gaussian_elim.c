#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*
    @shogunhirei
    EQE749 - Métodos Numéricos 
    Implementação do método de Eliminação Gaussiana para
    Resolução da Questão Nº da 1ª Lista de exercicios
    qui 08 nov 2018 13:19:57 -02
*/

void pivotamento(int n_lines, int indice_linha, double matriz[n_lines][n_lines], double vetor[n_lines]);

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

#define n_lin 3

int main(int argc, char** argv)
{
    /*
        @shogunhirei
        Etapas do Processo de Eliminação:
        -> Inserir dados na matriz (garantir matriz quadrada)
        -> Verificar Pivotamento das linhas
        -> Percorrer linhas para colunas (eliminação de elemeto 1 a 1)
        -> Aumentar indice de coluna
        -> Retornar ao item de Pivotamento até fim das colunas (m-1)
        Etapas do processo de retorno:
        -> Encontrar último X_(n)
        -> Percorrer a partir de penultima linha
        -> Para cada variavel usar formula para determinar valor
        -> Ir para próxima linha -> (n-1)
        Adicionar valores de Xn à um array com as repostas
            (ou apresentar em sequencia)

        
        Declaração de Variaveis:
        -> Indices: i j m n...
        -> Número de linhas -> (User)
        -> Número de colunas -> Implicito == (n linhas)
        -> Matriz -> Implicito: LinhasxColunas
        -> Elementos da Matriz -> (User)
        -> Vetor-Resposta -> Implicito == (n linhas)
        -> Dados do Vetor -> (User) 
        -> Vetor de Resposta (implicito)
        qui 08 nov 2018 13:26:52 -02
    */
    int m_col = n_lin;
    int i,j,k,m;

    // Matriz A
    double matriz[n_lin][n_lin] = {{1, -2, 1}, {2, 1, 2}, {-1, 1, 3}}; 
    double vet_b[n_lin] = {-1, 3, 8};
    // Matriz B
    //double matriz[n_lin][n_lin] = {{2, 3, 5}, {3, 1, -2}, {1, 3, 4}}; 
    //double vet_b[n_lin] = {0, -2, -3};

    print_matriz(n_lin, matriz, vet_b);

    for (j = 0; j < m_col; j++) {

        pivotamento(n_lin, i, matriz, vet_b);

        for (i = j+1; i < n_lin; i++) {


            double b = matriz[j][j];
            double c = matriz[i][j];
            double mul = b/c;
            for (m = 0; m < m_col; m++) {
                double a = matriz[i][m]; 
                double d = matriz[j][m];
                matriz[i][m]=a*mul-d;
            }
            vet_b[i]=vet_b[i]*mul - vet_b[j];
            print_matriz(n_lin, matriz, vet_b);
        }
    }
        //TODO: Finalizado a parte de diagonalização
        //@shogunhirei 
        //qui 08 nov 2018 16:51:29 -02
    /*
        @shogunhirei
        Inserir Processo de Retorno e Aquisição de Variáveis
        qui 08 nov 2018 16:52:12 -02
    */
    double vet_vars[n_lin];
    /*
        @shogunhirei
        Determinando X_n;
        qui 08 nov 2018 16:59:15 -02
    */
    vet_vars[n_lin -1] = vet_b[n_lin -1]/matriz[n_lin -1][m_col-1];     //X_n

    double soma;

    for (int n = n_lin - 2; n >= 0; --n)
    {
        soma = 0;
        for (int m = m_col - 1; m > n; --m)
        {
            soma += matriz[n][m]*vet_vars[m];
        }
        printf("Som= %f \n",soma);
        vet_vars[n]=(vet_b[n] - soma)/matriz[n][n];
    }

    for (i=0; i<n_lin; i++)
    {
        printf("Variavel X_%d: %f \n" , i, vet_vars[i]);
    }


    return(EXIT_SUCCESS);
}


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

