import time

# Ordenamientos Basicos

def bubbleSort(arr):
    n = len(arr)
    intentos = 0
    for i in range(n):
        intentos += 1
        swapped = False
        for j in range(0, n - i - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
                swapped = True
        if not swapped:
            break
    return arr, intentos


def selectionSort(arr):
    n = len(arr)
    intentos = 0
    for i in range(n):
        intentos += 1
        min_idx = i
        for j in range(i + 1, n):
            if arr[j] < arr[min_idx]:
                min_idx = j
        arr[i], arr[min_idx] = arr[min_idx], arr[i]
    return arr, intentos


def insertionSort(arr):
    intentos = 0
    for i in range(1, len(arr)):
        intentos += 1
        key = arr[i]
        j = i - 1
        while j >= 0 and arr[j] > key:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key
    return arr, intentos


# Merge Sort y Quicksort

def mergeSort(arr):
    if len(arr) > 1:
        mid = len(arr) // 2
        left_half = arr[:mid]
        right_half = arr[mid:]

        mergeSort(left_half)
        mergeSort(right_half)

        i = j = k = 0

        while i < len(left_half) and j < len(right_half):
            if left_half[i] < right_half[j]:
                arr[k] = left_half[i]
                i += 1
            else:
                arr[k] = right_half[j]
                j += 1
            k += 1

        while i < len(left_half):
            arr[k] = left_half[i]
            i += 1
            k += 1

        while j < len(right_half):
            arr[k] = right_half[j]
            j += 1
            k += 1
    return arr


def quickSort(arr):
    if len(arr) <= 1:
        return arr
    else:
        pivot = arr[len(arr) // 2]
        left = [x for x in arr if x < pivot]
        middle = [x for x in arr if x == pivot]
        right = [x for x in arr if x > pivot]
        return quickSort(left) + middle + quickSort(right)


def quickSortInSitu(arr, izq=0, der=None):
    """Quicksort en el sitio sin crear listas nuevas, usando dos indices que se cruzan."""
    if der is None:
        der = len(arr) - 1

    if izq < der:
        pivote = arr[izq]
        i = izq + 1
        j = der

        while i <= j:
            while i <= j and arr[i] <= pivote:
                i += 1
            while i <= j and arr[j] > pivote:
                j -= 1
            if i < j:
                arr[i], arr[j] = arr[j], arr[i]

        arr[izq], arr[j] = arr[j], arr[izq]

        quickSortInSitu(arr, izq, j - 1)
        quickSortInSitu(arr, j + 1, der)

    return arr


# Heap Sort y Bucket Sort

def heapify(arr, n, i):
    largest = i
    left = 2 * i + 1
    right = 2 * i + 2

    if left < n and arr[left] > arr[largest]:
        largest = left

    if right < n and arr[right] > arr[largest]:
        largest = right

    if largest != i:
        arr[i], arr[largest] = arr[largest], arr[i]
        heapify(arr, n, largest)


def heapSort(arr):
    n = len(arr)

    for i in range(n // 2 - 1, -1, -1):
        heapify(arr, n, i)

    for i in range(n - 1, 0, -1):
        arr[0], arr[i] = arr[i], arr[0]
        heapify(arr, i, 0)

    return arr


def heapifyMinimo(arr, n, i):
    """Heapify para minimos: cambia > por <."""
    smallest = i
    left = 2 * i + 1
    right = 2 * i + 2

    if left < n and arr[left] < arr[smallest]:
        smallest = left

    if right < n and arr[right] < arr[smallest]:
        smallest = right

    if smallest != i:
        arr[i], arr[smallest] = arr[smallest], arr[i]
        heapifyMinimo(arr, n, smallest)


def heapSortMinimo(arr):
    """Heapsort de minimos: ordena de mayor a menor."""
    n = len(arr)

    for i in range(n // 2 - 1, -1, -1):
        heapifyMinimo(arr, n, i)

    for i in range(n - 1, 0, -1):
        arr[0], arr[i] = arr[i], arr[0]
        heapifyMinimo(arr, i, 0)

    return arr


def bucketSort(arr, numeroCubetas=10):
    """Bucket Sort con numero de cubetas variable."""
    if len(arr) == 0:
        return arr

    min_value = min(arr)
    max_value = max(arr)
    bucket_range = (max_value - min_value) / numeroCubetas

    buckets = [[] for _ in range(numeroCubetas)]

    for num in arr:
        if bucket_range == 0:
            index = 0
        else:
            index = int((num - min_value) / bucket_range)
            if index == numeroCubetas:
                index -= 1
        buckets[index].append(num)

    sorted_arr = []
    for bucket in buckets:
        sorted_arr.extend(sorted(bucket))

    return sorted_arr


# Pruebas

def pruebaUno():
    print("Bubble Sort optimizado - Comparaciones en datos ordenados")

    datosOrdenados = list(range(1, 29))
    print(f"Datos ya ordenados (1 a 28): longitud = {len(datosOrdenados)}")
    print()

    arrBubble = datosOrdenados.copy()
    arrBubble, intentosBubble = bubbleSort(arrBubble)

    arrInsertion = datosOrdenados.copy()
    arrInsertion, intentosInsertion = insertionSort(arrInsertion)

    print(f"Bubble Sort con bandera optimizado: {intentosBubble} comparaciones")
    print(f"Insertion Sort: {intentosInsertion} comparaciones")
    print()
    print(f"Bubble baja de 28 comparaciones a {intentosBubble} (como Insertion: {intentosInsertion})")
    print()


def pruebaDos():
    print("Ordenar registros por criterio especifico")

    registros = [
        {"id": 1, "veces_prestado": 15, "saturacion": 45, "urgencia": 8},
        {"id": 2, "veces_prestado": 3, "saturacion": 78, "urgencia": 9},
        {"id": 3, "veces_prestado": 42, "saturacion": 12, "urgencia": 2},
        {"id": 4, "veces_prestado": 8, "saturacion": 88, "urgencia": 10},
        {"id": 5, "veces_prestado": 25, "saturacion": 34, "urgencia": 5},
    ]

    print("Registros originales:")
    for r in registros:
        print(f"  {r}")
    print()

    registrosOrdenados = sorted(registros, key=lambda x: x["veces_prestado"], reverse=True)
    print("Ordenados por veces prestado (descendente):")
    for r in registrosOrdenados:
        print(f"  {r}")
    print()


def pruebaTres():
    print("Tabla de comparaciones e intercambios con datos reales")

    datosReales = [64, 34, 25, 12, 22, 11, 90, 88, 76, 50, 43, 19, 7, 33, 55]
    print(f"Datos reales a ordenar ({len(datosReales)} elementos): {datosReales}")
    print()

    print(f"{'Metodo':} {'Iteraciones':} {'Lista Ordenada':}")

    arr1 = datosReales.copy()
    arr1, int1 = bubbleSort(arr1)
    print(f"{'Bubble':} {int1:} {str(arr1):}")

    arr2 = datosReales.copy()
    arr2, int2 = selectionSort(arr2)
    print(f"{'Selection':} {int2:} {str(arr2):}")

    arr3 = datosReales.copy()
    arr3, int3 = insertionSort(arr3)
    print(f"{'Insertion':} {int3:} {str(arr3):}")
    print()


def reto1MergeQuick():
    print("Quicksort en el sitio sin crear listas nuevas")

    datos = [64, 34, 25, 12, 22, 11, 90, 88]
    print(f"Datos originales: {datos}")
    print()

    arr = datos.copy()
    arrOrdenado = quickSortInSitu(arr)
    print(f"Quicksort en sitio: {arrOrdenado}")
    print()


def reto2MergeQuick():
    print("Caso pesimo para Quicksort (pivote en primer elemento)")

    datosOrdenados = list(range(1, 11))
    print(f"Datos ya ordenados: {datosOrdenados}")
    print("Con pivote en primer elemento, Quicksort hara O(n^2) operaciones")
    print()

    arr = datosOrdenados.copy()
    arr = quickSort(arr)

    print(f"Resultado: {arr}")
    print()


def reto1HeapBucket():
    print("Heapsort de minimos (ordena descendente)")

    datos = [64, 34, 25, 12, 22, 11, 90, 88]
    print(f"Datos originales: {datos}")
    print()

    arr = datos.copy()
    arr = heapSortMinimo(arr)
    print(f"Heapsort minimos (descendente): {arr}")
    print()
    print("Cambio: Se invierte la comparacion > por < en heapify")
    print()


def reto2HeapBucket():
    print("Bucket Sort con diferente numero de cubetas")

    datos = [64, 34, 25, 12, 22, 11, 90, 88, 76, 50, 43, 19, 7, 33, 55]
    print(f"Datos: {datos} ({len(datos)} elementos)")
    print()

    print(f"{'Cubetas'} {'Resultado'}")

    arr5 = datos.copy()
    resultado5 = bucketSort(arr5, 5)
    print(f"{'5 cubetas'} {str(resultado5):}")

    arr50 = datos.copy()
    resultado50 = bucketSort(arr50, 50)
    print(f"{'50 cubetas'} {str(resultado50):<70}")

    print()
    print("Con 5 cubetas: elementos agrupados, menos buckets pero mas ordenamiento")
    print("Con 50 cubetas: elementos distribuidos, mas buckets pero menos ordenamiento")
    print("Punto optimo: numero de cubetas cercano a cantidad de datos")
    print()


def tablaComparativaFinal():
    print("Tabla comparativa de todos los metodos")

    datos = [64, 34, 25, 12, 22, 11, 90, 88, 76, 50, 43, 19, 7, 33, 55]
    print(f"Datos: {datos} ({len(datos)} elementos)")
    print()

    print(f"{'Metodo':} {'Comparaciones':} {'Resultado Correcto':}")

    resultadoEsperado = sorted(datos)

    # Bubble
    arr = datos.copy()
    arr, comps = bubbleSort(arr)
    correcto = arr == resultadoEsperado
    print(f"{'Bubble':} {comps:} {str(correcto):}")

    # Selection
    arr = datos.copy()
    arr, comps = selectionSort(arr)
    correcto = arr == resultadoEsperado
    print(f"{'Selection':} {comps:} {str(correcto):}")

    # Insertion
    arr = datos.copy()
    arr, comps = insertionSort(arr)
    correcto = arr == resultadoEsperado
    print(f"{'Insertion'} {comps:} {str(correcto):}")

    # Merge
    arr = datos.copy()
    arr = mergeSort(arr)
    correcto = arr == resultadoEsperado
    print(f"{'Merge':} {'O(n log n)':} {str(correcto):}")

    # Quick
    arr = datos.copy()
    arr = quickSort(arr)
    correcto = arr == resultadoEsperado
    print(f"{'Quick':} {'Promedio O(n log n)'} {str(correcto):}")

    # Heap
    arr = datos.copy()
    arr = heapSort(arr)
    correcto = arr == resultadoEsperado
    print(f"{'Heap':} {'O(n log n)':} {str(correcto):}")

    # Bucket
    arr = datos.copy()
    arr = bucketSort(arr, 10)
    correcto = arr == resultadoEsperado
    print(f"{'Bucket':} {'O(n + k)':} {str(correcto):}")

    print()


if __name__ == "__main__":
    pruebaUno()
    pruebaDos()
    pruebaTres()
    reto1MergeQuick()
    reto2MergeQuick()
    reto1HeapBucket()
    reto2HeapBucket()
    tablaComparativaFinal()

    print("CONCLUSIONES")
    print("- Bubble Sort optimizado es eficiente en datos ya ordenados")
    print("- Quicksort en sitio es mas eficiente en memoria que la version recursiva")
    print("- Heapsort minimo invierte el orden del resultado final")
    print("- Bucket Sort mejora con numero optimo de cubetas")
    print("- Merge y Heap garantizan O(n log n) siempre")
    print("- Quicksort puede ser O(n^2) en casos pesimos")
