# Reto 2 - El converso: de matriz a lista y de lista a matriz
import random

def matrizALista(m):
    return [[j for j in range(len(m)) if m[i][j] == 1] for i in range(len(m))]

def listaAMatriz(l):
    m = [[0]*len(l) for _ in l]
    for u, vecinos in enumerate(l):
        for v in vecinos:
            m[u][v] = 1
    return m

# ---------- Verificacion ----------
fallas = 0

def verificar(nombre, condicion):
    global fallas
    if not condicion: fallas += 1
    print(f"  {'OK   ' if condicion else 'FALLA'} {nombre}")

def idaYVuelta(m):
    return listaAMatriz(matrizALista(m)) == m

def matrizDeAristas(n, aristas):
    m = [[0]*n for _ in range(n)]
    for u, v in aristas:
        m[u][v] = 1
        m[v][u] = 1
    return m

def matrizAleatoria(n, simetrica):
    m = [[random.randint(0, 1) for _ in range(n)] for _ in range(n)]
    if simetrica:
        for i in range(n):
            for j in range(i):
                m[i][j] = m[j][i]
    return m

# Red de vias del proyecto (la misma del reto 1)
RED = matrizDeAristas(10, [(0,1), (0,2), (0,3), (0,5), (1,4), (1,5), (1,9), (2,4),
                           (2,7), (3,5), (3,6), (4,7), (4,9), (5,6), (6,9), (7,8)])

print("IDA Y VUELTA: listaAMatriz(matrizALista(m)) == m")
verificar("red del proyecto", idaYVuelta(RED))
verificar("grafo sin vertices", idaYVuelta([]))
verificar("un vertice sin aristas", idaYVuelta([[0]]))
verificar("vertices sin aristas", idaYVuelta([[0]*4 for _ in range(4)]))
verificar("grafo completo", idaYVuelta([[int(i != j) for j in range(5)] for i in range(5)]))
verificar("dirigido (matriz no simetrica)", idaYVuelta([[0,1,1], [0,0,1], [0,0,0]]))
verificar("con lazo (diagonal en 1)", idaYVuelta([[1,0], [0,0]]))

random.seed(40)
aleatorias = [matrizAleatoria(random.randint(0, 12), i % 2 == 0) for i in range(1000)]
verificar("1000 matrices aleatorias", all(idaYVuelta(m) for m in aleatorias))

# La ida y vuelta no basta: dos conversiones que inviertan las aristas tambien la pasarian
print("\nCONTENIDO: cada conversion por separado")
verificar("matrizALista conserva la direccion", matrizALista([[0,1], [0,0]]) == [[1], []])
verificar("listaAMatriz conserva la direccion", listaAMatriz([[1], []]) == [[0,1], [0,0]])

print("\nVUELTA E IDA: matrizALista(listaAMatriz(l)) == l (con vecinos ordenados y sin repetir)")
l = [[1,2], [0], [0]]
verificar("lista ordenada", matrizALista(listaAMatriz(l)) == l)

print(f"\n{'TODO CORRECTO' if fallas == 0 else f'{fallas} VERIFICACIONES FALLARON'}")
raise SystemExit(1 if fallas else 0)
