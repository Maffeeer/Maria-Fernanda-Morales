#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
using namespace std;

const vector<string> NOMBRES = {"CENTRO","NORTE","SUR","ORIENTE","OCCIDENTE",
                                "CHAPINERO","USAQUEN","BOSA","VEREDA"};
// Los 18 recorridos del archivo recorridos.md
const vector<pair<int,int>> ARISTAS = {{0,1},{1,4},{0,2},{0,3},{1,5},{2,7},{3,6},{5,6},{4,7},
                                       {7,8},{8,1},{7,5},{5,8},{2,6},{6,8},{1,8},{5,7},{5,2}};
const int N = 9;

int main() {
    // ---------- Representacion 1: matriz de adyacencia ----------
    vector<vector<int>> matriz(N, vector<int>(N, 0));
    for (auto [u, v] : ARISTAS) matriz[u][v] = 1;  // dirigido: solo u -> v, NO es simetrica

    cout << "MATRIZ DE ADYACENCIA\n            ";
    for (auto& n : NOMBRES) cout << setw(5) << n.substr(0, 3);
    cout << endl;
    for (int i = 0; i < N; i++) {
        cout << setw(11) << NOMBRES[i] << " ";
        for (int j = 0; j < N; j++) cout << setw(5) << matriz[i][j];
        cout << endl;
    }

    // ---------- Representacion 2: lista de adyacencia ----------
    vector<vector<int>> lista(N);
    for (auto [u, v] : ARISTAS) lista[u].push_back(v);  // A -> B y B -> A son dos aristas distintas
    for (auto& v : lista) sort(v.begin(), v.end());

    cout << "\nLISTA DE ADYACENCIA" << endl;
    for (int i = 0; i < N; i++) {
        cout << "  " << setw(10) << NOMBRES[i] << " -> ";
        for (size_t k = 0; k < lista[i].size(); k++) {
            cout << NOMBRES[lista[i][k]];
            if (k + 1 < lista[i].size()) cout << ", ";
        }
        cout << endl;
    }

    cout << "\nGRADO DE CADA VERTICE (cuantas vias salen de el y cuantas entran)" << endl;
    for (int i = 0; i < N; i++) {
        int gMat = 0;
        for (int j = 0; j < N; j++) gMat += matriz[i][j];   // recorrer la fila: O(N)
        int gLis = (int)lista[i].size();                    // leer el tamano: O(1)
        int gEnt = 0;
        for (int j = 0; j < N; j++) gEnt += matriz[j][i];   // recorrer la columna: O(N)
        cout << "  " << setw(10) << NOMBRES[i] << ": salen " << gLis << ", entran " << gEnt
             << (gMat == gLis ? "" : "  <-- DISCREPANCIA") << endl;
    }

    int E = (int)ARISTAS.size();
    cout << "\nV = " << N << " vertices,  E = " << E << " aristas" << endl;
    cout << "  Matriz : " << N * N << " casillas en memoria. Existe arista? O(1). Recorrer vecinos: O(V) = " << N << " casillas." << endl;
    cout << "  Lista  : " << E << " referencias en memoria. Existe arista? O(grado). Recorrer vecinos: O(grado)." << endl;
    double dens = 1.0 * E / (N * (N - 1.0));
    cout << "  Densidad = E / (V(V-1)) = " << fixed << setprecision(2) << dens
         << "  ->  grafo " << (dens > 0.5 ? "DENSO: conviene matriz" : "DISPERSO: conviene lista") << endl;

    auto hayViaMatriz = [&](int u, int v) { return matriz[u][v] == 1; };
    auto hayViaLista  = [&](int u, int v) { return find(lista[u].begin(), lista[u].end(), v) != lista[u].end(); };
    for (auto [u, v] : vector<pair<int,int>>{{0,1},{0,7},{5,6}})
        cout << "  Conecta " << NOMBRES[u] << " con " << NOMBRES[v] << "? matriz="
             << (hayViaMatriz(u,v) ? "true" : "false") << "  lista="
             << (hayViaLista(u,v) ? "true" : "false") << endl;

    // consulta de aristas desde sede centro
    int origen = (int)(find(NOMBRES.begin(), NOMBRES.end(), "CENTRO") - NOMBRES.begin());
    for (int i = 0; i < N; i++) {
        if (i == origen) continue;
        cout << "  Conecta " << NOMBRES[origen] << " con " << NOMBRES[i] << "? matriz="
             << (hayViaMatriz(origen,i) ? "true" : "false") << "  lista="
             << (hayViaLista(origen,i) ? "true" : "false") << endl;
    }
    return 0;
}
