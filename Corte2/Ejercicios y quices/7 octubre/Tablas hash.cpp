#include <iostream>
#include <list>
#include <string>
#include <vector>
using namespace std;

class TablaHash {
private:
    int cap;
    int n;
    vector<list<pair<string, string>>> cubetas;

public:
    TablaHash(int capacidad = 8) : cap(capacidad), n(0), cubetas(capacidad) {}

    int hashear(const string& clave) const {
        unsigned long long h = 0;
        for (unsigned char c : clave) h = (h * 31 + c) % cap;
        return (int)h;
    }

    void insertar(const string& clave, const string& valor) {
        int i;

        i = hashear(clave);
        for (auto& par : cubetas[i]) {
            if (par.first == clave) {
                par.second = valor;
                return;
            }
        }
        cubetas[i].push_back({clave, valor});
        n++;
    }

    bool buscar(const string& clave, string& salida) const {
        int i;

        i = hashear(clave);
        for (const auto& par : cubetas[i]) {
            if (par.first == clave) {
                salida = par.second;
                return true;
            }
        }
        return false;
    }

    bool eliminar(const string& clave) {
        int i;
        auto it = cubetas[0].begin();

        i = hashear(clave);
        for (it = cubetas[i].begin(); it != cubetas[i].end(); ++it) {
            if (it->first == clave) {
                cubetas[i].erase(it);
                n--;
                return true;
            }
        }
        return false;
    }

    double factorCarga() const {
        return (double)n / cap;
    }

    void imprimir() const {
        int i;
        int tamano;
        int cunetasVacias;

        cunetasVacias = 0;

        cout << "Capacidad: " << cap << ", Elementos: " << n << endl;
        cout << "Factor de carga: " << factorCarga() << endl << endl;

        for (i = 0; i < cap; i++) {
            tamano = cubetas[i].size();
            cout << "Cubeta " << i << ": " << tamano << " elementos";
            if (tamano > 0) {
                cout << " [";
                for (const auto& par : cubetas[i]) {
                    cout << par.first << ":" << par.second << " ";
                }
                cout << "]";
            } else {
                cunetasVacias++;
            }
            cout << endl;
        }
        cout << "\nCubetas vacías: " << cunetasVacias << endl;
    }
};

int main() {
    vector<pair<string, string>> codigos;
    string resultado;

    codigos = {
        {"REC-001", "Recaudos 1"},
        {"REC-002", "Recaudos 2"},
        {"REC-003", "Recaudos 3"},
        {"EQ-100", "Equipo 100"},
        {"EQ-101", "Equipo 101"},
        {"PA-007", "Pasivo 007"},
        {"PA-008", "Pasivo 008"},
        {"EST-42", "Estacionamiento 42"}
    };

    TablaHash tabla;

    for (const auto& cod : codigos) {
        tabla.insertar(cod.first, cod.second);
    }
    tabla.imprimir();
    
    //Buscar codigo que exista
    if (tabla.buscar("EQ-100", resultado)) {
        cout << "Encontrado: EQ-100 -> " << resultado << endl;
    }

    //Buscar codigo que no exista
    if (tabla.buscar("XX-999", resultado)) {
        cout << "Encontrado: XX-999 -> " << resultado << endl;
    } else {
        cout << "No encontrado: XX-999" << endl;
    }

    //Actualizar un codigo
    cout << "Antes: EQ-100 -> ";
    if (tabla.buscar("EQ-100", resultado)) {
        cout << resultado << endl;
    }
    tabla.insertar("EQ-100", "Equipo Actualizado");
    cout << "Después: EQ-100 -> ";
    if (tabla.buscar("EQ-100", resultado)) {
        cout << resultado << endl;
    }

    //Eliminar un codigo
    if (tabla.eliminar("PA-008")) {
        cout << "Eliminado: PA-008" << endl;
    }
    tabla.imprimir();

    cout << "Se pueden ver en la distribución: las cubetas con mas de 1 elemento tienen colisiones" << endl;

    return 0;
}
