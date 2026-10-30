
class Nodo:
    def __init__(self, clave, nombre=""):
        self.clave = clave; self.nombre = nombre
        self.izq = None; self.der = None

def insertar(n, clave, nombre=""):
    if n is None: return Nodo(clave, nombre)
    if clave < n.clave: n.izq = insertar(n.izq, clave, nombre)   # el retorno se REENGANCHA
    elif clave > n.clave: n.der = insertar(n.der, clave, nombre)
    # clave repetida: no se inserta
    return n

def contarNodos(n):
    if n is None: return 0
    return 1 + contarNodos(n.izq) + contarNodos(n.der)

def enRango(n, a, b, resultado, visitados):
    if n is None: return
    visitados.append(n.clave)
    if n.clave > a: enRango(n.izq, a, b, resultado, visitados)    # poda izquierda
    if a <= n.clave <= b: resultado.append(n.clave)
    if n.clave < b: enRango(n.der, a, b, resultado, visitados)    # poda derecha

raiz = None
for c in [50, 30, 70, 20, 40, 60, 80, 35]:
    raiz = insertar(raiz, c)

totalNodos = contarNodos(raiz)
for a, b in [(35, 65), (20, 80), (71, 79)]:
    resultado = []; visitados = []
    enRango(raiz, a, b, resultado, visitados)
    print(f"enRango([{a}, {b}]): {resultado}")
    print(f"  nodos visitados: {len(visitados)} de {totalNodos}  ({' -> '.join(str(v) for v in visitados)})")

