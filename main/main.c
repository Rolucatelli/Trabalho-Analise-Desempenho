#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "../hdr/utils.h"
#include "../hdr/fila.h"

int main(int argc, char *argv[])
{
    srand(time(NULL));

    // FILE *out = abre_relatorio(argc, argv);
    FILE *out = fopen("./exe/relatorios/relatorio_fila0.csv", "w+");
    FILE *out1 = fopen("./exe/relatorios/relatorio_fila1.csv", "w+");
    FILE *out2 = fopen("./exe/relatorios/relatorio_fila2.csv", "w+");

    /*--------------------------------------------------------------------*/
    //- Declarando Variáveis

    // Declaracao little
    Medida_little E_N_global;
    Medida_little E_W_chegadas_global, E_W_saidas_global;

    // Iniciando variaveis de little
    inicia_little(&E_N_global);
    inicia_little(&E_W_chegadas_global);
    inicia_little(&E_W_saidas_global);

    // inicio
    double tempo_decorrido = 0.0; // 0 segundos

    // tempo total que desejo simular
    double tempo_simulacao = 1.0 DIAS; // 24 horas

    // tempo medio gasto entre 1 atendimento
    double media_tempo_servico;

    // possui o tempo de servico da requisicao atualmente
    double tempo_servico;

    // filas
    Fila filas[3];
    inicia_fila(&filas[0]);
    inicia_fila(&filas[1]);
    inicia_fila(&filas[2]);

    // variáveis de medicao para validacao matematica
    unsigned long int qtd_servicos = 0;
    double soma_tempo_servico = 0.0;

    /*--------------------------------------------------------------------*/
    //- Lendo media_inter_requisicoes e media_inter_servicos
    if (argc >= 3)
    {
        char *endptr1;
        filas[0].media_inter_requisicoes = strtod(argv[2], &endptr1);
        filas[1].media_inter_requisicoes = strtod(argv[2], &endptr1);
        filas[2].media_inter_requisicoes = strtod(argv[2], &endptr1);
    }
    else
    {
        printf("Informe a media de tempo entre requisicoes da fila 1: ");
        scanf("%lf", &(filas[0].media_inter_requisicoes));
        printf("Informe a media de tempo entre requisicoes da fila 2: ");
        scanf("%lf", &(filas[1].media_inter_requisicoes));
        printf("Informe a media de tempo entre requisicoes da fila 3: ");
        scanf("%lf", &(filas[2].media_inter_requisicoes));
    }
    if (argc >= 4)
    {
        char *endptr2;
        media_tempo_servico = strtod(argv[3], &endptr2);
    }
    else
    {
        printf("Informe a media de tempo para atendimento: ");
        scanf("%lf", &media_tempo_servico);
    }

    /*--------------------------------------------------------------------*/
    //- Iniciando variáveis para a simulação

    /*
        precisamos do valor do parametro l para gerar
        os numeros pseudo-aleatorios.
        lembre-se que l = 1.0/media
    */
    filas[0].media_inter_requisicoes = 1.0 / filas[0].media_inter_requisicoes;
    filas[1].media_inter_requisicoes = 1.0 / filas[1].media_inter_requisicoes;
    filas[2].media_inter_requisicoes = 1.0 / filas[2].media_inter_requisicoes;

    media_tempo_servico = 1.0 / media_tempo_servico;

    tempo_decorrido = 0.0;

    double volta = 10.0;

    fprintf(out, "Tempo decorrido,E[N],E[W] chegadas,E[W] saídas,E[W],Lambda,Erro Little,Fila,Requisições feitas,Requisições atendidas,Média entre requisições,Média entre servicos,Ocupação calculada\n");
    fprintf(out1, "Tempo decorrido,E[N],E[W] chegadas,E[W] saídas,E[W],Lambda,Erro Little,Fila,Requisições feitas,Requisições atendidas,Média entre requisições,Média entre servicos,Ocupação calculada\n");
    fprintf(out2, "Tempo decorrido,E[N],E[W] chegadas,E[W] saídas,E[W],Lambda,Erro Little,Fila,Requisições feitas,Requisições atendidas,Média entre requisições,Média entre servicos,Ocupação calculada\n");

    // gerando o tempo de chegada da primeira requisicao
    fila_prox_req(&filas[0], tempo_decorrido);
    fila_prox_req(&filas[1], tempo_decorrido);
    fila_prox_req(&filas[2], tempo_decorrido);

    double proxima_requisicao;

    /*--------------------------------------------------------------------*/
    //- Fazendo a simulação
    while (tempo_decorrido < tempo_simulacao)
    {
        proxima_requisicao = min(3, filas[0].proxima_requisicao, filas[1].proxima_requisicao, filas[2].proxima_requisicao);
        tempo_decorrido = min(2 + ((filas[0].tam) || (filas[1].tam) || (filas[2].tam)), proxima_requisicao, volta, tempo_servico);

        // tratando os eventos da simulacao:
        if (tempo_decorrido == proxima_requisicao)
        {
            //& ACONTECE UMA CHEGADA

            int idx;
            if (proxima_requisicao == filas[0].proxima_requisicao)
            {
                idx = 0;
            }
            else if (proxima_requisicao == filas[1].proxima_requisicao)
            {
                idx = 1;
            }
            else if (proxima_requisicao == filas[2].proxima_requisicao)
            {
                idx = 2;
            }

            (filas[idx].tam)++;
            (filas[idx].max) = (filas[idx].tam) > (filas[idx].max) ? (filas[idx].tam) : (filas[idx].max);
            if ((filas[0].tam + filas[1].tam + filas[2].tam) == 1)
            {
                // ambiente estava ocioso, inicia atendimento imediatamente
                tempo_servico = tempo_decorrido + exponencial(media_tempo_servico);
                qtd_servicos++;
                soma_tempo_servico += tempo_servico - tempo_decorrido;
            }
            fila_prox_req(&filas[idx], tempo_decorrido);

            fila_entrada_little(&filas[idx], tempo_decorrido);
        }
        else if (tempo_decorrido == volta)
        {
            //& Calcula a área e printa no arquivo
            fila_atualiza_little(&filas[0], tempo_decorrido);
            fila_atualiza_little(&filas[1], tempo_decorrido);
            fila_atualiza_little(&filas[2], tempo_decorrido);

            // Printar no arquivo
            fprint_metrics(out, filas[0].E_N, filas[0].E_W_chegadas, filas[0].E_W_saidas, tempo_decorrido, (filas[0].tam), filas[0].soma_inter_requisicoes, filas[0].qtd_requisicoes, soma_tempo_servico, qtd_servicos);
            fprint_metrics(out1, filas[1].E_N, filas[1].E_W_chegadas, filas[1].E_W_saidas, tempo_decorrido, (filas[1].tam), filas[1].soma_inter_requisicoes, filas[1].qtd_requisicoes, soma_tempo_servico, qtd_servicos);
            fprint_metrics(out2, filas[2].E_N, filas[2].E_W_chegadas, filas[2].E_W_saidas, tempo_decorrido, (filas[2].tam), filas[2].soma_inter_requisicoes, filas[2].qtd_requisicoes, soma_tempo_servico, qtd_servicos);
            volta += 10.0;
        }
        else
        {
            //& ACONTECE UMA SAIDA

            int idx;
            double menor_tempo = INFINITY;

            for (int i = 0; i < 3; i++)
            {
                if (filas[i].tam > 0 && filas[i].ultimo_atendimento < menor_tempo)
                {
                    menor_tempo = filas[i].ultimo_atendimento;
                    idx = i;
                }
            }

            (filas[idx].tam)--;
            if ((filas[0].tam) || (filas[1].tam) || (filas[2].tam))
            {
                // atendo o proximo
                tempo_servico = tempo_decorrido + exponencial(media_tempo_servico);
                qtd_servicos++;
                soma_tempo_servico += tempo_servico - tempo_decorrido;
            }

            fila_saida_little(&filas[idx], tempo_decorrido);
        }
    }
    /*--------------------------------------------------------------------*/

    filas[0].E_W_chegadas.soma_area += (tempo_decorrido - filas[0].E_W_chegadas.tempo_anterior) * filas[0].E_W_chegadas.qt_requisicoes;
    filas[0].E_W_saidas.soma_area += (tempo_decorrido - filas[0].E_W_saidas.tempo_anterior) * filas[0].E_W_saidas.qt_requisicoes;

    filas[1].E_W_chegadas.soma_area += (tempo_decorrido - filas[1].E_W_chegadas.tempo_anterior) * filas[1].E_W_chegadas.qt_requisicoes;
    filas[1].E_W_saidas.soma_area += (tempo_decorrido - filas[1].E_W_saidas.tempo_anterior) * filas[1].E_W_saidas.qt_requisicoes;

    filas[2].E_W_chegadas.soma_area += (tempo_decorrido - filas[2].E_W_chegadas.tempo_anterior) * filas[2].E_W_chegadas.qt_requisicoes;
    filas[2].E_W_saidas.soma_area += (tempo_decorrido - filas[2].E_W_saidas.tempo_anterior) * filas[2].E_W_saidas.qt_requisicoes;

    /**
     * little
     */
    double E_N_final = (filas[0].E_N.soma_area + filas[1].E_N.soma_area + filas[2].E_N.soma_area) / tempo_decorrido;
    double E_W_soma = (filas[0].E_W_chegadas.soma_area - filas[0].E_W_saidas.soma_area) + (filas[1].E_W_chegadas.soma_area - filas[1].E_W_saidas.soma_area) + (filas[2].E_W_chegadas.soma_area - filas[2].E_W_saidas.soma_area);
    unsigned long int E_W_qt_req = (filas[0].E_W_chegadas.qt_requisicoes + filas[1].E_W_chegadas.qt_requisicoes + filas[2].E_W_chegadas.qt_requisicoes);
    double E_W_final = E_W_soma / E_W_qt_req;
    double lambda = (E_W_qt_req / tempo_decorrido);
    double erro_little = E_N_final - lambda * E_W_final;

    printf("\n===============================\n");
    printf("     Metricas e validacoes     \n");
    printf("===============================\n");
    printf("qtd_requisicoes: %ld\n", filas[0].qtd_requisicoes + filas[1].qtd_requisicoes + filas[2].qtd_requisicoes);
    printf("max_fila (0,1,2): %ld %ld %ld\n", filas[0].max, filas[1].max, filas[2].max);
    printf("media entre requisicoes (0,1,2): %lf %lf %lf\n", filas[0].soma_inter_requisicoes / filas[0].qtd_requisicoes, filas[2].soma_inter_requisicoes / filas[2].qtd_requisicoes, filas[2].soma_inter_requisicoes / filas[2].qtd_requisicoes);
    printf("media entre servicos: %lf\n", soma_tempo_servico / qtd_servicos);
    printf("\n===============================\n");
    printf("          Ocupacao\n");
    printf("===============================\n");
    printf("ocupacao calculada: %lf\n", soma_tempo_servico / tempo_decorrido);
    printf("ocupacao esperada: %lf\n", (filas[0].media_inter_requisicoes + filas[1].media_inter_requisicoes + filas[2].media_inter_requisicoes) / media_tempo_servico);
    printf("\n===============================\n");
    printf("          Little\n");
    printf("===============================\n");
    printf("E[N]: %lf\n", E_N_final);
    printf("E[W]: %lf\n", E_W_final);
    printf("lambda: %lf\n", lambda);
    printf("Erro little: %.20lf\n", erro_little);

    fclose(out);
}
