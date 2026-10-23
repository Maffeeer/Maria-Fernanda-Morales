## BLOQUE A — Recursión y backtracking

### Ejercicio 1: Trazado de recursión - Python

```python
def recoger(n, k):
    if n == 0:
        return 0
    if n % 2 == 0:
        return k + recoger(n - 1, k + 1)
    return recoger(n - 1, k)

print(recoger(5, 1))

a) ¿Qué imprime?
   3
   

b) ¿Cuántos marcos en la pila en su punto más profundo?
   6 marcos
   
   (recoger(5,1) → recoger(4,1) → recoger(3,2) → recoger(2,2) → recoger(1,3) → recoger(0,3))

c) ¿Qué ocurre si se elimina la primera condición?

   Bucle infinito (Stack Overflow)
   Sin la condición if n == 0: return 0, la recursión nunca termina.
   El programa sigue restando 1 a n indefinidamente.
   

### Ejercicio 2: Detección de errores en C++.

**Código con error:**
cpp
int contar(const vector<int>& v, int n, int umbral) {
    if (n < 0) return 0;                    // (1)
    if (v[n] >= umbral)                     // (2)
        return 1 + contar(v, n - 1, umbral);
    return contar(v, n - 1, umbral);
}

contar(v, v.size(), 20)  // v = {12, 45, 7, 38, 60, 19, 23}



El programa accede a `v[v.size()]` que está fuera de rango.
- `v.size()` retorna 7, pero los índices válidos van de 0 a 6
- `v[7]` intenta acceder a una posición que no existe
- Esto causa comportamiento indefinido (posible crash o lectura de memoria basura)

**Versión corregida:**
```cpp
int contar(const vector<int>& v, int n, int umbral) {
    if (n < 0) return 0;
    if (v[n] >= umbral)
        return 1 + contar(v, n - 1, umbral);
    return contar(v, n - 1, umbral);
}

// Llamada correcta:
contar(v, v.size() - 1, 20)  // Empezar en índice 6, no 7
```

---

## BLOQUE B — Algoritmos de búsqueda

### Ejercicio 3: Búsqueda binaria - Trazado

**Arreglo:** `v = {103, 118, 127, 134, 149, 156, 168, 175, 182, 190, 203, 219}`

**Buscar 175:**

| Iteración | izq | der | medio | v[medio] | Acción | Comparación |
|-----------|-----|-----|-------|----------|--------|-------------|
| 1         | 0   | 11  | 5     | 156      | izq=6  | 156 < 175   |
| 2         | 6   | 11  | 8     | 182      | der=7  | 182 > 175   |
| 3         | 6   | 7   | 6     | 168      | izq=7  | 168 < 175   |
| 4         | 7   | 7   | 7     | 175      | ✓      | 175 == 175  |

**4**

**160:**

**4** (No encontrado, devuelve -1)

---

### Ejercicio 4: Detección de errores - Búsqueda binaria Python

**Código con error:**
```python
def buscar(v, x):
    izq, der = 0, len(v) - 1
    while izq <= der:
        medio = (izq + der) // 2
        if v[medio] == x:
            return medio
        elif v[medio] < x:
            izq = medio        # (1) ERROR
        else:
            der = medio        # (2) ERROR
    return -1

v = [8, 15, 23, 31, 42, 56, 64, 77, 89, 91]
```
El programa entra en un **bucle infinito**.

En línea (1): `izq = medio` debería ser `izq = medio + 1`
- Sin el +1, izq se queda apuntando al mismo medio
- Si v[medio] < x nuevamente, izq = medio nuevamente
- Los límites nunca convergen

En línea (2): `der = medio` debería ser `der = medio - 1`
- Sin el -1, der se queda apuntando al mismo medio
- Si v[medio] > x nuevamente, der = medio nuevamente
- Los límites nunca convergen

**Precondición que debe cumplirse:**
El arreglo debe estar **ordenado en orden ascendente** (ya lo está en este caso).

**Versión corregida:**
```python
def buscar(v, x):
    izq, der = 0, len(v) - 1
    while izq <= der:
        medio = (izq + der) // 2
        if v[medio] == x:
            return medio
        elif v[medio] < x:
            izq = medio + 1    # CORRECCIÓN
        else:
            der = medio - 1    # CORRECCIÓN
    return -1
```
