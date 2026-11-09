# ============================================================
#  Laboratorio integrador · Corte 3 · RETO 1  (25 puntos)
#  Sesiones 35 y 36 — Arboles binarios y BST
#  Sistema: RedAcopio — indice de recursos por codigo
#
#  MODIFIQUE SOLO ESTE ARCHIVO.  NO TOQUE pruebas_r1.py
#  Ejecute:   python3 pruebas_r1.py
# ============================================================


class Nodo:
    def __init__(self, codigo, nombre):
        self.codigo = codigo
        self.nombre = nombre
        self.izq = None
        self.der = None


def insertar(n, codigo, nombre):
    """Inserta en el BST respetando la invariante: menores a la izquierda, mayores a la derecha. Si el codigo ya existe, NO se inserta. Devuelve la raiz del subarbol (patron de reenganche)."""
    
    if n is None: 
        return Nodo(codigo, nombre)          # Se llega a un hueco entonces se crea el nodo y se devuelve
    if codigo < n.codigo: 
        n.izq = insertar(n.izq, codigo, nombre)   # En este caso el recorrido es por la izquierda, se reengancha el subarbol izquierdo
    elif codigo > n.codigo: 
        n.der = insertar(n.der, codigo, nombre)
    # Cuando el codigo es igual, no se hace nada es decir que no se inserta como en los otros casos
    return n


def inorden(n, salida):
    """Ya implementado: recorre izquierda, raiz, derecha."""
    
    if n is None:
        return
    inorden(n.izq, salida)
    salida.append(n.codigo)
    inorden(n.der, salida)


def altura(n):
    """Numero de aristas del camino mas largo de n hasta una hoja. Un arbol vacio tiene altura -1; un solo nodo, altura 0."""

    if n is None: return -1 #  Arbol vacio
    return 1 + max(altura(n.izq), altura(n.der)) # Se suma 1 por la arista que conecta el nodo actual con su hijo y se toma el máximo entre las alturas de los subárboles izquierdo y derecho.


def buscar(n, codigo):
    """Devuelve (nodo, comparaciones). Si no esta, el nodo es None.Debe bajar comparando, NO recorrer todo el arbol."""

    comparaciones = 0
    while n is not None:                      # Aqui es donde se hace la busqueda, mientras n no sea None, se compara el codigo con el codigo del nodo actual
        comparaciones += 1
        if codigo == n.codigo: return n, comparaciones
        n = n.izq if codigo < n.codigo else n.der
    return None, comparaciones                # Si se sale del while, significa que no se encontro el nodo, entonces se devuelve None y el numero de comparaciones realizadas


def minimo(n):
    """Ya implementado: el extremo izquierdo."""
    while n.izq is not None:
        n = n.izq
    return n
