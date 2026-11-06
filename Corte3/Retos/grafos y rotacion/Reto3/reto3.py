# Reto 3 - El grafo imposible: ¿para que V y grado k existe un grafo donde todos tengan grado k?
# Grafo simple: no dirigido, sin lazos y sin aristas repetidas. Respuesta completa en respuesta.md
from itertools import combinations

def grados(V, aristas):
    g = [0]*V
    for u, v in aristas:
        g[u] += 1
        g[v] += 1
    return g

def esPosible(V, k):
    return 0 <= k <= V - 1 and V*k % 2 == 0

def motivo(V, k):
    if k > V - 1: return "k>=V"
    if V*k % 2 == 1: return "impar"
    return "si"

# Vertices en circulo: cada uno se une con sus k//2 vecinos a cada lado y, si k es impar, con el opuesto
def construirRegular(V, k):
    aristas = [(i, (i + s) % V) for i in range(V) for s in range(1, k//2 + 1)]
    if k % 2 == 1:
        aristas += [(i, i + V//2) for i in range(V//2)]
    return aristas

# Prueba todos los grafos posibles de V vertices: 2^(V(V-1)/2) subconjuntos de aristas
def existePorFuerzaBruta(V, k):
    pares = list(combinations(range(V), 2))
    for mascara in range(1 << len(pares)):
        elegidas = [pares[b] for b in range(len(pares)) if mascara >> b & 1]
        if all(g == k for g in grados(V, elegidas)):
            return True
    return False

# ---------- El intento de dibujarlo: V = 5, k = 3 ----------
INTENTO = [(0,4), (1,4), (2,3), (0,2), (1,2), (0,3), (1,3)]
g = grados(5, INTENTO)
print("INTENTO CON V = 5 Y GRADO 3")
print(f"  Mejor intento: {len(INTENTO)} aristas, grados {g}  (suma {sum(g)}). Al vertice 4 le falta una arista")
print("  y los demas ya tienen grado 3: cualquier arista nueva deja a otro vertice con grado 4.")
print(f"  Suma necesaria = 5*3 = 15, pero la suma siempre es 2E (par): E = 15/2 = {15/2} no es entero.")
print(f"  Fuerza bruta sobre los 2^10 grafos de 5 vertices: existe = {existePorFuerzaBruta(5, 3)}")

# ---------- Generalizacion ----------
MAX_V = 8
print("\n¿EXISTE UN GRAFO CON V VERTICES, TODOS DE GRADO k?")
print("  si = existe | impar = V*k es impar | k>=V = no alcanzan los vertices")
print("      " + "".join(f"{'k=' + str(k):>7}" for k in range(MAX_V + 1)))
for V in range(1, MAX_V + 1):
    print(f"  V={V} " + "".join(f"{motivo(V, k):>7}" for k in range(MAX_V + 1)))

# ---------- Verificacion de la regla ----------
print("\nVERIFICACION")
for V in range(1, 7):
    for k in range(V + 1):
        assert existePorFuerzaBruta(V, k) == esPosible(V, k), (V, k)
print("  Fuerza bruta: la regla acierta en todos los casos con V <= 6 y 0 <= k <= V")

for V in range(1, 31):
    for k in range(V):
        if esPosible(V, k):
            aristas = construirRegular(V, k)
            sinRepetir = {tuple(sorted(a)) for a in aristas}
            assert len(sinRepetir) == len(aristas) == V*k//2, (V, k)
            assert all(u != v for u, v in aristas), (V, k)
            assert all(g == k for g in grados(V, aristas)), (V, k)
print("  Construccion: todo caso posible con V <= 30 da un grafo simple con los grados pedidos")
