// Reto 3 - Cuando NO alcanza una rotacion: en insercion siempre basta, en eliminacion no
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <cassert>
#include <climits>
using namespace std;

struct Nodo {
    int clave, alt;
    Nodo* izq; Nodo* der;
    Nodo(int c) : clave(c), alt(0), izq(nullptr), der(nullptr) {}
};

int alt(Nodo* n) { return n == nullptr ? -1 : n->alt; }
int fe(Nodo* n)  { return n == nullptr ? 0 : alt(n->izq) - alt(n->der); }   // factor de equilibrio
void recalc(Nodo* n) { n->alt = 1 + max(alt(n->izq), alt(n->der)); }

Nodo* rotarDerecha(Nodo* y) {
    Nodo* x = y->izq; Nodo* B = x->der;
    x->der = y; y->izq = B;
    recalc(y); recalc(x);
    return x;
}

Nodo* rotarIzquierda(Nodo* x) {
    Nodo* y = x->der; Nodo* B = y->izq;
    y->izq = x; x->der = B;
    recalc(x); recalc(y);
    return y;
}

void preorden(Nodo* n, string& s) {
    if (n == nullptr) return;
    s += " " + to_string(n->clave) + "(fe=" + to_string(fe(n)) + ")";
    preorden(n->izq, s); preorden(n->der, s);
}

void ver(const string& titulo, Nodo* raiz) {
    string s;
    preorden(raiz, s);
    cout << "  " << left << setw(22) << titulo << right << " altura=" << alt(raiz) << "  preorden:" << s << endl;
}

void liberar(Nodo* n) {
    if (n == nullptr) return;
    liberar(n->izq); liberar(n->der); delete n;
}

// ---------- AVL: cuenta cada rebalanceo (una rotacion simple o una doble cuentan como uno) ----------
int rebalanceos = 0;

Nodo* rebalancear(Nodo* n) {
    recalc(n);
    int f = fe(n);
    if (f > 1) {                                 // pesa la izquierda
        rebalanceos++;
        if (fe(n->izq) < 0) n->izq = rotarIzquierda(n->izq);   // caso LR
        return rotarDerecha(n);
    }
    if (f < -1) {                                // pesa la derecha
        rebalanceos++;
        if (fe(n->der) > 0) n->der = rotarDerecha(n->der);     // caso RL
        return rotarIzquierda(n);
    }
    return n;
}

Nodo* insertarAVL(Nodo* n, int c) {
    if (n == nullptr) return new Nodo(c);
    int alturaAntes = n->alt;
    if (c < n->clave)      n->izq = insertarAVL(n->izq, c);
    else if (c > n->clave) n->der = insertarAVL(n->der, c);
    recalc(n);
    bool desbalanceado = abs(fe(n)) > 1;
    n = rebalancear(n);
    if (desbalanceado) assert(n->alt == alturaAntes);   // la clave de la demostracion: recupera la altura de antes
    return n;
}

Nodo* eliminarAVL(Nodo* n, int c) {
    if (n == nullptr) return nullptr;
    if (c < n->clave)      n->izq = eliminarAVL(n->izq, c);
    else if (c > n->clave) n->der = eliminarAVL(n->der, c);
    else {
        if (n->izq == nullptr) { Nodo* d = n->der; delete n; return d; }
        if (n->der == nullptr) { Nodo* i = n->izq; delete n; return i; }
        Nodo* s = n->der;
        while (s->izq != nullptr) s = s->izq;    // sucesor: el menor del subarbol derecho
        n->clave = s->clave;
        n->der = eliminarAVL(n->der, s->clave);
    }
    return rebalancear(n);
}

bool esAVL(Nodo* n, long minimo = LONG_MIN, long maximo = LONG_MAX) {
    if (n == nullptr) return true;
    if (n->clave <= minimo || n->clave >= maximo) return false;
    if (n->alt != 1 + max(alt(n->izq), alt(n->der)) || abs(fe(n)) > 1) return false;
    return esAVL(n->izq, minimo, n->clave) && esAVL(n->der, n->clave, maximo);
}

// ---------- El arbol del reto: AVL con el minimo de nodos para altura 4 ----------
const vector<int> ORDEN = {5, 2, 8, 1, 3, 7, 10, 4, 6, 9, 11, 12};

