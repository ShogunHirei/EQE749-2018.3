#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
    @shogunhirei
    EQE749 Métodos Numéricos
    Método de Gauss-Seidel de Resolução de Sistemas lineares

    Processo:
    --> Similar ao Jacobi...
    --> Mudança nas etapas de do próximo Xi da iteração
    --> Residuo também é alterado
    --> As mudanças nas variaveis são feitas assim que determinadas
        as aproximações
    dom 11 nov 2018 12:39:22 -02
*/


double* input_listing(int ar_len, double input[ar_len]){

    for(int i = 0; i < ar_len; i++)
    {
        scanf("%lf,",&input[i]);
    }
    return input;

}

int main(int argc, char** argv)
{
    int n_lin, i, j; 
    double conv_cri;
    int limite = 300; //Definindo limite de operações de repetição

    printf("Insira a ordem do sistema: ");
    scanf("%d",&n_lin);

    double matriz[n_lin][n_lin];
    double vet_b[n_lin];

    for (i = 0; i < n_lin; ++i) {
        printf("Insira os coeficientes da linha %d ",i); 
        input_listing(n_lin, matriz[i]);
        printf("Insira o vetor b%d ",i);
        scanf("%lf",&vet_b[i]);
    }

    double gues[n_lin];
    printf("Insira os palpites agora, cara... ");
    input_listing(n_lin, gues);

    printf("Insira o critério de convergência: ");
    scanf("%lf",&conv_cri);

    double soma;
    double soma_res = 5;
    double residuo[n_lin];
    int n = 0; //Definindo limite externo de repetições para evitar loop infinito
    
    for(i = 0; i < n_lin; ++i){
        for (j = 0; j < n_lin; ++j) {
            printf("a%d%d: %f", i, j, matriz[i][j]);
        }
        printf(" b%d: %f Guess_%d: %f\n", i, vet_b[i], i, gues[i]);
    }

    /*
        @shogunhirei
        ------------------------------------------------------------
        Copiado do método de Jacobi a parte de inserção de elementos e dados
        ------------------------------------------------------------
        dom 11 nov 2018 12:44:30 -02
    */
       //TODO: Verificar a atualização de cada variavel e verifica
       // do critério de convergencia, 
       // Obs.: Atualizar cada valor de gues antes do final da iteração
       //@shogunhirei 
       //dom 11 nov 2018 12:46:34 -02
 
    double soma_antes;
    double soma_depois;
        //TODO: Inserir OBRIGATORIAMENTE Agora o critério de convergência
        //Para que esse método convirja necessário que o sistema tenha diagonal dominante
        // Diagonal dominante: 
        //          Soma dos aij tem que ser menor que aii para cada linha;
        //          Algumas transformações podem fazer com que a matriz se adapate a isso...
        //@shogunhirei 
        //dom 11 nov 2018 17:38:54 -02
    while (soma_res > conv_cri)
    {
        soma_res = 0;
        for (i = 0; i< n_lin; i++)
        {
            soma_antes = 0;
            soma_depois = 0;
            for (j = 0; j < n_lin; ++j) 
            {
                if(j < i)
                {
                    soma_antes +=matriz[i][j]*gues[j];
                }
                else
                {
                    soma_depois += matriz[i][j]*gues[j];
                }
            }

            residuo[i] = vet_b[i] - soma_antes - soma_depois;
            soma_res += fabs(residuo[i]/matriz[i][i]);
            printf("Gues_ant%d = %f; Soma_antes%d = %f; Soma_depois%d = %f; Residuo%d  = %f\n", i, gues[i], i, soma_antes, i, soma_depois, i, residuo[i]);
            gues[i] = gues[i] + residuo[i]/matriz[i][i];
            printf("Soma_res: %f; g_%d: %f\n",soma_res, i, gues[i]);

        }
        if(n > limite)
        {
            printf("Limite de operações atingido\n");
            break;
        }
    }
    for (i = 0; i < n_lin; ++i) {
        printf("X_%d: %f\n", i, gues[i]);
    }
}
