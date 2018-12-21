#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
    @shogunhirei
    EQE749 - Métodos Numéricos 
    Resolução da Questão 3 da 3ª lista de exercícios

    Método Implicitos de Euler
    seg 17 dez 2018 13:34:57 -02
*/


#define k1 0.08 // Alterei a ordem de grandeza das constantes  
#define k2 2e4 // com base em alguns problemas similares  
#define k3 6e7 // de cinética. 
#define dT 0.001
#define conv_crit 1e-6 // Critério de convergência 


double sum_mat(int n,double vet[n]);

void mult_mat (int n, double mat[n][n],double vet[n], double result[n]);

void  subt_matrix(int n, double vet1[n],  double vet2[n], double result[n]);

double err_rel(double k_vet[3], double kN_vet[3]);

void function(double dados0[3], double dados[3], double fi_x[3])
{
    double x = dados[0];
    double y = dados[1];
    double z = dados[2];
    double x0 = dados0[0];
    double y0 = dados0[1];
    double z0 = dados0[2];
    /*fi_x[0] = dados0[0] - dados[0] - dT * k1 * dados[0] + dT * k2 * dados[2] * dados[2];*/
    /*fi_x[1] = dados0[1] - dados[1] + dT * k1 * dados[0] - dT * k2 * dados[1] * dados[2] - dT * k3 * pow(dados[1], 2.0);*/
    /*fi_x[2] = dados0[2] - dados[2] + dT * k3 * pow(dados[1], 2.0);*/
    // Vetor com as funções na forma f(x) = 0, dados0 são os valores pela iteração n no tempo
    //  e o array dados são aqueles que serão utilizados para iteração no método de Newton-Raphson
    fi_x[0] = x - (x0 + dT * k2 * y * z)/(1 + dT * k1);
    fi_x[1] = y - (y0 + dT * k1 * x)/(1 + dT * ( k2 * z + k3 * y ) );
    fi_x[2] = z - (z * z0)/(z - dT * k3 * y * y);
    
}

void euler_explic(double dados[3], double k0[3])
{
   // Usando a estimativa inicial a partir do Método de Euler Explícito 

   k0[0] = 1e-6 * (-k1 * dados[0] + k2 * dados[1] * dados[2]);
   k0[1] = 1e-6 * (k1 * dados[0] - k2 * dados[1] * dados[2] - k3 * pow(dados[1], 2.0));
   k0[2] = 1e-6 * (k3 * pow(dados[1] , 2.0)); 
}

void jacbian(double dados0[3], double dados[3], double invjacob[3][3])
{
    double x = dados[0];
    double y = dados[1];
    double z = dados[2];
    double x0 = dados0[0];
    double y0 = dados0[1];
    double z0 = dados0[2];
    double jac[3][3];
    double det_jac;
    // Matriz Jacobiana do sistema de equações
    /*
        @shogunhirei
        As três equações elaboradas foram:
            f1(x) = x - (x0 + dT * k2 * y * z)/(1 + dT * k1);
            f2(x) = y - (y0 + dT * k1 * x)/(1 + dT * ( k2 * z + k3 * y ) );
            f3(x) = z - (z * z0)/(z - dT * k3 * y * y);
        Nas quais será implementado diretamente as derivadas nos elementos da jacobiana
        seg 17 dez 2018 19:50:33 -02
    */

    jac[0][0] = 1 ; // -(1 + dT * k1);
    jac[0][1] = - (k2 * dT * z)/(k1 * dT + 1); // -(- k2 * dT * dados[2]);
    jac[0][2] = - (k2 * dT * y)/(k1 * dT + 1); // -(- k2 * dT * dados[1]);
    
    jac[1][0] = - (k1 * dT)/ (dT * (k2 * z + k3 * y) + 1); // -(-dT * k1);
    jac[1][1] = 1 + (k3 * dT * (k1 * dT * x + y0))/pow((dT * (k2 * z + k3 * y) + 1), 2.0); // -(1 + dT * k2 * dados[2] + 2 * k3 * dados[1]);
    jac[1][2] = k2 * dT * (k1 * dT * x + y0)/pow((dT * (k2 * z + k3 * y) + 1), 2.0); // -(dT * k2 * dados[1]);
    
    jac[2][0] = 0 ; // 0;
    jac[2][1] = - (2 * z0 * k3 * dT * y * z)/pow((-k3 * dT * y*y + z),2.0); // -(-2.0 * dT * k3 * dados[1]);
    jac[2][2] = 1 + (z0 * z)/pow((-k3 * dT * y*y + z), 2.0) - z0/((-k3 * dT * y*y + z)); // -1.0;

    // Cálculo da Jacobiana inversa para o Método Newton-Raphson 
    // Determinante cálculado pelo método de Sarrus
    det_jac = (jac[0][0] * jac[1][1] * jac[2][2] + jac[0][1] * jac[1][2] * jac[2][0] + 
            jac[0][2] * jac[1][0] * jac[2][1] ) - (jac[0][2] * jac[1][1] * jac[2][0] +
                jac[0][1] * jac[1][0] * jac[2][2] + jac[0][0] * jac[1][2] * jac[2][1]);

    // Matriz inversa pelo método direto descrito em http://mathworld.wolfram.com/MatrixInverse.html

    invjacob[0][0] = (jac[1][1] * jac[2][2] - jac[1][2] * jac[2][1])/det_jac;
    invjacob[0][1] = (jac[0][2] * jac[2][1] - jac[0][1] * jac[2][2])/det_jac;
    invjacob[0][2] = (jac[0][1] * jac[1][2] - jac[0][2] * jac[1][1])/det_jac;

    invjacob[1][0] = (jac[1][2] * jac[2][0] - jac[1][0] * jac[2][2])/det_jac;
    invjacob[1][1] = (jac[0][0] * jac[2][2] - jac[0][2] * jac[2][0])/det_jac;
    invjacob[1][2] = (jac[0][2] * jac[1][0] - jac[0][0] * jac[1][2])/det_jac;

    invjacob[2][0] = (jac[1][0] * jac[2][1] - jac[1][1] * jac[2][0])/det_jac;
    invjacob[2][1] = (jac[0][1] * jac[2][0] - jac[0][0] * jac[2][1])/det_jac;
    invjacob[2][2] = (jac[0][0] * jac[1][1] - jac[0][1] * jac[1][0])/det_jac;
    
}

