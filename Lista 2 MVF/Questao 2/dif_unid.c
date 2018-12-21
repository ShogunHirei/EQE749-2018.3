#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
    @shogunhirei
    EQE749 - Métodos Numéricos
    2ª Lista de Exercícios - Questão 2 - Difusão Unidimensional

    Lucas Henrique Queiroz dos Reis
    qui 20 dez 2018 21:57:12 -02
*/

#define conv_crit 1e-4
#define limite 1000 //Limite de Iterações 

double media_harm(double alpha1, double alpha2)
{
    double result;

    result = ( 1/(2 * alpha1) + 1/(2 * alpha2)); 
    result = 1/result;

    return result;
}

double alpha_funct(double Teta)
{
    return 10 * exp(-1/(0.1 + Teta));
}

void thomas_algoritm(int n_lin, double vet_b[n_lin],  double matriz[n_lin][n_lin], double sols[n_lin]);

double error_function(int n_lin, double mat1[n_lin], double mat2[n_lin]);

int main(int argc, char** argv)
{
    int n = 0; 
    int vol;
    int i, j;        // Contadores diversos
    double alpha_P;
    double alpha_W;
    double alpha_E;
    double alpha_w;
    double alpha_e;
    FILE *file;

    printf("Insira a quantidade de volumes: ");
    scanf("%d",&vol);

    double matriz[vol][vol]; // Matriz de Coeficientes para o problema 
    double termo_fonte[vol]; // Vetor com os termos-fonte para cada equação 
    double sol[vol];         // vetor para armazenar resultados 
    double theta_chute[vol]; // vetor para verificar convergência do loop  
    double err;
    double X;

    double theta0 = 1;
    double thetaL = 1;
    double L = 1;
    double dX = L/vol;

    for (i = 0; i < vol; ++i) {
        theta_chute[i] = 1;
    }
    
	do
    {
		alpha_W = alpha_funct(theta0);
		alpha_P = alpha_funct(theta_chute[0]);
		alpha_E = alpha_funct(theta_chute[1]);
		alpha_w = media_harm(alpha_W, alpha_P);
		alpha_e = media_harm(alpha_E, alpha_P);
		matriz[0][1] = - alpha_e/dX;
		matriz[0][0] = - matriz[0][1] + 2 * alpha_w/dX - 2 * dX * theta_chute[0];
		termo_fonte[0] = (1 - pow(theta_chute[0], 2.0)) * dX + 2 * theta0 * alpha_w/dX;

		for (i = 1; i < vol-1; i++)
		{
			alpha_W = alpha_funct(theta_chute[i - 1]);
			alpha_P = alpha_funct(theta_chute[i]);
			alpha_E = alpha_funct(theta_chute[i + 1]);
			alpha_w = media_harm(alpha_W, alpha_P);
			alpha_e = media_harm(alpha_E, alpha_P);
			matriz[i][i - 1] = -alpha_w/dX;
			matriz[i][i + 1] = -alpha_e/dX;
			matriz[i][i] = -(matriz[i][i - 1] + matriz[i][i + 1]) - 2 * theta_chute[i] * dX;
			termo_fonte[i] = (1 - pow(theta_chute[0], 2.0)) * dX;
		}

		alpha_W = alpha_funct(theta_chute[vol - 2]);
		alpha_P = alpha_funct(theta_chute[vol - 1]);
		alpha_E = alpha_funct(thetaL);
		alpha_w = media_harm(alpha_W, alpha_P);
		alpha_e = media_harm(alpha_E, alpha_P);
		matriz[vol - 1][vol - 2] = - alpha_w/dX;
		matriz[vol - 1][vol - 1] = - matriz[vol - 1][vol - 2] + 2 * alpha_e/dX - 2 * dX * theta_chute[vol - 1];
		termo_fonte[vol - 1] = (1 - pow (theta_chute[vol - 1], 2.0)) * dX + 2 * thetaL * alpha_e/dX;

		thomas_algoritm(vol, termo_fonte, matriz, sol);

        err = error_function(vol, sol, theta_chute); // Retorna o maior erro relativo 

	    for (i = 0; i < vol; i++)
	    {
	    	theta_chute[i] = sol[i];
	    }
        
        if(n > limite)
        {
            printf("Não convergiu! \n");
            break;
        }

		n++;
	}
	while (err > conv_crit);

    file = fopen("Q2_Respostas.txt", "w");

    fprintf(file, "\tX \t Theta \n");

    for (i = 0; i < vol; i++)
    {
        X = dX/2.0 + i * dX;
        fprintf(file, "%lf \t %lf \t \n", X, sol[i]);
    }

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
        matriz_linha[i][0] = matriz[i][i - 1];
        matriz_linha[i][1] = matriz[i][i];
        matriz_linha[i][2] = matriz[i][i + 1];
    }

    for (i = 1; i < n_lin; ++i) {
        // Operação de Eliminação, Li - M * Lj
        m = (matriz_linha[i][0]/matriz_linha[i - 1][1]);
        matriz_linha[i][1] = matriz_linha[i][1] - m * matriz_linha[i - 1][2];
        vet_b[i] = vet_b[i] - m  * vet_b[i - 1];
    }
    /*Inicio de processo de retorno */
    // Especificando o último valor do conjunto de soluções 
    sols[n_lin - 1] = vet_b[n_lin - 1]/matriz_linha[n_lin-1][1];

    for (i = n_lin - 2; i >= 0; i-- )
    {
        sols[i] = (vet_b[i] - matriz_linha[i][2]*sols[i + 1])/matriz_linha[i][1];
    }

}

double error_function(int n_lin, double mat1[n_lin], double mat2[n_lin])
{
    /*
        @shogunhirei
        Para poder verificar a convergência, essa função vai avaliar o maior erro
        relativo entre os dois vetores recebidos e retorná-lo para comparação 
        no loop do while
        sex 21 dez 2018 00:06:38 -02
    */
    double comp1;
    double comp2;

    if(mat1[0] != 0)
    {
        comp1 = fabs((mat2[0] - mat1[0])/mat1[0]);
    }

    for( int i = 0; i < n_lin; i++)
    {
        if (mat1[i] != 0)
        {
            comp2 = fabs((mat2[i] - mat1[i])/mat1[i]);
            if( comp2 > comp1 )
            {
                comp1 = comp2;
            }
        }
        else 
        {
            comp1 = 1;
        }
    }

    return comp1;
}
