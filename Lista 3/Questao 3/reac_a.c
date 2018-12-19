#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
    @shogunhirei
    EQE749 - Métodos Numéricos
    Lista de soluções de Sistemas de Equações Diferenciais oridinárias - Questão 3

    Conjunto de reações competitivas
    Usando o método de Euler Explícito e Implicito para resolver os sistema de equações
    
    seg 17 dez 2018 12:35:17 -02
*/

int main(int argc, char** argv)
{
    // Constantes e dados
    int i; // Contadores diversos
    double k1 = 0.08; // Alterei a ordem de grandeza das constantes  
    double k2 = 2e4; // com base em alguns problemas similares  
    double k3 = 6e7; // de cinética. 

    double dT = 1e-4;// Passo de tempo em segundos
    double passos = 30.0/dT; 
    int num = abs(passos); // Quantidade de passos
    
    // Para armazenar respostas das três variáveis
    double dados1[num]; // para concentração de A
    double dados2[num]; // para concentração de B
    double dados3[num]; // Para concentração de C
    /*
        @shogunhirei
        Por questão de simplicidade as variaveis foram alteradas da seguinte forma:
        Ca --> x 
        Cb --> y
        Cc --> z 
        seg 17 dez 2018 12:53:53 -02
    */

    // Para armazenar os valores obtidos nas derivadas
    double x_lin;
    double y_lin;
    double z_lin;
    // Nas condições de contorno x0 = 1; y0 = z0 = 0
    dados1[0] = 1;
    dados2[0] = 0;
    dados3[0] = 0;
    FILE *file;
    file = fopen("data_a.txt", "w"); // Para gravação dos dados em arquivos txt para plotar

    // Para as diferenciais nas condições de contorno
    x_lin = -k1;
    y_lin = k1;
    z_lin = 0;

    for (i = 0; i < num; i++)
    {
        x_lin = -k1 * dados1[i] + k2 * dados2[i] * dados3[i];
        y_lin = k1 * dados1[i] - k2 * dados2[i] * dados3[i] - k3 * pow(dados2[i], 2.0);
        z_lin = k3 * pow(dados2[i],2.0);

        dados1[i + 1] = dados1[i] + dT * x_lin;
        dados2[i + 1] = dados2[i] + dT * y_lin;
        dados3[i + 1] = dados3[i] + dT * z_lin;
        
    }

    for (i = 0; i < num; ++i) {
        fprintf(file,"%f \t %f \t %f \t\n",dados1[i],dados2[i],dados3[i]);
    }
    fclose(file);

    return(EXIT_SUCCESS);
    
}
