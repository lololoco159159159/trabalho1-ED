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
    matriz_add_value(matriz);

    matriz_imprime_debug(matriz);
    matriz_destruct(matriz);
    return 0;
}

