En parejas, cada estudiante adapta la TablaHash del Momento 1 a un caso nuevo y descubre por sí mismo dos lecciones: una función hash que mira la parte repetida de la clave lo amontona todo, y redimensionar no arregla una mala función hash. Una persona de la pareja trabaja en Python y la otra en C++; al final comparan salidas.
Enunciado
La universidad quiere encontrar a un estudiante por su código en tiempo constante. Los códigos tienen la forma EST-2026-0101 … EST-2026-0112.
EST-2026-0101 Ana Torres       EST-2026-0107 Pedro Ruiz
EST-2026-0102 Carlos Rojas     EST-2026-0108 Camila Diaz
EST-2026-0103 Diego Pardo      EST-2026-0109 Luis Herrera
EST-2026-0104 Sofia Mejia      EST-2026-0110 Valentina Cruz
EST-2026-0105 Juan Gomez       EST-2026-0111 Andres Vega
EST-2026-0106 Maria Lopez      EST-2026-0112 Laura Castro
1. Cargar. Partiendo de la TablaHash del Momento 1 con capacidad 8, inserten los 12 estudiantes (código → nombre) y busquen EST-2026-0107.
2. Redimensionar. Agreguen el método redimensionar: cuando el factor de carga pase de 0,75, duplican la capacidad y vuelven a insertar todo. Usen esta plantilla:
Python:
def _redimensionar(self):
        viejas = self.cubetas
        # TODO 1: duplicar self.cap
        # TODO 2: crear cubetas vacias nuevas y poner self.n en 0
        # TODO 3: recorrer 'viejas' e insertar cada (clave, valor) otra vez

    # y al final de insertar():
        if self.factor_carga() > 0.75:
            self._redimensionar()
c++:
void redimensionar() {
        vector<list<pair<string, string>>> viejas = cubetas;
        // TODO 1: duplicar cap
        // TODO 2: cubetas.assign(cap, list<pair<string, string>>()); n = 0;
        // TODO 3: recorrer 'viejas' e insertar cada par otra vez
    }
    // y al final de insertar():
    //     if (factorCarga() > 0.75) redimensionar();
void redimensionar() {
        vector<list<pair<string, string>>> viejas = cubetas;
        // TODO 1: duplicar cap
        // TODO 2: cubetas.assign(cap, list<pair<string, string>>()); n = 0;
        // TODO 3: recorrer 'viejas' e insertar cada par otra vez
    }
    // y al final de insertar():
    //     if (factorCarga() > 0.75) redimensionar();
3. Comparar dos funciones hash. Agreguen una segunda función, la "mala", que solo suma los 4 primeros caracteres de la clave:
return sum(ord(c) for c in clave[:4]) % self.cap
Carguen los 12 estudiantes con cada función e impriman: capacidad final, distribución, factor de carga, cubeta más llena y cubetas vacías.
4. Responder en un md:
    1. ¿Por qué la función mala pone a todos en la misma cubeta?
    2. La tabla con la función mala también se redimensionó. ¿Mejoró la distribución? ¿Por qué?
    3. Con la función mala, ¿cuántas comparaciones hace buscar("EST-2026-0112") en el peor caso? ¿Y con la buena?
    4. ¿Qué parte del código debería mirar una buena función hash para sus claves del proyecto?

    