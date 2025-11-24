#ifndef H_FILA
#define H_FILA 1

#include "utils.h"
#include "janela.h"

typedef struct _fila
{
    unsigned long int tam;
    unsigned long int max;
    // Intervalos entre requisicoes
    double media_inter_requisicoes;
    // Marca sempre o tempo de chegada da proxima requisicao
    double proxima_requisicao;
    unsigned long int qtd_requisicoes;
    double soma_inter_requisicoes;
    Medida_little E_N;
    Medida_little E_W_chegadas, E_W_saidas;
    double ultimo_atendimento;

    // Medidas para parte 3

    // Soma do tempo de chegada
    double S;
    // Soma do atraso das requisicoes atendidas
    double D;
    // Tamanho da janela
    unsigned long int T;

    Janela janela;

} Fila;

void inicia_fila(Fila *fila);

void fila_prox_req(Fila *fila, double tempo_decorrido);

void fila_entrada_little(Fila *fila, double tempo_decorrido);

void fila_saida_little(Fila *fila, double tempo_decorrido);

void fila_atualiza_little(Fila *fila, double tempo_decorrido);

void fprint_metrics(FILE *file, Fila filas[3], double tempo_decorrido, double soma_tempo_servico, unsigned long int qtd_servicos);

int fila_maior_atraso_medio(Fila filas[3], double tempo_decorrido);

int fila_menor_atraso_medio(Fila filas[3], double tempo_decorrido);
#endif