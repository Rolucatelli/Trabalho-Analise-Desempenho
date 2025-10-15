#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <float.h>
#include <math.h>
#include <string.h>
#include "../hdr/utils.h"

double min(int n, ...)
{
    va_list args;
    va_start(args, n);

    double menor = DBL_MAX;

    for (int i = 0; i < n; i++)
    {
        double valor = va_arg(args, double);
        if (valor < menor)
            menor = valor;
    }
    va_end(args);
    return menor;
}
void fprint_metrics(
    FILE *file,
    Medida_little E_N,
    Medida_little E_W_chegadas,
    Medida_little E_W_saidas,
    double tempo_decorrido,
    unsigned long int fila,
    double soma_inter_requisicoes,
    unsigned long int qtd_requisicoes,
    double soma_tempo_servico,
    unsigned long int qtd_servicos)
{
    double E_N_final = E_N.soma_area / tempo_decorrido;
    double E_W_final = (E_W_chegadas.soma_area - E_W_saidas.soma_area) / E_W_chegadas.qt_requisicoes;
    double lambda = (E_W_chegadas.qt_requisicoes / tempo_decorrido);
    double erro_little = E_N_final - lambda * E_W_final;

    int horas_decorridos = (int)(tempo_decorrido / 3600);
    int minutos_decorridos = ((int)tempo_decorrido % 3600) / 60;
    int segundos_decorridos = (int)tempo_decorrido % 60;

    if (horas_decorridos < 10)
        fprintf(file, "0%d:", horas_decorridos);
    else
        fprintf(file, "%d:", horas_decorridos);
    if (minutos_decorridos < 10)
        fprintf(file, "0%d:", minutos_decorridos);
    else
        fprintf(file, "%d:", minutos_decorridos);
    if (segundos_decorridos < 10)
        fprintf(file, "0%d,", segundos_decorridos);
    else
        fprintf(file, "%d,", segundos_decorridos);

    fprintf(file, "%.10lf,%.10lf,%.10lf,%.10lf,%.10lf,%.20lf,%ld,%ld,%ld,%lf,%lf,%lf\n",
            E_N_final,
            E_W_chegadas.soma_area / E_W_chegadas.qt_requisicoes,
            E_W_saidas.soma_area / E_W_saidas.qt_requisicoes,
            E_W_final,
            lambda,
            erro_little,
            fila,
            qtd_requisicoes,
            qtd_servicos,
            soma_inter_requisicoes / qtd_requisicoes,
            soma_tempo_servico / qtd_servicos,
            soma_tempo_servico / tempo_decorrido);
}
void fprint_metrics_global(
    FILE *file,
    Medida_little E_N,
    Medida_little E_W_chegadas,
    Medida_little E_W_saidas,
    double tempo_decorrido,
    unsigned long int fila,
    double soma_inter_requisicoes,
    unsigned long int qtd_requisicoes,
    double soma_tempo_servico,
    unsigned long int qtd_servicos)
{
    double E_N_final = E_N.soma_area / tempo_decorrido;
    double E_W_final = (E_W_chegadas.soma_area - E_W_saidas.soma_area) / E_W_chegadas.qt_requisicoes;
    double lambda = (E_W_chegadas.qt_requisicoes / tempo_decorrido);
    double erro_little = E_N_final - lambda * E_W_final;

    /*--------------------------------------------------------------------*/
    //- Calculo de hora
    int horas_decorridos = (int)(tempo_decorrido / 3600);
    int minutos_decorridos = ((int)tempo_decorrido % 3600) / 60;
    int segundos_decorridos = (int)tempo_decorrido % 60;

    if (horas_decorridos < 10)
        fprintf(file, "0%d:", horas_decorridos);
    else
        fprintf(file, "%d:", horas_decorridos);
    if (minutos_decorridos < 10)
        fprintf(file, "0%d:", minutos_decorridos);
    else
        fprintf(file, "%d:", minutos_decorridos);
    if (segundos_decorridos < 10)
        fprintf(file, "0%d,", segundos_decorridos);
    else
        fprintf(file, "%d,", segundos_decorridos);
    /*--------------------------------------------------------------------*/

    fprintf(file, "%.10lf,%.10lf,%.10lf,%.10lf,%.10lf,%.20lf,%ld,%ld,%ld,%lf,%lf,%lf\n",
            E_N_final,
            E_W_chegadas.soma_area / E_W_chegadas.qt_requisicoes,
            E_W_saidas.soma_area / E_W_saidas.qt_requisicoes,
            E_W_final,
            lambda,
            erro_little,
            fila,
            qtd_requisicoes,
            qtd_servicos,
            soma_inter_requisicoes / qtd_requisicoes,
            soma_tempo_servico / qtd_servicos,
            soma_tempo_servico / tempo_decorrido);
}

double aleatorio()
{
    double u = rand() / ((double)RAND_MAX + 1); // u entre [0,1)

    u = 1.0 - u; // u entre (0,1]

    return u;
}

double exponencial(double l)
{
    return (-1.0 / l) * log(aleatorio());
}

void inicia_little(Medida_little *medida)
{
    medida->tempo_anterior = 0.0;
    medida->qt_requisicoes = 0.0;
    medida->soma_area = 0;
}

FILE *abre_relatorio(int argc, char *argv[])
{
    // Abrindo arquivo do relatorio
    char path[256] = "./exe/relatorios/",
         nome_arq[256];
    if (argc < 2)
    {
        printf("Digite o nome do relatorio: ");
        scanf("%s", nome_arq);
    }
    else
    {
        strcpy(nome_arq, argv[1]);
    }

    int len = strlen(nome_arq);
    // Adiciona ".csv" apenas se não houver extensão
    if (len < 4 || strcmp(&nome_arq[len - 4], ".csv") != 0)
    {
        strcat(nome_arq, ".csv");
    }
    strcat(path, nome_arq);
    printf("%s\n", path);

    FILE *out = fopen(path, "w+");
    if (out == NULL)
    {
        printf("Erro ao abrir arquivo!\n");
        exit(1);
    }
    return out;
}