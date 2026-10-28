#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Nodo {
    string dato;
    Nodo* izq;
    Nodo* der;
    Nodo(string d) : dato(d), izq(nullptr), der(nullptr) {}
};

void inorden(Nodo* n, vector<string>& s) {
    if (n == nullptr) return;
    inorden(n->izq, s);
    s.push_back(n->dato);
    inorden(n->der, s);
}
void espejo(Nodo* nodo) {
    if (nodo == nullptr) return;               // caso base
    swap(nodo->izq, nodo->der);                // 1) intercambiar hijos
    espejo(nodo->izq);                         // 2) espejar izquierda
    espejo(nodo->der);                         // 3) espejar derecha
}
void liberar(Nodo* n) {                        // postorden: borrar hijos antes que el padre
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
    cout << "Espejo del catalogo" << endl << endl;
    Nodo* raiz = new Nodo("CATALOGO");
    raiz->izq = new Nodo("HERRAMIENTA");  raiz->der = new Nodo("LIBRO");
    raiz->izq->izq = new Nodo("TALADRO"); raiz->izq->der = new Nodo("SIERRA");
    raiz->der->izq = new Nodo("ARTE");    raiz->der->der = new Nodo("TECNICO");
    raiz->der->der->der = new Nodo("REDES");

    vector<string> inordenOriginal;
    inorden(raiz, inordenOriginal);
    mostrar("Inorden original", inordenOriginal);

    espejo(raiz);

    vector<string> inordenEspejo;
    inorden(raiz, inordenEspejo);
    mostrar("Inorden espejo  ", inordenEspejo);
    cout << endl;

    vector<string> inordenInvertido(inordenOriginal.rbegin(), inordenOriginal.rend());
    bool esReverso = inordenEspejo == inordenInvertido;
    cout << "El inorden del espejo es el inorden original al reves: "
         << (esReverso ? "true" : "false") << endl;

    liberar(raiz);                             // sin fugas de memoria
    return 0;
}
