#include <stdio.h> 
#include <stdlib.h>
#include "matriz.h"


void matriz_imprime_debug(Matriz *matriz){
    int i = 0;
    
    printf("formato denso:\n");
    for(i = 0; i < matriz->tamLinha; i++){
        list_imprime_linha_esparso(matriz->linhas[i], matriz->tamColuna);
        printf("\n");
    }

    /*
    printf("\nformato esparso: \n");
    for(i = 0; i < matriz->tamLinha; i++){
        list_imprime_linha(matriz->linhas[i]);
        printf("\n");
    }*/
    
    printf("\ndados linhas:\n");
    for(i = 0; i < matriz->tamLinha; i++){
        list_imprime_debug_linha(matriz->linhas[i]);
        printf("  tam: %d", list_size(matriz->linhas[i]));
        printf("\n");
    }
    
    /*
    printf("\ndados colunas:\n");
    for(i = 0; i < matriz->tamColuna; i++){
        list_imprime_debug_coluna(matriz->colunas[i]);
        printf("  tam: %d", list_size(matriz->colunas[i]));
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

void matriz_armazena_bin(Matriz *matriz, FILE *bin){
    fwrite(&(matriz->tamLinha), sizeof(int), 1, bin);
    printf("%d ", matriz->tamLinha);

    fwrite(&(matriz->tamColuna), sizeof(int), 1, bin);
    printf("%d", matriz->tamColuna);
    printf("\n");
    for(int i = 0; i < matriz->tamLinha; i++){
        list_imprime_bin(matriz->linhas[i], matriz->tamColuna, bin);
    }
}

Matriz *matriz_le_bin(FILE *bin){
    Matriz *matriz = NULL;
    int tamLinha = 0, tamColuna = 0, size = 0;
    int i = 0, j = 0, linha = 0, coluna = 0;
    data_type value = 0;

    fread(&tamLinha, sizeof(int), 1, bin);
    fread(&tamColuna, sizeof(int), 1, bin);
    matriz = matriz_construct(tamLinha, tamColuna);
    
    for(i = 0; i < tamLinha; i++){
        fread(&size, sizeof(int), 1, bin);
        for(j = 0; j < size; j++){
            fread(&linha, sizeof(int), 1, bin);
            fread(&coluna, sizeof(int), 1, bin);
            fread(&value, sizeof(data_type), 1, bin);
            matriz_insere_value(matriz, linha, coluna, value);
        }
    }
    return matriz;
}

void matriz_insere_value(Matriz *matriz, int linha, int coluna, data_type value){
    if (linha < 0 || linha >= matriz->tamLinha || coluna < 0 || coluna >= matriz->tamColuna){
        printf("linha ou coluna invalida!\n");
        return;
    }

    Node *aux = node_verifica_existe(matriz->linhas[linha], coluna);
    if(aux != NULL){
        if(value != 0){
            aux->value = value;
        }
        else if(value == 0){
            list_remove_linha(matriz->linhas[linha], linha, coluna);
            list_remove_coluna(matriz->colunas[coluna], linha, coluna);
        }
    }
    else{
        if(value != 0){
            aux = node_new_construct(matriz->linhas[linha], matriz->colunas[coluna], linha, coluna, value);

            Node *lastLinha = matriz->linhas[linha]->last;
            Node *lastColuna = matriz->colunas[coluna]->last;

            list_push_back_linha(matriz->linhas[linha], aux);
            list_push_back_coluna(matriz->colunas[coluna], aux);

            list_ajeita_entrada_node_linha(matriz->linhas[linha], aux, lastLinha);
            list_ajeita_entrada_node_coluna(matriz->colunas[coluna], aux, lastColuna);
        }
    }
}

