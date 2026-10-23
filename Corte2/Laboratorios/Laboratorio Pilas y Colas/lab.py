class Nodo:
    def __init__(self, valor):
        self.valor = valor
        self.siguiente = None


class Cola:
    def __init__(self):
        self.frente = None
        self.cola = None
        self.tamanio_actual = 0

    def encolar(self, valor):
        nuevoNodo = Nodo(valor)
        if self.estaVacia():
            self.frente = nuevoNodo
            self.cola = nuevoNodo
        else:
            self.cola.siguiente = nuevoNodo
            self.cola = nuevoNodo
        self.tamanio_actual += 1

    def desencolar(self):
        if self.estaVacia():
            return None
        valor = self.frente.valor
        self.frente = self.frente.siguiente
        self.tamanio_actual -= 1
        if self.estaVacia():
            self.cola = None
        return valor

    def consultarFrente(self):
        if self.estaVacia():
            return None
        return self.frente.valor

    def estaVacia(self):
        return self.frente is None

    def tamanio(self):
        return self.tamanio_actual


class Pila:
    def __init__(self):
        self.cima = None

    def apilar(self, operacion):
        nuevoNodo = Nodo(operacion)
        nuevoNodo.siguiente = self.cima
        self.cima = nuevoNodo

    def desapilar(self):
        if self.estaVacia():
            return None
        valor = self.cima.valor
        self.cima = self.cima.siguiente
        return valor

    def estaVacia(self):
        return self.cima is None


class RegistroOperacion:
    def __init__(self, tipo, recurso, cantidad):
        self.tipo = tipo
        self.recurso = recurso
        self.cantidad = cantidad

    def __repr__(self):
        return f"{self.tipo}({self.recurso}, {self.cantidad})"


def pruebaColaBasica():
    print("Parte A - Cola de Atencion")
    print("=" * 70)
    print()

    cola = Cola()

    print("Encolando: 101, 102, 103, 104, 105")
    for i in range(101, 106):
        cola.encolar(i)

    print(f"Tamanio: {cola.tamanio()}")
    print(f"Frente: {cola.consultarFrente()}\n")

    print("Desencolar 3 elementos:")
    for _ in range(3):
        print(f"  Desencolar: {cola.desencolar()}")

    print(f"Tamanio: {cola.tamanio()}")
    print(f"Frente: {cola.consultarFrente()}\n")


def pruebaCasoVacio():
    print("Prueba Especial - Vaciar y Volver a Encolar")
    print("=" * 70)
    print()

    cola = Cola()

    print("Encolando: 10, 20, 30")
    for val in [10, 20, 30]:
        cola.encolar(val)

    print(f"Tamanio: {cola.tamanio()}")
    print()

    print("Vaciando completamente:")
    while not cola.estaVacia():
        print(f"  Desencolar: {cola.desencolar()}")

    print(f"Cola vacia: {cola.estaVacia()}")
    print(f"Tamanio: {cola.tamanio()}")
    print()

    print("Volviendo a encolar: 40, 50, 60")
    for val in [40, 50, 60]:
        cola.encolar(val)

    print(f"Tamanio: {cola.tamanio()}")
    print(f"Frente: {cola.consultarFrente()}\n")


def pruebaDeshacer():
    print("Parte B - Deshacer Operaciones")
    print("=" * 70)
    print()

    recursos = {"Libros": 50, "Computadoras": 10, "Aulas": 5}
    pilaOperaciones = Pila()

    print("Estado inicial de recursos:")
    for recurso, cantidad in recursos.items():
        print(f"  {recurso}: {cantidad}")
    print()

    print("Operaciones realizadas:")

    op1 = RegistroOperacion("Prestamo", "Libros", 5)
    pilaOperaciones.apilar(op1)
    recursos["Libros"] -= 5
    print(f"  {op1} -> Libros: {recursos['Libros']}")

    op2 = RegistroOperacion("Prestamo", "Computadoras", 2)
    pilaOperaciones.apilar(op2)
    recursos["Computadoras"] -= 2
    print(f"  {op2} -> Computadoras: {recursos['Computadoras']}")

    op3 = RegistroOperacion("Prestamo", "Aulas", 1)
    pilaOperaciones.apilar(op3)
    recursos["Aulas"] -= 1
    print(f"  {op3} -> Aulas: {recursos['Aulas']}")
    print()

    print("Estado actual de recursos:")
    for recurso, cantidad in recursos.items():
        print(f"  {recurso}: {cantidad}")
    print()

    print("Deshaciendo operaciones (orden inverso):")
    while not pilaOperaciones.estaVacia():
        op = pilaOperaciones.desapilar()
        recursos[op.recurso] += op.cantidad
        print(f"  Deshacer {op} -> {op.recurso}: {recursos[op.recurso]}")

    print()
    print("Estado final despues de deshacer:")
    for recurso, cantidad in recursos.items():
        print(f"  {recurso}: {cantidad}")
    print()


if __name__ == "__main__":
    pruebaColaBasica()
    pruebaCasoVacio()
    pruebaDeshacer()
