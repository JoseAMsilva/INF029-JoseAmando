#include <stdio.h>
#include <stdlib.h>

typedef struct listaDuplamenteEncadeada {
    int valor;
    struct listaDuplamenteEncadeada *proximo;
    struct listaDuplamenteEncadeada *anterior;
} item;

void inserirOrdenado(item **head, int valor){
    item*novo = (item*)malloc(sizeof(item));
    novo->valor = valor;
    novo->proximo = NULL;
    novo->anterior = NULL;
    if (*head == NULL) {
        *head = novo;
    }
    else{
        item*atual = *head;
        item*anterior = NULL;
        while (atual != NULL && atual->valor < valor) {
            anterior = atual;
            atual = atual->proximo;
        }
        if (anterior == NULL) {
            novo->proximo = *head;
            (*head)->anterior = novo;
            *head = novo;
        }
        else{
            novo->proximo = atual;
            novo->anterior = anterior;
            anterior->proximo = novo;
            if (atual != NULL) {
                atual->anterior = novo;
            }
        }
    }
}

void imprimirLista(item*head){
    item*atual = head;
    while (atual != NULL) {
        printf("%d ", atual->valor);
        atual = atual->proximo;
    }
    printf("\n");
}

void liberarLista(item*head){
    item*atual = head;
    item*proximoNo;
    while (atual != NULL) {
        proximoNo = atual->proximo;
        free(atual);
        atual = proximoNo;
    }
}
int main(){
    item*head = NULL;
    
    inserirOrdenado(&head, 5);
    inserirOrdenado(&head, 2);
    inserirOrdenado(&head, 8);
    inserirOrdenado(&head, 1);
    inserirOrdenado(&head, 3);

    printf("Lista duplamente encadeada ordenada: ");
    imprimirLista(head);

    liberarLista(head);
    return 0;
}