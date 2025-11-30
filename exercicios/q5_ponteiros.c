#include <stdio.h>
#include <stdlib.h>

typedef struct listaEncadeadaOrdenada {
    int valor;
    struct listaEncadeadaOrdenada *proximo;
} Lista;

void inserirOrdenado(Lista **cabeca, int valor) {
    Lista *node = (Lista *)malloc(sizeof(Lista));
    node->valor = valor;
    node->proximo = NULL;

    if (*cabeca == NULL || (*cabeca)->valor >= valor) {
        node->proximo = *cabeca;
        *cabeca = node;
    } else {
        Lista *atual = *cabeca;
        while (atual->proximo != NULL && atual->proximo->valor < valor) {
            atual = atual->proximo;
        }
        node->proximo = atual->proximo;
        atual->proximo = node;
    }
}

void imprimirLista(Lista *cabeca) {
    Lista *atual = cabeca;
    while (atual != NULL) {
        printf("%d ", atual->valor);
        atual = atual->proximo;
    }
    printf("\n");
}

void liberarLista(Lista *cabeca) {
    Lista *atual = cabeca;
    Lista *proximoNo;
    while (atual != NULL) {
        proximoNo = atual->proximo;
        free(atual);
        atual = proximoNo;
    }
}

int main() {
    Lista *minhaLista = NULL;
    int n, valor;

    printf("Quantos numeros deseja inserir na lista ordenada? ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Digite o numero %d: ", i + 1);
        scanf("%d", &valor);
        inserirOrdenado(&minhaLista, valor);
    }

    printf("Lista ordenada: ");
    imprimirLista(minhaLista);

    liberarLista(minhaLista);
    return 0;
}