#include <string>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>
#include "sistema.h"
using namespace std;

// ============================================================
//   BASE YA RESUELTA — lea estas funciones: son su punto de partida
//   y muestran el estilo con el que debe escribir las que faltan.
//   En la mesa se le puede preguntar por cualquiera de ellas.
// ============================================================

Punto::Punto(int c, const string& n, int cantidad) {
    codigo = c;
    nombre = n;
    nm = cantidad;
    mediciones = new int[nm];              // memoria dinamica
    for (int i = 0; i < nm; i++) mediciones[i] = 0;
    sig = nullptr;
}

int Punto::total() const {
    int s = 0;
    for (int i = 0; i < nm; i++) s += mediciones[i];
    return s;
}

NodoIndice::NodoIndice(int c, Punto* p) {
    codigo = c; dato = p; izq = nullptr; der = nullptr;
}

Sistema::Sistema(int capacidadCola, const vector<pair<int,int>>& vias, int vertices) {
    lista  = nullptr;
    indice = nullptr;
    cap    = capacidadCola;
    cola   = new int[cap];
    frente = 0;
    enCola = 0;
    aristas = vias;
    red.assign(vertices, {});
    for (size_t i = 0; i < vias.size(); i++) {
        red[vias[i].first ].push_back(vias[i].second);
        red[vias[i].second].push_back(vias[i].first);
    }
    for (size_t i = 0; i < red.size(); i++) sort(red[i].begin(), red[i].end());
}

Sistema::~Sistema() {
    liberarTodo();                         // usted escribe liberarTodo()
    delete[] cola;
}

bool Sistema::encolar(int codigo) {
    if (enCola == cap) return false;                 // desbordamiento controlado
    cola[(frente + enCola) % cap] = codigo;          // el final se CALCULA
    enCola++;
    return true;
}

bool Sistema::siguiente(int& codigo) {
    if (enCola == 0) return false;                   // subdesbordamiento
    codigo = cola[frente];
    frente = (frente + 1) % cap;
    enCola--;
    return true;
}

string Sistema::enEspera() const {
    string r;
    for (int i = 0; i < enCola; i++) {
        if (i > 0) r += " ";
        r += to_string(cola[(frente + i) % cap]);
    }
    return r;
}

int Sistema::cuantos() const {
    int k = 0;
    for (Punto* a = lista; a != nullptr; a = a->sig) k++;
    return k;
}

string Sistema::codigos() const {
    string r;
    for (Punto* a = lista; a != nullptr; a = a->sig) {
        if (!r.empty()) r += " ";
        r += to_string(a->codigo);
    }
    return r;
}

void Sistema::medir(int codigo, int i, int valor) {
    Punto* p = buscar(codigo);                       // usa SU buscar()
    if (p == nullptr) return;
    if (i < 0 || i >= p->nm) return;                 // indice fuera de rango
    p->mediciones[i] = valor;
}

int Sistema::sumaTotales() const {
    int s = 0;
    for (Punto* a = lista; a != nullptr; a = a->sig) s += a->total();
    return s;
}
// ------------------------------------------------------------
//   Estas cinco funciones TAMBIEN se le entregan resueltas.
//   Lealas: son el modelo de lo que usted debe escribir, y en la
//   mesa se le puede preguntar por cualquiera de ellas.
// ------------------------------------------------------------

Punto* Sistema::buscar(int codigo) const {
    NodoIndice* n = indice;                 // DESCIENDE por el indice:
    while (n != nullptr) {                  // no recorre la lista
        if (codigo == n->codigo) return n->dato;
        n = (codigo < n->codigo) ? n->izq : n->der;
    }
    return nullptr;
}

static int altura(NodoIndice* n) {
    if (n == nullptr) return -1;
    return 1 + max(altura(n->izq), altura(n->der));
}

int Sistema::alturaIndice() const { return altura(indice); }

static void borrarIndice(NodoIndice* n) {
    if (n == nullptr) return;
    borrarIndice(n->izq);
    borrarIndice(n->der);
    delete n;                      // NO se borra n->dato: es de la lista
}

void Sistema::liberarTodo() {
    Punto* a = lista;
    while (a != nullptr) {
        Punto* s = a->sig;         // guardar el siguiente ANTES de borrar
        delete a;
        a = s;
    }
    lista = nullptr;
    borrarIndice(indice);
    indice = nullptr;
}

void Sistema::ampliarCola() {
    int* nueva = new int[cap * 2];
    for (int i = 0; i < enCola; i++)
        nueva[i] = cola[(frente + i) % cap];        // en ORDEN DE SALIDA
    delete[] cola;
    cola = nueva;
    cap *= 2;
    frente = 0;
}

