#include "utils.h"

//Cria um vetor de tamanho d1 e o preenche com 0.
int *vetor1d(int d1){
    return (int*)calloc(d1, sizeof(int));
}

//Cria uma matriz d1 x d2 e a preenche com 0.
int **vetor2d(int d1, int d2){
    int **v2 = malloc(d1 * sizeof(int *));

    int i;
    for(i=0; i<d1; i++){
        v2[i] = vetor1d(d2);
    }

    return v2;
}

int *sub_vetor(int *vetor, int inicio, int fim){
    int *sub = vetor1d(inicio-fim);
    int i;
    for(i=inicio; i<fim; i++){
        sub[i-inicio] = vetor[i];
    }
    return sub;
}

//Calcula a raiz de um quadrado perfeito.
int raiz_quadrado_perfeito(int quadrado_perfeito){
    int raiz;
    for(raiz=1; raiz*raiz<quadrado_perfeito; raiz++){}
    return raiz;
}
