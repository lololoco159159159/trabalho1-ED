#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

int ConfereOperacaoValida(Matriz *m1, Matriz *m2, char comando);
void imprime_interface();
void executaOpcao(Matriz *m1, Matriz *m2, Matriz *m3);
int ConfereOperacaoSwapValida(Matriz *m, int x1, int x2, char comando);
int ConfereSliceValido(Matriz *m, int l, int c, int l2, int c2);
void ImprimeMatrizes(Matriz *m1, Matriz *m2, Matriz *m3, int crioum3);
void BuscaValor(Matriz *m1);
void MultiplicaMatrizPorEscalar(Matriz *m1);
int ConfereSliceValido(Matriz *m, int l, int c, int l2, int c2);
int ConfereConvulacaoValida(Matriz *m1, Matriz *m2);

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
    int opcao = 0, operacaoValida = 0, crioum3 = 0, linha = 0, coluna = 0;
    int linha2 = 0, coluna2 = 0;

    do{
        imprime_interface();
        scanf("%d", &opcao);

        switch (opcao){
            case 1: //imprime as matrizes
                ImprimeMatrizes(m1, m2, m3, crioum3);
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
                    matriz_imprime(m3);
                    printf("\n");
                }
                else{
                    printf("operacao invalida! tamanhos incompativeis");
                } 
                break;
            case 3:// buscar valor linha/coluna
                BuscaValor(m1);
                break;
            case 4:// multiplicar matriz por escalar
                MultiplicaMatrizPorEscalar(m1);
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
            case 6:// multiplica ponto x ponto
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
            case 7:// swap linha
                printf("digite quais linhas deseja trocar (matriz 1):\n-> ");
                scanf("%d %d", &linha, &linha2);
                operacaoValida = ConfereOperacaoSwapValida(m1, linha, linha2, 'l');
                if(operacaoValida){
                    matriz_swap_linha(m1, linha, linha2);
                }
                else{
                    printf("operacao invalida! tamanhos incompativeis ou mesma linha");
                }
                break;
            case 8:// swap coluna
                printf("digite quais colunas deseja trocar (matriz 1):\n-> ");
                scanf("%d %d", &coluna, &coluna2);
                operacaoValida = ConfereOperacaoSwapValida(m1, coluna, coluna2, 'c');
                if(operacaoValida){
                    matriz_swap_coluna(m1, coluna, coluna2);
                }
                else{
                    printf("operacao invalida! tamanhos incompativeis ou mesma coluna");
                }
                break;
            case 9://transpor matriz
                printf("obs.: sera feita a transposta da matriz 1\n");
                if (m3 != NULL){
                    matriz_destruct(m3);
                }
                m3 = matriz_transposta(m1);
                crioum3 = 1;
                break;
            case 10://slice 
                printf("digite as coordenadas do inicio e do fim da submatriz\n");
                printf("(esquerdo superior e direto inferior respectivamente)\n(sera feito uma submatriz da matriz 1)\n-> ");
                scanf("%d %d", &linha, &coluna);
                scanf("%d %d", &linha2, &coluna2);
                operacaoValida = ConfereSliceValido(m1, linha, coluna, linha2, coluna2);
                if(operacaoValida){
                    if (m3 != NULL){
                        matriz_destruct(m3);
                    }
                    m3 = matriz_slice(m1, linha, coluna, linha2, coluna2);
                    crioum3 = 1;
                }
                else{
                    printf("valores invalidos");
                }
                break;
            case 11://convulacao
                printf("sera usada a matriz 1 como base e a matriz 2 como kernel, verifique o input caso necessario\n(o resultado saira em matriz 3)\n");
                operacaoValida = ConfereConvulacaoValida(m1, m2);
                if(operacaoValida){
                    if (m3 != NULL){
                        matriz_destruct(m3);
                    }
                    m3 = matriz_convulacao(m1, m2);
                    crioum3 = 1;
                }
                else{
                    printf("matriz de kenel invalida, matriz nao quadratica ou matriz nao impar\n");
                }
                break;
            default:
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
    printf("[6] multiplicacao PONTO a PONTO entre matrizes\n");
    printf("[7] swap das linhas\n");
    printf("[8] swap das colunas\n");
    printf("[9] transpor matriz\n");
    printf("[10] slice\n");
    printf("[11] convulacao (a matriz 2 será usada como kernel, verifique o input caso queira testar)\n");
    printf("-> ");
}

int ConfereSliceValido(Matriz *m, int l, int c, int l2, int c2){
    if((l >= 0 && l < m->tamLinha) && (c >= 0 && c < m->tamColuna) && (l2 >= 0 && l2 < m->tamLinha) && (c2 >= 0 && c2 < m->tamColuna)){
        if(l2 >= l && c2 >= c)
            return 1;
    }
    return 0;
}

void BuscaValor(Matriz *m1){
    data_type value = 0;
    int linha = 0, coluna = 0;
    printf("digite qual linha e coluna deseja buscar (matriz 1): ");
    scanf("%d %d", &linha, &coluna);
    value = matriz_value_linha_coluna(m1, linha, coluna);
    printf("valor: %.0f\n", value);
}

void MultiplicaMatrizPorEscalar(Matriz *m1){
    int aux = 0;
    printf("digite por qual valor deseja multiplicar a matriz (matriz 1): ");
    scanf("%d", &aux);
    matriz_multiplica_escalar(m1, aux);
    printf("\n");
}

void ImprimeMatrizes(Matriz *m1, Matriz *m2, Matriz *m3, int crioum3){
    printf("matriz1:\n");
    matriz_imprime(m1);
    printf("\n");
    printf("matriz2:\n");
    matriz_imprime(m2);
    printf("\n");
    if(crioum3){
        printf("matriz3:\n");
        matriz_imprime(m3);
        printf("\n");
    }
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

int ConfereOperacaoSwapValida(Matriz *m, int x1, int x2, char comando){
    if (comando == 'l' || comando == 'L'){
        if((x1 >= 0 && x1 < m->tamLinha) && (x2 >= 0 && x2 < m->tamLinha) && (x1 != x2))
            return 1;
        else
            return 0;
    }
    if (comando == 'c' || comando == 'C'){
        if((x1 >= 0 && x1 < m->tamColuna) && (x2 >= 0 && x2 < m->tamColuna) && (x1 != x2))
            return 1;
        else
            return 0;
    }
    return 0;
}

int ConfereConvulacaoValida(Matriz *m1, Matriz *m2){
    if((m2->tamColuna == m2->tamLinha) && (m2->tamLinha % 2 == 1))
        return 1;
    return 0;
}

