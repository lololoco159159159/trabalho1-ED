#ifndef _DOUBLE_LINKED_LIST_H_
#define _DOUBLE_LINKED_LIST_H_

#include "node.h"

typedef struct
{
    Node *head;
    Node *last;
    int size;
}List;

/**
 * @brief aloca espaco para um array de list 
 * 
 * @param tam quantidade de list
 * @return List** 
 */
List **lists_construct(int tam);

/**
 * @brief aloca espaco para uma lista
 * 
 * @return List* 
 */
List *list_construct();

/**
 * @brief retorna o ponteiro do ultimo da lista
 * 
 * @param l lista
 * @return Node* 
 */
Node *list_get_last(List *l); 

/**
 * @brief coloca um node na ultima posicao da linha
 * 
 * @param l lista
 * @param n node
 */
void list_push_back_linha(List *l, Node *n);

/**
 * @brief coloca um node na ultima posicao da coluna
 * 
 * @param l lista
 * @param n node
 */
void list_push_back_coluna(List *l, Node *n);

/**
 * @brief imprime a linha com elementos para debug
 * 
 * @param l lista
 */
void list_imprime_debug_linha(List *l);

/**
 * @brief imprime a coluna com elementos para debug
 * 
 * @param l lista
 */
void list_imprime_debug_coluna(List *l);

/**
 * @brief imprime uma linha no formato esparso
 * 
 * @param l lista
 */
void list_imprime_linha_esparso(List *l);

/**
 * @brief desacola memoria de uma linha
 * 
 * @param l lista
 */
void list_destroy_linha(List *l);

/**
 * @brief desaloca memoria de uma coluna
 * 
 * @param l list
 */
void list_destroy_coluna(List *l);

/**
 * @brief imprime uma linha no formato denso
 * 
 * @param l linha
 * @param tamColuna tamanho da list
 */
void list_imprime_linha_denso(List *l, int tamColuna);

/**
 * @brief imprime a list em arquivo bin
 * 
 * @param l list
 * @param tamColuna tamanho da list 
 * @param bin destino .bin
 */
void list_imprime_bin(List *l, int tamColuna, FILE *bin);

/**
 * @brief verifica se um node existe
 * 
 * @param l lista
 * @param coluna coluna do node procurado
 * @return Node* 
 */
Node *node_verifica_existe(List *l, int coluna);

/**
 * @brief descobre os ponteiros que devem ser armazenados no node e cria um node
 * 
 * @param listLinha linha
 * @param listColuna coluna
 * @param linha posicao na coluna
 * @param coluna posicao na linha
 * @param value valor armazenado
 * @return Node* 
 */
Node *node_new_construct(List *listLinha, List *listColuna, int linha, int coluna, data_type value);

/**
 * @brief ajeita os ponteiros armazenados pelos nodes apos a insercao de um node novo
 * na linha
 * 
 * @param l linha
 * @param node novo elemento inserido na linha
 * @param last_antigo antigo ultimo node antes da implementacao do novo node
 */
void list_ajeita_entrada_node_linha(List *l, Node *node, Node *last_antigo);

/**
 * @brief ajeita os ponteiros armazenados pelos nodes apos a insercao de um node novo
 * na coluna
 * 
 * @param l coluna
 * @param node novo elemento inserido na coluna
 * @param last_antigo antigo ultimo node antes da implementacao do novo node
 */
void list_ajeita_entrada_node_coluna(List *l, Node *node, Node *last_antigo);

/**
 * @brief remove um elemento da linha
 * 
 * @param l linha
 * @param linha posicao na coluna
 * @param coluna posicao na linha
 */
void list_remove_linha(List *l, int linha, int coluna);

/**
 * @brief remove um elemento da coluna
 * 
 * @param l coluna
 * @param linha posicao na coluna
 * @param coluna posicao na linha
 */
void list_remove_coluna(List *l, int linha, int coluna);

/**
 * @brief retorna tamanho da lista
 * 
 * @param l lista
 * @return int 
 */
int list_size(List *l);

/**
 * @brief confere se o ponteiro para o ultimo elemento da linha esta correto
 * 
 * @param l linha
 */
void list_ajeita_last_linha(List *l);

/**
 * @brief confere se o ponteiro para o ultimo elemento da coluna esta correto
 * 
 * @param l coluna
 */
void list_ajeita_last_coluna(List *l);

/**
 * @brief verifica se o node existe por meio da sua posicao
 * 
 * @param l coluna
 * @param linha posicao na coluna
 * @return Node* caso existe e NULL caso contrario 
 */
Node *node_verifica_existe_via_coluna(List *l, int linha);


#endif