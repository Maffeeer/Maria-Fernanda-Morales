# Reto 3 - Cuando NO alcanza una rotacion: en insercion siempre basta, en eliminacion no
import random
from itertools import permutations

class Nodo:
    def __init__(self, c):
        self.clave = c; self.izq = None; self.der = None; self.alt = 0

def alt(n):  return -1 if n is None else n.alt
def fe(n):   return 0 if n is None else alt(n.izq) - alt(n.der)   # factor de equilibrio
def recalc(n): n.alt = 1 + max(alt(n.izq), alt(n.der))

def rotarDerecha(y):
    x = y.izq; B = x.der
    x.der = y; y.izq = B
    recalc(y); recalc(x)
    return x

def rotarIzquierda(x):
    y = x.der; B = y.izq
    y.izq = x; x.der = B
    recalc(x); recalc(y)
    return y

def preorden(n, s):
    if n is None: return
    s.append(f"{n.clave}(fe={fe(n)})"); preorden(n.izq, s); preorden(n.der, s)

def ver(titulo, raiz):
    s = []; preorden(raiz, s)
    print(f"  {titulo:22s} altura={alt(raiz)}  preorden: {' '.join(s)}")

# ---------- AVL: cuenta cada rebalanceo (una rotacion simple o una doble cuentan como uno) ----------
rebalanceos = 0

def rebalancear(n):
    global rebalanceos
    recalc(n)
    f = fe(n)
    if f > 1:                                # pesa la izquierda
        rebalanceos += 1
        if fe(n.izq) < 0: n.izq = rotarIzquierda(n.izq)      # caso LR
        return rotarDerecha(n)
    if f < -1:                               # pesa la derecha
        rebalanceos += 1
        if fe(n.der) > 0: n.der = rotarDerecha(n.der)        # caso RL
        return rotarIzquierda(n)
    return n

def insertarAVL(n, c):
    if n is None: return Nodo(c)
    alturaAntes = n.alt
    if c < n.clave:   n.izq = insertarAVL(n.izq, c)
    elif c > n.clave: n.der = insertarAVL(n.der, c)
    recalc(n)
    desbalanceado = abs(fe(n)) > 1
    n = rebalancear(n)
    if desbalanceado:
        assert n.alt == alturaAntes          # la clave de la demostracion: recupera la altura de antes
    return n

def eliminarAVL(n, c):
    if n is None: return None
    if c < n.clave:   n.izq = eliminarAVL(n.izq, c)
    elif c > n.clave: n.der = eliminarAVL(n.der, c)
    else:
        if n.izq is None: return n.der
        if n.der is None: return n.izq
        s = n.der
        while s.izq is not None: s = s.izq   # sucesor: el menor del subarbol derecho
        n.clave = s.clave
        n.der = eliminarAVL(n.der, s.clave)
    return rebalancear(n)

def esAVL(n, minimo=None, maximo=None):
    if n is None: return True
    if minimo is not None and n.clave <= minimo: return False
    if maximo is not None and n.clave >= maximo: return False
    if n.alt != 1 + max(alt(n.izq), alt(n.der)) or abs(fe(n)) > 1: return False
    return esAVL(n.izq, minimo, n.clave) and esAVL(n.der, n.clave, maximo)

# ---------- El arbol del reto: AVL con el minimo de nodos para altura 4 ----------
ORDEN = [5, 2, 8, 1, 3, 7, 10, 4, 6, 9, 11, 12]

def construir():
    global rebalanceos
    rebalanceos = 0
    r = None
    for c in ORDEN: r = insertarAVL(r, c)
    assert rebalanceos == 0                  # se construye sin rotar: la forma es exactamente la del dibujo
    return r

print("ARBOL INICIAL")
print(f"  orden de insercion: {ORDEN}")
ver("inicial", construir())

# ---------- Eliminacion: paso a paso ----------
print("\nELIMINACION DEL 1, PASO A PASO")
r = construir()
r.izq.izq = None; recalc(r.izq); recalc(r)
ver("sin el 1", r)
print("    Desbalanceado solo el 2 (fe=-2). La raiz 5 aun esta bien (fe=-1).")
r.izq = rotarIzquierda(r.izq); recalc(r)
ver("tras rotar en el 2", r)
print("    Ese subarbol bajo de altura 2 a 1 y ahora la raiz 5 quedo desbalanceada (fe=-2).")
r = rotarIzquierda(r)
ver("tras rotar en el 5", r)
assert esAVL(r)

r2 = eliminarAVL(construir(), 1)
s1 = []; s2 = []; preorden(r, s1); preorden(r2, s2)
assert s1 == s2 and rebalanceos == 2
print(f"    eliminarAVL(1) llega al mismo arbol con {rebalanceos} rebalanceos.")

# ---------- Insercion: el mismo arbol ----------
print("\nINSERCION DEL 13 EN EL MISMO ARBOL")
r = construir()
ver("inicial", r)
r = insertarAVL(r, 13)
ver("con el 13", r)
assert esAVL(r) and rebalanceos == 1 and alt(r) == 4
print(f"    {rebalanceos} rebalanceo en el 11: el subarbol recupera la altura de antes y arriba nadie lo nota.")

# ---------- Verificacion masiva ----------
print("\nVERIFICACION")
maxInsercion = 0
for orden in permutations(range(1, 8)):
    r = None
    for c in orden:
        rebalanceos = 0
        r = insertarAVL(r, c)
        maxInsercion = max(maxInsercion, rebalanceos)
    assert esAVL(r)
print(f"  Las 5040 permutaciones de 1 a 7: maximo {maxInsercion} rebalanceo por insercion")

random.seed(40)
maxInsercion = 0; maxEliminacion = 0; conVarios = 0; eliminaciones = 0
for _ in range(50):
    claves = list(range(200))
    random.shuffle(claves)
    r = None
    for c in claves:
        rebalanceos = 0
        r = insertarAVL(r, c)
        maxInsercion = max(maxInsercion, rebalanceos)
        assert esAVL(r)
    random.shuffle(claves)
    for c in claves:
        rebalanceos = 0
        r = eliminarAVL(r, c)
        maxEliminacion = max(maxEliminacion, rebalanceos)
        conVarios += rebalanceos >= 2
        eliminaciones += 1
        assert esAVL(r)
print(f"  50 arboles aleatorios de 200 claves: maximo {maxInsercion} rebalanceo por insercion")
print(f"  y maximo {maxEliminacion} por eliminacion ({conVarios} de {eliminaciones} eliminaciones necesitaron 2 o mas)")
