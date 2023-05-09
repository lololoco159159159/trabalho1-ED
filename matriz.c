#include <stdio.h> 
#include <stdlib.h>
#include "matriz.h"


void matriz_imprime_debug(Matriz *matriz){
    int i = 0;
    //formato esparso
    printf("formato denso:\n");
    for(i = 0; i < matriz->tamLinha; i++){
        list_imprime_linha_esparso(matriz->linhas[i], matriz->tamColuna);
        printf("\n");
    }

    //formato denso
    printf("\nformato esparso: \n");
    for(i = 0; i < matriz->tamLinha; i++){
        list_imprime_linha(matriz->linhas[i]);
        printf("\n");
    }

    /*
    printf("\ndados linhas:\n");
    for(i = 0; i < matriz->tamLinha; i++){
        list_imprime_debug_linha(matriz->linhas[i]);
        printf("\n");
    }
    printf("\ndados colunas:\n");
    for(i = 0; i < matriz->tamColuna; i++){
        list_imprime_debug_coluna(matriz->colunas[i]);
        printf("\n");
    }
    */
}

Matriz *matriz_construct(int tamLinha, int tamColuna){
    Matriz *matriz = (Matriz*)malloc(sizeof(Matriz));
    matriz->tamLinha = tamLinha;
    matriz->tamColuna = tamColuna;
    matriz->linhas = lists_construct(tamLinha);
    matriz->colunas = lists_construct(tamColuna);
    return matriz;
}

void matriz_read(Matriz *matriz){
    int ilinha = 0, icoluna = 0;
    data_type value = 0;
    for(ilinha = 0; ilinha < matriz->tamLinha; ilinha++){
        for(icoluna = 0; icoluna < matriz->tamColuna; icoluna++){
            scanf("%f", &value);
            if(value != 0){
                matriz_armazena_node(matriz->linhas[ilinha], matriz->colunas[icoluna], value, ilinha, icoluna);
            }
        }
    }
}

void matriz_armazena_node(List *linha, List *coluna, data_type value, int ilinha, int icoluna){
    Node *n = node_construct(value, ilinha, icoluna, list_get_last(linha), NULL, list_get_last(coluna), NULL);
    list_push_back_linha(linha, n);
    list_push_back_coluna(coluna, n);
}

void matriz_destruct(Matriz *matriz){
    int i = 0;
    for(i = 0; i < matriz->tamLinha; i++){
        list_destroy_linha(matriz->linhas[i]);
    }
    free(matriz->linhas);

    for(i = 0; i < matriz->tamColuna; i++){
        list_destroy_coluna(matriz->colunas[i]);
    }
    free(matriz->colunas);
    free(matriz);
}

void matriz_add_value(Matriz *matriz){
    data_type value = 0;
    int linha = 0, coluna = 0;
    printf("Digite o valor: ");
    scanf("%f", &value);
    printf("Digite a linha e a coluna: ");
    scanf("%d %d", &linha, &coluna);
    if( (linha >= matriz->tamLinha || linha < 0) || (coluna >= matriz->tamColuna || coluna < 0)){
        printf("linha ou coluda invalida!\n");
        exit(0);
    }
}



