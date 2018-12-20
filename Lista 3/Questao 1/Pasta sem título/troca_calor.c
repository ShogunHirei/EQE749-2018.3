#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
    @shogunhirei
    EQE749 - Métodos Numéricos
    3ª Lista de Exercícios - Questão 1

    Obs.: Fixarei a variação do tempo em dT1 = 20, dT2 = 5, dT3 = 1.25, dT4 = 0.3125

    ter 18 dez 2018 18:17:13 -02
*/

#define tempo_total 50.0 // Restrição temporal imposta 
#define T0 2500
#define Ta 250
#define alpha 4E-12
#define conv_crit 1e-5

double rel_error(double val1, double val2)
{
    double err = 0;
    err = fabs((val1 - val2)/val2); // Considerando val2 como Tn
    return err;
}

double abs_error(double val1, double val2)
{
    double err = 0;
    err = fabs(val1 - val2);
    return err;
}

double funct(double T, double time){

    // Para receber valor da Função 
    double X = 0;
    // Para simplificar a leitura da equação;
    double a = atan( T0 / Ta );
    double b = ((T0 - Ta) * (T + Ta))/( (T - Ta) * (T0 + Ta) );

    X = atan(T/Ta) - a + 0.5 * log(b) - 2 * alpha * time * pow (Ta, 3.0);

    // Valor F(T)
    return X;
}

double dev_funct(double T, double time)
{
    double X = 0;
    // Derivada da solução analitica no formato F(T, t) = 0
    // considerando o tempo constante, já que ele será definido para
    // comparação com as iterações.
    X = 0.5 * ( 1/(T + Ta) -  1/(T - Ta)) + 1/(Ta * (pow(T/Ta, 2.0) + 1));

    return X;
}

// Função para resolução do método de Euler implícito  
// Isolando T_(n+1) de forma que G(T_(n+1)) = 0 
double func_implicit(double dT , double Tn, double T_prev)
{
    double Fx;
    Fx = Tn - (T_prev + dT * alpha * pow(Ta, 4.0))/(1 + pow(Tn, 3.0) * dT * alpha);
    return Fx;
}

// Derivada da função G(T_(n+1)) = 0 em função de T_(n+1) 
// Para usar no Método de Newton-Raphson 
double dev_func_implicit(double dT , double Tn, double T_prev)
{
    double Fx_linha;
    Fx_linha = 1 + (3 * dT * pow(Tn, 2.0) * alpha * (pow(Ta, 4.0) * dT * alpha + T_prev)/pow((dT * pow(Tn, 3.0) * alpha + 1), 2.0));
    return Fx_linha;
}

double NR_implicit( double dT, double inic_val, double T_prev)
{
    double X;     
    double x0;
    double func;  // valor de F(x_0)  
    double f_linha; // Valor que receberá a derivada 
    double err; 
    int n = 0;   // Contador
    int limite = 1000; // Máximo de iterações 

    x0 = inic_val;

    // Iteração de Newton-Raphson
    do
    {
        // Determinando F(x0) e F'(x0)
        func = func_implicit( dT , x0, T_prev);
        f_linha = dev_func_implicit( dT , x0, T_prev);
        
        // Iteração
        X = x0 - func/f_linha; 
        err = fabs(X - x0);

        // Caso não convirja para a vizinhança apresentada
        if(n > limite)
        {
            printf("Não Convergiu! \n");
            break;
        }
        x0 = X; 
        n++;
    }while(err > conv_crit);

    return X;
}


double NR_met(double inic_val, double time)
{
    double X;     
    double x0;
    double func;  // valor de F(x_0)  
    double f_linha; // Valor que receberá a derivada 
    double err; 
    int n = 0;   // Contador
    int limite = 1000; // Máximo de iterações 

    // Para garantir a convergência em valores altos de 
    // passo de tempo, evitar explosão numérica
    if( fabs(inic_val - 1500) >= 500 && time >= 15)
    {
        inic_val = 1500; // Para garantir a convergência para passos de tempo
                         // elevados 
    }

    x0 = inic_val;

    // Iteração de Newton-Raphson
    do
    {
        // Determinando F(x0) e F'(x0)
        func = funct(x0, time);
        f_linha = dev_funct(x0, time);
        
        // Iteração
        X = x0 - func/f_linha; 
        err = fabs(X - x0);

        // Caso não convirja para a vizinhança apresentada
        if(n > limite)
        {
            printf("Não Convergiu! \n");
            break;
        }
        x0 = X; 
        n++;
    }while(err > conv_crit);

    return X;
}

double euler_explic(double dT, double Tn)
{
    double T_next;
    
    T_next = Tn + dT * (- alpha * (pow(Tn, 4.0) - pow(Ta , 4.0))); // Euler Explicito

    return T_next;
}

