#include <stdio.h>
#include <stdlib.h>

typedef struct listaDuplamenteEncadeada {
    int valor;
    struct listaDuplamenteEncadeada *proximo;
    struct listaDuplamenteEncadeada *anterior;
} ListaDupla;

void inserirOrdenado(ListaDupla **head, int valor){
    ListaDupla*novo = (ListaDupla*)malloc(sizeof(ListaDupla));
    novo->valor = valor;
    novo->proximo = NULL;
    novo->anterior = NULL;
    if (*head == NULL) {
        *head = novo;
    }
    else{
        ListaDupla*atual = *head;
        ListaDupla*anterior = NULL;
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

void imprimirLista(ListaDupla*head){
    ListaDupla*atual = head;
    while (atual != NULL) {
        printf("%d ", atual->valor);
        atual = atual->proximo;
    }
    printf("\n");
}

void liberarLista(ListaDupla*head){
    ListaDupla*atual = head;
    ListaDupla*proximoNo;
    while (atual != NULL) {
        proximoNo = atual->proximo;
        free(atual);
        atual = proximoNo;
    }
}
int main(){
    ListaDupla*minhaLista = NULL;
    int n, valor;

    printf("Quantos numeros deseja inserir na lista duplamente encadeada ordenada? ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Digite o numero %d: ", i + 1);
        scanf("%d", &valor);
        inserirOrdenado(&minhaLista, valor);
    }

    printf("Lista duplamente encadeada ordenada: ");
    imprimirLista(minhaLista);

    liberarLista(minhaLista);
    return 0;
}