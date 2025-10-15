#ifndef H_UTILS
#define H_UTILS 1

#define MINUTOS *60
#define HORAS *60 MINUTOS
#define DIAS *24 HORAS
#define MESES *30 DIAS
#define ANOS *12 MESES

#include <stdio.h>

typedef struct _medida_little
{
    double tempo_anterior;
    unsigned long int qt_requisicoes;
    double soma_area;

} Medida_little;

/**
 * Retorna o menor valor dentre n valores
 */
double min(int n, ...);

double aleatorio();

double exponencial(double l);

void inicia_little(Medida_little *medidas);

FILE *abre_relatorio(int argc, char *argv[]);

#endif