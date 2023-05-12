#ifndef _DOUBLE_LINKED_LIST_H_
#define _DOUBLE_LINKED_LIST_H_

#include "node.h"

typedef struct
{
    Node *head;
    Node *last;
    int size;
}List;

List **lists_construct(int tam);
List *list_construct();
Node *list_get_last(List *l);

void list_push_back_linha(List *l, Node *n);
void list_push_back_coluna(List *l, Node *n);
void list_imprime_debug_linha(List *l);
void list_imprime_debug_coluna(List *l);
void list_imprime_linha(List *l);
void list_destroy_linha(List *l);
void list_destroy_coluna(List *l);
void list_imprime_linha_esparso(List *l, int tamColuna);
void list_imprime_bin(List *l, int tamColuna, FILE *bin);
Node *node_verifica_existe(List *l, int coluna);
Node *node_new_construct(List *listLinha, List *listColuna, int linha, int coluna, data_type value);
void list_ajeita_entrada_node_linha(List *l, Node *node, Node *last_antigo);
void list_ajeita_entrada_node_coluna(List *l, Node *node, Node *last_antigo);
void list_remove_linha(List *l, int linha, int coluna);
void list_remove_coluna(List *l, int linha, int coluna);
int list_size(List *l);
void list_ajeita_last_linha(List *l);
void list_ajeita_last_coluna(List *l);
Node *node_verifica_existe_via_coluna(List *l, int linha);

#endif