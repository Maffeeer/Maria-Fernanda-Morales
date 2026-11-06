from collections import deque
from grafo_base import NOMBRES, ARISTAS, N

lista = [[] for _ in range(N)]
for u, v in ARISTAS:
    lista[u].append(v); lista[v].append(u)
for v in lista: v.sort()

COLORES = ["AZUL", "VERDE", "ROJO", "BLANCO"]    # el color de cada nivel
CENTRO, OCCIDENTE, USAQUEN, BOSA, VEREDA = 0, 4, 6, 7, 8

# BFS
def bfs(inicio):
    visitado = [False] * N
    dist  = [-1] * N          # distancia en numero de tramos
    padre = [-1] * N          # de donde llegue: permite reconstruir el camino
    cola = deque([inicio])
    visitado[inicio] = True   # se marca al ENCOLAR
    dist[inicio] = 0
    orden = []
    while cola:
        u = cola.popleft()    # FIFO
        orden.append(u)
        for v in lista[u]:
            if not visitado[v]:
                visitado[v] = True
                dist[v]  = dist[u] + 1
                padre[v] = u
                cola.append(v)
    return orden, dist, padre

# Reconstruir el camino
def camino(padre, destino):
    c = []
    u = destino
    while u != -1:
        c.append(u)
        u = padre[u]
    c.reverse()
    return c

def textoCamino(c):
    return f"{' -> '.join(NOMBRES[i] for i in c)}   ({len(c) - 1} tramos)"

padre = bfs(CENTRO)[2]        # bfs devuelve (orden, dist, padre): solo se usa padre

print()
for destino in [VEREDA]:
    print(f"  BFS hacia {NOMBRES[destino]:<7}: {textoCamino(camino(padre, destino))}")

print(f"\nEl camino mas corto de CENTRO a VEREDA es: {textoCamino(camino(padre, VEREDA))}")
