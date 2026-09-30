//Basandonos en lo que hicimos en py, unicamente pasamos a c++, aunque con cierta ayuda para terminos de la IA de vs code

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>
#include <random>
#include <algorithm>
#include <stdexcept>

using namespace std;

// La clase Registro representa un registro con un id, un nombre y un valor
class Registro {
public:
    int id;
    string nombre;
    int valor;

    Registro(int id = 0, string nombre = "", int valor = 0)
        : id(id), nombre(nombre), valor(valor) {}

    // Equivalente a __repr__: devuelve una representación legible del objeto Registro
    string repr() const {
        return "Registro(" + to_string(id) + ", " + nombre + ", " + to_string(valor) + ")";
    }

    bool operator<(const Registro& otro) const { return valor < otro.valor; }   // Define si es menor que otro registro
    bool operator<=(const Registro& otro) const { return valor <= otro.valor; } // Define si es menor o igual que otro registro
    bool operator>(const Registro& otro) const { return valor > otro.valor; }   // Define si es mayor que otro registro
    bool operator==(const Registro& otro) const { return valor == otro.valor; } // Define si son iguales dos registros
};

ostream& operator<<(ostream& os, const Registro& r) {
    return os << r.repr();
}

// Clase para analizar los algoritmos de búsqueda y ordenamiento
class Analizar {
public:
    vector<Registro> datos;
    long long comparaciones;
    long long intercambios;

    Analizar(const vector<Registro>& datos) : datos(datos), comparaciones(0), intercambios(0) {}

    // Parte B: Búsqueda

    // Es búsqueda lineal y cuenta comparaciones
    int busquedaSecuencial(int target_valor) {
        comparaciones = 0;
        for (int i = 0; i < (int)datos.size(); i++) {
            comparaciones++;
            if (datos[i].valor == target_valor) {
                return i;
            }
        }
        return -1;
    }

    // Búsqueda binaria cuando los datos son ordenados y cuenta comparaciones
    int busquedaBinaria(int target_valor) {
        comparaciones = 0;
        int izq = 0, der = (int)datos.size() - 1;

        while (izq <= der) {
            comparaciones++;
            int mid = (izq + der) / 2;
            if (datos[mid].valor == target_valor) {
                return mid;
            } else if (datos[mid].valor < target_valor) {
                izq = mid + 1;
            } else {
                der = mid - 1;
            }
        }
        return -1;
    }

    // Parte C: Ordenamientos principales

    void bubbleSort() {
        comparaciones = 0;
        intercambios = 0;
        int n = (int)datos.size();

        for (int i = 0; i < n; i++) {
            bool swapped = false;
            for (int j = 0; j < n - i - 1; j++) {
                comparaciones++;
                if (datos[j] > datos[j + 1]) {
                    swap(datos[j], datos[j + 1]);
                    intercambios++;
                    swapped = true;
                }
            }
            if (!swapped) {
                break;
            }
        }
    }

    void selectionSort() {
        comparaciones = 0;
        intercambios = 0;
        int n = (int)datos.size();

        for (int i = 0; i < n; i++) {
            int min_idx = i;
            for (int j = i + 1; j < n; j++) {
                comparaciones++;
                if (datos[j] < datos[min_idx]) {
                    min_idx = j;
                }
            }
            if (min_idx != i) {
                swap(datos[i], datos[min_idx]);
                intercambios++;
            }
        }
    }

    void insertionSort() {
        comparaciones = 0;
        intercambios = 0;

        for (int i = 1; i < (int)datos.size(); i++) {
            Registro key = datos[i];
            int j = i - 1;
            while (j >= 0) {
                comparaciones++;
                if (datos[j] > key) {
                    datos[j + 1] = datos[j];
                    intercambios++;
                    j--;
                } else {
                    break;
                }
            }
            if (j != i - 1) {
                datos[j + 1] = key;
            }
        }
    }

    // Parte D: Merge Sort (divide y vencerás, con recursividad)

    void mergeSort() {
        comparaciones = 0;
        intercambios = 0;
        mergeSortRec(0, (int)datos.size() - 1);
    }

private:
    void mergeSortRec(int izq, int der) {
        if (izq < der) {
            int mid = (izq + der) / 2;
            mergeSortRec(izq, mid);
            mergeSortRec(mid + 1, der);
            merge(izq, mid, der);
        }
    }

    void merge(int izq, int mid, int der) {
        vector<Registro> izq_arr(datos.begin() + izq, datos.begin() + mid + 1);
        vector<Registro> der_arr(datos.begin() + mid + 1, datos.begin() + der + 1);

        size_t i = 0, j = 0;
        int k = izq;

        while (i < izq_arr.size() && j < der_arr.size()) {
            comparaciones++;
            if (izq_arr[i] <= der_arr[j]) {
                datos[k] = izq_arr[i];
                i++;
            } else {
                datos[k] = der_arr[j];
                j++;
            }
            k++;
            intercambios++;
        }

        while (i < izq_arr.size()) {
            datos[k] = izq_arr[i];
            i++;
            k++;
            intercambios++;
        }

        while (j < der_arr.size()) {
            datos[k] = der_arr[j];
            j++;
            k++;
            intercambios++;
        }
    }
};

