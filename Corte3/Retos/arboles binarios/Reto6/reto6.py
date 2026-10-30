# Reto 3 - El detector de impostores
# esBST(nodo) determina si un arbol binario cualquiera cumple la invariante.
# Comparar cada nodo solo con sus dos hijos NO basta: cada nodo tiene un rango
# permitido (minimo, maximo) que se va estrechando al bajar.
#   al bajar por la izquierda el maximo pasa a ser la clave del nodo
#   al bajar por la derecha el minimo pasa a ser la clave del nodo

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

def esBST(n, minimo=None, maximo=None):
    if n is None: return True
    if minimo is not None and n.clave <= minimo: return False
    if maximo is not None and n.clave >= maximo: return False
    return esBST(n.izq, minimo, n.clave) and esBST(n.der, n.clave, maximo)

def esBSTIngenuo(n):
    # version incorrecta: solo compara con los hijos directos
    if n is None: return True
    if n.izq is not None and n.izq.clave >= n.clave: return False
    if n.der is not None and n.der.clave <= n.clave: return False
    return esBSTIngenuo(n.izq) and esBSTIngenuo(n.der)

# Arbol construido con insertar: siempre cumple la invariante
raiz = None
for c in [50, 30, 70, 20, 40, 60, 80, 35]:
    raiz = insertar(raiz, c)
print("Arbol del ejemplo:  esBST =", esBST(raiz), "  esBSTIngenuo =", esBSTIngenuo(raiz))

# Contraejemplo armado a mano: raiz 50, hijo izquierdo 30, hijo DERECHO del 30 es 60
impostor = Nodo(50)
impostor.izq = Nodo(30)
impostor.izq.der = Nodo(60)
print("Contraejemplo:      esBST =", esBST(impostor), "  esBSTIngenuo =", esBSTIngenuo(impostor))
print("El 60 esta en el subarbol izquierdo del 50 y es mayor que 50: NO es BST")

# Salida:
# Arbol del ejemplo:  esBST = True   esBSTIngenuo = True
# Contraejemplo:      esBST = False   esBSTIngenuo = True
# El 60 esta en el subarbol izquierdo del 50 y es mayor que 50: NO es BST
