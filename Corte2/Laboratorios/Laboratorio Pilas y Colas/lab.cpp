#include <iostream>
#include <map>
#include <string>
using namespace std;

template <typename T>
struct Nodo {
    T valor;
    Nodo* siguiente;
    Nodo(T v) : valor(v), siguiente(nullptr) {}
};

template <typename T>
class Cola {
private:
    Nodo<T>* frente;
    Nodo<T>* cola;
    int tamanio_actual;

public:
    Cola() : frente(nullptr), cola(nullptr), tamanio_actual(0) {}

    ~Cola() {
        while (!estaVacia()) {
            desencolar();
        }
    }

    void encolar(T valor) {
        Nodo<T>* nuevoNodo = new Nodo<T>(valor);
        if (estaVacia()) {
            frente = nuevoNodo;
            cola = nuevoNodo;
        } else {
            cola->siguiente = nuevoNodo;
            cola = nuevoNodo;
        }
        tamanio_actual++;
    }

    T desencolar() {
        if (estaVacia()) throw runtime_error("Cola vacia");
        T valor = frente->valor;
        Nodo<T>* temp = frente;
        frente = frente->siguiente;
        tamanio_actual--;
        if (estaVacia()) cola = nullptr;
        delete temp;
        return valor;
    }

    T consultarFrente() {
        if (estaVacia()) throw runtime_error("Cola vacia");
        return frente->valor;
    }

    bool estaVacia() const {
        return frente == nullptr;
    }

    int tamanio() const {
        return tamanio_actual;
    }
};

template <typename T>
class Pila {
private:
    Nodo<T>* cima;

public:
    Pila() : cima(nullptr) {}

    ~Pila() {
        while (!estaVacia()) {
            desapilar();
        }
    }

    void apilar(T valor) {
        Nodo<T>* nuevoNodo = new Nodo<T>(valor);
        nuevoNodo->siguiente = cima;
        cima = nuevoNodo;
    }

    T desapilar() {
        if (estaVacia()) throw runtime_error("Pila vacia");
        T valor = cima->valor;
        Nodo<T>* temp = cima;
        cima = cima->siguiente;
        delete temp;
        return valor;
    }

    bool estaVacia() const {
        return cima == nullptr;
    }
};

struct Operacion {
    string tipo;
    string recurso;
    int cantidad;

    Operacion(string t, string r, int c) : tipo(t), recurso(r), cantidad(c) {}

    string toString() const {
        return tipo + "(" + recurso + ", " + to_string(cantidad) + ")";
    }
};

void pruebaColaBasica() {
    cout << "Parte A - Cola de Atencion\n";
    cout << string(70, '=') << "\n\n";

    Cola<int> cola;

    cout << "Encolando: 101, 102, 103, 104, 105\n";
    for (int i = 101; i <= 105; i++) {
        cola.encolar(i);
    }

    cout << "Tamanio: " << cola.tamanio() << "\n";
    cout << "Frente: " << cola.consultarFrente() << "\n\n";

    cout << "Desencolar 3 elementos:\n";
    for (int i = 0; i < 3; i++) {
        cout << "  Desencolar: " << cola.desencolar() << "\n";
    }

    cout << "Tamanio: " << cola.tamanio() << "\n";
    cout << "Frente: " << cola.consultarFrente() << "\n\n";
}

void pruebaCasoVacio() {
    cout << "Prueba Especial - Vaciar y Volver a Encolar\n";
    cout << string(70, '=') << "\n\n";

    Cola<int> cola;

    cout << "Encolando: 10, 20, 30\n";
    for (int val : {10, 20, 30}) {
        cola.encolar(val);
    }

    cout << "Tamanio: " << cola.tamanio() << "\n\n";

    cout << "Vaciando completamente:\n";
    while (!cola.estaVacia()) {
        cout << "  Desencolar: " << cola.desencolar() << "\n";
    }

    cout << "Cola vacia: " << (cola.estaVacia() ? "true" : "false") << "\n";
    cout << "Tamanio: " << cola.tamanio() << "\n\n";

    cout << "Volviendo a encolar: 40, 50, 60\n";
    for (int val : {40, 50, 60}) {
        cola.encolar(val);
    }

    cout << "Tamanio: " << cola.tamanio() << "\n";
    cout << "Frente: " << cola.consultarFrente() << "\n\n";
}

void pruebaDeshacer() {
    cout << "Parte B - Deshacer Operaciones\n";
    cout << string(70, '=') << "\n\n";

    map<string, int> recursos;
    recursos["Libros"] = 50;
    recursos["Computadoras"] = 10;
    recursos["Aulas"] = 5;

    Pila<Operacion> pilaOperaciones;

    cout << "Estado inicial de recursos:\n";
    for (auto& p : recursos) {
        cout << "  " << p.first << ": " << p.second << "\n";
    }
    cout << "\n";

    cout << "Operaciones realizadas:\n";

    Operacion op1("Prestamo", "Libros", 5);
    pilaOperaciones.apilar(op1);
    recursos["Libros"] -= 5;
    cout << "  " << op1.toString() << " -> Libros: " << recursos["Libros"] << "\n";

    Operacion op2("Prestamo", "Computadoras", 2);
    pilaOperaciones.apilar(op2);
    recursos["Computadoras"] -= 2;
    cout << "  " << op2.toString() << " -> Computadoras: " << recursos["Computadoras"] << "\n";

    Operacion op3("Prestamo", "Aulas", 1);
    pilaOperaciones.apilar(op3);
    recursos["Aulas"] -= 1;
    cout << "  " << op3.toString() << " -> Aulas: " << recursos["Aulas"] << "\n\n";

    cout << "Estado actual de recursos:\n";
    for (auto& p : recursos) {
        cout << "  " << p.first << ": " << p.second << "\n";
    }
    cout << "\n";

    cout << "Deshaciendo operaciones (orden inverso):\n";
    while (!pilaOperaciones.estaVacia()) {
        Operacion op = pilaOperaciones.desapilar();
        recursos[op.recurso] += op.cantidad;
        cout << "  Deshacer " << op.toString() << " -> " << op.recurso << ": " << recursos[op.recurso] << "\n";
    }

    cout << "\n";
    cout << "Estado final despues de deshacer:\n";
    for (auto& p : recursos) {
        cout << "  " << p.first << ": " << p.second << "\n";
    }
    cout << "\n";
}

int main() {
    pruebaColaBasica();
    pruebaCasoVacio();
    pruebaDeshacer();
    return 0;
}
