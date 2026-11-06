// Reto 3 - El grafo imposible: para que V y grado k existe un grafo donde todos tengan grado k?
// Grafo simple: no dirigido, sin lazos y sin aristas repetidas. Respuesta completa en respuesta.md
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <set>
#include <algorithm>
#include <cassert>
using namespace std;

using Aristas = vector<pair<int,int>>;

vector<int> grados(int V, const Aristas& aristas) {
    vector<int> g(V, 0);
    for (auto [u, v] : aristas) { g[u]++; g[v]++; }
    return g;
}

bool todosGrado(const vector<int>& g, int k) {
    return all_of(g.begin(), g.end(), [k](int x) { return x == k; });
}

bool esPosible(int V, int k) {
    return 0 <= k && k <= V - 1 && V * k % 2 == 0;
}

string motivo(int V, int k) {
    if (k > V - 1) return "k>=V";
    if (V * k % 2 == 1) return "impar";
    return "si";
}

// Vertices en circulo: cada uno se une con sus k/2 vecinos a cada lado y, si k es impar, con el opuesto
Aristas construirRegular(int V, int k) {
    Aristas aristas;
    for (int i = 0; i < V; i++)
        for (int s = 1; s <= k / 2; s++) aristas.push_back({i, (i + s) % V});
    if (k % 2 == 1)
        for (int i = 0; i < V / 2; i++) aristas.push_back({i, i + V / 2});
    return aristas;
}

// Prueba todos los grafos posibles de V vertices: 2^(V(V-1)/2) subconjuntos de aristas
bool existePorFuerzaBruta(int V, int k) {
    Aristas pares;
    for (int u = 0; u < V; u++)
        for (int v = u + 1; v < V; v++) pares.push_back({u, v});
    for (long mascara = 0; mascara < (1L << pares.size()); mascara++) {
        vector<int> g(V, 0);
        for (size_t b = 0; b < pares.size(); b++)
            if (mascara >> b & 1) { g[pares[b].first]++; g[pares[b].second]++; }
        if (todosGrado(g, k)) return true;
    }
    return false;
}

int main() {
    // ---------- El intento de dibujarlo: V = 5, k = 3 ----------
    const Aristas INTENTO = {{0,4},{1,4},{2,3},{0,2},{1,2},{0,3},{1,3}};
    vector<int> g = grados(5, INTENTO);
    int suma = 0;
    cout << "INTENTO CON V = 5 Y GRADO 3" << endl;
    cout << "  Mejor intento: " << INTENTO.size() << " aristas, grados [";
    for (int i = 0; i < 5; i++) { cout << g[i] << (i < 4 ? ", " : ""); suma += g[i]; }
    cout << "]  (suma " << suma << "). Al vertice 4 le falta una arista" << endl;
    cout << "  y los demas ya tienen grado 3: cualquier arista nueva deja a otro vertice con grado 4." << endl;
    cout << "  Suma necesaria = 5*3 = 15, pero la suma siempre es 2E (par): E = 15/2 = " << 15 / 2.0 << " no es entero." << endl;
    cout << "  Fuerza bruta sobre los 2^10 grafos de 5 vertices: existe = "
         << (existePorFuerzaBruta(5, 3) ? "true" : "false") << endl;

    // ---------- Generalizacion ----------
    const int MAX_V = 8;
    cout << "\nEXISTE UN GRAFO CON V VERTICES, TODOS DE GRADO k?" << endl;
    cout << "  si = existe | impar = V*k es impar | k>=V = no alcanzan los vertices" << endl;
    cout << "      ";
    for (int k = 0; k <= MAX_V; k++) cout << setw(7) << "k=" + to_string(k);
    cout << endl;
    for (int V = 1; V <= MAX_V; V++) {
        cout << "  V=" << V << " ";
        for (int k = 0; k <= MAX_V; k++) cout << setw(7) << motivo(V, k);
        cout << endl;
    }

    // ---------- Verificacion de la regla ----------
    cout << "\nVERIFICACION" << endl;
    for (int V = 1; V <= 6; V++)
        for (int k = 0; k <= V; k++)
            assert(existePorFuerzaBruta(V, k) == esPosible(V, k));
    cout << "  Fuerza bruta: la regla acierta en todos los casos con V <= 6 y 0 <= k <= V" << endl;

    for (int V = 1; V <= 30; V++)
        for (int k = 0; k < V; k++)
            if (esPosible(V, k)) {
                Aristas aristas = construirRegular(V, k);
                set<pair<int,int>> sinRepetir;
                for (auto [u, v] : aristas) {
                    assert(u != v);
                    sinRepetir.insert({min(u, v), max(u, v)});
                }
                assert((int)sinRepetir.size() == V * k / 2 && aristas.size() == sinRepetir.size());
                assert(todosGrado(grados(V, aristas), k));
            }
    cout << "  Construccion: todo caso posible con V <= 30 da un grafo simple con los grados pedidos" << endl;
    return 0;
}
