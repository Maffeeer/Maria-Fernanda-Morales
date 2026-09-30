import time
import random

class Registro:
    'La clase Registro representa un registro con un id, un nombre y un valores'
    def __init__(self, id, nombre, valor):
        self.id = id
        self.nombre = nombre
        self.valor = valor

    def __repr__(self): #La función __repr__ devuelve una representación legible del objeto Registro
        return f"Registro({self.id}, {self.nombre}, {self.valor})"

    def __lt__(self, otro): #Define si es menor que otro registro
        return self.valor < otro.valor

    def __le__(self, otro): #Define si es mayor o igual que otro registro
        return self.valor <= otro.valor

    def __gt__(self, otro): #Define si es mayor que otro registro
        return self.valor > otro.valor

    def __eq__(self, otro):#Define si son iguales dos registros
        return self.valor == otro.valor


class Analizar: #Buscando la forma más eficiente de analizar los algoritmos de búsqueda y ordenamiento, es hacer una clase a implementar en todas las partes y funciones
    
    def __init__(self, datos):
        self.datos = datos[:]
        self.comparaciones = 0
        self.intercambios = 0

    #Parte B: Búsqueda

    def busquedaSecuencial(self, target_valor):
        'Es búsqueda lineal y cuenta comparaciones'
        self.comparaciones = 0
        for i in range(len(self.datos)):
            self.comparaciones += 1
            if self.datos[i].valor == target_valor:
                return i
        return -1

    def busquedaBinaria(self, target_valor):
        'Busqueda binaria cuando los datos son ordenados y cuenta comparaciones'
        self.comparaciones = 0
        izq, der = 0, len(self.datos) - 1

        while izq <= der:
            self.comparaciones += 1
            mid = (izq + der) // 2
            if self.datos[mid].valor == target_valor:
                return mid
            elif self.datos[mid].valor < target_valor:
                izq = mid + 1
            else:
                der = mid - 1
        return -1

    # Parte C: Ordenamientos principales

    def bubbleSort(self):
        self.comparaciones = 0
        self.intercambios = 0
        n = len(self.datos)

        for i in range(n):
            swapped = False
            for j in range(0, n - i - 1):
                self.comparaciones += 1
                if self.datos[j] > self.datos[j + 1]:
                    self.datos[j], self.datos[j + 1] = self.datos[j + 1], self.datos[j]
                    self.intercambios += 1
                    swapped = True
            if not swapped:
                break

    def selectionSort(self):
        self.comparaciones = 0
        self.intercambios = 0
        n = len(self.datos)

        for i in range(n):
            min_idx = i
            for j in range(i + 1, n):
                self.comparaciones += 1
                if self.datos[j] < self.datos[min_idx]:
                    min_idx = j
            if min_idx != i:
                self.datos[i], self.datos[min_idx] = self.datos[min_idx], self.datos[i]
                self.intercambios += 1

    def insertionSort(self):
        self.comparaciones = 0
        self.intercambios = 0

        for i in range(1, len(self.datos)):
            key = self.datos[i]
            j = i - 1
            while j >= 0:
                self.comparaciones += 1
                if self.datos[j] > key:
                    self.datos[j + 1] = self.datos[j]
                    self.intercambios += 1
                    j -= 1
                else:
                    break
            if j != i - 1:
                self.datos[j + 1] = key

    #Parte D: Merge Sort

    #Para este punto me ayude con IA, me dice que la mejor forma de implementar merge sort es con recursividad, y que es un algoritmo de ordenamiento eficiente basado en el paradigma divide y vencerás. Divide la lista en mitades, ordena cada mitad y luego las combina.

    def mergeSort(self):
        self.comparaciones = 0
        self.intercambios = 0
        self._mergeSortRec(0, len(self.datos) - 1)

    def _mergeSortRec(self, izq, der): #  
        if izq < der:
            mid = (izq + der) // 2
            self._mergeSortRec(izq, mid)
            self._mergeSortRec(mid + 1, der)
            self._merge(izq, mid, der)

    def _merge(self, izq, mid, der):
        izq_arr = self.datos[izq:mid + 1]
        der_arr = self.datos[mid + 1:der + 1]

        i = j = 0
        k = izq

        while i < len(izq_arr) and j < len(der_arr):
            self.comparaciones += 1
            if izq_arr[i] <= der_arr[j]:
                self.datos[k] = izq_arr[i]
                i += 1
            else:
                self.datos[k] = der_arr[j]
                j += 1
            k += 1
            self.intercambios += 1

        while i < len(izq_arr):
            self.datos[k] = izq_arr[i]
            i += 1
            k += 1
            self.intercambios += 1

        while j < len(der_arr):
            self.datos[k] = der_arr[j]
            j += 1
            k += 1
            self.intercambios += 1

def ingresarRegistros():

    registros = []
    print('Ingreso de Registros')
    print("Ingrese registros. Escriba '0' para terminar.\n")

    contador = 1
    while True:
        nombre = input(f"Nombre del registro {contador} (o '0' para terminar): ").strip()
        if nombre == '0':
            if contador == 1:
                print("Error: Ingrese al menos un registro.")
                continue
            break

        try:
            valor = int(input(f"Valor del registro: "))
            registros.append(Registro(contador, nombre, valor))
            contador += 1
        except ValueError:
            print("Error: El valor debe ser un número entero.\n")

    return registros


#Main

if __name__ == "__main__":
    registros = ingresarRegistros()

