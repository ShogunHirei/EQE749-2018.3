#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
    @shogunhirei
    EQE749 - Métodos Numéricos
    Questão Número 6 - Cálculo de fração molar em coluna de destilação 

    Processo:
    Através do BM organizar a equação para cada prato
    Considerar casos especiais xo e y(n+1) conhecidos 
    Considerar inserção do número de pratos
    qua 28 nov 2018 10:56:13 -02
*/
void thomas_alg(int n_lin, double matriz_linha[n_lin][n_lin], double vet_b[n_lin], double sols[n_lin])
{
    int i;
    double m;

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
    for (i = 0; i < n_lin; ++i) 
    {
        printf("X_%d: %f\n", i, sols[i]);
    }
}

/*
    @shogunhirei
    Questão 6 - Letra c
    Propor um algoritmo caso a e b dependenssem de x e y;
    
    Processo:
    -> Determinar a e b através dos dados da relação anterior
    -> Calcular x_i e y_i da equação atual
    -> Repetir o processo

    Para propor outra alternativa com maior chance de convergir:
    Processo: 
        --> Calcular x e y para um valor inicial de a0 e b0;

     |----------->Etapa 1 <--------------------------------------------------------------------  
     |  --> Para cada prato utilzar os valores de x e y para determinar a e b daquele prato   |
     |      --> Realizar etapa anterior, para todos pratos                                    |
     |-----------------------------------------------------------------------------------------

     |----------->Etapa 2 <--------------------------------------------------------------------  
     |  --> Calcular x e y para todos os pratos, com os valores atuais de a e b               |
     |      --> Comparar valores anteriores de x e y para verificar convergência              |
     |          --> Caso não, usar valores atuais de x e y e voltar pra Etapa 1               |
     |-----------------------------------------------------------------------------------------

    qua 28 nov 2018 17:10:23 -02
*/
double a_fun(double x,double y){
    double a;
    a = 1 + 0*x + 0*y;
    return a;
}
double b_fun(double x, double y)
{
    double b;
    b = 0*x + 0*y;
    return b;
}


int main(int argc, char** argv)
{
    int n_pratos = 40;// Primeiro teste, à nível de comparação 
    double x, y; // Fração molar de líquido e gás, respectivamente
    double G = 66.7; // Quantidade molar de gás
    double L = 40.8; // Quantidade molar de líquido 
    double a = 0.72; // razão termodinâmica 
    double b = 0.0; //Da relação Termodinâmica
    double mat[n_pratos][n_pratos]; // Matrix com as equações de equilibrio para cada prato
    double vet[n_pratos]; // Termo-fonte, valores que serão inseridos de para x e y conhecidos
    double sols[n_pratos];                                 
    double gas_sol[n_pratos];
    double y_N = 0.2; // Valor de y_(n+1)
    double x0 = 0.0; // Valor de x0
    int i, j, k, m; // Contadores

    /*
        @shogunhirei
        Vetor solução contem as frações de líquido 
        Adicionado mais 2 elementos par incluir os valores de x0 e x_(n+1)
        qua 28 nov 2018 11:21:00 -02
    */
    /*
        @shogunhirei
        A Equação do BM para cada prato em função da fração molar de líquido:
            (L)*x_(i-1) - (L - G*a_i)*x_(i) + G*(a_(i+1))*x_(i+1) = G*(b_i - b_(i+1))
        Como os x0 e y(n+1) são conhecidos os primeiro e últimos termos fontes serão alterados
        Logo, para i = 1: 
               - (L - G*a_1)*x_(1) + G*(a_(2))*x_(2) = G*(b_1 - b_(2)) - L*x0
        Logo, para i = n: 
                (L)*x_(n-1) - (L - G*a_n)*x_(n)  = G*(b_n - b_(n+1)) - G*(y_(n+1))

        qua 28 nov 2018 11:07:34 -02
    */ 
    
    // Adicionado os coeficientes da 1ª linha 
    mat[0][1] = - (L + G*a);
    mat[0][2] = G*(a);
    vet[0] =  G*(b - b) - L*x0;

    //Adicionando coeficientes da última linha;
    mat[n_pratos - 1][1] =  - (L + G*a);
    mat[n_pratos - 1][0] = L;
    vet[n_pratos - 1] = G*(b - b) - G*(y_N);
    printf("b%d = %f\n", n_pratos - 1, vet[n_pratos -1 ]);
    /*
       @shogunhirei
       -> Considerando os coeficientes termodinâmicos como não dependentes das frações molares
       -> Como vai adquirir o formato tridiagonal, estou considerando a formatação na matriz 
       adaptada 
       qua 28 nov 2018 11:37:13 -02
       */ 

    //Geração de matriz de coeficientes n x 3 para solução por algoritmo de thomas
    for (i = 1; i < n_pratos -1; i++) {
        mat[i][0] = L;
        mat[i][1] = - (L + G*a);
        mat[i][2] = G*(a);
        vet[i] =  G*(b - b) - L*sols[0];
    }

    /*// Mostrar matriz para conferir coeficientes*/
    /*for (m = 0; m < n_pratos; ++m) {*/
        /*if(m <= 1)*/
        /*{*/
            /*printf("A(1,%d): %3.3f, ", m + 1, mat[0][1]);*/
            /*printf("A(1,%d): %3.3f, ", m + 2, mat[0][2]);*/
            /*m+=2;*/
        /*}*/
        /*else*/
        /*{*/
            /*printf("A(1,%d): 0.000000, ",m+1);*/
        /*}*/
    /*}*/
    /*printf("\n");*/
    /*for (i = 1; i < n_pratos; i++)*/
    /*{*/
        /*for (j = 0; j < n_pratos; ++j) {*/
           /*if(j >= i - 1 && j <= i+1)*/
           /*{*/
               /*printf("A(%d,%d): %3.3f, ", i+1, j+1, mat[i][0]);*/
               /*printf("A(%d,%d): %3.3f, ", i+1, j+2, mat[i][1]);*/
               /*printf("A(%d,%d): %3.3f, ", i+1, j+3, mat[i][2]);*/
               /*j+=3;*/
           /*} */
           /*else*/
           /*{*/
               /*printf("A(%d,%d): 0.000000, ", i+1, j+1);*/
           /*}*/
        /*}*/
        /*printf("\n");*/
    /*}*/
    /*for (m = 0; m < n_pratos; m++)*/
    /*{*/
        /*if( m < n_pratos - 2)*/
        /*{*/
            /*printf("A(%d,%d): 0.000000 ",n_pratos + 1, m+1);*/
        /*}*/
        /*else*/
        /*{*/
            /*printf("A(%d,%d): %3.3f, ", n_pratos + 1, m+1, mat[n_pratos][0]);*/
            /*printf("A(%d,%d): %3.3f, ", n_pratos + 1, m+1, mat[n_pratos][1]);*/
            /*m += 2;*/
        /*}*/
    /*}*/
    /*printf("\n");*/

    thomas_alg(n_pratos, mat, vet, sols);

    return(EXIT_SUCCESS);
}
