#include <stdio.h>
#include <stdlib.h>

/*
    @shogunhirei
    EQE749 - Métodos Numéricos 
    Implementação do método de Eliminação Gaussiana para
    Resolução da Questão Nº da 1ª Lista de exercicios
    qui 08 nov 2018 13:19:57 -02
*/

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
                printf(" a%d%d: %f,", y, g, matriz[y][g]);
            }
            printf(" b%d: %f \n", y, vet_b[y]);
        }
        printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
}

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
    int n_lin;
    int m_col;
    int i,j,k,m;

    printf("Insira a ordem da matriz: \n");
    scanf("%d",&n_lin);
    m_col = n_lin ;

    double matriz[n_lin][m_col];
    double vet_b[n_lin];


    for (i = 0; i < n_lin; ++i) 
    {
        printf("Vamos inserir os dados da linha %d ",i);
        input_listing(m_col, matriz[i]);
        
        printf("Insira agora b_%d: ",i+1);
        scanf("%lf",&vet_b[i]);
    }
        //TODO: Inserir seção de pivotamento
        //@shogunhirei 
        //qui 08 nov 2018 16:33:21 -02
    for (i = 0; i < n_lin; i++)
    {
        for (j = 0; j < m_col; j++)
            printf("a%d%d: %f,  ", i, j, matriz[i][j]);
            printf("\n");
    }

    for (j = 0; j < m_col; j++) {
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