# Parte B
print('Comparación (Secuencial vs Binaria)')

datosBusqueda = [3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5]
datosBusqueda.sort()
print(f"\nDatos ordenados: {datosBusqueda}\n")

analizador = Analizar(datosBusqueda)

# Casos de búsqueda
casos = [
    ("Primer elemento", datosBusqueda[0]),
    ("Elemento del medio", datosBusqueda[len(datosBusqueda)//2]),
    ("Último elemento", datosBusqueda[-1]),
    ("Elemento que NO existe", 999)
]

print(f"{'Caso'} {'Secuencial'} {'Binaria'}")

for nombreCaso, target in casos:
    analizador.datos = datosBusqueda[:]

    # Búsqueda secuencial
    analizador.busquedaSecuencial(target)
    comp_sec = analizador.comparaciones

    # Búsqueda binaria
    analizador.busquedaBinaria(target)
    comp_bin = analizador.comparaciones

    print(f"{nombreCaso} {comp_sec} {comp_bin}")

# Prueba con datos desordenados
print("\n--- Con datos desordenados ---")
datosDesordenados = [3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5]  # Sin ordenar
print(f"Datos desordenados: {datosDesordenados}\n")

analizador.datos = datosDesordenados
print(f"{'Caso'} {'Secuencial'} {'Binaria (no es válida en datos desordenados)'}")

for nombreCaso, target in casos:
    analizador.datos = datosDesordenados[:]

    # Búsqueda secuencial
    analizador.busquedaSecuencial(target)
    comp_sec = analizador.comparaciones

    # La búsqueda binaria en datos desordenados no es confiable
    analizador.busquedaBinaria(target)
    comp_bin = analizador.comparaciones

    print(f"{nombreCaso} {comp_sec} {comp_bin}")

# DIFERENCIA: La búsqueda secuencial trabaja correctamente en ambos casos (ordenados y desordenados)
# porque examina todos los elementos linealmente. Sin embargo, la búsqueda binaria solo es buena
# en datos ordenados; en datos desordenados puede no encontrar el elemento aunque exista, porque
# depende de que el array esté ordenado para eliminar mitades. En datos ordenados, la búsqueda
# binaria reduce significativamente las comparaciones, especialmente en listas grandes.

# Parte C

tamaño = 20

print(f"\nCon datos desordenads (n={tamaño}):")
print(f"{'Algoritmo'} {'Comparaciones'} {'Intercambios'}")

# Datos desordenados
datosDes = ingresarRegistros(tamaño, "desordenado")

for nombre, metodo in [("Bubble Sort", "bubble"), ("Selection Sort", "selection"), ("Insertion Sort", "insertion")]:
    analizador.datos = datosDes[:]
    if metodo == "bubble":
        analizador.bubbleSort()
    elif metodo == "selection":
        analizador.selectionSort()
    else:
        analizador.insertionSort()

    print(f"{nombre} {analizador.comparaciones} {analizador.intercambios}")

print(f"\nCon datos ordenados (n={tamaño}):")
print(f"{'Algoritmo'} {'Comparaciones'} {'Intercambios'}")

# Ordenados
datosOrd = ingresarRegistros(tamaño, "ordenado")

for nombre, metodo in [("Bubble Sort", "bubble"), ("Selection Sort", "selection"), ("Insertion Sort", "insertion")]:
    analizador.datos = datosOrd[:]
    if metodo == "bubble":
        analizador.bubbleSort()
    elif metodo == "selection":
        analizador.selectionSort()
    else:
        analizador.insertionSort()

    print(f"{nombre} {analizador.comparaciones} {analizador.intercambios}")

# Parte D

tamaños = [100, 500, 1000]

print(f"\n{'Tamaño'} {'Bubble (ms)'} {'Merge (ms)'} {'Factor'}")

for tamaño in tamaños:
    datosTest = ingresarRegistros(tamaño, "desordenado")

    # Bubble Sort
    analizador.datos = datosTest[:]
    inicio = time.time()
    analizador.bubbleSort()
    tiempo_bubble = (time.time() - inicio) * 1000

    # Merge Sort
    analizador.datos = datosTest[:]
    inicio = time.time()
    analizador.mergeSort()
    tiempo_merge = (time.time() - inicio) * 1000

    factor = tiempo_bubble / tiempo_merge if tiempo_merge > 0 else 0
    print(f"{tamaño} {tiempo_bubble} {tiempo_merge} {factor}x")

# Parte E - Análisis de complejidad de Merge Sort

tamaños_complejidad = [50, 100, 200, 400]

print(f"\n{'n'} {'Comparaciones'} {'Factor (n/comparaciones)'}")

for tamaño in tamaños_complejidad:
    datosTest = ingresarRegistros(tamaño, "desordenado")
    analizador.datos = datosTest[:]
    analizador.mergeSort()

    factor = tamaño / analizador.comparaciones if analizador.comparaciones > 0 else 0
    print(f"{tamaño} {analizador.comparaciones} {factor}x")

# Interpretación de la tabla:
# Básicamente, la tabla compara el tamaño de la lista (n) con cuántas comparaciones 
# hace Merge Sort, para ver si de verdad es O(n log n). Si lo es, las comparaciones 
# deberían ser más o menos n·log₂(n), así que el factor n/comparaciones debería irse 
# haciendo más chiquito a medida que n crece. Si baja poquito a poquito, listo, 
# se confirma.