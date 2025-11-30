#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *dados;
    int topo;
    int capacidade;
} pilhaDinamica;

void inicializarPilha(pilhaDinamica *pilha, int capacidade) {
    pilha->dados = (int *)malloc(capacidade * sizeof(int));
    pilha->topo = -1;
    pilha->capacidade = capacidade;
}

int estaVazia(pilhaDinamica *pilha) {
    return pilha->topo == -1;
}

int estaCheia(pilhaDinamica *pilha) {
    return pilha->topo == pilha->capacidade - 1;
}

void empilhar(pilhaDinamica *pilha, int valor) {
    if (!estaCheia(pilha)) {
        pilha->dados[++(pilha->topo)] = valor;
    } else {
        printf("Pilha cheia!\n");
    }
}

int desempilhar(pilhaDinamica *pilha) {
    if (!estaVazia(pilha)) {
        return pilha->dados[(pilha->topo)--];
    } else {
        printf("Pilha vazia!\n");
        return -1;
    }
}

void liberarPilha(pilhaDinamica *pilha) {
    free(pilha->dados);
    pilha->topo = -1;
    pilha->capacidade = 0;
}

int main() {
    pilhaDinamica minhaPilha;
    int capacidade;
    int valor;

    printf("Digite a capacidade da pilha: ");
    scanf("%d", &capacidade);

    inicializarPilha(&minhaPilha, capacidade);

    for (int i = 0; i < capacidade; i++) {
        printf("Digite um valor para empilhar: ");
        scanf("%d", &valor);
        empilhar(&minhaPilha, valor);
    }
    

    for (int i = 0; i < capacidade; i++) {
        valor = desempilhar(&minhaPilha);
        if (valor != -1) {
            printf("Desempilhado: %d\n", valor);
        }
    }

    liberarPilha(&minhaPilha);

    return 0;
}