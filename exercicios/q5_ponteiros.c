#include <stdio.h>
#include <stdlib.h>

typedef struct elementoLista {
    int valor;
    struct elementoLista *proximo;
}item;

void inserirFinal(item **head, int valor){
    item *novo = (item*)malloc(sizeof(item));
    novo->valor = valor;
    novo->proximo = NULL;
    if (*head == NULL || (*head)->valor >= valor){
        novo->proximo = *head;
        *head = novo;
    }
    else {
        item *atual = *head;
        while (atual->proximo !=NULL && atual->proximo->valor < valor){
            atual = atual->proximo;
        }
        novo->proximo = atual->proximo;
        atual->proximo = novo;
    }
}

void inserirIndice(item **head, int indice, int valor){
    item *novo = (item*)malloc(sizeof(item));
    novo->valor = valor;
    novo->proximo = NULL;
    if (indice == 0){
        novo->proximo = *head;
        *head = novo;
    }
    else {
        item *atual = *head;
        for (int i = 0; i < indice - 1 && atual != NULL; i++){
            atual = atual->proximo;
        }
        if (atual != NULL) {
            novo->proximo = atual->proximo;
            atual->proximo = novo;
        }
    }
}

void imprimirLista(item *head){
    item *atual = head;
    while (atual != NULL){
        printf("%d ", atual->valor);
        atual = atual->proximo;
    }
}

void liberarLista(item *head){
    item *atual = head;
    item *proximoNo;
    while (atual != NULL){
        proximoNo = atual->proximo;
        free(atual);
        atual = proximoNo;
    }
}

int main() {
    item *head = NULL;

    inserirFinal(&head, 5);
    inserirFinal(&head, 2);
    inserirFinal(&head, 8);
    inserirFinal(&head, 1);
    inserirFinal(&head, 3);

    printf("Lista ordenada: ");
    imprimirLista(head);

    printf("\n");

    inserirIndice(&head, 2, 10);
    inserirIndice(&head, 0, 15);

    printf("Lista com insercao: ");
    imprimirLista(head);

    liberarLista(head);
    return 0;
}