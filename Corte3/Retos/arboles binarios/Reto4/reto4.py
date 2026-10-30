
class Nodo:
    def __init__(self, codigo, nombre=""):
        self.codigo = codigo; self.nombre = nombre
        self.izq = None; self.der = None

def insertar(n, codigo, nombre=""):
    if n is None: return Nodo(codigo, nombre)
    if codigo < n.codigo: n.izq = insertar(n.izq, codigo, nombre)   # el retorno se REENGANCHA
    elif codigo > n.codigo: n.der = insertar(n.der, codigo, nombre)
    # codigo repetido: no se inserta
    return n

def buscar(n, codigo, pasos=None):
    if pasos is not None and n is not None: pasos.append(n.codigo)
    if n is None or n.codigo == codigo: return n
    return buscar(n.izq, codigo, pasos) if codigo < n.codigo else buscar(n.der, codigo, pasos)

def inorden(n, s):
    if n is None: return
    inorden(n.izq, s); s.append(n); inorden(n.der, s)

def listarOrdenado(raiz):
    s = []; inorden(raiz, s)
    print("Listado ordenado por codigo:")
    for nodo in s:
        print(f"  {nodo.codigo}  {nodo.nombre}")

def informe(raiz, codigo):
    pasos = []; r = buscar(raiz, codigo, pasos)
    camino = " -> ".join(str(p) for p in pasos)
    if r:
        print(f"informe({codigo}): {r.nombre}  (camino {camino}, {len(pasos)} comparaciones)")
    else:
        print(f"informe({codigo}): codigo no encontrado  (camino {camino}, {len(pasos)} comparaciones)")

# Recursos de la linea de proyecto (laboratorio de software)
recursos = [
    (500, "Servidor de pruebas"),
    (300, "Portatil de desarrollo"),
    (700, "Licencia de IDE"),
    (200, "Router del laboratorio"),
    (400, "Base de datos PostgreSQL"),
    (600, "Repositorio GitHub"),
    (800, "Cuenta en la nube"),
    (350, "Monitor externo"),
    (450, "Disco duro de respaldo"),
    (650, "Manual de estilo de codigo"),
    (750, "Tablero Kanban"),
    (150, "Impresora 3D"),
]

raiz = None
for codigo, nombre in recursos:
    raiz = insertar(raiz, codigo, nombre)

listarOrdenado(raiz)
print()
for codigo in [500, 450, 150, 750, 999, 100]:
    informe(raiz, codigo)
