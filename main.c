#include <stdio.h>
#include <stdlib.h>

// definir o nó da lista encadeada
typedef struct No {
    int dado;
    struct No* proximo;
} No;

//definir lista encadeada
typedef struct Lista {
    No* cabeca;
} Lista;

// criar lista
Lista* criarLista() {
    Lista* lista = (Lista*)malloc(sizeof(Lista));
    lista->cabeca = NULL;
    return lista;
}

// ver se a lista está vazia
int verificarVazia(Lista* lista) {
    return lista->cabeca == NULL;
}

// inserir em ordem crescente
void inserirListaOrdem(Lista* lista, int valor) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->dado = valor;
    novoNo->proximo = NULL;

    if (verificarVazia(lista) || lista->cabeca->dado >= valor) {
        novoNo->proximo = lista->cabeca;
        lista->cabeca = novoNo;
    } else {
        No* atual = lista->cabeca;
        while (atual->proximo != NULL && atual->proximo->dado < valor) {
            atual = atual->proximo;
        }
        novoNo->proximo = atual->proximo;
        atual->proximo = novoNo;
    }
}

// exibir elementos
void exibirLista(Lista* lista) {
    No* atual = lista->cabeca;
    while (atual != NULL) {
        printf("%d -> ", atual->dado);
        atual = atual->proximo;
    }
    printf("NULL\n");
}

// procurar elemento da lista
No* buscarLista(Lista* lista, int valor) {
    No* atual = lista->cabeca;
    while (atual != NULL) {
        if (atual->dado == valor) {
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL;
}

// excluir elemento a lista
void excluirLista(Lista* lista, int valor) {
    if (verificarVazia(lista)) {
        printf("Lista vazia. Não é possível excluir.\n");
        return;
    }

    No* atual = lista->cabeca;
    No* anterior = NULL;

    while (atual != NULL && atual->dado != valor) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Elemento %d não encontrado na lista.\n", valor);
        return;
    }

    if (anterior == NULL) {
        lista->cabeca = atual->proximo; // tira o primeiro nó
    } else {
        anterior->proximo = atual->proximo; // tira o do meio ou do fim
    }

    free(atual);
}

// libera a lista
void liberarLista(Lista* lista) {
    No* atual = lista->cabeca;
    No* proximo;

    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    free(lista);
}

// funçao pra testar as funcionalidades
int main() {
    Lista* lista = criarLista();

    inserirListaOrdem(lista, 5);
    inserirListaOrdem(lista, 3);
    inserirListaOrdem(lista, 8);
    inserirListaOrdem(lista, 1);
    inserirListaOrdem(lista, 4);

    printf("Lista após inserções em ordem crescente:\n");
    exibirLista(lista);

    printf("Buscando elemento 3:\n");
    No* resultado = buscarLista(lista, 3);
    if (resultado) {
        printf("Elemento %d encontrado.\n", resultado->dado);
    } else {
        printf("Elemento não encontrado.\n");
    }

    printf("Excluindo elemento 3:\n");
    excluirLista(lista, 3);
    exibirLista(lista);

    printf("Liberando lista...\n");
    liberarLista(lista);

    return 0;
}