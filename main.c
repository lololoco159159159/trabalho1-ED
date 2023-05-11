#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

int main (){
    int tamLinha = 0, tamColuna = 0;

    scanf("%d %d", &tamLinha, &tamColuna);
    Matriz *matriz = matriz_construct(tamLinha, tamColuna);
    matriz_read(matriz);
    
    scanf("%d %d", &tamLinha, &tamColuna);
    Matriz *matriz2 = matriz_construct(tamLinha, tamColuna);
    matriz_read(matriz2);

    //armazena em bin    
    FILE *bin = fopen("binario.bin", "wb");
    if (bin == NULL){
        printf("Erro! o documento binario nao foi inicializado com sucesso!\n");
        exit(0);
    }

    matriz_armazena_bin(matriz, bin);
    matriz_armazena_bin(matriz2, bin);
    fclose(bin);
    
    matriz_destruct(matriz);
    return 0;
}

