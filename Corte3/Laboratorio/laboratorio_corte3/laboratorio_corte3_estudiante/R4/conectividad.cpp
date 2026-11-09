// ============================================================
//  Laboratorio integrador · Corte 3 · RETO 4  (25 puntos)
//  Sesiones 41 y 43 — DFS, componentes conexas y vias criticas
//  Sistema: RedAcopio — que vias no pueden cerrarse
//
//  Este archivo NO tiene main(): el main esta en pruebas_r4.cpp
//  MODIFIQUE SOLO ESTE ARCHIVO.  NO TOQUE pruebas_r4.cpp ni red.h
//  Compile y ejecute:
//     g++ -std=c++17 -g -o pruebas_r4 conectividad.cpp pruebas_r4.cpp
//     ./pruebas_r4
// ============================================================
#include <vector>
#include <string>
#include "red.h"
using namespace std;

int cuantasComponentes(const vector<vector<int>>& g) {
    // Cuenta en cuantos pedazos esta partida la red.
    // Lance un DFS desde cada vertice que todavia no haya sido visitado;
    // cada DFS que arranca es una componente nueva.
    //
    // Use una PILA explicita (un vector<int> con push_back y pop_back),
    // no recursion.
    //
    // PENDIENTE: implementar.
    vector<bool> visitado(N, false);
    int comps = 0;
    for (int s = 0; s < N; s++) {
        if (visitado[s]) continue;
        comps++;                                   // cada DFS que arranca es una componente nueva
        vector<int> pila = {s};
        while (!pila.empty()) {
            int u = pila.back(); pila.pop_back();  // LIFO: saca el ultimo que entro
            if (visitado[u]) continue;
            visitado[u] = true;
            for (int v : g[u])
                if (!visitado[v]) pila.push_back(v);
        }
    }
    return comps;
}

vector<string> viasCriticas() {
    // Una via es CRITICA si al cerrarla la red deja de estar conectada.
    // Para cada arista: arme la red SIN esa arista y cuente componentes.
    // Si pasa de 1 a mas de 1, la via es critica.
    //
    // Devuelva los nombres con el formato  "ORIGEN-DESTINO"
    // respetando el orden en que aparecen en ARISTAS.
    // Ejemplo de formato:  "ACOPIO-NORTE"
    //
    // PENDIENTE: implementar.
    vector<string> criticas;
    for (size_t i = 0; i < ARISTAS.size(); i++) {
        vector<pair<int,int>> sinUna;              // la red SIN la arista i
        for (size_t j = 0; j < ARISTAS.size(); j++)
            if (j != i) sinUna.push_back(ARISTAS[j]);
        if (cuantasComponentes(construir(sinUna)) > 1) {
            auto [u, v] = ARISTAS[i];
            criticas.push_back(NOMBRES[u] + "-" + NOMBRES[v]);
        }
    }
    return criticas;
}
