## ¿Existe un grafo de 5 vértices donde todos tengan grado 3?

**No existe.**

Con las aristas 0-4, 1-4, 2-3, 0-2, 1-2, 0-3 y 1-3, los vértices 0, 1, 2 y 3 quedan con grado 3 y el vértice 4 con grado 2. Le falta una arista, pero cualquier vecino que se le dé pasa a tener grado 4. Otros intentos fallan de la misma manera.

Cada arista toca exactamente dos vértices, así que suma 2 a la suma de los grados. Por eso, en cualquier grafo:

```
suma de los grados = 2E
```

Esa suma siempre es par. Si cinco vértices tuvieran grado 3, la suma sería 5 × 3 = 15, que es impar. También harían falta E = 15 / 2 = 7,5 aristas, y eso no puede ser. Por lo tanto, el grafo no existe. ∎

## Generalización: V vértices, todos de grado k

Un grafo así **existe si y solo si** se cumplen las dos condiciones:

1. `0 ≤ k ≤ V − 1`
2. `V × k` es par

Es **imposible** en estos casos:

- **`V × k` es impar**, es decir, V y k son impares a la vez. La suma de los grados sería impar, y debe ser 2E.
- **`k ≥ V`**: un vértice solo tiene V − 1 vértices con los que conectarse.

**Por qué en los demás casos sí existe.** Se colocan los vértices en círculo y cada uno se une con sus ⌊k/2⌋ vecinos más cercanos a cada lado.

- Si k es par, eso ya da grado k.
- Si k es impar, entonces V es par (porque V × k es par) y cada vértice se une además con su opuesto, lo que da el grado que faltaba.

| V \ k | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
|---|---|---|---|---|---|---|---|---|
| 1 | sí | k≥V | k≥V | k≥V | k≥V | k≥V | k≥V | k≥V |
| 2 | sí | sí | k≥V | k≥V | k≥V | k≥V | k≥V | k≥V |
| 3 | sí | impar | sí | k≥V | k≥V | k≥V | k≥V | k≥V |
| 4 | sí | sí | sí | sí | k≥V | k≥V | k≥V | k≥V |
| 5 | sí | impar | sí | **impar** | sí | k≥V | k≥V | k≥V |
| 6 | sí | sí | sí | sí | sí | sí | k≥V | k≥V |
| 7 | sí | impar | sí | impar | sí | impar | sí | k≥V |
| 8 | sí | sí | sí | sí | sí | sí | sí | sí |

## Verificación con código

`reto3.py` y `reto3.cpp` comprueban la regla de dos maneras:

- **Fuerza bruta:** prueban todos los grafos posibles para V ≤ 6 y 0 ≤ k ≤ V. El resultado coincide con la regla en todos los casos.
- **Construcción:** arman el grafo del círculo en cada caso posible con V ≤ 30 y confirman que es simple y que todos sus vértices tienen grado k.

## Consecuencia

Como la suma de los grados es par, **el número de vértices de grado impar siempre es par**. Este resultado se conoce como el lema del apretón de manos.