Nodo* construir() {
    rebalanceos = 0;
    Nodo* r = nullptr;
    for (int c : ORDEN) r = insertarAVL(r, c);
    assert(rebalanceos == 0);                    // se construye sin rotar: la forma es exactamente la del dibujo
    return r;
}

int main() {
    cout << "ARBOL INICIAL" << endl;
    cout << "  orden de insercion: [";
    for (size_t i = 0; i < ORDEN.size(); i++) cout << ORDEN[i] << (i + 1 < ORDEN.size() ? ", " : "");
    cout << "]" << endl;
    Nodo* r = construir();
    ver("inicial", r);
    liberar(r);

    // ---------- Eliminacion: paso a paso ----------
    cout << "\nELIMINACION DEL 1, PASO A PASO" << endl;
    r = construir();
    delete r->izq->izq;
    r->izq->izq = nullptr; recalc(r->izq); recalc(r);
    ver("sin el 1", r);
    cout << "    Desbalanceado solo el 2 (fe=-2). La raiz 5 aun esta bien (fe=-1)." << endl;
    r->izq = rotarIzquierda(r->izq); recalc(r);
    ver("tras rotar en el 2", r);
    cout << "    Ese subarbol bajo de altura 2 a 1 y ahora la raiz 5 quedo desbalanceada (fe=-2)." << endl;
    r = rotarIzquierda(r);
    ver("tras rotar en el 5", r);
    assert(esAVL(r));

    Nodo* r2 = eliminarAVL(construir(), 1);
    string s1, s2;
    preorden(r, s1); preorden(r2, s2);
    assert(s1 == s2 && rebalanceos == 2);
    cout << "    eliminarAVL(1) llega al mismo arbol con " << rebalanceos << " rebalanceos." << endl;
    liberar(r); liberar(r2);

    // ---------- Insercion: el mismo arbol ----------
    cout << "\nINSERCION DEL 13 EN EL MISMO ARBOL" << endl;
    r = construir();
    ver("inicial", r);
    r = insertarAVL(r, 13);
    ver("con el 13", r);
    assert(esAVL(r) && rebalanceos == 1 && alt(r) == 4);
    cout << "    " << rebalanceos << " rebalanceo en el 11: el subarbol recupera la altura de antes y arriba nadie lo nota." << endl;
    liberar(r);

    // ---------- Verificacion masiva ----------
    cout << "\nVERIFICACION" << endl;
    int maxInsercion = 0;
    vector<int> orden = {1,2,3,4,5,6,7};
    do {
        r = nullptr;
        for (int c : orden) {
            rebalanceos = 0;
            r = insertarAVL(r, c);
            maxInsercion = max(maxInsercion, rebalanceos);
        }
        assert(esAVL(r));
        liberar(r);
    } while (next_permutation(orden.begin(), orden.end()));
    cout << "  Las 5040 permutaciones de 1 a 7: maximo " << maxInsercion << " rebalanceo por insercion" << endl;

    mt19937 gen(40);
    maxInsercion = 0;
    int maxEliminacion = 0, conVarios = 0, eliminaciones = 0;
    vector<int> claves(200);
    iota(claves.begin(), claves.end(), 0);
    for (int vez = 0; vez < 50; vez++) {
        shuffle(claves.begin(), claves.end(), gen);
        r = nullptr;
        for (int c : claves) {
            rebalanceos = 0;
            r = insertarAVL(r, c);
            maxInsercion = max(maxInsercion, rebalanceos);
            assert(esAVL(r));
        }
        shuffle(claves.begin(), claves.end(), gen);
        for (int c : claves) {
            rebalanceos = 0;
            r = eliminarAVL(r, c);
            maxEliminacion = max(maxEliminacion, rebalanceos);
            if (rebalanceos >= 2) conVarios++;
            eliminaciones++;
            assert(esAVL(r));
        }
    }
    cout << "  50 arboles aleatorios de 200 claves: maximo " << maxInsercion << " rebalanceo por insercion" << endl;
    cout << "  y maximo " << maxEliminacion << " por eliminacion (" << conVarios << " de " << eliminaciones
         << " eliminaciones necesitaron 2 o mas)" << endl;
    return 0;
}
