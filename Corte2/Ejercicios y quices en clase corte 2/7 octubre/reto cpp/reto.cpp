#include <iostream>
#include <list>
#include <string>
#include <vector>
using namespace std;

class TablaHashBuena {
private:
    int cap;
    int n;
    vector<list<pair<string, string>>> cubetas;

public:
    TablaHashBuena(int capacidad = 8) : cap(capacidad), n(0), cubetas(capacidad) {}

    int hashear(const string& clave) const {
        unsigned long long h = 0;
        for (unsigned char c : clave) h = (h * 31 + c) % cap;
        return (int)h;
    }

    double factorCarga() const {
        return (double)n / cap;
    }

    void redimensionar() {
        vector<list<pair<string, string>>> viejas;

        viejas = cubetas;
        cap *= 2;
        cubetas.assign(cap, list<pair<string, string>>());
        n = 0;
        for (const auto& cubeta : viejas) {
            for (const auto& par : cubeta) {
                insertar(par.first, par.second);
            }
        }
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
        if (factorCarga() > 0.75) {
            redimensionar();
        }
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

    void imprimir() const {
        int cunetasVacias;
        int maxTamano;
        int maxIndice;
        int i;
        int tamano;

        cunetasVacias = 0;
        maxTamano = 0;
        maxIndice = -1;

        cout << "\nCapacidad final: " << cap << endl;
        cout << "Elementos: " << n << endl;
        cout << "Factor de carga: " << factorCarga() << endl;

        cout << "\nDistribución:" << endl;
        for (i = 0; i < cap; i++) {
            tamano = cubetas[i].size();
            cout << "Cubeta " << i << ": " << tamano << endl;
            if (tamano == 0) {
                cunetasVacias++;
            } else {
                if (tamano > maxTamano) {
                    maxTamano = tamano;
                    maxIndice = i;
                }
            }
        }

        cout << "\nCubeta más llena: " << maxIndice << " con " << maxTamano << " elementos" << endl;
        cout << "Cubetas vacías: " << cunetasVacias << endl;
    }
};

class TablaHashMala {
private:
    int cap;
    int n;
    vector<list<pair<string, string>>> cubetas;

public:
    TablaHashMala(int capacidad = 8) : cap(capacidad), n(0), cubetas(capacidad) {}

    int hashear(const string& clave) const {
        int suma;
        int i;

        suma = 0;
        for (i = 0; i < 4 && i < (int)clave.length(); i++) {
            suma += (int)clave[i];
        }
        return suma % cap;
    }

    double factorCarga() const {
        return (double)n / cap;
    }

    void redimensionar() {
        vector<list<pair<string, string>>> viejas;

        viejas = cubetas;
        cap *= 2;
        cubetas.assign(cap, list<pair<string, string>>());
        n = 0;
        for (const auto& cubeta : viejas) {
            for (const auto& par : cubeta) {
                insertar(par.first, par.second);
            }
        }
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
        if (factorCarga() > 0.75) {
            redimensionar();
        }
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

    void imprimir() const {
        int cunetasVacias;
        int maxTamano;
        int maxIndice;
        int i;
        int tamano;

        cunetasVacias = 0;
        maxTamano = 0;
        maxIndice = -1;

        cout << "\nCapacidad final: " << cap << endl;
        cout << "Elementos: " << n << endl;
        cout << "Factor de carga: " << factorCarga() << endl;

        cout << "\nDistribución:" << endl;
        for (i = 0; i < cap; i++) {
            tamano = cubetas[i].size();
            cout << "Cubeta " << i << ": " << tamano << endl;
            if (tamano == 0) {
                cunetasVacias++;
            } else {
                if (tamano > maxTamano) {
                    maxTamano = tamano;
                    maxIndice = i;
                }
            }
        }

        cout << "\nCubeta más llena: " << maxIndice << " con " << maxTamano << " elementos" << endl;
        cout << "Cubetas vacías: " << cunetasVacias << endl;
    }
};

int main() {
    vector<pair<string, string>> estudiantes;
    string resultado;

    estudiantes = {
        {"EST-2026-0101", "Ana Torres"},
        {"EST-2026-0102", "Carlos Rojas"},
        {"EST-2026-0103", "Diego Pardo"},
        {"EST-2026-0104", "Sofia Mejia"},
        {"EST-2026-0105", "Juan Gomez"},
        {"EST-2026-0106", "Maria Lopez"},
        {"EST-2026-0107", "Pedro Ruiz"},
        {"EST-2026-0108", "Camila Diaz"},
        {"EST-2026-0109", "Luis Herrera"},
        {"EST-2026-0110", "Valentina Cruz"},
        {"EST-2026-0111", "Andres Vega"},
        {"EST-2026-0112", "Laura Castro"}
    };

    cout << "Tabla hash buena (función hash multinomio)" << endl;
    TablaHashBuena tablabuena;
    for (const auto& est : estudiantes) {
        tablabuena.insertar(est.first, est.second);
    }
    tablabuena.imprimir();

    cout << "\nBúsqueda de EST-2026-0107: ";
    if (tablabuena.buscar("EST-2026-0107", resultado)) {
        cout << "Encontrado: " << resultado << endl;
    } else {
        cout << "No encontrado" << endl;
    }

    cout << "\n\nTabla hash mala (suma primeros 4 caracteres)" << endl;
    TablaHashMala tablamala;
    for (const auto& est : estudiantes) {
        tablamala.insertar(est.first, est.second);
    }
    tablamala.imprimir();

    cout << "\nBúsqueda de EST-2026-0112: ";
    if (tablamala.buscar("EST-2026-0112", resultado)) {
        cout << "Encontrado: " << resultado << endl;
    } else {
        cout << "No encontrado" << endl;
    }

    return 0;
}