static int componentes(const vector<vector<int>>& g) {
    int V = (int)g.size();
    vector<bool> vis(V, false);
    int c = 0;
    for (int s = 0; s < V; s++) {
        if (vis[s]) continue;
        c++;
        vector<int> pila;                      // recorrido en PROFUNDIDAD
        pila.push_back(s); vis[s] = true;
        while (!pila.empty()) {
            int u = pila.back(); pila.pop_back();
            for (size_t t = 0; t < g[u].size(); t++)
                if (!vis[g[u][t]]) { vis[g[u][t]] = true; pila.push_back(g[u][t]); }
        }
    }
    return c;
}

vector<string> Sistema::viasCriticas() const {
    vector<string> out;
    int V = (int)red.size();
    for (size_t i = 0; i < aristas.size(); i++) {
        vector<vector<int>> g(V);
        for (size_t j = 0; j < aristas.size(); j++) {
            if (j == i) continue;
            g[aristas[j].first ].push_back(aristas[j].second);
            g[aristas[j].second].push_back(aristas[j].first);
        }
        if (componentes(g) > 1)
            out.push_back(to_string(aristas[i].first) + "-" + to_string(aristas[i].second));
    }
    return out;
}

// ============================================================
//   LO QUE USTED DEBE COMPLETAR
//   Son SEIS funciones: cinco aqui y una en analisis.py.
//   Estan acopladas: medir() usa buscar(), buscar() usa el indice que
//   construye registrar(), y mejorSeleccion() usa total().
//   Si registrar() queda mal, falla casi todo lo demas: empiece por ahi.
// ============================================================

// ---------------- PARTE A · memoria, lista e indice ----------------

Punto::~Punto() {
    // (6 puntos) El constructor pidio memoria con new[]. Devuelvala.
    // PENDIENTE
    delete[] mediciones;
}

bool Sistema::registrar(int codigo, const string& nombre, int cantidad) {
    // (24 puntos) ESTA ES LA FUNCION CENTRAL DEL PARCIAL.
    //
    // Debe hacer TRES cosas, y las tres tienen que quedar coherentes:
    //   1. Si el codigo ya existe, no registrar nada y devolver false.
    //      Tiene buscar() ya resuelta para averiguarlo.
    //   2. Crear el Punto e insertarlo en 'lista' manteniendola ORDENADA
    //      de forma ascendente por codigo. Contemple los tres casos:
    //      lista vacia, insercion antes de la cabeza, e insercion en el
    //      medio o al final.
    //   3. Insertar en 'indice' un NodoIndice con ese codigo que APUNTE
    //      al Punto que acabo de crear. El arbol es un BST por codigo.
    //      Puede escribir una funcion auxiliar libre en este archivo.
    //
    // El indice NO duplica la informacion: guarda un puntero al mismo
    // Punto que esta en la lista. Si inserta una copia, medir() escribira
    // en un sitio y total() leera de otro, y el sistema queda incoherente
    // sin dar un solo error de compilacion.
    //
    // PENDIENTE

    // 1. Si el codigo ya existe, no registrar nada y devolver false.
    if (buscar(codigo) != nullptr) {
    return false;
    }

    // 2. Crear el Punto e insertarlo en 'lista' manteniendola ORDENADA
    Punto* nuevoPunto = new Punto(codigo, nombre, cantidad);
    if (lista == nullptr || codigo < lista->codigo) {
        nuevoPunto->sig = lista;
        lista = nuevoPunto;
    } else {
        Punto* actual = lista;
        while (actual->sig != nullptr && actual->sig->codigo < codigo) {
            actual = actual->sig;
        }
        nuevoPunto->sig = actual->sig;
        actual->sig = nuevoPunto;
    }
    // 3. Insertar en 'indice' un NodoIndice con ese codigo que APUNTE al Punto que acabo de crear.
    NodoIndice* nuevoNodo = new NodoIndice(codigo, nuevoPunto);
    if (indice == nullptr) {
        indice = nuevoNodo;
    } else {
        NodoIndice* actual = indice;
        while (true) {
            if (codigo < actual->codigo) {
                if (actual->izq == nullptr) {
                    actual->izq = nuevoNodo;
                    break;
                } else {
                    actual = actual->izq;
                }
            } else {
                if (actual->der == nullptr) {
                    actual->der = nuevoNodo;
                    break;
                } else {
                    actual = actual->der;
                }
            }
        }
    }
    return true;
}


// ---------------- PARTE B · consultas sobre el indice ----------------

