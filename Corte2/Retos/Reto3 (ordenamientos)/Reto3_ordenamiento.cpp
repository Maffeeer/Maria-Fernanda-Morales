#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <cmath>

using namespace std;

// Ordenamientos Basicos

pair<vector<int>, int> bubbleSort(vector<int> arr) {
    int n = arr.size();
    int intentos = 0;
    for (int i = 0; i < n; i++) {
        intentos++;
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
    return {arr, intentos};
}

pair<vector<int>, int> selectionSort(vector<int> arr) {
    int n = arr.size();
    int intentos = 0;
    for (int i = 0; i < n; i++) {
        intentos++;
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        swap(arr[i], arr[minIdx]);
    }
    return {arr, intentos};
}

pair<vector<int>, int> insertionSort(vector<int> arr) {
    int intentos = 0;
    for (int i = 1; i < arr.size(); i++) {
        intentos++;
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
    return {arr, intentos};
}

// Merge Sort y Quicksort

vector<int> mergeSort(vector<int> arr) {
    if (arr.size() > 1) {
        int mid = arr.size() / 2;
        vector<int> leftHalf(arr.begin(), arr.begin() + mid);
        vector<int> rightHalf(arr.begin() + mid, arr.end());

        leftHalf = mergeSort(leftHalf);
        rightHalf = mergeSort(rightHalf);

        int i = 0, j = 0, k = 0;

        while (i < leftHalf.size() && j < rightHalf.size()) {
            if (leftHalf[i] < rightHalf[j]) {
                arr[k] = leftHalf[i];
                i++;
            } else {
                arr[k] = rightHalf[j];
                j++;
            }
            k++;
        }

        while (i < leftHalf.size()) {
            arr[k] = leftHalf[i];
            i++;
            k++;
        }

        while (j < rightHalf.size()) {
            arr[k] = rightHalf[j];
            j++;
            k++;
        }
    }
    return arr;
}

vector<int> quickSort(vector<int> arr) {
    if (arr.size() <= 1) {
        return arr;
    } else {
        int pivot = arr[arr.size() / 2];
        vector<int> left, middle, right;

        for (int x : arr) {
            if (x < pivot) left.push_back(x);
            else if (x == pivot) middle.push_back(x);
            else right.push_back(x);
        }

        left = quickSort(left);
        right = quickSort(right);

        vector<int> result = left;
        result.insert(result.end(), middle.begin(), middle.end());
        result.insert(result.end(), right.begin(), right.end());
        return result;
    }
}

vector<int> quickSortInSitu(vector<int> arr, int izq = 0, int der = -1) {
    if (der == -1) der = arr.size() - 1;

    if (izq < der) {
        int pivote = arr[izq];
        int i = izq + 1;
        int j = der;

        while (i <= j) {
            while (i <= j && arr[i] <= pivote) i++;
            while (i <= j && arr[j] > pivote) j--;
            if (i < j) {
                swap(arr[i], arr[j]);
            }
        }

        swap(arr[izq], arr[j]);

        quickSortInSitu(arr, izq, j - 1);
        quickSortInSitu(arr, j + 1, der);
    }

    return arr;
}

// Heap Sort y Bucket Sort

void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

vector<int> heapSort(vector<int> arr) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }

    return arr;
}

void heapifyMinimo(vector<int>& arr, int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] < arr[smallest]) {
        smallest = left;
    }

    if (right < n && arr[right] < arr[smallest]) {
        smallest = right;
    }

    if (smallest != i) {
        swap(arr[i], arr[smallest]);
        heapifyMinimo(arr, n, smallest);
    }
}

vector<int> heapSortMinimo(vector<int> arr) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--) {
        heapifyMinimo(arr, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapifyMinimo(arr, i, 0);
    }

    return arr;
}

vector<int> bucketSort(vector<int> arr, int numeroCubetas = 10) {
    if (arr.empty()) return arr;

    int minValue = *min_element(arr.begin(), arr.end());
    int maxValue = *max_element(arr.begin(), arr.end());
    double bucketRange = (double)(maxValue - minValue) / numeroCubetas;

    vector<vector<int>> buckets(numeroCubetas);

    for (int num : arr) {
        int index;
        if (bucketRange == 0) {
            index = 0;
        } else {
            index = (int)((num - minValue) / bucketRange);
            if (index == numeroCubetas) index--;
        }
        buckets[index].push_back(num);
    }

    vector<int> sortedArr;
    for (auto& bucket : buckets) {
        sort(bucket.begin(), bucket.end());
        for (int num : bucket) {
            sortedArr.push_back(num);
        }
    }

    return sortedArr;
}

// Utilidad para imprimir vectores
void printVector(const vector<int>& arr) {
    cout << "[";
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i];
        if (i < arr.size() - 1) cout << ", ";
    }
    cout << "]";
}

// Pruebas

