#ifndef H_UTILS
#define H_UTILS 1

#define MINUTOS *60
#define HORAS *60 MINUTOS
#define DIAS *24 HORAS
#define MESES *30 DIAS
#define ANOS *12 MESES

#include <stdio.h>

typedef struct
{
    double tempo_anterior;
    unsigned long int qt_requisicoes;
    double soma_area;

} Medida_little;

/**
 * Retorna o menor valor dentre n valores
 */
double min(int n, ...);

void fprint_metrics(FILE *file, Medida_little E_N, Medida_little E_W_chegadas, Medida_little E_W_saidas,
                    double tempo_decorrido, unsigned long int fila, double soma_inter_requisicoes,
                    unsigned long int qtd_requisicoes, double soma_tempo_servico, unsigned long int qtd_servicos);

double aleatorio();

double exponencial(double l);

void inicia_little(Medida_little *medidas);

FILE *abre_relatorio(int argc, char *argv[]);

#endif