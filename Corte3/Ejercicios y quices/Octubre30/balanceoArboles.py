# 30 Octubre Quiz

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

def insertar(n, c):                         # insercion BST SIN balancear
    if n is None: return Nodo(c)
    if c < n.clave:   n.izq = insertar(n.izq, c)
    elif c > n.clave: n.der = insertar(n.der, c)
    recalc(n)
    return n

def inorden(n, s):
    if n is None: return
    inorden(n.izq, s); s.append(n.clave); inorden(n.der, s)

def preorden(n, s):
    if n is None: return
    s.append(f"{n.clave}(fe={fe(n)})"); preorden(n.izq, s); preorden(n.der, s)

def ver(titulo, raiz):
    s = []; preorden(raiz, s)
    t = []; inorden(raiz, t)
    print(f"  {titulo:22s} preorden: {' '.join(s)}")
    print(f"  {'':22s} inorden : {t}   altura={alt(raiz)}")

def diagnosticar(r):
    f = fe(r)
    if f > 1:                                # pesa la izquierda
        return "LL" if fe(r.izq) >= 0 else "LR"
    if f < -1:                               # pesa la derecha
        return "RR" if fe(r.der) <= 0 else "RL"
    return "EQUILIBRADO"

def balancear(r, caso):
    if caso == "LL":
        print("  -> una rotacion DERECHA sobre la raiz")
        r = rotarDerecha(r)
    elif caso == "RR":
        print("  -> una rotacion IZQUIERDA sobre la raiz")
        r = rotarIzquierda(r)
    elif caso == "LR":
        print("  -> IZQUIERDA sobre el hijo, luego DERECHA sobre la raiz")
        r.izq = rotarIzquierda(r.izq); recalc(r); ver("tras rotar el hijo", r)
        r = rotarDerecha(r)
    elif caso == "RL":
        print("  -> DERECHA sobre el hijo, luego IZQUIERDA sobre la raiz")
        r.der = rotarDerecha(r.der); recalc(r); ver("tras rotar el hijo", r)
        r = rotarIzquierda(r)
    else:
        print("  -> no hace falta rotar")
    return r

claves = []
while len(claves) < 3:
    try:
        claves.append(int(input(f"Clave {len(claves) + 1}: ")))
    except ValueError:
        print("  Ingrese un numero entero")

r = None
for c in claves: r = insertar(r, c)

ver("antes", r)
hijo = r.izq if fe(r) > 0 else r.der
caso = diagnosticar(r)
print(f"\n  fe raiz = {fe(r)}, fe hijo pesado = {fe(hijo)}  ->  caso {caso}")
r = balancear(r, caso)
ver("despues", r)