void pruebaUno() {
    cout << "Bubble Sort optimizado - Comparaciones en datos ordenados\n\n";

    vector<int> datosOrdenados;
    for (int i = 1; i <= 28; i++) {
        datosOrdenados.push_back(i);
    }
    cout << "Datos ya ordenados (1 a 28): longitud = " << datosOrdenados.size() << "\n\n";

    pair<vector<int>, int> resBubble = bubbleSort(datosOrdenados);
    pair<vector<int>, int> resInsertion = insertionSort(datosOrdenados);

    cout << "Bubble Sort con bandera optimizado: " << resBubble.second << " comparaciones\n";
    cout << "Insertion Sort: " << resInsertion.second << " comparaciones\n\n";
    cout << "Bubble baja de 28 comparaciones a " << resBubble.second << " (como Insertion: " << resInsertion.second << ")\n\n";
}

struct Registro {
    int id;
    int veces_prestado;
    int saturacion;
    int urgencia;
};

void pruebaDos() {
    cout << "Ordenar registros por criterio especifico\n\n";

    vector<Registro> registros = {
        {1, 15, 45, 8},
        {2, 3, 78, 9},
        {3, 42, 12, 2},
        {4, 8, 88, 10},
        {5, 25, 34, 5}
    };

    cout << "Registros originales:\n";
    for (const auto& r : registros) {
        cout << "  {id: " << r.id << ", veces_prestado: " << r.veces_prestado
             << ", saturacion: " << r.saturacion << ", urgencia: " << r.urgencia << "}\n";
    }
    cout << "\n";

    sort(registros.begin(), registros.end(),
         [](const Registro& a, const Registro& b) {
             return a.veces_prestado > b.veces_prestado;
         });

    cout << "Ordenados por veces prestado (descendente):\n";
    for (const auto& r : registros) {
        cout << "  {id: " << r.id << ", veces_prestado: " << r.veces_prestado
             << ", saturacion: " << r.saturacion << ", urgencia: " << r.urgencia << "}\n";
    }
    cout << "\n";
}

void pruebaTres() {
    cout << "Tabla de comparaciones e intercambios con datos reales\n\n";

    vector<int> datosReales = {64, 34, 25, 12, 22, 11, 90, 88, 76, 50, 43, 19, 7, 33, 55};
    cout << "Datos reales a ordenar (" << datosReales.size() << " elementos): ";
    printVector(datosReales);
    cout << "\n\n";

    cout << left << setw(20) << "Metodo" << setw(15) << "Iteraciones" << setw(50) << "Lista Ordenada" << "\n";

    pair<vector<int>, int> res1 = bubbleSort(datosReales);
    cout << left << setw(20) << "Bubble" << setw(15) << res1.second << setw(50);
    printVector(res1.first);
    cout << "\n";

    pair<vector<int>, int> res2 = selectionSort(datosReales);
    cout << left << setw(20) << "Selection" << setw(15) << res2.second << setw(50);
    printVector(res2.first);
    cout << "\n";

    pair<vector<int>, int> res3 = insertionSort(datosReales);
    cout << left << setw(20) << "Insertion" << setw(15) << res3.second << setw(50);
    printVector(res3.first);
    cout << "\n\n";
}

void reto1MergeQuick() {
    cout << " Quicksort en el sitio sin crear listas nuevas\n\n";

    vector<int> datos = {64, 34, 25, 12, 22, 11, 90, 88};
    cout << "Datos originales: ";
    printVector(datos);
    cout << "\n\n";

    vector<int> arr = datos;
    vector<int> arrOrdenado = quickSortInSitu(arr);
    cout << "Quicksort en sitio: ";
    printVector(arrOrdenado);
    cout << "\n\n";
}

void reto2MergeQuick() {
    cout << "Caso pesimo para Quicksort (pivote en primer elemento)\n\n";

    vector<int> datosOrdenados;
    for (int i = 1; i <= 10; i++) {
        datosOrdenados.push_back(i);
    }
    cout << "Datos ya ordenados: ";
    printVector(datosOrdenados);
    cout << "\n";
    cout << "Con pivote en primer elemento, Quicksort hara O(n^2) operaciones\n\n";

    vector<int> arr = datosOrdenados;
    clock_t inicio = clock();
    vector<int> arrOrdenado = quickSort(arr);
    clock_t fin = clock();
    double tiempo = ((double)(fin - inicio) / CLOCKS_PER_SEC) * 1000000;

    cout << "Resultado: ";
    printVector(arrOrdenado);
    cout << "\n";
    cout << fixed << setprecision(2) << "Tiempo: " << tiempo << " microsegundos\n\n";
}

void reto1HeapBucket() {
    cout << "Heapsort de minimos (ordena descendente)\n\n";

    vector<int> datos = {64, 34, 25, 12, 22, 11, 90, 88};
    cout << "Datos originales: ";
    printVector(datos);
    cout << "\n\n";

    vector<int> arr = datos;
    vector<int> arrOrdenado = heapSortMinimo(arr);
    cout << "Heapsort minimos (descendente): ";
    printVector(arrOrdenado);
    cout << "\n\n";
    cout << "Cambio: Se invierte la comparacion > por < en heapify\n\n";
}

