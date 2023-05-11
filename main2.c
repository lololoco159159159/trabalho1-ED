#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

int ConfereOperacaoValida(Matriz *m1, Matriz *m2, char comando);
void imprime_interface();
void executaOpcao(Matriz *m1, Matriz *m2, Matriz *m3);

int main (){
    FILE *bin = fopen("binario.bin", "rb");
    if (bin == NULL){
        printf("binario.bin inexistente, rode a main antes!\n");
        exit(0);
    }
    Matriz *matriz = matriz_le_bin(bin);
    Matriz *matriz2 = matriz_le_bin(bin);
    Matriz *matriz3 = NULL;
    fclose(bin);

    executaOpcao(matriz, matriz2, matriz3);
    return 0;
}


void executaOpcao(Matriz *m1, Matriz *m2, Matriz *m3){
    int opcao = 0, operacaoValida = 0, crioum3 = 0, linha = 0, coluna = 0, aux = 0;
    data_type value = 0;
    do{
        imprime_interface();
        scanf("%d", &opcao);

        switch (opcao){
            case 1: //imprime as matrizes
                printf("matriz1:\n");
                matriz_imprime_debug(m1);
                printf("\n");
                printf("matriz2:\n");
                matriz_imprime_debug(m2);
                printf("\n");
                if(crioum3){
                    printf("matriz3:\n");
                    matriz_imprime_debug(m3);
                    printf("\n");
                }
                break;
            case 2:// soma entre matrizes
                operacaoValida = ConfereOperacaoValida(m1, m2, 's');
                if(operacaoValida){
                    crioum3 = 1;
                    if(m3 != NULL){
                        matriz_destruct(m3);
                    }
                    m3 = matriz_add(m1, m2);
                    printf("matriz3 criada:\n");
                    matriz_imprime_debug(m3);
                    printf("\n");
                }
                else{
                    printf("operacao invalida! tamanhos incompativeis");
                } 
                break;
            case 3:// buscar valor linha/coluna
                printf("digite qual linha e coluna deseja buscar (matriz 1): ");
                scanf("%d %d", &linha, &coluna);
                value = matriz_value_linha_coluna(m1, linha, coluna);
                printf("valor: %.0f\n", value);
                break;
            case 4:// multiplicar matriz por escalar
                printf("digite por qual valor deseja multiplicar a matriz (matriz 1): ");
                scanf("%d", &aux);
                matriz_multiplica_escalar(m1, aux);
                printf("\n");
                break;
            case 5:// produto entre matrizes
                printf("obs.: matriz 1 x matriz 2 = matriz 3 \n");
                operacaoValida = ConfereOperacaoValida(m1, m2, 'm');
                if(operacaoValida){
                    if(m3 != NULL){
                        matriz_destruct(m3);
                    }
                    m3 = matriz_multiplica_matriz(m1, m2);
                    crioum3 = 1;
                }
                else{
                    printf("operacao invalida! tamanhos incompativeis");
                }
                break;
            case 6:
                printf("obs.: matriz 1 x matriz 2 = matriz 3 \n");
                operacaoValida = ConfereOperacaoValida(m1, m2, 'p');
                if(operacaoValida){
                    if(m3 != NULL){
                        matriz_destruct(m3);
                    }
                    m3 = matriz_multiplica_ponto_a_ponto(m1, m2);
                    crioum3 = 1;
                }
                else{
                    printf("operacao invalida! tamanhos incompativeis");
                }
                break;
        }
    }while(opcao != 0);
    matriz_destruct(m1);
    matriz_destruct(m2);
    if(crioum3){
        matriz_destruct(m3);
    }
}

void imprime_interface(){
    printf("\n---------------------\n");
    printf("[0] sair\n");
    printf("[1] imprime matriz debug\n");
    printf("[2] somar duas matrizes\n");
    printf("[3] valor na linha/coluna\n");
    printf("[4] multiplicar matriz por escalar\n");
    printf("[5] multiplicar MATRIZ x MATRIZ\n");
    printf("[6] multiplicacao PONTO a PONTO entre matrizes");
    printf("-> ");
}


int ConfereOperacaoValida(Matriz *m1, Matriz *m2, char comando){
    if(comando == 's' || comando == 'S'){
        if((m1->tamLinha == m2->tamLinha) && (m1->tamColuna == m2->tamColuna))
            return 1;
        else
            return 0;
    }
    if(comando == 'm' || comando == 'M'){
        if (m1->tamColuna == m2->tamLinha)
            return 1;
        else
            return 0;
    }
    if(comando == 'p' || comando == 'P'){
        if((m1->tamLinha == m2->tamLinha) && (m1->tamColuna == m2->tamColuna))
            return 1;
        else
            return 0;
    }
    return 0;
}