// Método de Euler Implícito
double euler_implic(double dT, double T_next_chute, double T_prev)
{
    double T_next;

    T_next = NR_implicit( dT, T_next_chute, T_prev); // Retorna a próxima temperatura para esse tempo

    return T_next;
}

int main(int argc, char** argv)
{
    // 1ª Parte: Declaração de Variáveis comuns aos dois itens:
    //      absl --> Erro absoluto
    //      rel --> Erro relativo
    //      Passos de Tempo --> Array com os valores de passos de tempo (PG com r = 0.25)
    //      num_passos --> variavel que determina para quantos t's vão ser calculados os métodos
    //      T_analitica --> Temperatura encontrada através da solução analítica
    //      T_chute --> Para estimar temperatura, para t = 0, T(t) = 2500K ela inicialmente é 2500
    //      Tempo --> Apenas para fazer evolução no tempo, facilitar elaboração dos gráficos
    //                  usado apenas para a solução analítica;
    //      dT --> Passo de tempo para os Métodos Implícito e Explícito de Euler
    //      T_prev --> Para a solução implicita, mesma função do T_chute
    //
    //
    int i, j; // Contadores diversos 
    double passos_temp[4] = {20.0, 5.0, 1.25, 0.3125};
    double Tempo; // Tempo acumulado
    double Tn;
    double T_analitica;
    double T_prev;
    double T_chute;
    double absl; // Para armazenar localmente os erros absolutos e relativos
    double rel; // Para armazenar localmente os erros absolutos e relativos
    int num_passos;
    double dT; // Passo de tempo

    FILE *file;
    file = fopen("Q1_letraA.txt", "w");
    
    printf("******************** Item a *******************\n");

    for ( i = 0; i < sizeof(passos_temp)/sizeof(double); i++) // Para poder realizar os cálculos para cada passo de tempo
    {
        // Respeitando a restrição do tempo de 0 a 50 segundos 
        num_passos = abs(tempo_total/passos_temp[i]);

        Tempo = 0;
        dT = passos_temp[i]; 

        T_chute = T0;

        fprintf(file, "Resolução para passo de tempo: %f \n", passos_temp[i]);

        fprintf(file, "----------------------------------------------------------------------\n");
        
        fprintf(file, "Passo \t Tempo \t Solução Analítica \t Euler Explicíto \t Er. Abs. \t Er. Rel. \n");
        for(j = 0; j < num_passos; j++)
        {
            Tempo += dT; // Incremento de tempo;

            Tn = euler_explic( dT, T_chute );

            // Usando o valor estimado pelo método de Euler Explícito para aproximar da solução 
            T_analitica = NR_met(T_chute, Tempo); // Solução Analítica

            absl = abs_error(Tn, T_analitica); // Determinação do Erro absoluto 
            rel = rel_error(Tn, T_analitica); // Determinação do erro relativo

            T_chute = Tn;
            
            fprintf(file, "%d \t %f \t %f \t %f \t %f \t %f \n", j + 1, Tempo, T_analitica, Tn, absl, rel); 

        }

        fprintf(file, "----------------------------------------------------------------------\n");
    }

    fclose(file);

    printf("**************** Item b ******************\n");

    file = fopen("Q1_letraB.txt", "w");
    
    for ( i = 0; i < sizeof(passos_temp)/sizeof(double); i++) // Para poder realizar os cálculos para cada passo de tempo
    {
        // Respeitando a restrição do tempo de 0 a 50 segundos 
        num_passos = abs(tempo_total/passos_temp[i]);

        Tempo = 0;
        dT = passos_temp[i]; 

        T_chute = T0;
        T_prev = T0;

        fprintf(file, "Resolução para passo de tempo: %f \n", passos_temp[i]);

        fprintf(file, "----------------------------------------------------------------------\n");
        
        fprintf(file, "Passo \t Tempo \t Solução Analítica \t Euler Implícito \t Er. Abs. \t Er. Rel. \n");

        for(j = 0; j < num_passos; j++)
        {
            Tempo += dT; // Incremento de tempo;

            T_prev = euler_implic( dT, T_chute, T_prev ); // Resolve a equação não linear e retorna o T_(n+1)

            // Usando o valor estimado pelo método de Euler Explícito para aproximar da solução 
            T_analitica = NR_met(T_chute, Tempo); // Solução Analítica

            absl = abs_error(T_prev, T_analitica); // Determinação do Erro absoluto 
            rel = rel_error(T_prev, T_analitica); // Determinação do erro relativo

            T_chute = T_prev;
            
            fprintf(file, "%d \t %f \t %f \t %f \t %f \t %f \n", j + 1, Tempo, T_analitica, T_prev, absl, rel); 

        }

        fprintf(file, "----------------------------------------------------------------------\n");
    }

    fclose(file);

     
}
