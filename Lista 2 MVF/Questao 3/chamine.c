#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
    @shogunhirei
    EQE749 - Métodos Numéricos 
    2ª Lista de Exercícios  Questão 3 - Análise de Escoamento Unidimensional
    Movimento Difusivo e Convectivo

    Lucas Henrique Queiroz dos Reis
    sex 21 dez 2018 10:51:52 -02
*/

void euler_explic(int n, double dT, double resp[n]);

void thomas_algoritm(int n_lin, double vet_b[n_lin],  double matriz[n_lin][n_lin], double sols[n_lin]);

void difus_SOU(int vol, double dX, double results[vol]);

void gauss_elim(int n_lin, double matriz[n_lin][n_lin], double vet_b[n_lin], double vet_vars[n_lin]);

int main(int argc, char** argv)
{
    int i, j; // Contadores diversos
    
    int vol;     // Número de Volumes de Controle
    double dX;      // Delta X
    double X;
    double err_abs;
    double L = 6;
    FILE *file;

    printf("Insira o número de CV's: ");
    scanf("%d",&vol);

    dX = L / vol;
    X = dX/2.0;

    double m = -3;
    double gama = -2;
    double D = gama/dX;
    double phi_linha0 = 1;
    double phi_L = 2;

    double matriz[vol][vol]; // Matriz de Coeficientes para o problema 
    double termo_fonte[vol]; // Vetor com os termos-fonte para cada equação 
    double sol[vol];         // vetor para armazenar resultados 
    double final[vol];       // Para comparar com a resolução por Euler explícito
    double SOU_resp[vol];    // Para comparação com o método SOU

    matriz[0][1] = D + m;
    matriz[0][0] = -matriz[0][1]; // Não é preciso linearizar phi_p, termo fonte não depende de phi
    termo_fonte[0] = X * cos(M_PI * X) * dX + gama * phi_linha0;

    matriz[vol - 1][vol - 2] = D ;
    matriz[vol - 1][vol - 1] = m * D ;
    termo_fonte[vol - 1] = (dX * vol - X) * cos(M_PI * (dX * vol - X)) * dX - 2 * phi_L * D;

    // Como o sistema de equações, matriz de coeficientes é tridiagonal
    // É possível utilizar o Algoritmo de Thomas para resolução

    for (i = 1; i < vol - 1; i++)
    {
        matriz[i][i-1] = D;
        matriz[i][i + 1] = D + m;
        matriz[i][i] =  -( D + (D + m));
        termo_fonte[i] = (dX * i + X) * (cos(M_PI * (dX * i + X))) * dX;
        
    }
    
    thomas_algoritm(vol, termo_fonte, matriz, sol );

    // Comparação com a resolução ṕor euler explicito
    euler_explic(vol, dX, final);

    // Método de Discretização Difusiva-Convectiva SOU
    difus_SOU(vol, dX, SOU_resp);

    file = fopen("Q3_resposta.txt", "w");

    fprintf(file, "\tX \t\t Phi_UDS \t Phi (Eul. Ex.) \t Phi_SOU\n");

    for (i = 0; i < vol; i++) {
        X = dX/2.0 +  dX * i;
        fprintf(file, "%lf \t %lf \t %lf \t\t\t %lf \n", X, sol[i], final[i], SOU_resp[i]);
    }

    fclose(file);

    return(EXIT_SUCCESS);

}

