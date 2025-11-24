#ifndef H_FILA
#define H_FILA 1

#include "utils.h"

void inicia_fila(Fila *fila);

void fila_prox_req(Fila *fila, double tempo_decorrido);

void fila_entrada_little(Fila *fila, double tempo_decorrido);

void fila_saida_little(Fila *fila, double tempo_decorrido);

void fila_atualiza_little(Fila *fila, double tempo_decorrido);

void fprint_metrics(FILE *file, Fila filas[3], double tempo_decorrido, double soma_tempo_servico, unsigned long int qtd_servicos);

double fila_atraso_medio(Fila fila, double tempo_decorrido);

int fila_maior_atraso_medio(Fila filas[3], double tempo_decorrido);

int fila_menor_atraso_medio(Fila filas[3], double tempo_decorrido);
#endif