#include "../hdr/janela.h"
#include <stdlib.h>

void insere_janela(Fila *fila, double tempo_decorrido)
{
    fila->S += tempo_decorrido;
    fila->T++;
    fila->janela.p = (fila->janela.p + 1) % (MAX_FILA);
    fila->janela.janela[fila->janela.p] = tempo_decorrido;
}

void remove_janela(Fila *fila, double tempo_decorrido)
{
    fila->janela.q = (fila->janela.q + 1) % (MAX_FILA);
    fila->S -= fila->janela.janela[fila->janela.q];
    fila->D += tempo_decorrido - fila->janela.janela[fila->janela.q];
}