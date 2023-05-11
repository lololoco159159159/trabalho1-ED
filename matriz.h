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
void matriz_armazena_bin(Matriz *matriz, FILE *bin);
Matriz *matriz_le_bin(FILE *bin);
void matriz_insere_value(Matriz *matriz, int linha, int coluna, data_type value);
Matriz *matriz_add(Matriz *m1, Matriz *m2);
data_type matriz_value_linha_coluna(Matriz *m, int linha, int coluna);
void matriz_multiplica_escalar(Matriz *m, int escalar);
Matriz *matriz_multiplica_matriz(Matriz *m1, Matriz *m2);
Matriz *matriz_multiplica_ponto_a_ponto(Matriz *m1, Matriz *m2);
#endif