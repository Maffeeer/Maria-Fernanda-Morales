// ============================================================
//  sistema.h — DECLARACIONES DEL SISTEMA.  NO MODIFIQUE ESTE ARCHIVO.
// ============================================================
#pragma once
#include <string>
#include <vector>
#include <utility>

// Un punto del sistema. Guarda un arreglo DINAMICO de mediciones.
struct Punto {
    int          codigo;
    std::string  nombre;
    int*         mediciones;   // arreglo de 'nm' posiciones pedido con new[]
    int          nm;
    Punto*       sig;          // siguiente en la lista ORDENADA por codigo

    Punto(int c, const std::string& n, int cantidad);
    ~Punto();
    int total() const;
};

// Nodo del indice. NO duplica la informacion: apunta al nodo de la lista.
struct NodoIndice {
    int          codigo;
    Punto*       dato;
    NodoIndice*  izq;
    NodoIndice*  der;
    NodoIndice(int c, Punto* p);
};

class Sistema {
public:
    Punto*      lista;    // lista enlazada ordenada ascendente por codigo
    NodoIndice* indice;   // arbol binario de busqueda sobre los mismos codigos
    int*        cola;     // arreglo CIRCULAR de codigos por atender
    int         cap, frente, enCola;
    std::vector<std::vector<int>>   red;       // lista de adyacencia (ya construida)
    std::vector<std::pair<int,int>> aristas;   // las mismas vias, como pares

    Sistema(int capacidadCola, const std::vector<std::pair<int,int>>& vias, int vertices);
    ~Sistema();

    // ---------- PARTE A · memoria, lista enlazada e indice ----------
    bool registrar(int codigo, const std::string& nombre, int cantidad);
    void liberarTodo();

    // ---------- PARTE B · consultas sobre el indice ----------
    Punto*            buscar(int codigo) const;
    int               alturaIndice() const;
    std::vector<int>  enRango(int a, int b) const;

    // ---------- PARTE C · cola circular de atencion ----------
    void ampliarCola();

    // ---------- PARTE D · la red de puntos ----------
    std::vector<int>          rutaMinima(int origen, int destino) const;
    std::vector<std::string>  viasCriticas() const;

    // ---------- PARTE E · seleccion optima ----------
    std::vector<int> mejorSeleccion(int capacidad) const;

    // ---------- ya implementados: puede usarlos ----------
    bool        encolar(int codigo);
    bool        siguiente(int& codigo);
    std::string enEspera() const;
    int         cuantos() const;
    std::string codigos() const;
    void        medir(int codigo, int i, int valor);
    int         sumaTotales() const;
};
