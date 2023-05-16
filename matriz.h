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

/**
 * @brief aloca espaco para uma matriz
 * complexidade: O(1)
 * @param tamLinha quantidade de linhas
 * @param tamColuna quantidade de colunas
 * @return Matriz* 
 */
Matriz *matriz_construct(int tamLinha, int tamColuna);

/**
 * @brief armazena um node na ultima posicao da linha e da coluna
 * complexidade: O(1)
 * @param linha array com nodes da linha
 * @param coluna array com elementos da coluna
 * @param value valor armazenado pelo node
 * @param ilinha posicao na matriz
 * @param icoluna posicao na matriz
 */
void matriz_armazena_node(List *linha, List *coluna, data_type value, int ilinha, int icoluna);

/**
 * @brief le elementos e armazena na matriz
 * 
 */
void matriz_read();

/**
 * @brief imprime a matriz em formato esparso e denso
 * 
 * @param matriz ponteiro para a matriz
 */
void matriz_imprime(Matriz *matriz);

/**
 * @brief imprime matriz em formato denso
 * complexidade: O(n)
 * @param matriz ponteiro de matriz
 */
void matriz_imprime_denso(Matriz *matriz);

/**
 * @brief imprime matriz em formato esparso
 * complexidade: O(n)
 * @param matriz ponteiro de matriz
 */
void matriz_imprime_esparso(Matriz *matriz);

/**
 * @brief desacola o espaco armazenado para a matriz
 * complexidade: O(1)
 * @param matriz ponteiro para matriz
 */
void matriz_destruct(Matriz *matriz);

/**
 * @brief armazena os elementos da matriz em um arquivo.bin
 * complexidade: O(n) . O(m)
 * @param matriz ponteiro para a matriz
 * @param bin ponteiro para o arquivo.bin
 */
void matriz_armazena_bin(Matriz *matriz, FILE *bin);

/**
 * @brief le os elementos de um arquivo.bin e cria uma matriz com eles
 * complexidade: O(n²m) + O(nm²)
 * @param bin ponteiro para o arquivo.bin
 * @return Matriz* preenchida com os elementos
 */
Matriz *matriz_le_bin(FILE *bin);

/**
 * @brief insere um node na matriz 
 * complexidade: O(n) + O(m)
 * @param matriz ponteiro da matriz
 * @param linha posicao linha do node
 * @param coluna posicao coluna do node
 * @param value valor a ser armazenado pelo node
 */
void matriz_insere_value(Matriz *matriz, int linha, int coluna, data_type value);

/**
 * @brief efetua a operacao de soma de matrizes
 * complexidade:  O(n³m) + O(n²m²)
 * @param m1 ponteiro da primeira matriz
 * @param m2 ponteiro da segunda matriz
 * @return Matriz* nova matriz com os elementos da adicao
 */
Matriz *matriz_add(Matriz *m1, Matriz *m2);

/**
 * @brief retorna o valor de um node da matriz por meio da sua posicao
 * complexidade: O(n)
 * @param m ponteiro da matriz
 * @param linha posicao linha do node
 * @param coluna posicao coluna do node
 * @return data_type valor armazenado pelo node
 */
data_type matriz_value_linha_coluna(Matriz *m, int linha, int coluna);

/**
 * @brief multiplica todos os termos de uma matriz por um escalar
 * nao eh criado uma matriz nova, ela sera mantida alterada pelo resto do programa
 * complexidade: O(n²m) + O(nm²)
 * @param m ponteiro da matriz
 * @param escalar constante usada para multiplicar os elementos
 */
void matriz_multiplica_escalar(Matriz *m, int escalar);

/**
 * @brief multiplica duas matrizes 
 * complexidade: O(n².m2²)
 * @param m1 ponteiro da primeira matriz
 * @param m2 ponteiro da segunda matriz
 * @return Matriz* nova matriz criada pela multiplicacao das duas matrizes
 */
