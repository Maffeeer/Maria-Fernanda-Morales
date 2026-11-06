class Nodo:
    def __init__(self, dato):
        self.dato = dato
        self.izq = None
        self.der = None

def preorden(n, salida):
    if n is None: return          # caso base: subarbol vacio
    salida.append(n.dato)         # 1) raiz
    preorden(n.izq, salida)       # 2) izquierda
    preorden(n.der, salida)       # 3) derecha

def inorden(n, salida):
    if n is None: return
    inorden(n.izq, salida)        # 1) izquierda
    salida.append(n.dato)         # 2) raiz
    inorden(n.der, salida)        # 3) derecha

def postorden(n, salida):
    if n is None: return
    postorden(n.izq, salida)      # 1) izquierda
    postorden(n.der, salida)      # 2) derecha
    salida.append(n.dato)         # 3) raiz

def altura(n):
    if n is None: return -1       # arbol vacio: altura -1 (un solo nodo: 0)
    return 1 + max(altura(n.izq), altura(n.der))

def contar(n):
    if n is None: return 0
    return 1 + contar(n.izq) + contar(n.der)

def contar_hojas(n):
    if n is None: return 0
    if n.izq is None and n.der is None: return 1
    return contar_hojas(n.izq) + contar_hojas(n.der)

def por_niveles(raiz):
    if raiz is None: return []
    from collections import deque
    cola = deque([raiz]); salida = []
    while cola:
        n = cola.popleft()
        salida.append(n.dato)
        if n.izq: cola.append(n.izq)
        if n.der: cola.append(n.der)
    return salida

#            CATALOGO
#           /        \
#      HERRAMIENTA   LIBRO
#       /     \      /    \
#   TALADRO  SIERRA ARTE  TECNICO
#                           \
#                           REDES
raiz = Nodo("CATALOGO")
raiz.izq = Nodo("HERRAMIENTA"); raiz.der = Nodo("LIBRO")
raiz.izq.izq = Nodo("TALADRO");  raiz.izq.der = Nodo("SIERRA")
raiz.der.izq = Nodo("ARTE");     raiz.der.der = Nodo("TECNICO")
raiz.der.der.der = Nodo("REDES")

for nombre, fn in [("Preorden ", preorden), ("Inorden  ", inorden), ("Postorden", postorden)]:
    s = []; fn(raiz, s)
    print(f"{nombre}: {' -> '.join(s)}")
print(f"Niveles  : {' -> '.join(por_niveles(raiz))}")
print(f"nodos={contar(raiz)}  hojas={contar_hojas(raiz)}  altura={altura(raiz)}")