int main(int argc, char** argv)
{

    int i; // Contadores diversos

    double passos = 50.0/dT;

    int num = abs(passos); // Quantidade de passos, para que atingisse mesmo tempo apprx 50s
    
    // Para armazenar respostas das três variáveis
    double dados1[num]; // para concentração de A
    double dados2[num]; // para concentração de B
    double dados3[num]; // Para concentração de C
    FILE *file;
    file = fopen("data_b.txt","w");

    /*
        @shogunhirei
        Por questão de simplicidade as variaveis foram alteradas da seguinte forma:
        Ca --> x 
        Cb --> y
        Cc --> z 
        seg 17 dez 2018 12:53:53 -02
    */
    // Nas condições de contorno x0 = 1; y0 = z0 = 0
    dados1[0] = 1.0;
    dados2[0] = 0.0;
    dados3[0] = 0.0;

    double data[3];
    
    double k[3];

    double xN[3];
    double mult[3];
    double sum[3];
    double inv_jac[3][3];
    double func_vet[3];
    double val; // para determinar convergência

    for( i = 1; i < num; i++)
    {
        data[0] = dados1[i - 1];
        data[1] = dados2[i - 1];
        data[2] = dados3[i - 1];

        euler_explic(data, k);

        do // Seção responsável pela parte iterativa de Newton-Raphson 
        {
            // No formato x_(m+1) = x_m - Jac_inv * F(x_m)
            jacbian(data, k, inv_jac); // Determinação da Jacobiana Inversa, armazenada localmente
            function( data, k, func_vet ); // Determinando F(x_m) para a iteração atual

            mult_mat(3, inv_jac, func_vet, mult); // Multiplicação das matrizes
            subt_matrix(3, k, mult, xN); // subtração das matrizes, armazenando em x_(m+1);

            // Verificação de Erro relativo do NR multivariado 
            val = err_rel(k, xN); 

            for (int j = 0; j < 3; ++j) {
                k[j] = xN[j];
            }

        } while ( val > conv_crit);

        dados1[i] = k[0];
        dados2[i] = k[1];
        dados3[i] = 1 - k[0] - k[1]; //k[2]; // Pelo balanço de massa
        fprintf(file, "%.15f \t %.15f \t %.15f \t\n",dados1[i],dados2[i],dados3[i]);

    }

    fclose(file);

    printf("Fim dos cálculos!\n");

    return(EXIT_SUCCESS);

}

// Somatório de vetores
double sum_mat(int n,double vet[n])
{
    double result = 0;
    for (int i = 0; i < n; i++)
    {
        result += (vet[i]);
    }
    return result;
}

// Multiplicação de matriz e vetor e armazenamento em resultado
void mult_mat (int n, double mat[n][n],double vet[n], double result[n])
{
    for (int i = 0; i < n; i++)
    {
        result[i] = 0; 
        for (int j = 0; j < n; j++)
        {
            result[i] += mat[i][j] * vet[j];
        }
    }
    
}
// Subtração de vetores 
void  subt_matrix(int n, double vet1[n],  double vet2[n], double result[n])
{
    for (int i = 0; i < n; ++i) {
        result[i] = vet1[i] - vet2[i];
    }
}

// Função de erro relativo para comparação de erro de sistema de equações
// Norma com distancia euclidiana do vetor resposta
double err_rel(double k_vet[3], double kN_vet[3])
{
    // Erro relativo para os vetores k e xN 
    double result = 0;
    for (int i = 0; i < 3; i++)
    {
        result += pow((kN_vet[i] - k_vet[i])/k_vet[i], 2.0);
    }
    result = sqrt(result/3.0);
    return result;

}

