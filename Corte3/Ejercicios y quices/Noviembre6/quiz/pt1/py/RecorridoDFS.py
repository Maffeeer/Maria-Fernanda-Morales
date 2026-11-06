from grafo_base import NOMBRES, ARISTAS, N

lista = [[] for _ in range(N)]
for u, v in ARISTAS:
    lista[u].append(v); lista[v].append(u)
for v in lista: v.sort()

# ---------- DFS recursivo ----------
def dfs_rec(u, visitado, orden, prof=0, traza=None):
    visitado[u] = True
    orden.append(u)
    if traza is not None:
        traza.append(f"{'  '*prof}entra {NOMBRES[u]}")
    for v in lista[u]:
        if not visitado[v]:
            dfs_rec(v, visitado, orden, prof+1, traza)
        elif traza is not None:
            traza.append(f"{'  '*(prof+1)}{NOMBRES[v]} ya visitado, no entra")
    if traza is not None:
        traza.append(f"{'  '*prof}sale  {NOMBRES[u]}")

vis = [False]*N; orden = []; traza = []
dfs_rec(0, vis, orden, 0, traza)
print("DFS RECURSIVO desde CENTRO")
for t in traza: print("  " + t)
print("  orden de visita:", " -> ".join(NOMBRES[i] for i in orden))

# ---------- DFS iterativo con pila ----------
def dfs_iter(inicio):
    visitado = [False]*N
    pila = [inicio]; orden = []
    while pila:
        u = pila.pop()                      # LIFO: saca el ultimo que entro
        if visitado[u]: continue
        visitado[u] = True
        orden.append(u)
        for v in reversed(lista[u]):        # al revés para igualar el orden del recursivo
            if not visitado[v]: pila.append(v)
    return orden

print("\nDFS ITERATIVO (con pila explicita) desde CENTRO")
print("  orden de visita:", " -> ".join(NOMBRES[i] for i in dfs_iter(0)))

# ---------- Aplicacion 1: componentes conexas ----------
def componentes():
    visitado = [False]*N; comps = []
    for s in range(N):
        if not visitado[s]:
            o = []; dfs_rec(s, visitado, o)
            comps.append([NOMBRES[i] for i in o])
    return comps
print("\nCOMPONENTES CONEXAS de la red completa:", componentes())

# red con un punto aislado y un par suelto
lista_rota = [[] for _ in range(N)]
for u, v in [(0,1),(0,2),(3,6)]:
    lista_rota[u].append(v); lista_rota[v].append(u)
lista_orig = lista
lista = lista_rota
print("COMPONENTES de una red con tramos cortados:", componentes())
lista = lista_orig

# ---------- Aplicacion 2: deteccion de ciclo ----------
def hay_ciclo():
    visitado = [False]*N
    def explorar(u, padre):
        visitado[u] = True
        for v in lista[u]:
            if not visitado[v]:
                if explorar(v, u): return True
            elif v != padre:          # vecino ya visitado que NO es de donde vengo
                return True
        return False
    for s in range(N):
        if not visitado[s] and explorar(s, -1): return True
    return False
print("¿La red tiene algun circuito?", hay_ciclo())