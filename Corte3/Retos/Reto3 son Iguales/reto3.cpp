    // Reto 3 - Son iguales?
    // Dos arboles son iguales si tienen la misma forma Y los mismos
    // datos en las mismas posiciones.
    #include <iostream>
    #include <string>
    #include <algorithm>
    using namespace std;

    struct Nodo {
        string dato;
        Nodo* izq;
        Nodo* der;
        Nodo(string d) : dato(d), izq(nullptr), der(nullptr) {}
    };

    bool sonIguales(Nodo* a, Nodo* b) {
        if (a == nullptr && b == nullptr) return true;   // caso base: los dos vacios
        if (a == nullptr || b == nullptr) return false;  // distinta forma
        if (a->dato != b->dato) return false;            // 1) misma raiz
        return sonIguales(a->izq, b->izq) && sonIguales(a->der, b->der);  // 2) y 3) mismos hijos
    }
    Nodo* copiar(Nodo* nodo) {
        if (nodo == nullptr) return nullptr;
        Nodo* nuevoNodo = new Nodo(nodo->dato);          // preorden: copiar la raiz primero
        nuevoNodo->izq = copiar(nodo->izq);
        nuevoNodo->der = copiar(nodo->der);
        return nuevoNodo;
    }
    void espejo(Nodo* nodo) {
        if (nodo == nullptr) return;
        swap(nodo->izq, nodo->der);
        espejo(nodo->izq);
        espejo(nodo->der);
    }
    void liberar(Nodo* n) {                              // postorden: borrar hijos antes que el padre
        if (n == nullptr) return;
        liberar(n->izq);
        liberar(n->der);
        delete n;
    }
    Nodo* construirCatalogo() {
        Nodo* raiz = new Nodo("CATALOGO");
        raiz->izq = new Nodo("HERRAMIENTA");  raiz->der = new Nodo("LIBRO");
        raiz->izq->izq = new Nodo("TALADRO"); raiz->izq->der = new Nodo("SIERRA");
        raiz->der->izq = new Nodo("ARTE");    raiz->der->der = new Nodo("TECNICO");
        raiz->der->der->der = new Nodo("REDES");
        return raiz;
    }
    string texto(bool valor) { return valor ? "true" : "false"; }

    int main() {
        cout << "Original contra su propio espejo" << endl << endl;
        Nodo* raiz = construirCatalogo();
        Nodo* raizEspejo = copiar(raiz);                 // se copia para no perder el original
        espejo(raizEspejo);
        cout << "sonIguales(original, espejo): " << texto(sonIguales(raiz, raizEspejo)) << endl << endl;

        cout << "Casos de control" << endl << endl;
        Nodo* raizCopia = copiar(raiz);
        cout << "sonIguales(original, copia)        : " << texto(sonIguales(raiz, raizCopia)) << endl;

        Nodo* raizCambiada = copiar(raiz);
        liberar(raizCambiada->der->der->der);            // quitar REDES: cambia la forma
        raizCambiada->der->der->der = nullptr;
        cout << "sonIguales(original, sin REDES)    : " << texto(sonIguales(raiz, raizCambiada)) << endl;

        Nodo* raizOtroDato = copiar(raiz);
        raizOtroDato->izq->izq->dato = "MARTILLO";       // misma forma, distinto dato
        cout << "sonIguales(original, con MARTILLO) : " << texto(sonIguales(raiz, raizOtroDato)) << endl;

        cout << "sonIguales(vacio, vacio)           : " << texto(sonIguales(nullptr, nullptr)) << endl << endl;

        cout << "Arbol simetrico" << endl << endl;
        Nodo* raizSimetrica = new Nodo("A");
        raizSimetrica->izq = new Nodo("B"); raizSimetrica->der = new Nodo("B");
        Nodo* simetricaEspejo = copiar(raizSimetrica);
        espejo(simetricaEspejo);
        cout << "sonIguales(simetrico, espejo): " << texto(sonIguales(raizSimetrica, simetricaEspejo)) << endl;

        liberar(raiz);                                   // sin fugas de memoria
        liberar(raizEspejo);
        liberar(raizCopia);
        liberar(raizCambiada);
        liberar(raizOtroDato);
        liberar(raizSimetrica);
        liberar(simetricaEspejo);
        return 0;
    }
