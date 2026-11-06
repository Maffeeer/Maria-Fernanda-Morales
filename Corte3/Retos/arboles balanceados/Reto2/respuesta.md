# Reto 2 — El orden maldito

La altura se cuenta en aristas: una hoja tiene altura 0 y el árbol vacío, −1.

## Un orden que da altura 2

`4, 2, 6, 1, 3, 5, 7` produce este árbol sin aplicar ninguna rotación:

```
      4
    /   \
   2     6
  / \   / \
 1   3 5   7
```

## El peor orden

`1, 2, 3, 4, 5, 6, 7` produce una cadena de altura 6, que en la práctica es una lista enlazada. Buscar el 7 cuesta 7 comparaciones, frente a 3 en el árbol equilibrado.

No es el único peor orden: hay **64**. Por ejemplo, el zigzag `1, 7, 2, 6, 3, 5, 4` también da altura 6.

Para formar una cadena, cada clave debe ser el mínimo o el máximo de las que faltan. Si no lo fuera, quedarían claves por llegar a ambos lados de ella y el árbol se ramificaría. Hay 2 opciones en cada una de las seis primeras inserciones y la última clave queda forzada: 2⁶ = 64.

## Qué tienen en común los órdenes de altura 2

La primera clave que llega se queda como raíz para siempre, y las demás se reparten según sean menores o mayores que ella. Para partir el árbol por la mitad, la raíz tiene que ser la mediana, **el 4**. El mismo razonamiento se repite en cada mitad: el 2 debe llegar antes que 1 y 3, y el 6 antes que 5 y 7.

Entonces, un orden da altura 2 **si y solo si cada clave llega después de su padre en el árbol perfecto**:

- El 4 llega antes que todas las demás.
- El 2 llega antes que el 1 y el 3.
- El 6 llega antes que el 5 y el 7.

Empezar por el 4 es necesario, pero no suficiente: `4, 1, 2, 3, 5, 6, 7` da altura 3.

## Cuántos son: 80

El 4 va de primero y quedan seis posiciones.

1. Las claves de la mitad izquierda y las de la derecha no se afectan entre sí, así que se pueden intercalar libremente. Se escogen las tres posiciones de la mitad izquierda: C(6,3) = 20 maneras.
2. En la mitad izquierda, el 2 va primero y el 1 y el 3 pueden ir en cualquier orden: 2 maneras.
3. En la mitad derecha pasa lo mismo con el 6, el 5 y el 7: 2 maneras.

**Total: 20 × 2 × 2 = 80 órdenes**, solo el 1,59 % de los 5040 posibles.

## Todas las permutaciones

`reto2.py` y `reto2.cpp` construyen el BST de las 5040 permutaciones:

| Altura | Órdenes | Porcentaje |
|---|---:|---:|
| 2 (la mejor) | 80 | 1,59 % |
| 3 | 2240 | 44,44 % |
| 4 | 2048 | 40,63 % |
| 5 | 608 | 12,06 % |
| 6 (la peor) | 64 | 1,27 % |

Los programas también confirman que las dos reglas de arriba seleccionan exactamente esos 80 y esos 64 órdenes.

Sin rotaciones, equilibrar por casualidad es muy improbable: cerca de 85 % de los órdenes da altura 3 o 4. Por eso existen los árboles que se balancean solos.