Matriz *matriz_multiplica_matriz(Matriz *m1, Matriz *m2);

/**
 * @brief multiplica elemento por elemento de duas matrizes
 * complexidade: O(n²m) + O(nm²)
 * @param m1 ponteiro da primeira matriz
 * @param m2 ponteiro da segunda matriz
 * @return Matriz* nova matriz criada pela multiplicacao ponto a ponto das duas matrizes
 */
Matriz *matriz_multiplica_ponto_a_ponto(Matriz *m1, Matriz *m2);

/**
 * @brief troca um node de uma linha com um node de outra linha
 * 
 * @param m ponteiro para a matriz
 * @param node1 node da primeira linha
 * @param node2 node da segunda linha
 * @param l1 primeira linha
 * @param l2 segunda linha
 */
void node_swap_linha(Matriz *m, Node *node1, Node *node2, int l1, int l2);

 /**
  * @brief troca duas linhas de uma matriz
  * complexidade: O(mn) + O(m²)
  * @param m ponteiro para uma matriz
  * @param l1 primeira linha
  * @param l2 segunda linha
  */
void matriz_swap_linha(Matriz *m, int l1, int l2);

/**
 * @brief troca duas colunas de uma matriz
 * complexidade: O(nm) + O(n²)
 * @param m ponteiro de uma matriz
 * @param c1 primeira coluna
 * @param c2 segunda coluna
 */
void matriz_swap_coluna(Matriz *m, int c1, int c2);

/**
 * @brief troca um node de uma coluna com um node de outra coluna
 * 
 * @param m ponteiro de uma matriz
 * @param node1 primeiro node
 * @param node2 segundo node
 * @param c1 coluna do primeiro node
 * @param c2 coluna do segundo node
 */
void node_swap_coluna(Matriz *m, Node *node1, Node *node2, int c1, int c2);

/**
 * @brief calcula a transposta de uma matriz
 * complexidade: O(n²m) + O(nm²)
 * @param m ponteiro de uma matriz
 * @return Matriz* transposta da matriz passada
 */
Matriz *matriz_transposta(Matriz *m);

/**
 * @brief recebe duas coordenadas (esquerdo superior e direiro inferior) e cria um submatriz com inicio e fim
 * nas coordenadas passadas 
 * complexidade: O(n²m) + O(nm²)
 * @param m ponteiro da matriz usada como base
 * @param l linha do canto superior esquedo
 * @param c coluna do canto superior esquerdo
 * @param l2 linha do canto inferior direito
 * @param c2 coluna do canto inferior direito
 * @return Matriz* nova matriz criada pelo recorte da matriz passada
 */
Matriz *matriz_slice(Matriz *m, int l, int c, int l2, int c2);

/**
 * @param l2 linha do canto inferior direito
 * @param c2 coluna do canto inferior direito
 * @return Matriz* nova matriz criada pelo recorte da matriz pass
 * @brief calcula o valor do elemento a ser inserido na nova matriz a ser criada pela convulacao
 * 
 * @param m1 ponteiro da matriz usada como base
 * @param kernel ponteiro de matriz de kernel
 * @param linhaCentral linha do elemento a ser calculado
 * @param colunaCentral coluna do elemento a ser calculado
 * @return data_type resultado do calculo
 */
data_type calcula_value_convulacao(Matriz *m1, Matriz *kernel, int linhaCentral, int colunaCentral);

/**
 * @brief realiza a operacao de convulacao entre duas matrizes
 * complexidade: O(n³m²) + O(m²m³)
 * @param m1 ponteiro da matriz usada como base
 * @param kernel ponteiro da matriz de kernel
 * @return Matriz* nova matriz com o resultado da convulacao
 */
Matriz *matriz_convulacao(Matriz *m1, Matriz *kernel);

/**
 * @brief soma de todos os termos de uma matriz
 * 
 * @param m ponteiro da matriz 
 * @return data_type resultado da soma
 */
data_type matriz_soma_dos_termos(Matriz *m);


#endif