void euler_explic(int n, double dT, double resp[n])
{
    double y2_n[n];
    double x;

    y2_n[0] = 1; // Condição initial para a derivada

    for( int i = 1; i < n; i++)
    {
        x = dT/2 + i*dT;
        y2_n[i] = y2_n[i-1] - dT * (x * cos(M_PI * x) + 3 * y2_n[i-1])/2.0;
    }

    resp[n] = 2; // Condição de contorno para a função 

    for( int i = n - 1; i > -1; i--)
    {
        resp[i] = resp[i + 1] - dT * y2_n[i + 1];
    }

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

void difus_SOU(int vol, double dX, double results[vol])
{
    // Pelo método SOU de discretização difusivo convectivo
    int i,j;
    double m = -3;
    double gama = -2;
    double D = gama/dX;
    double phi_linha0 = 1;
    double phi_L = 2;
    double X = dX/2.0 ;

    double matriz_coef[vol][vol]; // Matriz de Coeficientes para o problema 
    double termo_fonte[vol]; // Vetor com os termos-fonte para cada equação 
    
    for (i = 0; i < vol; i++)
    {
        for(j = 0; j < vol; j++)
        {
            matriz_coef[i][j] = 0; // Para garantir que outros valores estejam na matriz_coef
        }
    }

    // Adicionando termo referente à a_EE
    matriz_coef[0][2] = -m/2;
    matriz_coef[0][1] = D + 1.5 * m;
    matriz_coef[0][0] = -(matriz_coef[0][2] + matriz_coef[0][1]); // Não é preciso linearizar phi_p, termo fonte não depende de phi
    termo_fonte[0] = X * cos((M_PI * X)) * dX + gama * phi_linha0;

    // Por causa da direção do fluxo o termo a_WW é zerado

    matriz_coef[vol - 2][vol - 1] = D + (1.5) * m;
    matriz_coef[vol - 2][vol - 3] = D;
    matriz_coef[vol - 2][vol - 2] = - (matriz_coef[vol - 2][vol - 1] + matriz_coef[vol - 2][vol - 3]);
    termo_fonte[vol - 2] =  dX *( vol - 1.5) * (cos(M_PI * (dX * (vol - 1.5)))) * dX;

    matriz_coef[vol - 1][vol - 2] = D ;
    matriz_coef[vol - 1][vol - 1] = -3 * matriz_coef[vol - 1][vol - 2] ;
    termo_fonte[vol - 1] = (dX * vol - X) * cos(M_PI * (dX * vol - X)) * dX - 2 * phi_L * D;

    // Como o sistema de equações, matriz_coef de coeficientes não é tridiagonal
    // Necessário utilizar outro método para resolução da matriz_coef
    
    for (i = 1; i < vol - 2; i++)
    {
        matriz_coef[i][i-1] = D;
        matriz_coef[i][i + 1] = D + 1.5 * m;
        matriz_coef[i][i + 2] = -m/2;
        matriz_coef[i][i] =  -(matriz_coef[i][i + 2] + matriz_coef[i][i + 1] + matriz_coef[i][i-1]);
        termo_fonte[i] = (dX * i + X) * (cos(M_PI * (dX * i + X))) * dX;
        
    }

    gauss_elim(vol, matriz_coef, termo_fonte, results );
    
}

void gauss_elim(int n_lin, double matriz[n_lin][n_lin], double vet_b[n_lin], double vet_vars[n_lin])
{
    int i,j,m; 
    double a, b, c, d;
    double mul;
    double soma;

    for (j = 0; j < n_lin; j++) {

        for (i = j+1; i < n_lin; i++) {

            b = matriz[j][j];
            c = matriz[i][j];
            mul = c/b;
            for (m = 0; m < n_lin; m++) {
                a = matriz[i][m]; 
                d = matriz[j][m];
                matriz[i][m]=a - mul * d;
            }
            vet_b[i]=vet_b[i] - mul* vet_b[j];
        }
    }

    vet_vars[n_lin -1] = vet_b[n_lin -1]/matriz[n_lin -1][n_lin-1];     //X_n

    for (int n = n_lin - 2; n >= 0; --n)
    {
        soma = 0;
        for (int m = n_lin - 1; m > n; --m)
        {
            soma += matriz[n][m]*vet_vars[m];
        }
        vet_vars[n]=(vet_b[n] - soma)/matriz[n][n];
    }

}
