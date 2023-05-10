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
            printf(" ");
        }

    }
}

void list_imprime_bin(List *l, int tamColuna, FILE *bin){
    Node *aux = l->head;
    fwrite(&(l->size), sizeof(int), 1, bin);
    printf("%d   ", l->size);
    while(aux != NULL){
        fwrite(&(aux->linha), sizeof(int), 1, bin);
        fwrite(&(aux->coluna), sizeof(int), 1, bin);
        fwrite(&(aux->value), sizeof(data_type), 1, bin);
        printf("%d %d %.0f  ", aux->linha, aux->coluna, aux->value);
        aux = aux->linhaNext;
    }
    printf("\n");
}

Node *node_verifica_existe(List *l, int coluna){
    Node *aux = l->head;
    while(aux != NULL){
        if (aux->coluna == coluna){
            return aux;
        }
        aux = aux->linhaNext;
    }
    return NULL;
}

Node *node_new_construct(List *listLinha, List *listColuna, int linha, int coluna, data_type value){

    Node *nodeLinhaPrev, *nodeLinhaNext, *nodeColunaPrev, *nodeColunaNext, *aux = listLinha->head;
    int achou = 0;

    //===linha
    //caso n existe
    if(listLinha->size == 0){
        nodeLinhaNext = NULL;
        nodeLinhaPrev = NULL;
        achou = 1;
    }
    //caso existe maior
    if(achou == 0){
        while(aux != NULL){
            if (aux->coluna > coluna){
                nodeLinhaNext = aux;
                nodeLinhaPrev = aux->linhaPrev;
                achou = 1;
                break;
            }
            aux = aux->linhaNext;
        }
    }
    //caso nao existe maior
    if(achou == 0){
        nodeLinhaNext = NULL;
        nodeLinhaPrev = listLinha->last;
    }

    //===coluna
    achou = 0;
    aux = listColuna->head;
    //caso n existe
    if(listColuna->size == 0){
        nodeColunaNext = NULL;
        nodeColunaPrev = NULL;
        achou = 1;
    }
    //caso existe maior
    if (achou == 0){
        while(aux != NULL){
            if(aux->linha > linha){
                nodeColunaNext = aux;
                nodeColunaPrev = aux->colunaPrev;
                achou = 1;
                break;
            }
            aux = aux->colunaNext;
        }
    }
    //caso nao existe maior
    if(achou == 0){
        nodeColunaNext = NULL;
        nodeColunaPrev = listColuna->last;
    }

    Node *node = node_construct(value, linha, coluna, nodeLinhaPrev, nodeLinhaNext, nodeColunaPrev, nodeColunaNext);
    return node;
}

void list_ajeita_entrada_node_linha(List *l, Node *node, Node *last_antigo){
    //caso ultimo ou unico (ja esta correto)
    if(node->linhaNext == NULL){
        return;
    }
    //caso primeiro    
    else if(node->linhaPrev == NULL){
        last_antigo->linhaNext = NULL;
        l->last = last_antigo;
        l->head->linhaPrev = node;
        l->head = node;
    }
    //caso meio
    else{
        Node *prev = node->linhaPrev;
        Node *next = node->linhaNext;
        prev->linhaNext = node;
        next->linhaPrev = node;
    }
}

void list_ajeita_entrada_node_coluna(List *l, Node *node, Node *last_antigo){
    //caso ultimo ou unico (ja esta correto)
    if(node->colunaNext == NULL){
        return;
    }
    //caso primeiro    
    else if(node->colunaPrev == NULL){
        last_antigo->colunaNext = NULL;
        l->last = last_antigo;
        l->head->colunaPrev = node;
        l->head = node;
    }
    //caso meio
    else{
        Node *prev = node->colunaPrev;
        Node *next = node->colunaNext;
        prev->colunaNext = node;
        next->colunaPrev = node;
    }
}

void list_remove_linha(List *l, int linha, int coluna){
    Node *aux = l->head;
    if (aux == NULL){
        printf("lista vazia!");
        exit(0);
    }

    while(aux != NULL){
        if (aux->linha == linha && aux->coluna == coluna){
            if(aux == l->head){
                l->head = l->head->linhaNext;
                if(l->head != NULL)
                    l->head->linhaPrev = NULL;
            }
            else if(aux == l->last){
                l->last = l->last->linhaPrev;
                l->last->linhaNext = NULL;
            }
            else{
                Node *prev = aux->linhaPrev;
                Node *next = aux->linhaNext;
                prev->linhaNext = next;
                next->linhaPrev = prev;
            }
            l->size--;
            if(l->size == 1){
                l->last = l->head;
            }
            else if(l->size == 0){
                l->last = NULL;
                l->head = NULL;
            }
            break;
        }
        else{
            aux = aux->linhaNext;
        }
    }
}

void list_remove_coluna(List *l, int linha, int coluna){
    Node *aux = l->head;
    if (aux == NULL){
        printf("lista vazia!");
        exit(0);
    }
    while(aux != NULL){
        if (aux->linha == linha && aux->coluna == coluna){
            if(aux == l->head){
                l->head = l->head->colunaNext;
                if(l->head != NULL)
                    l->head->colunaPrev = NULL;
            }
            else if(aux == l->last){
                l->last = l->last->colunaPrev;
                l->last->colunaNext = NULL;
            }
            else{
                Node *prev = aux->colunaPrev;
                Node *next = aux->colunaNext;
                prev->colunaNext = next;
                next->colunaPrev = prev;
            }
            l->size--;
            if(l->size == 1){
                l->last = l->head;
            }
            else if(l->size == 0){
                l->last = NULL;
                l->head = NULL;
            }
            node_destroy(aux);
            break;
        }
        else{
            aux = aux->colunaNext;
        }
    }
}

int list_size(List *l){
    return l->size;
}

