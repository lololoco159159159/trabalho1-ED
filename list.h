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
#endif