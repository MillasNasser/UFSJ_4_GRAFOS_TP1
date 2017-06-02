#include "lista.h"

//Opera��es com N�.
//Cria um novo n� com os par�metro passados.
No *novo_No(No *anterior, void *dado, No *proximo){
    No *no = malloc(sizeof(No));

    no->anterior = anterior;
    no->dado = dado;
    no->proximo = proximo;

    return no;
}

//Opera��es com Lista.
//Cria uma nova lista vazia.
Lista *nova_Lista(size_t sizeof_dado){
    Lista *lista = malloc(sizeof (Lista));

    lista->size = sizeof_dado;
    lista->tamanho = 0;
    lista->primeiro = NULL;
    lista->ultimo = NULL;

    return lista;
}

//Verifica se a lista est� vazia.
bool lista_vazia(Lista *lista){
    return (lista->tamanho == 0);
}

//Insere um elemento ao final da lista.
void lista_insere_final(Lista *lista, void *dado){
    No *no = novo_No(lista->ultimo, dado, NULL);

    if(lista_vazia(lista)){
        lista->primeiro = no;
    }else{
        lista->ultimo->proximo = no;
    }
    lista->ultimo = no;
    lista->tamanho++;
}
