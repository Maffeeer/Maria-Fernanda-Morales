#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Nodo {
    string dato;
    Nodo* izq;
    Nodo* der;
    Nodo(string d) : dato(d), izq(nullptr), der(nullptr) {}
};

void preorden(Nodo* n, vector<string>& s) {
    if (n == nullptr) return;          // caso base
    s.push_back(n->dato);              // 1) raiz
    preorden(n->izq, s);               // 2) izquierda
    preorden(n->der, s);               // 3) derecha
}
void inorden(Nodo* n, vector<string>& s) {
    if (n == nullptr) return;
    inorden(n->izq, s);
    s.push_back(n->dato);
    inorden(n->der, s);
}
void postorden(Nodo* n, vector<string>& s) {
    if (n == nullptr) return;
    postorden(n->izq, s);
    postorden(n->der, s);
    s.push_back(n->dato);
}
int altura(Nodo* n) {
    if (n == nullptr) return -1;
    return 1 + max(altura(n->izq), altura(n->der));
}
int contar(Nodo* n) {
    if (n == nullptr) return 0;
    return 1 + contar(n->izq) + contar(n->der);
}
int contarHojas(Nodo* n) {
    if (n == nullptr) return 0;
    if (n->izq == nullptr && n->der == nullptr) return 1;
    return contarHojas(n->izq) + contarHojas(n->der);
}
vector<string> porNiveles(Nodo* raiz) {
    vector<string> s;
    if (raiz == nullptr) return s;
    queue<Nodo*> q; q.push(raiz);
    while (!q.empty()) {
        Nodo* n = q.front(); q.pop();
        s.push_back(n->dato);
        if (n->izq) q.push(n->izq);
        if (n->der) q.push(n->der);
    }
    return s;
}
void liberar(Nodo* n) {                // postorden: borrar hijos antes que el padre
    if (n == nullptr) return;
    liberar(n->izq);
    liberar(n->der);
    delete n;
}
void mostrar(const string& titulo, const vector<string>& v) {
    cout << titulo << ": ";
    for (size_t i = 0; i < v.size(); i++) {
        cout << v[i];
        if (i + 1 < v.size()) cout << " -> ";
    }
    cout << endl;
}

int main() {
    Nodo* raiz = new Nodo("CATALOGO");
    raiz->izq = new Nodo("HERRAMIENTA");  raiz->der = new Nodo("LIBRO");
    raiz->izq->izq = new Nodo("TALADRO"); raiz->izq->der = new Nodo("SIERRA");
    raiz->der->izq = new Nodo("ARTE");    raiz->der->der = new Nodo("TECNICO");
    raiz->der->der->der = new Nodo("REDES");

    vector<string> s;
    s.clear(); preorden(raiz, s);  mostrar("Preorden ", s);
    s.clear(); inorden(raiz, s);   mostrar("Inorden  ", s);
    s.clear(); postorden(raiz, s); mostrar("Postorden", s);
    mostrar("Niveles  ", porNiveles(raiz));
    cout << "nodos=" << contar(raiz) << "  hojas=" << contarHojas(raiz)
         << "  altura=" << altura(raiz) << endl;

    liberar(raiz);                 // sin fugas de memoria
    return 0;
}  