void reto2HeapBucket() {
    cout << "Bucket Sort con diferente numero de cubetas\n\n";

    vector<int> datos = {64, 34, 25, 12, 22, 11, 90, 88, 76, 50, 43, 19, 7, 33, 55};
    cout << "Datos: ";
    printVector(datos);
    cout << " (" << datos.size() << " elementos)\n\n";

    cout << left << setw(15) << "Cubetas" << setw(70) << "Resultado" << "\n";

    vector<int> arr5 = datos;
    vector<int> resultado5 = bucketSort(arr5, 5);
    cout << left << setw(15) << "5 cubetas" << setw(70);
    printVector(resultado5);
    cout << "\n";

    vector<int> arr50 = datos;
    vector<int> resultado50 = bucketSort(arr50, 50);
    cout << left << setw(15) << "50 cubetas" << setw(70);
    printVector(resultado50);
    cout << "\n\n";

    cout << "Con 5 cubetas: elementos agrupados, menos buckets pero mas ordenamiento\n";
    cout << "Con 50 cubetas: elementos distribuidos, mas buckets pero menos ordenamiento\n";
    cout << "Punto optimo: numero de cubetas cercano a cantidad de datos\n\n";
}

void tablaComparativaFinal() {
    cout << "Tabla comparativa de todos los metodos\n";

    vector<int> datos = {64, 34, 25, 12, 22, 11, 90, 88, 76, 50, 43, 19, 7, 33, 55};
    cout << "Datos: ";
    printVector(datos);
    cout << " (" << datos.size() << " elementos)\n\n";

    cout << left << setw(20) << "Metodo" << setw(15) << "Comparaciones" << setw(20) << "Resultado Correcto" << "\n";

    vector<int> resultadoEsperado = datos;
    sort(resultadoEsperado.begin(), resultadoEsperado.end());

    // Bubble
    {
        vector<int> arr = datos;
        pair<vector<int>, int> res = bubbleSort(arr);
        bool correcto = res.first == resultadoEsperado;
        cout << left << setw(20) << "Bubble" << setw(15) << res.second << setw(20) << (correcto ? "true" : "false") << "\n";
    }

    // Selection
    {
        vector<int> arr = datos;
        pair<vector<int>, int> res = selectionSort(arr);
        bool correcto = res.first == resultadoEsperado;
        cout << left << setw(20) << "Selection" << setw(15) << res.second << setw(20) << (correcto ? "true" : "false") << "\n";
    }

    // Insertion
    {
        vector<int> arr = datos;
        pair<vector<int>, int> res = insertionSort(arr);
        bool correcto = res.first == resultadoEsperado;
        cout << left << setw(20) << "Insertion" << setw(15) << res.second << setw(20) << (correcto ? "true" : "false") << "\n";
    }

    // Merge
    {
        vector<int> arr = datos;
        vector<int> arrOrdenado = mergeSort(arr);
        bool correcto = arrOrdenado == resultadoEsperado;
        cout << left << setw(20) << "Merge" << setw(15) << "O(n log n)" << setw(20) << (correcto ? "true" : "false") << "\n";
    }

    // Quick
    {
        vector<int> arr = datos;
        vector<int> arrOrdenado = quickSort(arr);
        bool correcto = arrOrdenado == resultadoEsperado;
        cout << left << setw(20) << "Quick" << setw(15) << "Promedio O(n log n)" << setw(20) << (correcto ? "true" : "false") << "\n";
    }

    // Heap
    {
        vector<int> arr = datos;
        vector<int> arrOrdenado = heapSort(arr);
        bool correcto = arrOrdenado == resultadoEsperado;
        cout << left << setw(20) << "Heap" << setw(15) << "O(n log n)" << setw(20) << (correcto ? "true" : "false") << "\n";
    }

    // Bucket
    {
        vector<int> arr = datos;
        vector<int> arrOrdenado = bucketSort(arr, 10);
        bool correcto = arrOrdenado == resultadoEsperado;
        cout << left << setw(20) << "Bucket" << setw(15) << "O(n + k)" << setw(20) << (correcto ? "true" : "false") << "\n";
    }

    cout << "\n";
}

int main() {
    pruebaUno();
    pruebaDos();
    pruebaTres();
    reto1MergeQuick();
    reto2MergeQuick();
    reto1HeapBucket();
    reto2HeapBucket();
    tablaComparativaFinal();

    cout << "CONCLUSIONES\n";
    cout << "- Bubble Sort optimizado es eficiente en datos ya ordenados\n";
    cout << "- Quicksort en sitio es mas eficiente en memoria que la version recursiva\n";
    cout << "- Heapsort minimo invierte el orden del resultado final\n";
    cout << "- Bucket Sort mejora con numero optimo de cubetas\n";
    cout << "- Merge y Heap garantizan O(n log n) siempre\n";
    cout << "- Quicksort puede ser O(n^2) en casos pesimos\n";

    return 0;
}
