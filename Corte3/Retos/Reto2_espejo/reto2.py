
class Nodo:
    def __init__(self, dato):
        self.dato = dato
        self.izq = None
        self.der = None

def inorden(n, salida):
    if n is None: return
    inorden(n.izq, salida)        # 1) izquierda
    salida.append(n.dato)         # 2) raiz
    inorden(n.der, salida)        # 3) derecha

def espejo(nodo):
    if nodo is None: return                   # caso base: subarbol vacio
    nodo.izq, nodo.der = nodo.der, nodo.izq   # 1) intercambiar hijos
    espejo(nodo.izq)                          # 2) espejar izquierda
    espejo(nodo.der)                          # 3) espejar derecha

def pruebaUno():
    print("Espejo del catalogo")
    print()
    raiz = Nodo("CATALOGO")
    raiz.izq = Nodo("HERRAMIENTA"); raiz.der = Nodo("LIBRO")
    raiz.izq.izq = Nodo("TALADRO");  raiz.izq.der = Nodo("SIERRA")
    raiz.der.izq = Nodo("ARTE");     raiz.der.der = Nodo("TECNICO")
    raiz.der.der.der = Nodo("REDES")

    inordenOriginal = []; inorden(raiz, inordenOriginal)
    print(f"Inorden original: {' -> '.join(inordenOriginal)}")

    espejo(raiz)
    inordenEspejo = []; inorden(raiz, inordenEspejo)
    print(f"Inorden espejo  : {' -> '.join(inordenEspejo)}")
    print()

    esReverso = inordenEspejo == inordenOriginal[::-1]
    print(f"El inorden del espejo es el inorden original al reves: {esReverso}")
    print()

if __name__ == "__main__":
    pruebaUno()

    print("conclusión")
    print("- espejo visita cada nodo una sola vez, por eso es O(n)")
    print("- El inorden del arbol espejado es el inorden original invertido")
    print("- espejo modifica el arbol original, no crea uno nuevo")
