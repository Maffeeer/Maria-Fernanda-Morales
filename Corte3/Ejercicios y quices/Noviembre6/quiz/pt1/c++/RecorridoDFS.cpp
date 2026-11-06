#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

const vector<string> NOMBRES = {"CENTRO","NORTE","SUR","ORIENTE","OCCIDENTE",
                                "CHAPINERO","USAQUEN","BOSA","VEREDA"};
const vector<pair<int,int>> ARISTAS = {{0,1},{1,4},{0,2},{0,3},{1,5},{2,7},{3,6},{5,6},{4,7},
                                       {7,8},{8,1},{7,5},{5,8},{2,6},{6,8},{1,8},{5,7},{5,2}};
const int N = 9;

vector<vector<int>> lista(N);

string sangria(int prof) { return string(2 * prof, ' '); }

// ---------- DFS recursivo ----------
void dfsRec(int u, vector<bool>& visitado, vector<int>& orden, int prof = 0, vector<string>* traza = nullptr) {
    visitado[u] = true;
    orden.push_back(u);
    if (traza) traza->push_back(sangria(prof) + "entra " + NOMBRES[u]);
    for (int v : lista[u]) {
        if (!visitado[v]) dfsRec(v, visitado, orden, prof + 1, traza);
        else if (traza) traza->push_back(sangria(prof + 1) + NOMBRES[v] + " ya visitado, no entra");
    }
    if (traza) traza->push_back(sangria(prof) + "sale  " + NOMBRES[u]);
}

void imprimirOrden(const vector<int>& orden) {
    cout << "  orden de visita: ";
    for (size_t i = 0; i < orden.size(); i++) {
        cout << NOMBRES[orden[i]];
        if (i + 1 < orden.size()) cout << " -> ";
    }
    cout << endl;
}

// ---------- DFS iterativo con pila ----------
vector<int> dfsIter(int inicio) {
    vector<bool> visitado(N, false);
    vector<int> pila = {inicio}, orden;
    while (!pila.empty()) {
        int u = pila.back(); pila.pop_back();          // LIFO: saca el ultimo que entro
        if (visitado[u]) continue;
        visitado[u] = true;
        orden.push_back(u);
        for (auto it = lista[u].rbegin(); it != lista[u].rend(); ++it)   // al reves para igualar el orden del recursivo
            if (!visitado[*it]) pila.push_back(*it);
    }
    return orden;
}

// ---------- Aplicacion 1: componentes conexas ----------
vector<vector<string>> componentes() {
    vector<bool> visitado(N, false);
    vector<vector<string>> comps;
    for (int s = 0; s < N; s++) {
        if (!visitado[s]) {
            vector<int> o;
            dfsRec(s, visitado, o);
            vector<string> comp;
            for (int i : o) comp.push_back(NOMBRES[i]);
            comps.push_back(comp);
        }
    }
    return comps;
}

void imprimirComponentes(const vector<vector<string>>& comps) {
    cout << "[";
    for (size_t c = 0; c < comps.size(); c++) {
        cout << "[";
        for (size_t i = 0; i < comps[c].size(); i++) {
            cout << "'" << comps[c][i] << "'";
            if (i + 1 < comps[c].size()) cout << ", ";
        }
        cout << "]";
        if (c + 1 < comps.size()) cout << ", ";
    }
    cout << "]" << endl;
}

// ---------- Aplicacion 2: deteccion de ciclo ----------
bool explorar(int u, int padre, vector<bool>& visitado) {
    visitado[u] = true;
    for (int v : lista[u]) {
        if (!visitado[v]) {
            if (explorar(v, u, visitado)) return true;
        } else if (v != padre) {          // vecino ya visitado que NO es de donde vengo
            return true;
        }
    }
    return false;
}

bool hayCiclo() {
    vector<bool> visitado(N, false);
    for (int s = 0; s < N; s++)
        if (!visitado[s] && explorar(s, -1, visitado)) return true;
    return false;
}

int main() {
    for (auto [u, v] : ARISTAS) { lista[u].push_back(v); lista[v].push_back(u); }
    for (auto& v : lista) sort(v.begin(), v.end());

    vector<bool> vis(N, false);
    vector<int> orden;
    vector<string> traza;
    dfsRec(0, vis, orden, 0, &traza);
    cout << "DFS RECURSIVO desde CENTRO" << endl;
    for (auto& t : traza) cout << "  " << t << endl;
    imprimirOrden(orden);

    cout << "\nDFS ITERATIVO (con pila explicita) desde CENTRO" << endl;
    imprimirOrden(dfsIter(0));

    cout << "\nCOMPONENTES CONEXAS de la red completa: ";
    imprimirComponentes(componentes());

    // red con un punto aislado y un par suelto
    vector<vector<int>> listaRota(N);
    for (auto [u, v] : vector<pair<int,int>>{{0,1},{0,2},{3,6}}) {
        listaRota[u].push_back(v); listaRota[v].push_back(u);
    }
    vector<vector<int>> listaOrig = lista;
    lista = listaRota;
    cout << "COMPONENTES de una red con tramos cortados: ";
    imprimirComponentes(componentes());
    lista = listaOrig;

    cout << "La red tiene algun circuito? " << (hayCiclo() ? "true" : "false") << endl;
    return 0;
}
