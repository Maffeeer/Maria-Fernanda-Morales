class Nodo:
    def __init__(self, valor):
        self.valor = valor
        self.siguiente = None


class Pila:
    def __init__(self):
        self.cima = None

    def apilar(self, valor):
        nuevoNodo = Nodo(valor)
        nuevoNodo.siguiente = self.cima
        self.cima = nuevoNodo

    def desapilar(self):
        if self.estaVacia():
            return None
        valor = self.cima.valor
        self.cima = self.cima.siguiente
        return valor

    def obtenerCima(self):
        if self.estaVacia():
            return None
        return self.cima.valor

    def estaVacia(self):
        return self.cima is None

    def tamanio(self):
        contador = 0
        actual = self.cima
        while actual is not None:
            contador += 1
            actual = actual.siguiente
        return contador

    def __repr__(self):
        elementos = []
        actual = self.cima
        while actual is not None:
            elementos.append(str(actual.valor))
            actual = actual.siguiente
        return "[" + ", ".join(elementos) + "]"


class RegistroPrestamo:
    def __init__(self, idLibro, usuario, fecha):
        self.idLibro = idLibro
        self.usuario = usuario
        self.fecha = fecha

    def __repr__(self):
        return f"Prestamo(libro={self.idLibro}, usuario={self.usuario}, fecha={self.fecha})"


class RegistroRecoleccion:
    def __init__(self, tipo, cantidad, ubicacion):
        self.tipo = tipo
        self.cantidad = cantidad
        self.ubicacion = ubicacion

    def __repr__(self):
        return f"Recoleccion(tipo={self.tipo}, cantidad={self.cantidad}, ubicacion={self.ubicacion})"


class RegistroMonitoria:
    def __init__(self, estudiante, materia, horario):
        self.estudiante = estudiante
        self.materia = materia
        self.horario = horario

    def __repr__(self):
        return f"Monitoria(estudiante={self.estudiante}, materia={self.materia}, horario={self.horario})"


def deshacerPrestamo(pilaPrestamos):
    print("Reto 1: Deshacer ultimo prestamo")
    print()

    if pilaPrestamos.estaVacia():
        print("No hay prestamos para deshacer\n")
        return None

    prestamo = pilaPrestamos.desapilar()
    print(f"Prestamo deshecho: {prestamo}")
    print(f"Prestamos restantes en pila: {pilaPrestamos.tamanio()}\n")
    return prestamo


def deshacerRecoleccion(pilaRecoleccion):
    print("Reto 2: Deshacer ultima recoleccion")
    print()

    if pilaRecoleccion.estaVacia():
        print("No hay recolecciones para deshacer\n")
        return None

    recoleccion = pilaRecoleccion.desapilar()
    print(f"Recoleccion deshecha: {recoleccion}")
    print(f"Recolecciones restantes en pila: {pilaRecoleccion.tamanio()}\n")
    return recoleccion


def deshacerMonitoria(pilaMonitoria):
    print("Reto 3: Deshacer ultima asignacion de monitoria")
    print()

    if pilaMonitoria.estaVacia():
        print("No hay monitorias para deshacer\n")
        return None

    monitoria = pilaMonitoria.desapilar()
    print(f"Monitoria deshecha: {monitoria}")
    print(f"Monitorias restantes en pila: {pilaMonitoria.tamanio()}\n")
    return monitoria


def evaluarRPN(expresion):
    print("Evaluando: " + " ".join(expresion))

    pila = Pila()
    operadores = {'+', '-', '*', '/'}

    for token in expresion:
        if token in operadores:
            if pila.tamanio() < 2:
                print("Error: operandos insuficientes\n")
                return None

            b = pila.desapilar()
            a = pila.desapilar()

            if token == '+':
                resultado = a + b
            elif token == '-':
                resultado = a - b
            elif token == '*':
                resultado = a * b
            elif token == '/':
                if b == 0:
                    print("Error: division por cero\n")
                    return None
                resultado = a // b

            pila.apilar(resultado)
        else:
            try:
                numero = int(token)
                pila.apilar(numero)
            except ValueError:
                print(f"Error: token invalido {token}\n")
                return None

    if pila.tamanio() != 1:
        print("Error: expresion invalida\n")
        return None

    resultado = pila.desapilar()
    print(f"Resultado: {resultado}\n")
    return resultado


