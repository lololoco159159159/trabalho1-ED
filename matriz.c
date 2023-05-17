#include <stdio.h> 
#include <stdlib.h>
#include "matriz.h"


void matriz_imprime(Matriz *matriz){
    //int i = 0;
    matriz_imprime_denso(matriz);
    matriz_imprime_esparso(matriz);
    printf("-------------------------------\n");
    //debug linha
    /*
    printf("\ndados linhas:\n");
    for(i = 0; i < matriz->tamLinha; i++){
        list_imprime_debug_linha(matriz->linhas[i]);
        printf("  tam: %d", list_size(matriz->linhas[i]));
        printf("\n");
    }
    
    //debug coluna
    printf("\ndados colunas:\n");
    for(i = 0; i < matriz->tamColuna; i++){
        list_imprime_debug_coluna(matriz->colunas[i]);
        printf("  tam: %d", list_size(matriz->colunas[i]));
        printf("\n");
    }*/
    
}

void matriz_imprime_denso(Matriz *matriz){
    printf("%d %d\n", matriz->tamLinha, matriz->tamColuna);
    printf("formato denso:\n");
    for(int i = 0; i < matriz->tamLinha; i++){       
        list_imprime_linha_denso(matriz->linhas[i], matriz->tamColuna);
        printf("\n");
    }
        
}

