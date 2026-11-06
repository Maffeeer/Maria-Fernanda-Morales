# Reto 2 - El orden maldito: como cambia la altura del BST segun el orden de insercion de 1 a 7
from itertools import permutations
from math import comb

class Nodo:
    def __init__(self, c):
        self.clave = c; self.izq = None; self.der = None; self.alt = 0

def alt(n):  return -1 if n is None else n.alt
def recalc(n): n.alt = 1 + max(alt(n.izq), alt(n.der))

def insertar(n, c):                         # insercion BST SIN balancear
    if n is None: return Nodo(c)
    if c < n.clave:   n.izq = insertar(n.izq, c)
    elif c > n.clave: n.der = insertar(n.der, c)
    recalc(n)
    return n

def preorden(n, s):
    if n is None: return
    s.append(n.clave); preorden(n.izq, s); preorden(n.der, s)

def construir(orden):
    r = None
    for c in orden: r = insertar(r, c)
    return r

def ver(titulo, orden):
    r = construir(orden); s = []; preorden(r, s)
    print(f"  {titulo:20s} {orden}  altura={alt(r)}  preorden={s}")

# Padre de cada clave en el arbol perfecto: 4 es la raiz, 2 y 6 sus hijos
PADRE = {2:4, 6:4, 1:2, 3:2, 5:6, 7:6}

def padresAntes(orden):                     # cada clave llega despues de su padre
    return all(orden.index(p) < orden.index(h) for h, p in PADRE.items())

def siempreExtremo(orden):                  # cada clave es el minimo o el maximo de las que faltan
    return all(orden[i] in (min(orden[i:]), max(orden[i:])) for i in range(len(orden)))

# ---------- Ejemplos ----------
print("EJEMPLOS")
ver("mejor (por niveles)", (4,2,6,1,3,5,7))
ver("mejor (preorden)", (4,2,1,3,6,5,7))
ver("peor (ordenado)", (1,2,3,4,5,6,7))
ver("peor (zigzag)", (1,7,2,6,3,5,4))
ver("empieza por 4, malo", (4,1,2,3,5,6,7))

# ---------- Todas las permutaciones ----------
todas = list(permutations(range(1, 8)))
porAltura = {}
for orden in todas:
    porAltura.setdefault(alt(construir(orden)), []).append(orden)

print(f"\nLOS {len(todas)} ORDENES POSIBLES, SEGUN LA ALTURA QUE PRODUCEN")
for h in sorted(porAltura):
    print(f"  altura {h}: {len(porAltura[h]):>5} ordenes ({100*len(porAltura[h])/len(todas):5.2f}%)  primero: {porAltura[h][0]}")

# ---------- Que tienen en comun ----------
mejores = porAltura[2]; peores = porAltura[6]
assert all(o[0] == 4 for o in mejores)
assert {o for o in todas if padresAntes(o)} == set(mejores)
assert {o for o in todas if siempreExtremo(o)} == set(peores)
print("\nQUE TIENEN EN COMUN")
print("  Altura 2 <=> cada clave llega despues de su padre: 4 antes que todas, 2 antes que 1 y 3, 6 antes que 5 y 7.")
print(f"  Conteo: C(6,3) * 2 * 2 = {comb(6,3)} * 2 * 2 = {comb(6,3)*2*2}  (coincide con los {len(mejores)} encontrados)")
print("  Altura 6 <=> cada clave es el minimo o el maximo de las que faltan.")
print(f"  Conteo: 2^6 = {2**6}  (coincide con los {len(peores)} encontrados)")
