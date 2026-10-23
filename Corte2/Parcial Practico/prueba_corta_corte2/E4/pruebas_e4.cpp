// NO MODIFIQUE ESTE ARCHIVO. Alterarlo se considera fraude academico
// segun la seccion 13 de la guia de asignatura.
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
using namespace std;

string zonaMayor(const vector<pair<string,int>>& reg,
                 map<string,int>& totales, set<string>& repetidas);

static int fallas = 0;
static void chk(const string& nombre, const string& obtenido, const string& esperado) {
    bool ok = (obtenido == esperado);
    cout << "  [" << (ok ? "OK " : "FALLA") << "] " << nombre << ": obtuvo \""
         << obtenido << "\"";
    if (!ok) cout << "  (esperaba \"" << esperado << "\")";
    cout << endl;
    if (!ok) fallas++;
}
static void chkInt(const string& nombre, int obtenido, int esperado) {
    bool ok = (obtenido == esperado);
    cout << "  [" << (ok ? "OK " : "FALLA") << "] " << nombre << ": obtuvo "
         << obtenido;
    if (!ok) cout << "  (esperaba " << esperado << ")";
    cout << endl;
    if (!ok) fallas++;
}

int main() {
    cout << "EJERCICIO 4 · verificacion" << endl;

    vector<pair<string,int>> reg = {{"norte",40},{"sur",25},{"norte",15},
                                    {"centro",60},{"sur",30},{"oriente",18},
                                    {"centro",5}};
    map<string,int> t; set<string> rep;
    string mejor = zonaMayor(reg, t, rep);

    chk   ("zona con mayor total",      mejor, "centro");
    chkInt("cantidad de zonas",         (int)t.size(), 4);
    chkInt("total de norte",            t.count("norte")   ? t["norte"]   : -1, 55);
    chkInt("total de sur",              t.count("sur")     ? t["sur"]     : -1, 55);
    chkInt("total de centro",           t.count("centro")  ? t["centro"]  : -1, 65);
    chkInt("total de oriente",          t.count("oriente") ? t["oriente"] : -1, 18);
    chkInt("cantidad de zonas repetidas", (int)rep.size(), 3);
    chkInt("oriente NO esta en repetidas", rep.count("oriente") ? 1 : 0, 0);
    chkInt("centro SI esta en repetidas",  rep.count("centro")  ? 1 : 0, 1);

    // caso borde: sin registros
    map<string,int> t2; set<string> rep2;
    vector<pair<string,int>> vacio;
    chk   ("lista vacia devuelve \"\"", zonaMayor(vacio, t2, rep2), "");
    chkInt("lista vacia no llena totales", (int)t2.size(), 0);

    if (fallas == 0) {
        // el codigo se DERIVA de los resultados correctos: no esta escrito aqui
        cout << "\n  EJERCICIO 4 CERRADO — codigo de cierre: 2204-"
             << t["centro"] << t.size() << rep.size() << endl;
    } else {
        cout << "\n  Ejercicio ABIERTO (" << fallas
             << " falla(s)). Corrija y vuelva a ejecutar." << endl;
    }
    return 0;
}
