#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int particion(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
        }
    }
    int temp = arr[i];
    arr[i] = arr[high];
    arr[high] = temp;
    return i;
}

int quickSelect(int arr[], int low, int high, int k) {
    if (low == high) return arr[low];
    int pi = particion(arr, low, high);
    int len = pi - low + 1;
    if (k == len) return arr[pi];
    else if (k < len) return quickSelect(arr, low, pi - 1, k);
    else return quickSelect(arr, pi + 1, high, k - len);
}

int main() {
    int n, k;
    printf("Ingrese el tamaño del arreglo: ");
    scanf("%d", &n);
    int *arr = (int*)malloc(n * sizeof(int));

    printf("Ingrese los %d elementos:\n", n);
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    printf("Ingrese el valor de k: ");
    scanf("%d", &k);

    clock_t inicio = clock();
    int kth = quickSelect(arr, 0, n - 1, k);
    clock_t fin = clock();

    printf("El %d-esimo elemento menor es: %d\n", k, kth);
    printf("Tiempo de ejecucion: %.6f segundos\n", (double)(fin - inicio) / CLOCKS_PER_SEC);
    free(arr);
    return 0;
}

