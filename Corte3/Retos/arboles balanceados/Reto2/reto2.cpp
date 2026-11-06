// Reto 2 - El orden maldito: como cambia la altura del BST segun el orden de insercion de 1 a 7
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>
#include <cassert>
using namespace std;

struct Nodo {
    int clave, alt;
    Nodo* izq; Nodo* der;
    Nodo(int c) : clave(c), alt(0), izq(nullptr), der(nullptr) {}
};

int alt(Nodo* n) { return n == nullptr ? -1 : n->alt; }
void recalc(Nodo* n) { n->alt = 1 + max(alt(n->izq), alt(n->der)); }

Nodo* insertar(Nodo* n, int c) {             // insercion BST SIN balancear
    if (n == nullptr) return new Nodo(c);
    if (c < n->clave)      n->izq = insertar(n->izq, c);
    else if (c > n->clave) n->der = insertar(n->der, c);
    recalc(n);
    return n;
}

void preorden(Nodo* n, vector<int>& s) {
    if (n == nullptr) return;
    s.push_back(n->clave); preorden(n->izq, s); preorden(n->der, s);
}

void liberar(Nodo* n) {
    if (n == nullptr) return;
    liberar(n->izq); liberar(n->der); delete n;
}

Nodo* construir(const vector<int>& orden) {
    Nodo* r = nullptr;
    for (int c : orden) r = insertar(r, c);
    return r;
}

int alturaDe(const vector<int>& orden) {
    Nodo* r = construir(orden);
    int h = alt(r);
    liberar(r);
    return h;
}

string texto(const vector<int>& v, const string& abre, const string& cierra) {
    string s = abre;
    for (size_t i = 0; i < v.size(); i++) s += to_string(v[i]) + (i + 1 < v.size() ? ", " : "");
    return s + cierra;
}

void ver(const string& titulo, const vector<int>& orden) {
    Nodo* r = construir(orden);
    vector<int> s;
    preorden(r, s);
    cout << "  " << left << setw(20) << titulo << right << " " << texto(orden, "(", ")")
         << "  altura=" << alt(r) << "  preorden=" << texto(s, "[", "]") << endl;
    liberar(r);
}

// Padre de cada clave en el arbol perfecto: 4 es la raiz, 2 y 6 sus hijos
const vector<pair<int,int>> PADRE = {{2,4},{6,4},{1,2},{3,2},{5,6},{7,6}};

bool padresAntes(const vector<int>& orden) {   // cada clave llega despues de su padre
    auto pos = [&](int c) { return find(orden.begin(), orden.end(), c) - orden.begin(); };
    for (auto [h, p] : PADRE)
        if (pos(p) >= pos(h)) return false;
    return true;
}

bool siempreExtremo(const vector<int>& orden) { // cada clave es el minimo o el maximo de las que faltan
    for (size_t i = 0; i < orden.size(); i++) {
        int minimo = *min_element(orden.begin() + i, orden.end());
        int maximo = *max_element(orden.begin() + i, orden.end());
        if (orden[i] != minimo && orden[i] != maximo) return false;
    }
    return true;
}

int main() {
    // ---------- Ejemplos ----------
    cout << "EJEMPLOS" << endl;
    ver("mejor (por niveles)", {4,2,6,1,3,5,7});
    ver("mejor (preorden)", {4,2,1,3,6,5,7});
    ver("peor (ordenado)", {1,2,3,4,5,6,7});
    ver("peor (zigzag)", {1,7,2,6,3,5,4});
    ver("empieza por 4, malo", {4,1,2,3,5,6,7});

    // ---------- Todas las permutaciones ----------
    vector<int> orden = {1,2,3,4,5,6,7};
    map<int, vector<vector<int>>> porAltura;
    set<vector<int>> conPadresAntes, conExtremos;
    int total = 0;
    do {
        total++;
        porAltura[alturaDe(orden)].push_back(orden);
        if (padresAntes(orden)) conPadresAntes.insert(orden);
        if (siempreExtremo(orden)) conExtremos.insert(orden);
    } while (next_permutation(orden.begin(), orden.end()));

    cout << "\nLOS " << total << " ORDENES POSIBLES, SEGUN LA ALTURA QUE PRODUCEN" << endl;
    for (auto& [h, ordenes] : porAltura)
        cout << "  altura " << h << ": " << setw(5) << ordenes.size() << " ordenes ("
             << fixed << setprecision(2) << setw(5) << 100.0 * ordenes.size() / total << "%)  primero: "
             << texto(ordenes[0], "(", ")") << endl;

    // ---------- Que tienen en comun ----------
    const auto& mejores = porAltura[2];
    const auto& peores = porAltura[6];
    for (auto& o : mejores) assert(o[0] == 4);
    assert(conPadresAntes == set<vector<int>>(mejores.begin(), mejores.end()));
    assert(conExtremos == set<vector<int>>(peores.begin(), peores.end()));
    cout << "\nQUE TIENEN EN COMUN" << endl;
    cout << "  Altura 2 <=> cada clave llega despues de su padre: 4 antes que todas, 2 antes que 1 y 3, 6 antes que 5 y 7." << endl;
    cout << "  Conteo: C(6,3) * 2 * 2 = 20 * 2 * 2 = " << 20 * 2 * 2 << "  (coincide con los " << mejores.size() << " encontrados)" << endl;
    cout << "  Altura 6 <=> cada clave es el minimo o el maximo de las que faltan." << endl;
    cout << "  Conteo: 2^6 = " << (1 << 6) << "  (coincide con los " << peores.size() << " encontrados)" << endl;
    return 0;
}
