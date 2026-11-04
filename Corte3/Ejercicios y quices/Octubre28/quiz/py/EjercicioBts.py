# BTS 50,30,70,20,40,60,80 y 35
#medir cuantos hijos tiene cada nodo antes de eliminar.

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

def buscar(n, clave, pasos=None):
    if pasos is not None: pasos.append("vacio" if n is None else str(n.clave))
    if n is None or n.clave == clave: return n
    return buscar(n.izq, clave, pasos) if clave < n.clave else buscar(n.der, clave, pasos)

def minimo(n):
    while n.izq is not None: n=n.izq
    return n
 
def maximo(n):
    while n.der is not None: n = n.der
    return n
 
def eliminar(n, clave):
    if n is None: return None
    if clave < n.clave: n.izq = eliminar(n.izq, clave)
    elif clave > n.clave: n.der = eliminar(n.der, clave)
    else: #encontramos el nodo a eliminar
        if n.izq is None: return n.der
        if n.der is None: return n.izq
        suc=minimo(n.der)
        n.clave,n.nombre=suc.clave,suc.nombre
        n.der=eliminar(n.der,suc.clave)
    return n
def inorden(n, s):
    if n is None: return
    inorden(n.izq, s); s.append(n.clave); inorden(n.der, s)
    
def altura(n):
    if n is None: return -1
    return 1 + max(altura(n.izq), altura(n.der))
raiz=None
for c in [50,30,70,20,40,60,80,35]:
    raiz=insertar(raiz,c)
s=[];inorden(raiz,s); print("Inorden (queda ordenado):",s)
print("minimo =",minimo(raiz).clave," maximo =",maximo(raiz).clave," altura =",altura(raiz))

for objetivo in [40,65]:
    p=[]; r=buscar(raiz,objetivo,p)
    print(f"buscar({objetivo}): camino {' ->'.join(p)}  =>{'ENCONTRADO' if r else 'NO ESTA'} ({len(p)} comparaciones)")
    
def hijos(n,clave):
    n=buscar(n,clave)
    if n is None: return -1
    return (1 if n.izq else 0) + (1 if n.der else 0)
NOOMBRE={0:"caso 1: hoja, 0 hijos", 1:"caso 2: un hijo", 2:"caso 3: dos hijos"}
for clave in [20,30,50]:
    k=hijos(raiz,clave )
    raiz=eliminar(raiz,clave)
    s=[];inorden(raiz,s)
    print(f"eliminar({clave}) [{NOOMBRE[k]}] ->",s)
deg=None
for c in [10,20,30,40,50,60,70,80]:
    deg=insertar(deg,c)
print(f"\nBTS con datos ordenados: altura = {altura(deg)} con 8 nodos (una lista enlazada)")
print(f"BTS con datos mezclados: altura = {altura(raiz)} con 8 nodos (log2(8) = 3)")



# Salida: Inorden (queda ordenado): [20, 30, 35, 40, 50, 60, 70, 80]
#minimo = 20  maximo = 80  altura = 3
#buscar(40): camino 50 -> 30 -> 40  =>  ENCONTRADO  (3 comparaciones)
#buscar(65): camino 50 -> 70 -> 60 -> vacio  =>  NO ESTA  (4 comparaciones)
#eliminar(20) [caso 1: hoja, 0 hijos] -> [30, 35, 40, 50, 60, 70, 80]
#eliminar(30) [caso 2: un hijo] -> [35, 40, 50, 60, 70, 80]
#eliminar(50) [caso 3: dos hijos] -> [35, 40, 60, 70, 80]
#BST con datos ordenados: altura = 7 con 8 nodos (una lista enlazada)
#BST con datos mezclados: altura = 3 con 8 nodos (log2(8) = 3)