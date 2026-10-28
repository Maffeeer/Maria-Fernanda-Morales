#include <iostream>
#include <string>
using namespace std;

struct Nodo {
    string dato;
    Nodo* izq;
    Nodo* der;
    Nodo(string d) : dato(d), izq(nullptr), der(nullptr) {}
};

void imprimirJerarquia(Nodo* nodo, int nivel) {
    if (nodo == nullptr) return;               // caso base
    cout << string(nivel * 2, ' ') << nodo->dato << endl;  // 1) raiz con sangria
    imprimirJerarquia(nodo->izq, nivel + 1);   // 2) izquierda
    imprimirJerarquia(nodo->der, nivel + 1);   // 3) derecha
}
void liberar(Nodo* n) {                        // postorden: borrar hijos antes que el padre
    if (n == nullptr) return;
    liberar(n->izq);
    liberar(n->der);
    delete n;
}

int main() {
    cout << "Catalogo del ejemplo" << endl << endl;
    Nodo* raiz = new Nodo("CATALOGO");
    raiz->izq = new Nodo("HERRAMIENTA");  raiz->der = new Nodo("LIBRO");
    raiz->izq->izq = new Nodo("TALADRO"); raiz->izq->der = new Nodo("SIERRA");
    raiz->der->izq = new Nodo("ARTE");    raiz->der->der = new Nodo("TECNICO");
    raiz->der->der->der = new Nodo("REDES");
    imprimirJerarquia(raiz, 0);
    cout << endl;

    cout << "Otro arbol" << endl << endl;
    Nodo* raizOtra = new Nodo("UNIVERSIDAD");
    raizOtra->izq = new Nodo("INGENIERIA");
    raizOtra->izq->der = new Nodo("SISTEMAS");
    raizOtra->izq->der->izq = new Nodo("ALGORITMOS");
    raizOtra->izq->der->der = new Nodo("REDES");
    imprimirJerarquia(raizOtra, 0);
    cout << endl;

    cout << "Arbol vacio:" << endl;
    imprimirJerarquia(nullptr, 0);             // no imprime nada
    cout << endl;

    liberar(raiz);                             // sin fugas de memoria
    liberar(raizOtra);
    return 0;
}
