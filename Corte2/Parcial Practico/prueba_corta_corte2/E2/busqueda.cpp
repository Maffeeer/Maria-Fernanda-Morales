// ============================================================
//  Prueba corta · Segundo corte · EJERCICIO 2  (25 puntos)
//  Tema: busqueda binaria
//  Sistema: RedAcopio — localizacion de codigos de material
//
//  Este archivo NO tiene main(): el main esta en pruebas_e2.cpp
//  NO MODIFIQUE el archivo pruebas_e2.cpp
//  Compile y ejecute:
//     g++ -std=c++17 -g -o pruebas_e2 busqueda.cpp pruebas_e2.cpp
//     ./pruebas_e2
//
//  Se reportan DOS fallas:
//   1. Devuelve -1 para codigos que si estan en el arreglo.
//   2. Con algunos valores el sanitizer aborta el programa.
// ============================================================
using namespace std;
#include <iostream>

int buscarCodigo(int v[], int n, int x) {
    int izq = 0, der = n - 1; // n-1 porque el arreglo tiene indices de 0 a n-1
    while (izq <= der) {                         // <-- revise
        int medio = (izq + der) / 2;
        if (v[medio] == x) return medio;
        // se corrigen los limites de busqueda, y se evita el desbordamiento de indices
        if (v[medio] < x) izq = medio + 1;       // <-- revise
        else der = medio - 1;       // <-- revise
    }
    return -1;
}

