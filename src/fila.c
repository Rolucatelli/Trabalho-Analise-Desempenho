#include "../hdr/fila.h"
#include "../hdr/utils.h"

void inicia_fila(Fila *fila)
{
    fila->tam = 0;
    fila->max = 0;
    fila->media_inter_requisicoes = 0.0;
    fila->proxima_requisicao = 0.0;
    fila->qtd_requisicoes = 0.0;
    fila->soma_inter_requisicoes = 0.0;
    inicia_little(&(fila->E_N));
    inicia_little(&(fila->E_W_chegadas));
    inicia_little(&(fila->E_W_saidas));
    fila->ultimo_atendimento = 0.0;
}

void fila_prox_req(Fila *fila, double tempo_decorrido)
{
    fila->proxima_requisicao = tempo_decorrido + exponencial(fila->media_inter_requisicoes);
    fila->qtd_requisicoes++;
    fila->soma_inter_requisicoes += fila->proxima_requisicao - tempo_decorrido;
}

void fila_entrada_little(Fila *fila, double tempo_decorrido)
{
    fila->E_N.soma_area += (tempo_decorrido - fila->E_N.tempo_anterior) * fila->E_N.qt_requisicoes;
    fila->E_N.qt_requisicoes++;
    fila->E_N.tempo_anterior = tempo_decorrido;

    fila->E_W_chegadas.soma_area += (tempo_decorrido - fila->E_W_chegadas.tempo_anterior) * fila->E_W_chegadas.qt_requisicoes;
    fila->E_W_chegadas.qt_requisicoes++;
    fila->E_W_chegadas.tempo_anterior = tempo_decorrido;
}
void fila_saida_little(Fila *fila, double tempo_decorrido)
{
    fila->E_N.soma_area += (tempo_decorrido - fila->E_N.tempo_anterior) * fila->E_N.qt_requisicoes;
    fila->E_N.qt_requisicoes--;
    fila->E_N.tempo_anterior = tempo_decorrido;

    fila->E_W_saidas.soma_area += (tempo_decorrido - fila->E_W_saidas.tempo_anterior) * fila->E_W_saidas.qt_requisicoes;
    fila->E_W_saidas.qt_requisicoes++;
    fila->E_W_saidas.tempo_anterior = tempo_decorrido;
}

void fila_atualiza_little(Fila *fila, double tempo_decorrido)
{
    fila->E_N.soma_area += (tempo_decorrido - fila->E_N.tempo_anterior) * fila->E_N.qt_requisicoes;
    fila->E_N.tempo_anterior = tempo_decorrido;

    fila->E_W_chegadas.soma_area += (tempo_decorrido - fila->E_W_chegadas.tempo_anterior) * fila->E_W_chegadas.qt_requisicoes;
    fila->E_W_chegadas.tempo_anterior = tempo_decorrido;

    fila->E_W_saidas.soma_area += (tempo_decorrido - fila->E_W_saidas.tempo_anterior) * fila->E_W_saidas.qt_requisicoes;
    fila->E_W_saidas.tempo_anterior = tempo_decorrido;
}