// Convierte un texto a entero, fallando como int() de Python si no es un entero válido
int convertirEntero(const string& texto) {
    string s = texto;
    s.erase(0, s.find_first_not_of(" \t\r\n"));
    s.erase(s.find_last_not_of(" \t\r\n") + 1);
    size_t pos = 0;
    int valor = stoi(s, &pos); // lanza invalid_argument si no hay número
    if (pos != s.size()) {
        throw invalid_argument("no es entero");
    }
    return valor;
}

vector<Registro> ingresarRegistros() {
    vector<Registro> registros;
    cout << "Ingreso de Registros" << endl;
    cout << "Ingrese registros. Escriba '0' para terminar.\n" << endl;

    int contador = 1;
    while (true) {
        cout << "Nombre del registro " << contador << " (o '0' para terminar): ";
        string nombre;
        if (!getline(cin, nombre)) break;
        // strip()
        nombre.erase(0, nombre.find_first_not_of(" \t\r\n"));
        nombre.erase(nombre.find_last_not_of(" \t\r\n") + 1);

        if (nombre == "0") {
            if (contador == 1) {
                cout << "Error: Ingrese al menos un registro." << endl;
                continue;
            }
            break;
        }

        try {
            cout << "Valor del registro: ";
            string entrada;
            getline(cin, entrada);
            int valor = convertirEntero(entrada);
            registros.push_back(Registro(contador, nombre, valor));
            contador++;
        } catch (const exception&) {
            cout << "Error: El valor debe ser un número entero.\n" << endl;
        }
    }

    return registros;
}

// Sobrecarga para las partes C, D y E, que llaman ingresarRegistros(tamaño, tipo):
// genera 'n' registros automáticamente, ordenados o desordenados
vector<Registro> ingresarRegistros(int n, const string& tipo) {
    static mt19937 gen(random_device{}());
    uniform_int_distribution<int> dist(1, 1000);

    vector<Registro> registros;
    for (int i = 0; i < n; i++) {
        int valor = (tipo == "ordenado") ? i + 1 : dist(gen);
        registros.push_back(Registro(i + 1, "R" + to_string(i + 1), valor));
    }
    return registros;
}

// Main

