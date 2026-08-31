// ============================================================
//  Cívica Software  ·  TCK-4422  ·  Severidad P1
//  Sistema: PrestaLab  —  Nueva funcionalidad: catalogo mixto
//  El reporte imprime siempre "Recurso generico". Debe imprimir
//  la descripcion propia de cada tipo.
// ============================================================
#include <iostream>
#include <string>
using namespace std;

class Recurso {
protected:
    string codigo;
    bool   prestado;
public:
    Recurso(string c) : codigo(c), prestado(false) {}
    ~Recurso() {}

    void prestar()  { prestado = true; }
    bool estaPrestado() const { return prestado; }

    virtual string descripcion() const { return "Recurso generico " + codigo; }
    // Cambio: agregado 'virtual' para que las clases derivadas puedan sobrescribir
    // Este es el mecanismo de polimorfismo que permite que cada objeto responda con su propia descripción

// Implemente Nueva clase LibroFisico, que hera de recurso, aparte se sobreescribe el metodo descripcion() para que devuelva "Libro <codigo> de <autor>"
class LibroFisico : public Recurso {
private:
    string autor;
public:
    LibroFisico(string c, string a) : Recurso(c), autor(a) {}
    
    string descripcion() const override { 
        return "Libro " + codigo + " de " + autor; 
    }
};

// Implementamos nueva clase equipo, que hereda de recurso, aparte se sobreescribe el metodo descripcion() para que devuelva "Equipo <codigo> (<horasUso>h)"
class Equipo : public Recurso {
private:
    int horasUso;
public:
    Equipo(string c, int h) : Recurso(c), horasUso(h) {}
    
    string descripcion() const override { 
        return "Equipo " + codigo + " (" + to_string(horasUso) + "h)"; 
    }
};

int main() {
    const int N = 3;
    Recurso* catalogo[N] = { nullptr, nullptr, nullptr };
    catalogo[0] = new Recurso("RG-001");
    // Cree una nueva instancia de LibroFisico y de Equipo, y las agrege al catalogo
    catalogo[1] = new LibroFisico("LF-002", "Borges");
    catalogo[2] = new Equipo("EQ-003", 12);

    // Se agrego el marcar al menos un recurso como prestado
    catalogo[1]->prestar();  // Marcar el libro como prestado

    int prestados = 0;
    for (int i = 0; i < N; i++) {
        if (catalogo[i] == nullptr) continue;
        cout << catalogo[i]->descripcion();
        if (catalogo[i]->estaPrestado()) { cout << "  [PRESTADO]"; prestados++; }
        cout << endl;
    }

    for (int i = 0; i < N; i++) delete catalogo[i];   // delete sobre nullptr es seguro
    return 0;
}
