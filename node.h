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

/**
 * @brief contrstroi um novo node
 * 
 * @param value valor armazenado no node
 * @param linha linha em que esta na matriz 
 * @param coluna coluna em que esta na matriz
 * @param linhaPrev ponteiro do anterior na linha
 * @param linhaNext ponteiro do proximo na linha
 * @param colunaPrev ponteiro do anterior na coluna
 * @param colunaNext ponteiro do proximo na coluna
 * @return Node* 
 */
Node *node_construct(data_type value, int linha, int coluna,Node *linhaPrev, Node *linhaNext, Node *colunaPrev, Node *colunaNext);

/**
 * @brief libera o espaco alocado pada o node
 * 
 * @param n node
 */
void node_destroy(Node *n);

/**
 * @brief imprime o valor do node
 * 
 * @param n node
 */
void node_printf(Node *n);

/**
 * @brief imprime o valor e os ponteiros armazenados para debug
 * 
 * @param n node
 * @param comando opcao se quer linha ou coluna para debug
 */
void node_printf_debug(Node *n, char comando);

/**
 * @brief retorna o valor armazenado no node
 * 
 * @param n node
 * @return data_type 
 */
data_type node_value(Node *n);

/**
 * @brief retorna a linha do node
 * 
 * @param n node
 * @return int 
 */
int node_linha(Node *n);

/**
 * @brief retorna a coluna do node
 * 
 * @param n node
 * @return int 
 */
int node_coluna(Node *n);

/**
 * @brief imprime o node com sua linha e coluna
 * 
 * @param n node
 */
void node_print_esparso(Node *n);

#endif