void matriz_imprime_esparso(Matriz *matriz){
    printf("\nformato esparso: \n");
    for(int i = 0; i < matriz->tamLinha; i++){
        list_imprime_linha_esparso(matriz->linhas[i]);
        printf("\n");
    }
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

void matriz_insere_value(Matriz *matriz, int linha, int coluna, data_type value){//complexidade: O(n) + O(m)
    if (linha < 0 || linha >= matriz->tamLinha || coluna < 0 || coluna >= matriz->tamColuna){
        printf("linha ou coluna invalida!\n");
        return;
    }

    Node *aux = node_verifica_existe(matriz->linhas[linha], coluna); //complexidade: O(n)
    if(aux != NULL){
        if(value != 0){
            aux->value = value;
        }
        else if(value == 0){
            list_remove_linha(matriz->linhas[linha], linha, coluna);//complexidade: O(n)
            list_remove_coluna(matriz->colunas[coluna], linha, coluna);//complexidade: O(m)
        }
    }
    else{
        if(value != 0){
            aux = node_new_construct(matriz->linhas[linha], matriz->colunas[coluna], linha, coluna, value);//complexidade: O(1)

            Node *lastLinha = matriz->linhas[linha]->last;
            Node *lastColuna = matriz->colunas[coluna]->last;

            list_push_back_linha(matriz->linhas[linha], aux);//complexidade: O(1)
            list_push_back_coluna(matriz->colunas[coluna], aux);//complexidade: O(1)

            list_ajeita_entrada_node_linha(matriz->linhas[linha], aux, lastLinha);//complexidade: O(1)
            list_ajeita_entrada_node_coluna(matriz->colunas[coluna], aux, lastColuna);//complexidade: O(1)
        }
    }
    list_ajeita_last_linha(matriz->linhas[linha]);//complexidade: O(n)
    list_ajeita_last_coluna(matriz->colunas[coluna]);//complexidade: O(m)
}

Matriz *matriz_add(Matriz *m1, Matriz *m2){
    Matriz *m3 = matriz_construct(m1->tamLinha, m1->tamColuna);
    int ilinha = 0;
    Node *aux = NULL;
    Node *node_verifica = NULL;

    for(ilinha = 0; ilinha < m1->tamLinha; ilinha++){//complexidade: O(n)
        //matriz1
        aux = m1->linhas[ilinha]->head;
        while(aux != NULL){//complexidade: O(m1)
            matriz_insere_value(m3, aux->linha, aux->coluna, aux->value);////complexidade: O(n) + O(m)
            aux = aux->linhaNext;
        }
        //matriz2
        aux = m2->linhas[ilinha]->head;
        while(aux != NULL){//complexidade: O(m2)
            node_verifica = node_verifica_existe(m3->linhas[ilinha], aux->coluna);//complexidade: O(n)
            if(node_verifica == NULL){
                matriz_insere_value(m3, aux->linha, aux->coluna, aux->value);//complexidade: O(n) + O(m2)
            }
            else{
                matriz_insere_value(m3, aux->linha, aux->coluna, aux->value + (node_verifica->value));//complexidade: O(n) + O(m2)
            }
            aux = aux->linhaNext;
        }
    }
    return m3;
}

Matriz *matriz_multiplica_ponto_a_ponto(Matriz *m1, Matriz *m2){
    Matriz *m3 = matriz_construct(m1->tamLinha, m1->tamColuna);
    int ilinha= 0, acabou = 0;
    Node *aux1 = NULL, *aux2 = NULL;

    for(ilinha = 0; ilinha < m1->tamLinha; ilinha++){
        //matriz 1
        aux1 = m1->linhas[ilinha]->head;
        aux2 = m2->linhas[ilinha]->head;
        if(aux2 == NULL || aux1 == NULL){
            continue;
        }
        while(aux1 != NULL){
            while(aux2->coluna < aux1->coluna){
                aux2 = aux2->linhaNext;
                if(aux2 == NULL){
                    acabou = 1;
                    break;
                }
            }
            if(acabou){
                break;
            }
            if(aux1->coluna == aux2->coluna){
                matriz_insere_value(m3, ilinha, aux1->coluna, (aux1->value * aux2->value));
            }
            aux1 = aux1->linhaNext;
        }
        acabou = 0;
    }
    return m3;
}

data_type matriz_value_linha_coluna(Matriz *m, int linha, int coluna){
    Node *aux = NULL;
    aux = m->linhas[linha]->head;
    
    while(aux != NULL){
        if(aux->coluna == coluna){
            return aux->value;
        }
        aux = aux->linhaNext;
    }
    return 0.0;
}

void matriz_multiplica_escalar(Matriz *m, int escalar){
    int i = 0;
    Node *aux = NULL;
    data_type value = 0;
    for(i = 0; i < m->tamLinha; i++){
        aux = m->linhas[i]->head;
        while(aux != NULL){
            value = aux->value;
            matriz_insere_value(m, i, aux->coluna, (value*escalar));//comp: O(n) + O(m)
            aux = aux->linhaNext;
        }
    }
}

Matriz *matriz_multiplica_matriz(Matriz *m1, Matriz *m2){
    Matriz *m3 = matriz_construct(m1->tamLinha, m2->tamColuna);
    int ilinha = 0, icoluna = 0, acabou = 0;    
    Node *linhaAux = NULL, *colunaAux = NULL;
    data_type value = 0;
    for(ilinha = 0; ilinha < m1->tamLinha; ilinha++){
        for(icoluna = 0; icoluna < m2->tamColuna; icoluna++){
            linhaAux = m1->linhas[ilinha]->head;
            colunaAux = m2->colunas[icoluna]->head;
            if(colunaAux == NULL){
                continue;
            }
            while(linhaAux != NULL){
                while(colunaAux->linha < linhaAux->coluna){
                    colunaAux = colunaAux->colunaNext;
                    if(colunaAux == NULL){
                        acabou = 1;
                        break;
                    }
                }

                if(acabou){
                   break;
                }    
                if(colunaAux->linha == linhaAux->coluna){
                    value += colunaAux->value * linhaAux->value;
                    colunaAux = colunaAux->colunaNext;
                    if(colunaAux == NULL){
                        acabou = 1;
                        break;
                    }
                }
                linhaAux = linhaAux->linhaNext;
                if(acabou){
                   break;
                }
            }
            //printf("l: %d c:%d value: %.0f\n", ilinha, icoluna, value);
            matriz_insere_value(m3, ilinha, icoluna, value);
            value = 0;
            acabou = 0;
        }
    }
    return m3;
}

void matriz_swap_linha(Matriz *m, int l1, int l2){
    Node *node1 = NULL;
    Node *node2 = NULL;

    for(int i = 0; i < m->tamColuna; i++){
        node1 = node_verifica_existe(m->linhas[l1], i);
        node2 = node_verifica_existe(m->linhas[l2], i);
        if(node1 != NULL || node2 != NULL){
            node_swap_linha(m, node1, node2, l1, l2);
        }
    }
}

void matriz_swap_coluna(Matriz *m, int c1, int c2){
    Node *node1 = NULL;
    Node *node2 = NULL;
    for(int i = 0; i < m->tamLinha; i++){
        node1 = node_verifica_existe_via_coluna(m->colunas[c1], i);
        node2 = node_verifica_existe_via_coluna(m->colunas[c2], i);
        if(node1 != NULL || node2 != NULL){
            node_swap_coluna(m, node1, node2, c1, c2);//n + m
        }
    }


}

void node_swap_linha(Matriz *m, Node *node1, Node *node2, int l1, int l2){
    data_type value = 0;

    if(node1 == NULL){
        printf("a troquei %.0f %.0f\n", node2->value , 0.0);
        matriz_insere_value(m, l1, node2->coluna, node2->value);
        matriz_insere_value(m, l2, node2->coluna, 0.0);
        
    }
    else if(node2 == NULL){
        printf("b troquei %.0f %.0f\n", node1->value , 0.0);
        matriz_insere_value(m, l2, node1->coluna, node1->value);
        matriz_insere_value(m, l1, node1->coluna, 0.0);
        
    }
    else{
        printf("c troquei %.0f %.0f\n", node1->value , node2->value);
        value = node1->value;
        node1->value = node2->value;
        node2->value = value;
    }
}

void node_swap_coluna(Matriz *m, Node *node1, Node *node2, int c1, int c2){
    data_type value = 0;
    if(node1 == NULL){
        printf("a troquei %.0f %.0f\n", node2->value , 0.0);
        matriz_insere_value(m, node2->linha, c1, node2->value);
        matriz_insere_value(m, node2->linha, c2, 0.0);
        
    }
    else if(node2 == NULL){
        printf("b troquei %.0f %.0f\n", node1->value , 0.0);
        matriz_insere_value(m, node1->linha, c2, node1->value);
        matriz_insere_value(m, node1->linha, c1, 0.0);
    }
    else{
        printf("c troquei %.0f %.0f\n", node1->value, node2->value);
        value = node1->value;
        node1->value = node2->value;
        node2->value = value;
    }
}

Matriz *matriz_transposta(Matriz *m){
    Matriz *trans = matriz_construct(m->tamColuna, m->tamLinha);
    Node *aux = NULL;
    for(int i = 0; i < m->tamLinha; i++){
        aux = m->linhas[i]->head;
        while(aux != NULL){
            matriz_insere_value(trans, aux->coluna, i, aux->value);
            aux = aux->linhaNext;
        }
    }
    return trans;
}

Matriz *matriz_slice(Matriz *m, int l, int c, int l2, int c2){ 
    int tamLinha = 0, tamColuna = 0, i = 0, acabou = 0, colunaInicial = c;
    tamLinha = (l2-l)+1;
    tamColuna = (c2-c)+1;
    Matriz *slice = matriz_construct(tamLinha, tamColuna);
    Node *aux = NULL;

    for(i = 0; l <= l2; i++, l++){
        aux = m->linhas[l]->head;
        if(aux == NULL)
            continue;
        while(aux != NULL){
            while(aux->coluna < c){
                aux = aux->linhaNext;
                if(aux == NULL){
                    acabou = 1;
                    break;
                }
            }
            if(acabou){
                break;
            }
            if(aux->coluna == c){
                matriz_insere_value(slice, i, (aux->coluna - colunaInicial), aux->value);
                aux = aux->linhaNext;
            }
            if(aux == NULL){
                break;
            }
            while(c < aux->coluna){
                c++;
                if(c > c2){
                    acabou = 1;
                    break;
                }
            }
            if(acabou){
                break;
            }
        }
        acabou = 0;
        c = colunaInicial;
    }

    return slice;
}

Matriz *matriz_convulacao(Matriz *m1, Matriz *kernel){
    Matriz *m3 = matriz_construct(m1->tamLinha, m1->tamColuna);
    data_type value = 0;
    int ilinha = 0, icoluna = 0;

    for(ilinha = 0; ilinha < m1->tamLinha; ilinha++){
        for(icoluna = 0; icoluna < m1->tamColuna; icoluna++){
            value = calcula_value_convulacao(m1, kernel, ilinha, icoluna);
            if (value != 0)
                matriz_insere_value(m3, ilinha, icoluna, value);
        }
    }
    return m3;
}

data_type calcula_value_convulacao(Matriz *m1, Matriz *kernel, int linhaCentral, int colunaCentral){
    data_type value = 0;
    int Mlinha1 = 0, Mcoluna1 = 0, Mlinha2 = 0, Mcoluna2 = 0; //coordenadas para o slice
    int Klinha1 = 0, Kcoluna1 = 0, Klinha2 = 0, Kcoluna2 = 0;
    int vazouLinha1 = 0, vazouColuna1 = 0, vazouLinha2 = 0, vazouColuna2 = 0;
    int constantLin = 0, constantCol;

    constantLin = (kernel->tamLinha/2);
    constantCol = (kernel->tamColuna/2);
    Mlinha1 = linhaCentral - constantLin;
    Mcoluna1 = colunaCentral - constantCol;
    Mlinha2 = linhaCentral + constantLin;
    Mcoluna2 = colunaCentral + constantCol;

    if(Mlinha1 < 0){
        vazouLinha1 = 0 - Mlinha1;
        Mlinha1 = 0;
    }
    if(Mcoluna1 < 0){
        vazouColuna1 = 0 - Mcoluna1;
        Mcoluna1 = 0;
    }
    if(Mlinha2 >= m1->tamLinha){
        vazouLinha2 = Mlinha2 - m1->tamLinha+1;
        Mlinha2 = m1->tamLinha-1;
    }
    if(Mcoluna2 >= m1->tamColuna){
        vazouColuna2 = Mcoluna2 - m1->tamColuna+1;
        Mcoluna2 = m1->tamColuna-1;
    }
    Klinha1 =  vazouLinha1;
    Kcoluna1 =  vazouColuna1;
    Klinha2 =  2*constantLin - vazouLinha2;
    Kcoluna2 = 2*constantCol - vazouColuna2;
    
    Matriz *m1Aux = matriz_slice(m1, Mlinha1, Mcoluna1, Mlinha2, Mcoluna2);
    Matriz *kernelAux = matriz_slice(kernel, Klinha1, Kcoluna1, Klinha2, Kcoluna2);
    Matriz *multiplicada = matriz_multiplica_ponto_a_ponto(m1Aux, kernelAux);
    value = matriz_soma_dos_termos(multiplicada);
    matriz_destruct(m1Aux);
    matriz_destruct(kernelAux);
    matriz_destruct(multiplicada);
    return value;
}

data_type matriz_soma_dos_termos(Matriz *m){
    data_type value = 0;
    Node *aux = NULL;
    for(int i = 0; i < m->tamLinha; i++){
        aux = m->linhas[i]->head;
        while(aux != NULL){
            value += aux->value;
            aux = aux->linhaNext;
        }
    }
    return value;
}

