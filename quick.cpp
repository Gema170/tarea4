#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
using namespace std;
using namespace std::chrono;

int particion(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[high]);
    return i;
}

int quickSelect(vector<int>& arr, int low, int high, int k) {
    if (low == high) return arr[low];
    int pi = particion(arr, low, high);
    int len = pi - low + 1;
    if (k == len) return arr[pi];
    else if (k < len) return quickSelect(arr, low, pi - 1, k);
    else return quickSelect(arr, pi + 1, high, k - len);
}

int main() {
    int n, k;
    cout << "Ingrese el tamaño del arreglo: ";
    cin >> n;
    vector<int> arr(n);
    cout << "Ingrese los " << n << " elementos:\n";
    for (int i = 0; i < n; i++) cin >> arr[i];

    cout << "Ingrese el valor de k: ";
    cin >> k;

    auto inicio = high_resolution_clock::now();
    int kth = quickSelect(arr, 0, n - 1, k);
    auto fin = high_resolution_clock::now();

    duration<double> tiempo = fin - inicio;
    cout << "El " << k << "-esimo elemento menor es: " << kth << endl;
    cout << "Tiempo de ejecucion: " << tiempo.count() << " segundos\n";

    return 0;
}
