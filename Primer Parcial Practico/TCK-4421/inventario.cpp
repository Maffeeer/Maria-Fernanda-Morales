// ============================================================
//  Cívica Software  ·  TCK-4421  ·  Severidad P2
//  Sistema: PrestaLab  —  El servicio consume memoria sin parar
//  Compile SIEMPRE con:
//     g++ -std=c++17 -fsanitize=address -g -o inventario inventario.cpp
// ============================================================
#include <iostream>
#include <string>
using namespace std;

class Equipo {
private:
    string codigo;
    int*   historial;      // kilos/usos registrados
    int    n;
public:
    Equipo(string c, int cantidad) : codigo(c), n(cantidad) {
        historial = new int[n];
        for (int i = 0; i < n; i++) historial[i] = 0;
    }
    // Faltaba el metodo delete para liberar memoria
    ~Equipo() {
        delete[] historial;
    }

    // Cambio: i < n - 1 ahora es i < n, antes dejaba fuera la posición n-1, por eso EQ-03 sumaba 7 en vez de 8
    void registrar(int i, int v) { if (i >= 0 && i < n) historial[i] = v; }
    int  total() const { int s = 0; for (int i = 0; i < n; i++) s += historial[i]; return s; }
    string getCodigo() const { return codigo; }
};

int* copiarTotales(Equipo** equipos, int cuantos) {
    int* copia = new int[cuantos];
    for (int i = 0; i < cuantos; i++) copia[i] = equipos[i]->total();
    return copia;
}

int main() {
    const int N = 3;
    Equipo** equipos = new Equipo*[N];
    equipos[0] = new Equipo("EQ-01", 4);
    equipos[1] = new Equipo("EQ-02", 4);
    equipos[2] = new Equipo("EQ-03", 4);

    equipos[0]->registrar(0, 5); equipos[0]->registrar(1, 3);
    equipos[1]->registrar(0, 9);
    equipos[2]->registrar(2, 7); equipos[2]->registrar(3, 1);

    int* totales = copiarTotales(equipos, N);
    int suma = 0;
    for (int i = 0; i < N; i++) {
        cout << equipos[i]->getCodigo() << ": " << totales[i] << endl;
        suma += totales[i];
    }
    cout << "SUMA=" << suma << endl;

    if (suma == 25)   // el codigo se DERIVA de los totales correctos
        cout << "TICKET CERRADO - codigo de cierre: 4421-"
             << totales[0] << totales[1] << totales[2] << suma << endl;

    delete[] totales;
    for (int i = 0; i < N; i++) delete equipos[i];
    delete[] equipos;

    return 0;
}
