#include <iostream>
using namespace std;

int intentos = 0;
int key = 0;

void bubbleSort(int arr[], int n) {
    intentos = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            intentos++;
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void selectionSort(int arr[], int n) {
    intentos = 0;
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
                intentos++;
            }
        }
        int temp = arr[minIdx];
        arr[minIdx] = arr[i];
        arr[i] = temp;
    }
}

void insertionSort(int arr[], int n) {
    intentos = 0;
    for (int i = 1; i < n; i++) {
        key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
            intentos++;
        }

        arr[j + 1] = key;
    }
}

void mostrarArreglo(const int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int arr[] = {64, 25, 12, 22, 11};
    int n = sizeof(arr) / sizeof(arr[0]);

    bubbleSort(arr, n);
    cout << "Bubble Sort intentos: " << intentos << endl;
    cout << "Lista ordenada: ";
    mostrarArreglo(arr, n);

    int arr2[] = {64, 25, 12, 22, 11};
    selectionSort(arr2, n);
    cout << "Selection Sort intentos: " << intentos << endl;
    cout << "Lista ordenada: ";
    mostrarArreglo(arr2, n);

    int arr3[] = {64, 25, 12, 22, 11};
    insertionSort(arr3, n);
    cout << "Insertion Sort intentos: " << intentos << endl;
    cout << "Lista ordenada: ";
    mostrarArreglo(arr3, n);

    return 0;
}
