#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
    @shogunhirei
    EQE749 - Métodos Numéricos
    2ª lista de Exercicios Método de Volumes Finitos 
    Problema de Transferência de calor Unidimensional em aleta piniforme 

    Lucas Henrique Queiroz dos Reis
    qui 20 dez 2018 18:11:55 -02
*/
#define k 10
#define h 5
#define T_inf 293 
#define Tb 373 
#define diam 0.01
#define L 0.05
#define alpha 1e-6

void thomas_algoritm(int n_lin, double vet_b[n_lin],  double matriz[n_lin][n_lin], double sols[n_lin]);

double analitica_sol(double X);

int main(int argc, char** argv)
{
    int i, j;       // Contadores diversos
    int vol;     // Número de Volumes de Controle
    double dX;      // Delta X
    double X;
    double err_abs;
    double an_sol;

    FILE *file;

    printf("Insira o número de CV's: ");
    scanf("%d",&vol);

    dX = L / vol;

    double matriz[vol][vol]; // Matriz de Coeficientes para o problema 
    double termo_fonte[vol]; // Vetor com os termos-fonte para cada equação 
    double sol[vol];         // vetor para armazenar resultados 
    double sol_adm[vol];     // Vetor para os valores adimensionados

    double A = 0.5 * ( (M_PI * pow(diam, 2.0) * h * k ) / dX ) / (h + 2 * k/dX);
    double dS = (M_PI * pow(diam/2.0, 2.0));

    matriz[0][1] = - dS * (k / dX) ;
    matriz[0][0] = -3 * matriz[0][1] +  M_PI * diam * dX * h;
    termo_fonte[0] = M_PI * pow(diam, 2.0) * k * Tb / (2 * dX) + M_PI * h * T_inf * dX;

    matriz[vol - 1][vol - 2] = - dS * (k / dX) ;
    matriz[vol - 1][vol - 1] = - matriz[vol - 1][vol - 2] +  M_PI * diam * dX * h + A ;
    termo_fonte[vol - 1] = M_PI * diam * dX * h * T_inf  + T_inf * A;

    // Como o sistema de equações, matriz de coeficientes é tridiagonal
    // É possível utilizar o Algoritmo de Thomas para resolução

    for (i = 1; i < vol - 1; i++)
    {
        matriz[i][i-1] = - dS * (k / dX);
        matriz[i][i] = -2 * matriz[i][i - 1] + M_PI * h * diam * dX;
        matriz[i][i + 1] = matriz[i][i - 1];
        termo_fonte[i] = M_PI * diam * h * T_inf * dX;
        
    }
    
    thomas_algoritm(vol, termo_fonte, matriz, sol );

    file = fopen("Q1_resposta.txt", "w");

    fprintf(file, "\tX \t\t Temp(x) \t\t Sol. Adim.  Analítica \t Err. Abs. \n");

    for (i = 0; i < vol; i++) {
        X = dX/2.0 +  dX * i;
        an_sol = analitica_sol(X);
        sol_adm[i] = (sol[i] - T_inf)/ (Tb - T_inf);
        err_abs = fabs(sol_adm[i] - an_sol);
        fprintf(file, "%lf \t %lf \t %lf \t %lf \t %lf \n", X, sol[i], sol_adm[i], analitica_sol(X), err_abs);
    }

    fprintf(file, "------------------------------------------------------");

    fclose(file);

    return(EXIT_SUCCESS);
}


void thomas_algoritm(int n_lin, double vet_b[n_lin],  double matriz[n_lin][n_lin], double sols[n_lin])
{
    int i;
    double matriz_linha[n_lin][3];
    double m; //multiplicador
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

}


double analitica_sol(double X)
{
    double m;
    double result;
    m = pow(4 * h/(k * diam), 0.5);

    result = (cosh(m*(L - X)) + h/(m*k)*sinh(m*(L - X)))/(cosh(m*L) + h/(m*k)*sinh(m*L)); 
    
    return result;

}
