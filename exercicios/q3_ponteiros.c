#include <stdio.h>

void insertionsort(int *arr, int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int main() {
    int n;

    printf("Digite o numero de elementos: ");
    scanf("%d", &n);

    int array[n];

    printf("Digite os elementos:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &array[i]);
    }

    insertionsort(array, n);

    printf("Array ordenado:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}