// Reto 2 - El converso: de matriz a lista y de lista a matriz
#include <iostream>
#include <vector>
#include <string>
#include <random>
using namespace std;

using Matriz = vector<vector<int>>;
using Lista  = vector<vector<int>>;

Lista matrizALista(const Matriz& m) {
    int n = (int)m.size();
    Lista l(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (m[i][j] == 1) l[i].push_back(j);
    return l;
}

Matriz listaAMatriz(const Lista& l) {
    int n = (int)l.size();
    Matriz m(n, vector<int>(n, 0));
    for (int u = 0; u < n; u++)
        for (int v : l[u]) m[u][v] = 1;
    return m;
}

// ---------- Verificacion ----------
int fallas = 0;

void verificar(const string& nombre, bool condicion) {
    if (!condicion) fallas++;
    cout << "  " << (condicion ? "OK    " : "FALLA ") << nombre << endl;
}

bool idaYVuelta(const Matriz& m) {
    return listaAMatriz(matrizALista(m)) == m;
}

Matriz matrizDeAristas(int n, const vector<pair<int,int>>& aristas) {
    Matriz m(n, vector<int>(n, 0));
    for (auto [u, v] : aristas) { m[u][v] = 1; m[v][u] = 1; }
    return m;
}

Matriz matrizAleatoria(int n, bool simetrica, mt19937& gen) {
    uniform_int_distribution<int> bit(0, 1);
    Matriz m(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) m[i][j] = bit(gen);
    if (simetrica)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < i; j++) m[i][j] = m[j][i];
    return m;
}

int main() {
    // Red de vias del proyecto (la misma del reto 1)
    Matriz red = matrizDeAristas(10, {{0,1},{0,2},{0,3},{0,5},{1,4},{1,5},{1,9},{2,4},
                                      {2,7},{3,5},{3,6},{4,7},{4,9},{5,6},{6,9},{7,8}});
    Matriz completo(5, vector<int>(5, 1));
    for (int i = 0; i < 5; i++) completo[i][i] = 0;

    cout << "IDA Y VUELTA: listaAMatriz(matrizALista(m)) == m" << endl;
    verificar("red del proyecto", idaYVuelta(red));
    verificar("grafo sin vertices", idaYVuelta(Matriz{}));
    verificar("un vertice sin aristas", idaYVuelta(Matriz{{0}}));
    verificar("vertices sin aristas", idaYVuelta(Matriz(4, vector<int>(4, 0))));
    verificar("grafo completo", idaYVuelta(completo));
    verificar("dirigido (matriz no simetrica)", idaYVuelta(Matriz{{0,1,1},{0,0,1},{0,0,0}}));
    verificar("con lazo (diagonal en 1)", idaYVuelta(Matriz{{1,0},{0,0}}));

    mt19937 gen(40);
    uniform_int_distribution<int> tamano(0, 12);
    bool todas = true;
    for (int i = 0; i < 1000; i++)
        if (!idaYVuelta(matrizAleatoria(tamano(gen), i % 2 == 0, gen))) todas = false;
    verificar("1000 matrices aleatorias", todas);

    // La ida y vuelta no basta: dos conversiones que inviertan las aristas tambien la pasarian
    cout << "\nCONTENIDO: cada conversion por separado" << endl;
    verificar("matrizALista conserva la direccion", matrizALista(Matriz{{0,1},{0,0}}) == Lista{{1},{}});
    verificar("listaAMatriz conserva la direccion", listaAMatriz(Lista{{1},{}}) == Matriz{{0,1},{0,0}});

    cout << "\nVUELTA E IDA: matrizALista(listaAMatriz(l)) == l (con vecinos ordenados y sin repetir)" << endl;
    Lista l = {{1,2},{0},{0}};
    verificar("lista ordenada", matrizALista(listaAMatriz(l)) == l);

    if (fallas == 0) cout << "\nTODO CORRECTO" << endl;
    else cout << "\n" << fallas << " VERIFICACIONES FALLARON" << endl;
    return fallas == 0 ? 0 : 1;
}
