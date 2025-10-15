#include "../hdr/fila.h"

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

void fprint_metrics(
    FILE *file,
    Fila filas[3],
    double tempo_decorrido,
    double soma_tempo_servico,
    unsigned long int qtd_servicos)
{
    double E_N_final = (filas[0].E_N.soma_area + filas[1].E_N.soma_area + filas[2].E_N.soma_area) / tempo_decorrido;
    double E_W_soma = (filas[0].E_W_chegadas.soma_area - filas[0].E_W_saidas.soma_area) + (filas[1].E_W_chegadas.soma_area - filas[1].E_W_saidas.soma_area) + (filas[2].E_W_chegadas.soma_area - filas[2].E_W_saidas.soma_area);
    unsigned long int E_W_qt_req = (filas[0].E_W_chegadas.qt_requisicoes + filas[1].E_W_chegadas.qt_requisicoes + filas[2].E_W_chegadas.qt_requisicoes);
    double E_W_final = E_W_soma / E_W_qt_req;
    double lambda = (E_W_qt_req / tempo_decorrido);
    double erro_little = E_N_final - lambda * E_W_final;
    unsigned long int qt_requisicoes = filas[0].qtd_requisicoes + filas[1].qtd_requisicoes + filas[2].qtd_requisicoes;

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

    fprintf(file, "%.10lf,%.10lf,%.10lf,%.20lf,%ld,%ld,%ld,%ld,%ld,%lf,%lf,%lf\n",
            E_N_final,
            E_W_final,
            lambda,
            erro_little,
            filas[0].tam,
            filas[1].tam,
            filas[2].tam,
            qt_requisicoes,
            qtd_servicos,
            (filas[0].soma_inter_requisicoes / filas[0].qtd_requisicoes) + (filas[1].soma_inter_requisicoes / filas[1].qtd_requisicoes) + (filas[2].soma_inter_requisicoes / filas[2].qtd_requisicoes),
            soma_tempo_servico / qtd_servicos,
            soma_tempo_servico / tempo_decorrido);
}