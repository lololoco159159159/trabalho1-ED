#include <stdio.h>
#include <stdlib.h>
#include "node.h"

void node_destroy(Node *n){
    free(n);
}

void node_print(Node *n, void (*print_fn)(data_type)){
    print_fn(n->value);
}

void node_printf(Node *n){
    printf("%.0f", n->value);
}

void node_printf_debug(Node *n , char comando){
    printf("(");
    if(comando == 'l'){
        if(n->linhaPrev == NULL){
            printf("NULL, ");
        }
        else{
            printf("%0.f, ", n->linhaPrev->value);
        }
        printf("%0.f, ", n->value);
        if(n->linhaNext == NULL){
            printf("NULL");
        }
        else{
            printf("%0.f", n->linhaNext->value);
        }
    }
    else{
        if(n->colunaPrev == NULL){
            printf("NULL, ");
        }
        else{
            printf("%0.f, ", n->colunaPrev->value);
        }
        printf("%0.f, ", n->value);
        if(n->colunaNext == NULL){
            printf("NULL");
        }
        else{
            printf("%0.f", n->colunaNext->value);
        }
    }
    printf(")");
}

Node *node_construct(data_type value, int linha, int coluna, Node *linhaPrev, Node *linhaNext, Node *colunaPrev, Node *colunaNext){
    Node *n = (Node *)malloc(sizeof(Node));
    n->value = value;
    n->linha = linha;
    n->coluna = coluna;
    n->colunaNext = colunaNext;
    n->colunaPrev = colunaPrev;
    n->linhaNext = linhaNext;
    n->linhaPrev = linhaPrev;
    return n;
}

data_type node_value(Node *n){
    return n->value;
}

int node_linha(Node *n){
    return n->linha;
}

int node_coluna(Node *n){
    return n->coluna;
}



