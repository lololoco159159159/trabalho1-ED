#ifndef _MATRIZ_H_
#define _MATRIZ_H_
#include "list.h"

typedef struct
{
    List **linhas;
    List **colunas;
    int tamLinha;
    int tamColuna;
}Matriz;

Matriz *matriz_construct(int tamLinha, int tamColuna);
void matriz_armazena_node(List *linha, List *coluna, data_type value, int ilinha, int icoluna);
void matriz_read();
void matriz_imprime_debug(Matriz *matriz);
void matriz_destruct(Matriz *matriz);
void matriz_add_value(Matriz *matriz);
#endif