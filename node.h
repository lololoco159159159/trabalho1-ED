#ifndef _NODE_H_
#define _NODE_H_

typedef float data_type;

typedef struct Node
{
    data_type value;
    struct Node *linhaPrev;
    struct Node *linhaNext;
    struct Node *colunaPrev;
    struct Node *colunaNext;
    int linha;
    int coluna;
}Node;

Node *node_construct(data_type value, int linha, int coluna,Node *linhaPrev, Node *linhaNext, Node *colunaPrev, Node *colunaNext);
void node_destroy(Node *n);
void node_print(Node *n, void (*print_fn)(data_type));
void node_printf(Node *n);
void node_printf_debug(Node *n, char comando);
data_type node_value(Node *n);
int node_linha(Node *n);
int node_coluna(Node *n);
#endif