vector<int> Sistema::enRango(int a, int b) const {
    // (14 puntos) Devuelve los codigos entre a y b, ambos incluidos,
    // en orden ASCENDENTE.
    //
    // No recorra todo el arbol para filtrar despues: PODE. Si el codigo
    // del nodo ya es menor o igual que a, no tiene sentido bajar por la
    // izquierda; si ya es mayor o igual que b, no tiene sentido bajar por
    // la derecha. La pregunta de la mesa es exactamente sobre esto.
    // PENDIENTE

    vector<int> codigosEnRango;
    function<void(NodoIndice*)> recorrer = [&](NodoIndice* nodo) { // nodoIndice no duplica la informacion, guarda un puntero al mismo Punto que esta en la lista
        
        if (nodo == nullptr) return;
        if (nodo->codigo > a) {
            recorrer(nodo->izq);
        }
        if (nodo->codigo >= a && nodo->codigo <= b) {
            codigosEnRango.push_back(nodo->codigo);
        }
        if (nodo->codigo < b) {
            recorrer(nodo->der);
        }
    };
    recorrer(indice);
    return codigosEnRango;
}


// ---------------- PARTE D · la red de puntos ----------------

vector<int> Sistema::rutaMinima(int origen, int destino) const {
    // (14 puntos) Devuelve la ruta con MENOS tramos entre los dos
    // vertices, como la secuencia de vertices desde 'origen' hasta
    // 'destino', ambos incluidos. Si no hay camino, devuelve un vector
    // vacio. Si origen == destino, devuelve {origen}.
    //
    // Use 'red', que ya esta construida. Recuerde que el recorrido que
    // garantiza el minimo numero de tramos es el de ANCHURA, y que para
    // reconstruir la ruta hace falta recordar de donde se llego a cada
    // vertice. Tiene viasCriticas() resuelta como ejemplo de recorrido
    // sobre la misma red.
    // PENDIENTE

    int V = static_cast<int>(red.size());
    if (origen < 0 || origen >= V || destino < 0 || destino >= V) {
        return {};
    }
    if (origen == destino) {
        return {origen};
    }

    vector<int> padre(V, -1);
    vector<bool> visitado(V, false);
    queue<int> pendientes;
    pendientes.push(origen);
    visitado[origen] = true;

    while (!pendientes.empty()) {
        int actual = pendientes.front();
        pendientes.pop();

        for (int siguiente : red[actual]) {
            if (visitado[siguiente]) continue;
            visitado[siguiente] = true;
            padre[siguiente] = actual;
            if (siguiente == destino) {
                vector<int> ruta;
                for (int v = destino; v != -1; v = padre[v]) {
                    ruta.push_back(v);
                }
                reverse(ruta.begin(), ruta.end());
                return ruta;
            }
            pendientes.push(siguiente);
        }
    }
    return {};
}


// ---------------- PARTE E · seleccion optima ----------------

vector<int> Sistema::mejorSeleccion(int capacidad) const {
    // (12 puntos) El vehiculo soporta 'capacidad' mediciones en total.
    // Cada punto ocupa 'nm' y aporta 'total()'. Cada punto se lleva o no
    // se lleva: no se parte ni se repite.
    //
    // Devuelva los CODIGOS de la seleccion de mayor aporte total que no
    // pase de la capacidad, en orden ascendente. Si hay empate en aporte,
    // la de MENOS puntos.
    //
    // Resuelvalo con recursion de tomar / no tomar, y pode la rama de
    // tomar cuando el punto ya no quepa.
    // PENDIENTE

    vector<int> seleccion;
    vector<int> mejorSeleccion;
    int mejorAporte = 0;
    function<void(Punto*, int, int)> backtrack = [&](Punto* p, int capacidadRestante, int aporteActual) { // Function its undefined, but it is a lambda function that takes a Punto pointer, an int for remaining capacity, and an int for current contribution
        if (p == nullptr) {
            if (aporteActual > mejorAporte || (aporteActual == mejorAporte && seleccion.size() < mejorSeleccion.size())) {
                mejorAporte = aporteActual;
                mejorSeleccion = seleccion;
            }
            return;
        }
        // No tomar el punto actual
        backtrack(p->sig, capacidadRestante, aporteActual);
        // Tomar el punto actual si cabe
        if (capacidadRestante >= p->nm) {
            seleccion.push_back(p->codigo);
            backtrack(p->sig, capacidadRestante - p->nm, aporteActual + p->total());
            seleccion.pop_back();
        }
    };
    backtrack(lista, capacidad, 0);
    sort(mejorSeleccion.begin(), mejorSeleccion.end());
    return mejorSeleccion;  
}

