#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

void print_float(data_type x){
    printf("%f", x);
}


int main (){
    int tamLinha = 0, tamColuna = 0;
    scanf("%d %d", &tamLinha, &tamColuna);

    Matriz *matriz = matriz_construct(tamLinha, tamColuna);
    matriz_read(matriz);
    //matriz_imprime_debug(matriz);

    //armazena em bin    
    FILE *bin = fopen("binario.bin", "wb");
    if (bin == NULL){
        printf("Erro! o documento binario nao foi inicializado com sucesso!\n");
        exit(0);
    }

    matriz_armazena_bin(matriz, bin);
    fclose(bin);
    
    matriz_destruct(matriz);
    return 0;
}

