#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using namespace std::chrono;

long long merge(vector<int>& arr, vector<int>& temp, int left, int mid, int right) {
    int i = left, j = mid, k = left;
    long long inv_count = 0;
    while (i <= mid - 1 && j <= right) {
        if (arr[i] <= arr[j]) temp[k++] = arr[i++];
        else {
            temp[k++] = arr[j++];
            inv_count += (mid - i);
        }
    }
    while (i <= mid - 1) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];
    for (i = left; i <= right; i++) arr[i] = temp[i];
    return inv_count;
}

long long mergeSort(vector<int>& arr, vector<int>& temp, int left, int right) {
    long long mid, inv_count = 0;
    if (right > left) {
        mid = (right + left) / 2;
        inv_count += mergeSort(arr, temp, left, mid);
        inv_count += mergeSort(arr, temp, mid + 1, right);
        inv_count += merge(arr, temp, left, mid + 1, right);
    }
    return inv_count;
}

int main() {
    int n;
    cout << "Ingrese el tamaño del arreglo: ";
    cin >> n;
    vector<int> arr(n), temp(n);
    cout << "Ingrese los " << n << " elementos:\n";
    for (int i = 0; i < n; i++) cin >> arr[i];

    auto inicio = high_resolution_clock::now();
    long long inv = mergeSort(arr, temp, 0, n - 1);
    auto fin = high_resolution_clock::now();

    duration<double> tiempo = fin - inicio;
    cout << "Numero de inversiones: " << inv << endl;
    cout << "Tiempo de ejecucion: " << tiempo.count() << " segundos\n";

    return 0;
}
