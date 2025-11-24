#ifndef H_JANELA
#define H_JANELA 1

#define MAX_FILA 1000
#define MAX_JANELA 500

typedef struct _janela
{
    double janela[MAX_FILA];
    int p, q;
} Janela;

void insere_janela(Janela *janela, double valor);

void remove_janela(Janela *janela);
#endif