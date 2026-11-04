# Sesion 40 — Grafos: matriz de adyacencia frente a lista de adyacencia
from grafo_base import NOMBRES, ARISTAS, N

# ---------- Representacion 1: matriz de adyacencia ----------
matriz = [[0]*N for _ in range(N)]
for u, v in ARISTAS:
    matriz[u][v] = 1              # grafo dirigido: solo u -> v, la matriz NO es simetrica

print("MATRIZ DE ADYACENCIA")
print("            " + " ".join(f"{n[:3]:>4}" for n in NOMBRES))
for i in range(N):
    print(f"{NOMBRES[i]:>11} " + " ".join(f"{matriz[i][j]:>4}" for j in range(N)))

# ---------- Representacion 2: lista de adyacencia ----------
lista = [[] for _ in range(N)]
for u, v in ARISTAS:
    lista[u].append(v)            # A -> B y B -> A son dos aristas distintas
for v in lista: v.sort()

print("\nLISTA DE ADYACENCIA")
for i in range(N):
    print(f"  {NOMBRES[i]:>10} -> {', '.join(NOMBRES[j] for j in lista[i])}")

# ---------- Grados ----------
print("\nGRADO DE CADA VERTICE (cuantas vias salen de el y cuantas entran)")
for i in range(N):
    g_mat = sum(matriz[i])        # recorrer una fila: O(N)
    g_lis = len(lista[i])         # leer el tamano: O(1)
    assert g_mat == g_lis
    g_ent = sum(matriz[j][i] for j in range(N))   # recorrer una columna: O(N)
    print(f"  {NOMBRES[i]:>10}: salen {g_lis}, entran {g_ent}")

# ---------- Costos ----------
aristas = len(ARISTAS)
print(f"\nV = {N} vertices,  E = {aristas} aristas")
print(f"  Matriz : {N*N} casillas en memoria. ¿Existe arista? O(1). Recorrer vecinos: O(V) = {N} casillas.")
print(f"  Lista  : {aristas} referencias en memoria. ¿Existe arista? O(grado). Recorrer vecinos: O(grado).")
densidad = aristas / (N*(N-1))
print(f"  Densidad = E / (V(V-1)) = {densidad:.2f}  ->  grafo {'DENSO: conviene matriz' if densidad > 0.5 else 'DISPERSO: conviene lista'}")

# ---------- Consulta de arista ----------
def hay_via_matriz(u, v): return matriz[u][v] == 1
def hay_via_lista(u, v):  return v in lista[u]
for u, v in [(0,1),(0,7),(5,6)]:
    print(f"  ¿{NOMBRES[u]} conecta con {NOMBRES[v]}? matriz={hay_via_matriz(u,v)}  lista={hay_via_lista(u,v)}")

# consulta de aristas desde sede centro
origen = NOMBRES.index("CENTRO")
for i in range(N):
    if i != origen:
        print(f"  ¿{NOMBRES[origen]} conecta con {NOMBRES[i]}? matriz={hay_via_matriz(origen,i)}  lista={hay_via_lista(origen,i)}")
