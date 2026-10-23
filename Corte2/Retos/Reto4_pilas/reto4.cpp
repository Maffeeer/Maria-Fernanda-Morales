#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <iomanip>

using namespace std;

template <typename T>
struct Nodo {
    T valor;
    Nodo* siguiente;

    Nodo(T v) : valor(v), siguiente(nullptr) {}
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
        if (estaVacia()) {
            throw runtime_error("Pila vacia");
        }
        Nodo<T>* temp = cima;
        T valor = cima->valor;
        cima = cima->siguiente;
        delete temp;
        return valor;
    }

    T obtenerCima() const {
        if (estaVacia()) {
            throw runtime_error("Pila vacia");
        }
        return cima->valor;
    }

    bool estaVacia() const {
        return cima == nullptr;
    }

    int tamanio() const {
        int contador = 0;
        Nodo<T>* actual = cima;
        while (actual != nullptr) {
            contador++;
            actual = actual->siguiente;
        }
        return contador;
    }
};

struct RegistroPrestamo {
    int idLibro;
    string usuario;
    string fecha;

    RegistroPrestamo(int id = 0, string u = "", string f = "")
        : idLibro(id), usuario(u), fecha(f) {}

    string toString() const {
        return "Prestamo(libro=" + to_string(idLibro) + ", usuario=" + usuario + ", fecha=" + fecha + ")";
    }
};

struct RegistroRecoleccion {
    string tipo;
    int cantidad;
    string ubicacion;

    RegistroRecoleccion(string t = "", int c = 0, string u = "")
        : tipo(t), cantidad(c), ubicacion(u) {}

    string toString() const {
        return "Recoleccion(tipo=" + tipo + ", cantidad=" + to_string(cantidad) + ", ubicacion=" + ubicacion + ")";
    }
};

struct RegistroMonitoria {
    string estudiante;
    string materia;
    string horario;

    RegistroMonitoria(string e = "", string m = "", string h = "")
        : estudiante(e), materia(m), horario(h) {}

    string toString() const {
        return "Monitoria(estudiante=" + estudiante + ", materia=" + materia + ", horario=" + horario + ")";
    }
};

void deshacerPrestamo(Pila<RegistroPrestamo>& pilaPrestamos) {
    cout << "Reto 1: Deshacer ultimo prestamo\n\n";

    if (pilaPrestamos.estaVacia()) {
        cout << "No hay prestamos para deshacer\n\n";
        return;
    }

    RegistroPrestamo prestamo = pilaPrestamos.desapilar();
    cout << "Prestamo deshecho: " << prestamo.toString() << "\n";
    cout << "Prestamos restantes en pila: " << pilaPrestamos.tamanio() << "\n\n";
}

void deshacerRecoleccion(Pila<RegistroRecoleccion>& pilaRecoleccion) {
    cout << "Reto 2: Deshacer ultima recoleccion\n\n";

    if (pilaRecoleccion.estaVacia()) {
        cout << "No hay recolecciones para deshacer\n\n";
        return;
    }

    RegistroRecoleccion recoleccion = pilaRecoleccion.desapilar();
    cout << "Recoleccion deshecha: " << recoleccion.toString() << "\n";
    cout << "Recolecciones restantes en pila: " << pilaRecoleccion.tamanio() << "\n\n";
}

void deshacerMonitoria(Pila<RegistroMonitoria>& pilaMonitoria) {
    cout << "Reto 3: Deshacer ultima asignacion de monitoria\n\n";

    if (pilaMonitoria.estaVacia()) {
        cout << "No hay monitorias para deshacer\n\n";
        return;
    }

    RegistroMonitoria monitoria = pilaMonitoria.desapilar();
    cout << "Monitoria deshecha: " << monitoria.toString() << "\n";
    cout << "Monitorias restantes en pila: " << pilaMonitoria.tamanio() << "\n\n";
}

int evaluarRPN(vector<string>& expresion) {
    cout << "Evaluando: ";
    for (const auto& token : expresion) {
        cout << token << " ";
    }
    cout << "\n";

    Pila<int> pila;
    set<string> operadores = {"+", "-", "*", "/"};

    for (const auto& token : expresion) {
        if (operadores.count(token)) {
            if (pila.tamanio() < 2) {
                cout << "Error: operandos insuficientes\n\n";
                return 0;
            }

            int b = pila.desapilar();
            int a = pila.desapilar();
            int resultado;

            if (token == "+") resultado = a + b;
            else if (token == "-") resultado = a - b;
            else if (token == "*") resultado = a * b;
            else if (token == "/") {
                if (b == 0) {
                    cout << "Error: division por cero\n\n";
                    return 0;
                }
                resultado = a / b;
            }

            pila.apilar(resultado);
        } else {
            try {
                int numero = stoi(token);
                pila.apilar(numero);
            } catch (...) {
                cout << "Error: token invalido " << token << "\n\n";
                return 0;
            }
        }
    }

    if (pila.tamanio() != 1) {
        cout << "Error: expresion invalida\n\n";
        return 0;
    }

    int resultado = pila.desapilar();
    cout << "Resultado: " << resultado << "\n\n";
    return resultado;
}

