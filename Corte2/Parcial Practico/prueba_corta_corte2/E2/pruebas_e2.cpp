// NO MODIFIQUE ESTE ARCHIVO. Alterarlo se considera fraude academico
// segun la seccion 13 de la guia de asignatura.
#include <iostream>
#include <string>
using namespace std;

int buscarCodigo(int v[], int n, int x);

static int fallas = 0;
static void chk(const string& nombre, int obtenido, int esperado) {
    bool ok = (obtenido == esperado);
    cout << "  [" << (ok ? "OK " : "FALLA") << "] " << nombre
         << ": obtuvo " << obtenido;
    if (!ok) cout << "  (esperaba " << esperado << ")";
    cout << endl;
    if (!ok) fallas++;
}

int main() {
    cout << "EJERCICIO 2 · verificacion" << endl;

    // El arreglo logico tiene N = 10 posiciones (indices 0..9).
    // Las posiciones 10 en adelante son CENTINELAS: la funcion no debe leerlas.
    const int N = 10;
    int buf[16] = {104, 117, 125, 138, 146, 159, 163, 178, 185, 197,
                   250, -1, -1, -1, -1, -1};

    chk("buscar 163 (interior)",        buscarCodigo(buf, N, 163), 6);
    chk("buscar 104 (primero)",         buscarCodigo(buf, N, 104), 0);
    chk("buscar 197 (ultimo)",          buscarCodigo(buf, N, 197), 9);
    chk("buscar 138",                   buscarCodigo(buf, N, 138), 3);
    chk("buscar 150 (ausente, medio)",  buscarCodigo(buf, N, 150), -1);
    chk("buscar 100 (menor que todos)", buscarCodigo(buf, N, 100), -1);

    // Centinela: el valor 250 esta en buf[10], FUERA del rango logico 0..9.
    // Si la funcion lo encuentra, esta leyendo una posicion que no le pertenece.
    int r = buscarCodigo(buf, N, 250);
    bool leyoFuera = (r == 10);
    cout << "  [" << (leyoFuera ? "FALLA" : "OK ")
         << "] no lee fuera del arreglo (buscar 250): devolvio " << r;
    if (leyoFuera) cout << "  (el indice 10 NO existe: el arreglo va de 0 a 9)";
    cout << endl;
    if (leyoFuera) fallas++;
    else chk("buscar 250 (mayor que todos)", r, -1);

    int uno[4] = {42, -1, -1, -1};
    chk("arreglo de 1: buscar 42", buscarCodigo(uno, 1, 42), 0);
    chk("arreglo de 1: buscar 7",  buscarCodigo(uno, 1, 7), -1);

    if (fallas == 0) {
        // el codigo se DERIVA de las posiciones correctas: no esta escrito aqui
        int a = buscarCodigo(buf, N, 163);
        int b = buscarCodigo(buf, N, 197);
        int c = buscarCodigo(buf, N, 138);
        cout << "\n  EJERCICIO 2 CERRADO — codigo de cierre: 2202-"
             << a << b << c << (a + b + c) << endl;
    } else {
        cout << "\n  Ejercicio ABIERTO (" << fallas
             << " falla(s)). Corrija y vuelva a ejecutar." << endl;
    }
    return 0;
}