def pruebaUno():
    print("Reto 1: Deshacer ultimo prestamo (Pila sobre lista enlazada)")
    print()

    pilaPrestamos = Pila()

    print("Agregando prestamos a la pila:")
    prestamo1 = RegistroPrestamo(101, "Juan", "2024-10-20")
    prestamo2 = RegistroPrestamo(102, "Maria", "2024-10-21")
    prestamo3 = RegistroPrestamo(103, "Pedro", "2024-10-22")

    pilaPrestamos.apilar(prestamo1)
    print(f"  {prestamo1}")
    pilaPrestamos.apilar(prestamo2)
    print(f"  {prestamo2}")
    pilaPrestamos.apilar(prestamo3)
    print(f"  {prestamo3}")
    print(f"Total prestamos: {pilaPrestamos.tamanio()}\n")

    deshacerPrestamo(pilaPrestamos)


def pruebaDos():
    print("Reto 2: Deshacer ultima recoleccion (Pila sobre lista enlazada)")
    print()

    pilaRecoleccion = Pila()

    print("Agregando recolecciones a la pila:")
    rec1 = RegistroRecoleccion("Plastico", 50, "Almacen A")
    rec2 = RegistroRecoleccion("Vidrio", 30, "Almacen B")
    rec3 = RegistroRecoleccion("Metal", 25, "Almacen C")

    pilaRecoleccion.apilar(rec1)
    print(f"  {rec1}")
    pilaRecoleccion.apilar(rec2)
    print(f"  {rec2}")
    pilaRecoleccion.apilar(rec3)
    print(f"  {rec3}")
    print(f"Total recolecciones: {pilaRecoleccion.tamanio()}\n")

    deshacerRecoleccion(pilaRecoleccion)


def pruebaTres():
    print("Reto 3: Deshacer ultima asignacion de monitoria (Pila sobre lista enlazada)")
    print()

    pilaMonitoria = Pila()

    print("Agregando monitorias a la pila:")
    mon1 = RegistroMonitoria("Ana", "Algoritmos", "Lunes 2-3pm")
    mon2 = RegistroMonitoria("Luis", "Estructuras", "Martes 3-4pm")
    mon3 = RegistroMonitoria("Sofia", "BD", "Miercoles 4-5pm")

    pilaMonitoria.apilar(mon1)
    print(f"  {mon1}")
    pilaMonitoria.apilar(mon2)
    print(f"  {mon2}")
    pilaMonitoria.apilar(mon3)
    print(f"  {mon3}")
    print(f"Total monitorias: {pilaMonitoria.tamanio()}\n")

    deshacerMonitoria(pilaMonitoria)


def pruebaRPN():
    print("Reto 4: Evaluar expresiones en Notacion Polaca Inversa")
    print()

    expresiones = [
        ["3", "4", "+"],
        ["10", "5", "-"],
        ["6", "7", "*"],
        ["20", "4", "/"],
        ["3", "4", "+", "2", "*"],
        ["15", "7", "1", "+", "/"],
    ]

    for expr in expresiones:
        evaluarRPN(expr)


if __name__ == "__main__":
    pruebaUno()
    pruebaDos()
    pruebaTres()
    pruebaRPN()

    print("CONCLUSIONES")
    print("- Pila sobre lista enlazada permite apilar y desapilar en O(1)")
    print("- Operacion deshacer es reversible usando una pila")
    print("- Notacion Polaca Inversa (RPN) se evalua eficientemente con una pila")
    print("- La pila es la estructura ideal para operaciones LIFO")