int main() {
    vector<Registro> registros = ingresarRegistros();

    // Parte B
    cout << "Comparación (Secuencial vs Binaria)" << endl;

    vector<int> datosBusqueda = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    sort(datosBusqueda.begin(), datosBusqueda.end());

    cout << "\nDatos ordenados: [";
    for (size_t i = 0; i < datosBusqueda.size(); i++) {
        cout << datosBusqueda[i] << (i + 1 < datosBusqueda.size() ? ", " : "");
    }
    cout << "]\n" << endl;

    // Los métodos trabajan con .valor, así que los enteros se envuelven en Registros
    vector<Registro> registrosBusqueda;
    for (size_t i = 0; i < datosBusqueda.size(); i++) {
        registrosBusqueda.push_back(Registro((int)i + 1, "R" + to_string(i + 1), datosBusqueda[i]));
    }

    Analizar analizador(registrosBusqueda);

    // Casos de búsqueda
    vector<pair<string, int>> casos = {
        {"Primer elemento", datosBusqueda[0]},
        {"Elemento del medio", datosBusqueda[datosBusqueda.size() / 2]},
        {"Último elemento", datosBusqueda.back()},
        {"Elemento que NO existe", 999}
    };

    cout << "Caso" << " " << "Secuencial" << " " << "Binaria" << endl;

    for (auto& caso : casos) {
        analizador.datos = registrosBusqueda;

        // Búsqueda secuencial
        analizador.busquedaSecuencial(caso.second);
        long long comp_sec = analizador.comparaciones;

        // Búsqueda binaria
        analizador.busquedaBinaria(caso.second);
        long long comp_bin = analizador.comparaciones;

        cout << caso.first << " " << comp_sec << " " << comp_bin << endl;
    }

    // Prueba con datos desordenados
    cout << "\n--- Con datos desordenados ---" << endl;
    vector<int> datosDesordenados = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};  // Sin ordenar
    cout << "Datos desordenados: [";
    for (size_t i = 0; i < datosDesordenados.size(); i++) {
        cout << datosDesordenados[i] << (i + 1 < datosDesordenados.size() ? ", " : "");
    }
    cout << "]\n" << endl;

    vector<Registro> registrosDesordenados;
    for (size_t i = 0; i < datosDesordenados.size(); i++) {
        registrosDesordenados.push_back(Registro((int)i + 1, "R" + to_string(i + 1), datosDesordenados[i]));
    }

    analizador.datos = registrosDesordenados;
    cout << "Caso" << " " << "Secuencial" << " " << "Binaria (no es válida en datos desordenados)" << endl;

    for (auto& caso : casos) {
        analizador.datos = registrosDesordenados;

        // Búsqueda secuencial
        analizador.busquedaSecuencial(caso.second);
        long long comp_sec = analizador.comparaciones;

        // La búsqueda binaria en datos desordenados NO es confiable
        analizador.busquedaBinaria(caso.second);
        long long comp_bin = analizador.comparaciones;

        cout << caso.first << " " << comp_sec << " " << comp_bin << endl;
    }

    // DIFERENCIA: La búsqueda secuencial trabaja correctamente en ambos casos (ordenados y desordenados)
    // porque examina todos los elementos linealmente. Sin embargo, la búsqueda binaria solo es eficiente
    // en datos ordenados; en datos desordenados puede no encontrar el elemento aunque exista, porque
    // depende de que el array esté ordenado para eliminar mitades. En datos ordenados, la búsqueda
    // binaria reduce significativamente las comparaciones, especialmente en listas grandes.

    // Parte C

    int tamano = 20;

    cout << "\nCon datos desordenados (n=" << tamano << "):" << endl;
    cout << "Algoritmo" << " " << "Comparaciones" << " " << "Intercambios" << endl;

    vector<pair<string, string>> algoritmos = {
        {"Bubble Sort", "bubble"}, {"Selection Sort", "selection"}, {"Insertion Sort", "insertion"}
    };

    // Datos desordenados
    vector<Registro> datosDes = ingresarRegistros(tamano, "desordenado");

    for (auto& alg : algoritmos) {
        analizador.datos = datosDes;
        if (alg.second == "bubble") {
            analizador.bubbleSort();
        } else if (alg.second == "selection") {
            analizador.selectionSort();
        } else {
            analizador.insertionSort();
        }
        cout << alg.first << " " << analizador.comparaciones << " " << analizador.intercambios << endl;
    }

    cout << "\nCon datos ordenados (n=" << tamano << "):" << endl;
    cout << "Algoritmo" << " " << "Comparaciones" << " " << "Intercambios" << endl;

    // Ordenados
    vector<Registro> datosOrd = ingresarRegistros(tamano, "ordenado");

    for (auto& alg : algoritmos) {
        analizador.datos = datosOrd;
        if (alg.second == "bubble") {
            analizador.bubbleSort();
        } else if (alg.second == "selection") {
            analizador.selectionSort();
        } else {
            analizador.insertionSort();
        }
        cout << alg.first << " " << analizador.comparaciones << " " << analizador.intercambios << endl;
    }

    // Parte D

    vector<int> tamanos = {100, 500, 1000};

    cout << "\n" << "Tamaño" << " " << "Bubble (ms)" << " " << "Merge (ms)" << " " << "Factor" << endl;

    for (int t : tamanos) {
        vector<Registro> datosTest = ingresarRegistros(t, "desordenado");

        // Bubble Sort
        analizador.datos = datosTest;
        auto inicio = chrono::high_resolution_clock::now();
        analizador.bubbleSort();
        double tiempo_bubble = chrono::duration<double, milli>(chrono::high_resolution_clock::now() - inicio).count();

        // Merge Sort
        analizador.datos = datosTest;
        inicio = chrono::high_resolution_clock::now();
        analizador.mergeSort();
        double tiempo_merge = chrono::duration<double, milli>(chrono::high_resolution_clock::now() - inicio).count();

        double factor = tiempo_merge > 0 ? tiempo_bubble / tiempo_merge : 0;
        cout << t << " " << tiempo_bubble << " " << tiempo_merge << " " << factor << "x" << endl;
    }

    // Parte E - Análisis de complejidad de Merge Sort

    vector<int> tamanos_complejidad = {50, 100, 200, 400};

    cout << "\n" << "n" << " " << "Comparaciones" << " " << "Factor (n/comparaciones)" << endl;

    for (int t : tamanos_complejidad) {
        vector<Registro> datosTest = ingresarRegistros(t, "desordenado");
        analizador.datos = datosTest;
        analizador.mergeSort();

        double factor = analizador.comparaciones > 0 ? (double)t / analizador.comparaciones : 0;
        cout << t << " " << analizador.comparaciones << " " << factor << "x" << endl;
    }

    // Interpretación de la tabla:
    // La tabla muestra que el número de comparaciones crece aproximadamente en proporción a 
    // n log n, lo que es consistente con la complejidad teórica de Merge Sort. A medida que n aumenta,
    // el factor n/comparaciones se mantiene relativamente constante, indicando que Merge Sort es eficiente
    // incluso para tamaños de entrada grandes.
    
    return 0;
}