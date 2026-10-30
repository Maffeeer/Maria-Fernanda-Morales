class Nodo:
    def __init__(self, dato):
        self.dato = dato
        self.izq = None
        self.der = None

def sonIguales(a, b):
    if a is None and b is None: return True   # caso base: los dos vacios
    if a is None or b is None: return False   # uno vacio y el otro no: distinta forma
    if a.dato != b.dato: return False         # 1) misma raiz
    return sonIguales(a.izq, b.izq) and sonIguales(a.der, b.der)  # 2) y 3) mismos hijos

def copiar(nodo):
    if nodo is None: return None
    nuevoNodo = Nodo(nodo.dato)               # preorden: copiar la raiz primero
    nuevoNodo.izq = copiar(nodo.izq)
    nuevoNodo.der = copiar(nodo.der)
    return nuevoNodo

def espejo(nodo):
    if nodo is None: return
    nodo.izq, nodo.der = nodo.der, nodo.izq
    espejo(nodo.izq)
    espejo(nodo.der)

def construirCatalogo():
    raiz = Nodo("CATALOGO")
    raiz.izq = Nodo("HERRAMIENTA"); raiz.der = Nodo("LIBRO")
    raiz.izq.izq = Nodo("TALADRO");  raiz.izq.der = Nodo("SIERRA")
    raiz.der.izq = Nodo("ARTE");     raiz.der.der = Nodo("TECNICO")
    raiz.der.der.der = Nodo("REDES")
    return raiz

def pruebaUno():
    print("Original contra su propio espejo")
    print()

    raiz = construirCatalogo()
    raizEspejo = copiar(raiz)                 # se copia para no perder el original
    espejo(raizEspejo)

    print(f"sonIguales(original, espejo): {sonIguales(raiz, raizEspejo)}")    # False
    print()

def pruebaDos():
    print("Casos de control")
    print()

    raiz = construirCatalogo()
    raizCopia = copiar(raiz)
    print(f"sonIguales(original, copia)        : {sonIguales(raiz, raizCopia)}")   # True

    raizCambiada = copiar(raiz)
    raizCambiada.der.der.der = None           # quitar REDES: cambia la forma
    print(f"sonIguales(original, sin REDES)    : {sonIguales(raiz, raizCambiada)}")  # False

    raizOtroDato = copiar(raiz)
    raizOtroDato.izq.izq.dato = "MARTILLO"    # misma forma, distinto dato
    print(f"sonIguales(original, con MARTILLO) : {sonIguales(raiz, raizOtroDato)}")  # False

    print(f"sonIguales(vacio, vacio)           : {sonIguales(None, None)}")    # True
    print()

def pruebaTres():
    print("Arbol simetrico (corchador)")
    print()

    raizSimetrica = Nodo("A")
    raizSimetrica.izq = Nodo("B"); raizSimetrica.der = Nodo("B")
    raizEspejo = copiar(raizSimetrica)
    espejo(raizEspejo)

    print(f"sonIguales(simetrico, espejo): {sonIguales(raizSimetrica, raizEspejo)}")  # True
    print()

if __name__ == "__main__":
    pruebaUno()
    pruebaDos()
    pruebaTres()

    print("Conclusión")
    print("- sonIguales compara forma y datos al mismo tiempo, nodo por nodo")
    print("- El catalogo no es igual a su espejo porque los hijos cambian de lado")
    print("- Hay que copiar el arbol antes de espejarlo, si no se compararia consigo mismo")
    print("- Un arbol simetrico si es igual a su espejo")
