#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <string.h>
#include "../hdr/utils.h"

double min(int n, ...)
{
    va_list args;
    va_start(args, n);

    double menor = INFINITY;

    for (int i = 0; i < n; i++)
    {
        double valor = va_arg(args, double);
        if (valor < menor)
            menor = valor;
    }
    va_end(args);
    return menor;
}

double aleatorio()
{
    double u = rand() / ((double)RAND_MAX + 1); // u entre [0,1)

    u = 1.0 - u; // u entre (0,1]

    return u;
}

double exponencial(double l)
{
    return (-1.0 / l) * log(aleatorio());
}

void inicia_little(Medida_little *medida)
{
    medida->tempo_anterior = 0.0;
    medida->qt_requisicoes = 0.0;
    medida->soma_area = 0;
}

FILE *abre_relatorio(int argc, char *argv[])
{
    // Abrindo arquivo do relatorio
    char path[256] = "./exe/relatorios/",
         nome_arq[256];
    if (argc < 2)
    {
        printf("Digite o nome do relatorio: ");
        scanf("%s", nome_arq);
    }
    else
    {
        strcpy(nome_arq, argv[1]);
    }

    int len = strlen(nome_arq);
    // Adiciona ".csv" apenas se não houver extensão
    if (len < 4 || strcmp(&nome_arq[len - 4], ".csv") != 0)
    {
        strcat(nome_arq, ".csv");
    }
    strcat(path, nome_arq);
    printf("%s\n", path);

    FILE *out = fopen(path, "w+");
    if (out == NULL)
    {
        printf("Erro ao abrir arquivo!\n");
        exit(1);
    }
    return out;
}