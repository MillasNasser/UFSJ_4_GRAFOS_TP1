#include "sudoku.h"

//Cria um grafo modelado como um tabuleiro de Sudoku.
Grafo *novo_Sudoku(char *str_vertices, int largura, int altura){
    int i, j, k;
    int n = strlen(str_vertices);
    int dimensao = raiz_quadrado_perfeito(n);

    Grafo *grafo = novo_Grafo(n);

    //Criando as arestas.
    int idh1, idh2;
    int idv1, idv2;

    //Horizontal e Vertical
    for(i=0; i<dimensao; i++){
        char *descricao_h = hiper_aresta_descricao("hiper aresta horizontal", i);
        lista_insere_final(grafo->hiper_arestas, descricao_h, (void*)vetor1d(grafo->n));
        int *hiper_aresta_horizontal = grafo->hiper_arestas->ultimo->dado;

        char *descricao_v = hiper_aresta_descricao("hiper aresta vertical", i);
        lista_insere_final(grafo->hiper_arestas, descricao_v, (void*)vetor1d(grafo->n));
        int *hiper_aresta_vertical = grafo->hiper_arestas->ultimo->dado;

        for(j=0; j<dimensao; j++){
            int idh = sudoku_lc_para_vertice_id(dimensao, i, j);
            hiper_aresta_horizontal[idh] = 1;

            int idv = sudoku_lc_para_vertice_id(dimensao, j, i);
            hiper_aresta_vertical[idv] = 1;
        }
        grafo_hiper_aresta_para_aresta(grafo, hiper_aresta_horizontal);
        grafo_hiper_aresta_para_aresta(grafo, hiper_aresta_vertical);
    }

    //Horizontal e Vertical
    /*for(k=0; k<dimensao-1; k++){
        for(i=0; i<dimensao; i++){
            idh1 = sudoku_lc_para_vertice_id(dimensao, i, k);
            idv1 = sudoku_lc_para_vertice_id(dimensao, k, i);
            for(j=k+1; j<dimensao; j++){
                idh2 = sudoku_lc_para_vertice_id(dimensao, i, j);
                idv2 = sudoku_lc_para_vertice_id(dimensao, j, i);

                //printf("aresta %d, %d  || ID:(%d, %d)\n", i, j, id1, id2);

                grafo_insere_aresta_nd(grafo, idh1, idh2);
                grafo_insere_aresta_nd(grafo, idv1, idv2);
            }
        }
    }*/
    //Quadrantes
    sudoku_conecta_quadrantes(grafo, largura, altura);

    //Coloração inicial.
    for(i=0; i<grafo->n; i++){
        grafo->cor[i] = str_vertices[i] - '0';
    }

    return grafo;
}

//Converte uma posição do Sudoku para o id do vértice.
int sudoku_lc_para_vertice_id(int dimensao, int linha, int coluna){
    return (dimensao * linha) + coluna;
}

//Converte o id do vértice para uma posição do Sudoku.
//Retorno: vetor de int com dimensão 2. posição 0: linha
//                                      posição 1: coluna
int *vertice_id_para_sudoku_lc(int dimensao, int id){
    return NULL;
}

//Conecta um quadrante do Sudoku.
void sudoku_conecta_quadrantes(Grafo *grafo, int largura, int altura){
    int i, j, k;

    int id;

    int dimensao = raiz_quadrado_perfeito(grafo->n);
    int quadrantes = grafo->n / (largura * altura);
    int quadrantes_horizontal = dimensao / largura;
    int quadrantes_vertical = dimensao / altura;

    for(k=0; k<quadrantes; k++){
        char *descricao = hiper_aresta_descricao("hiper aresta quadrante", k);
        lista_insere_final(grafo->hiper_arestas, descricao, (void*)vetor1d(grafo->n));
        int *hiper_aresta = grafo->hiper_arestas->ultimo->dado;

        //printf("Quadrante %d\n", k);

        int i_inicio = (k / quadrantes_horizontal) * altura;
        int i_final = i_inicio + altura;

        for(i=i_inicio; i<i_final; i++){
            //printf("  linha %d\n", i);

            int j_inicio = (k % quadrantes_horizontal) * largura;
            int j_final = j_inicio + largura;
            for(j=j_inicio; j<j_final; j++){
                //printf("    coluna %d ## id: %d\n", j, sudoku_lc_para_vertice_id(dimensao, i, j));

                id = sudoku_lc_para_vertice_id(dimensao, i, j);
                hiper_aresta[id] = 1;
            }
        }
        /*for(i=0; i<grafo->n; i++){
            printf("%2d: %2d\n", i, hiper_aresta[i]);
        }*/
    }
    No *temp;
    for(temp = grafo->hiper_arestas->primeiro; temp != NULL; temp = temp->proximo){
        grafo_hiper_aresta_para_aresta(grafo, (int*)temp->dado);
    }
}

//Descrição de uma hiper-aresta do sudoku.
char *hiper_aresta_descricao(char *descricao, int numero){
    char *descricao_format = malloc(strlen(descricao) + 10);

    sprintf(descricao_format, "%s %d", descricao, numero);

    return descricao_format;
}

//Retorna o id dos vértices que pertecem ao quadrante.
int *sudoku_ids_quadrante(int altura, int largura, int x, int y){
    int *ids = vetor1d(altura * largura);

    int i, j, k = 0;
    int i_inicio = y * altura;
    int i_final = i_inicio + altura;
    int j_inicio = x * largura;
    int j_final = j_inicio + largura;
    for(i=i_inicio; i<i_final; i++){
        for(j=j_inicio; j<j_final; j++){
            ids[k++] = sudoku_lc_para_vertice_id(altura * largura, i, j);
            //printf("%d\n", ids[k-1]);
        }
    }
    return ids;
}