void pruebaUno() {
    cout << "Reto 1: Deshacer ultimo prestamo (Pila con nodos y punteros)\n\n";

    Pila<RegistroPrestamo> pilaPrestamos;

    cout << "Agregando prestamos a la pila:\n";
    pilaPrestamos.apilar(RegistroPrestamo(101, "Juan", "2024-10-20"));
    cout << "  Prestamo(libro=101, usuario=Juan, fecha=2024-10-20)\n";
    pilaPrestamos.apilar(RegistroPrestamo(102, "Maria", "2024-10-21"));
    cout << "  Prestamo(libro=102, usuario=Maria, fecha=2024-10-21)\n";
    pilaPrestamos.apilar(RegistroPrestamo(103, "Pedro", "2024-10-22"));
    cout << "  Prestamo(libro=103, usuario=Pedro, fecha=2024-10-22)\n";
    cout << "Total prestamos: " << pilaPrestamos.tamanio() << "\n\n";

    deshacerPrestamo(pilaPrestamos);
}

void pruebaDos() {
    cout << "Reto 2: Deshacer ultima recoleccion (Pila con nodos y punteros)\n\n";

    Pila<RegistroRecoleccion> pilaRecoleccion;

    cout << "Agregando recolecciones a la pila:\n";
    pilaRecoleccion.apilar(RegistroRecoleccion("Plastico", 50, "Almacen A"));
    cout << "  Recoleccion(tipo=Plastico, cantidad=50, ubicacion=Almacen A)\n";
    pilaRecoleccion.apilar(RegistroRecoleccion("Vidrio", 30, "Almacen B"));
    cout << "  Recoleccion(tipo=Vidrio, cantidad=30, ubicacion=Almacen B)\n";
    pilaRecoleccion.apilar(RegistroRecoleccion("Metal", 25, "Almacen C"));
    cout << "  Recoleccion(tipo=Metal, cantidad=25, ubicacion=Almacen C)\n";
    cout << "Total recolecciones: " << pilaRecoleccion.tamanio() << "\n\n";

    deshacerRecoleccion(pilaRecoleccion);
}

void pruebaTres() {
    cout << "Reto 3: Deshacer ultima asignacion de monitoria (Pila con nodos y punteros)\n\n";

    Pila<RegistroMonitoria> pilaMonitoria;

    cout << "Agregando monitorias a la pila:\n";
    pilaMonitoria.apilar(RegistroMonitoria("Ana", "Algoritmos", "Lunes 2-3pm"));
    cout << "  Monitoria(estudiante=Ana, materia=Algoritmos, horario=Lunes 2-3pm)\n";
    pilaMonitoria.apilar(RegistroMonitoria("Luis", "Estructuras", "Martes 3-4pm"));
    cout << "  Monitoria(estudiante=Luis, materia=Estructuras, horario=Martes 3-4pm)\n";
    pilaMonitoria.apilar(RegistroMonitoria("Sofia", "BD", "Miercoles 4-5pm"));
    cout << "  Monitoria(estudiante=Sofia, materia=BD, horario=Miercoles 4-5pm)\n";
    cout << "Total monitorias: " << pilaMonitoria.tamanio() << "\n\n";

    deshacerMonitoria(pilaMonitoria);
}

void pruebaRPN() {
    cout << "Reto 4: Evaluar expresiones en Notacion Polaca Inversa\n\n";

    vector<vector<string>> expresiones = {
        {"3", "4", "+"},
        {"10", "5", "-"},
        {"6", "7", "*"},
        {"20", "4", "/"},
        {"3", "4", "+", "2", "*"},
        {"15", "7", "1", "+", "/"}
    };

    for (auto& expr : expresiones) {
        evaluarRPN(expr);
    }
}

int main() {
    pruebaUno();
    pruebaDos();
    pruebaTres();
    pruebaRPN();

    cout << "CONCLUSIONES\n";
    cout << "- Pila con nodos y punteros permite apilar y desapilar en O(1)\n";
    cout << "- Operacion deshacer es reversible usando una pila\n";
    cout << "- Notacion Polaca Inversa (RPN) se evalua eficientemente con una pila\n";
    cout << "- La pila es la estructura ideal para operaciones LIFO\n";

    return 0;
}
