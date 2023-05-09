#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void list_imprime_debug_linha(List *l){
    Node *aux = l->head;
    while(aux != NULL){
        node_printf_debug(aux, 'l');
        printf(" ");
        aux = aux->linhaNext;
    }
}

void list_imprime_debug_coluna(List *l){
    Node *aux = l->head;
    while(aux != NULL){
        node_printf_debug(aux, 'c');
        printf(" ");
        aux = aux->colunaNext;
    }
}

void list_imprime_linha(List *l){
    Node *aux = l->head;
    while(aux != NULL){
        node_printf(aux);
        printf(" ");
        aux = aux->linhaNext;
    }
}

List **lists_construct(int tam){
    int i = 0;
    List **lists = (List**)malloc(sizeof(List*) * tam);

    for(i = 0; i < tam; i++){
        lists[i] = list_construct();
    }
    return lists;
}

List *list_construct(){
    List *l = (List*)malloc(sizeof(List));
    l->size = 0;
    l->head = l->last = NULL;
    return l;
}

Node *list_get_last(List *l){
    return l->last;
}

void list_push_back_linha(List *l, Node *n){
    l->last = n;
    l->size++;
    if(l->size == 1){
        l->head = l->last;
    }

    if(l->last->linhaPrev != NULL){
        Node *aux = l->last->linhaPrev;
        aux->linhaNext = l->last;
    }
}

void list_push_back_coluna(List *l, Node *n){
    l->last = n;
    l->size++;
    if(l->size == 1){
        l->head = l->last;
    }

    if(l->last->colunaPrev != NULL){
        Node *aux = l->last->colunaPrev;
        aux->colunaNext = l->last;
    }
}

void list_destroy_linha(List *l){
    Node *aux = l->head;
    Node *destroy = l->head;
    while (aux != NULL){
        aux = aux->linhaNext;
        node_destroy(destroy);
        destroy = aux;
    }
    free(l);
}

void list_destroy_coluna(List *l){
    free(l);
}

void list_imprime_linha_esparso(List *l, int tamColuna){
    Node *aux = l->head;
    for(int i = 0; i < tamColuna; i++){
        if(aux != NULL){
            if(aux->coluna == i){
                node_printf(aux);
                aux = aux->linhaNext;
            }
            else
                printf("0");
        }
        else{
            printf("0");
        }
        if(i < tamColuna - 1){
            printf(", ");
        }

    }
}



