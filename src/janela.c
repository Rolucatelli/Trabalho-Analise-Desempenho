#include "../hdr/janela.h"
#include "../hdr/fila.h"

void insere_janela(Janela *janela, double valor)
{
    if ((janela->p + 1) % (MAX_FILA - 1) >= janela->q)
        return;

    janela->janela[(janela->p + 1) % (MAX_FILA - 1)] = valor;
}

void remove_janela(Janela *janela)
{
    if ((janela->q - 1 + (MAX_FILA - 1)) % (MAX_FILA - 1) <= janela->q)
        return;

    janela->q = (janela->q - 1 + (MAX_FILA - 1)) % (MAX_FILA - 1);
}