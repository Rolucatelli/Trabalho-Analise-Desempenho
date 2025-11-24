#ifndef H_UTILS
#define H_UTILS 1

#define MINUTOS *60
#define HORAS *60 MINUTOS
#define DIAS *24 HORAS
#define MESES *30 DIAS
#define ANOS *12 MESES

#include <stdio.h>

#define MAX_FILA 100000
typedef struct _janela
{
    double janela[MAX_FILA];
    int p, q;
} Janela;

typedef struct _medida_little
{
    double tempo_anterior;
    unsigned long int qt_requisicoes;
    double soma_area;

} Medida_little;
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

/**
 * Retorna o menor valor dentre n valores
 */
double min(int n, ...);

double aleatorio();

double exponencial(double l);

void inicia_little(Medida_little *medidas);

FILE *abre_relatorio(int argc, char *argv[]);

#endif