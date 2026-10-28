class Nodo:
    def __init__(self, dato):
        self.dato = dato
        self.izq = None
        self.der = None

def imprimirJerarquia(nodo, nivel=0):
    if nodo is None: return                   # caso base: subarbol vacio
    print("  " * nivel + nodo.dato)           # 1) raiz con sangria segun su nivel
    imprimirJerarquia(nodo.izq, nivel + 1)    # 2) izquierda, un nivel mas abajo
    imprimirJerarquia(nodo.der, nivel + 1)    # 3) derecha, un nivel mas abajo

def pruebaUno():
    print("Catalogo original")
    print()

    raiz = Nodo("CATALOGO")
    raiz.izq = Nodo("HERRAMIENTA"); raiz.der = Nodo("LIBRO")
    raiz.izq.izq = Nodo("TALADRO");  raiz.izq.der = Nodo("SIERRA")
    raiz.der.izq = Nodo("ARTE");     raiz.der.der = Nodo("TECNICO")
    raiz.der.der.der = Nodo("REDES")

    imprimirJerarquia(raiz, 0)
    print()

def pruebaDos():
    print("Otro arbol")
    print()

    raizOtra = Nodo("UNIVERSIDAD")
    raizOtra.izq = Nodo("INGENIERIA")
    raizOtra.izq.der = Nodo("SISTEMAS")
    raizOtra.izq.der.izq = Nodo("ALGORITMOS")
    raizOtra.izq.der.der = Nodo("REDES")

    imprimirJerarquia(raizOtra, 0)
    print()

    print("Arbol vacio:")
    imprimirJerarquia(None, 0)                # no imprime nada
    print()

if __name__ == "__main__":
    pruebaUno()
    pruebaDos()

    print("Conclusión")
    print("- El preorden visita primero al padre, por eso sirve para imprimir un indice")
    print("- El nivel aumenta en 1 en cada llamada recursiva y define la sangria")
    print("- Como solo depende de la recursion, funciona para cualquier arbol")
