#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

int main (){
    FILE *bin = fopen("binario.bin", "rb");
    if (bin == NULL){
        printf("binario.bin inexistente, rode a main antes!\n");
        exit(0);
    }
    Matriz *matriz = matriz_le_bin(bin);
    fclose(bin);
    matriz_imprime_debug(matriz);

    matriz_insere_value(matriz, 0, 0, 5);
    matriz_insere_value(matriz, 0, 1, 5);
    matriz_insere_value(matriz, 0, 2, 5);
    matriz_insere_value(matriz, 1, 10, 0);
    matriz_insere_value(matriz, 3, 4, 0);
    matriz_insere_value(matriz, 2, 7, 5);


    matriz_imprime_debug(matriz);
    matriz_destruct(matriz);
    return 0;
}