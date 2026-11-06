# Reto 3 — ¿Cuándo NO alcanza una rotación?

| Operación | ¿Puede quedar otro nodo desbalanceado más arriba? |
|---|---|
| Inserción | **No.** Un solo rebalanceo siempre basta. |
| Eliminación | **Sí.** El problema puede subir hasta la raíz. |

Aquí "un rebalanceo" es una rotación simple (LL, RR) o una doble (LR, RL) aplicada en un nodo.

## El árbol construido

Se obtiene insertando `5, 2, 8, 1, 3, 7, 10, 4, 6, 9, 11, 12`, sin ninguna rotación. Es un AVL de altura 4 con el mínimo de nodos posible (12), así que tiene muy poco margen.

```
            5
        /       \
       2         8
      / \       / \
     1   3     7   10
          \   /   /  \
           4 6   9    11
                        \
                         12
```

## Eliminación: hacen falta dos rotaciones

**Paso 1: eliminar el 1.** El nodo 2 queda con fe = −2. Es el único desbalanceado: la raíz 5 sigue con fe = −1.

```
            5  (fe=-1)
        /       \
       2 (fe=-2) 8
        \       / \
         3     7   10
          \   /   /  \
           4 6   9    11
                        \
                         12
```

**Paso 2: rotar a la izquierda en el 2** (caso RR). El subárbol queda bien, pero su altura baja de 2 a 1. Ahora la raíz tiene hijos de altura 1 y 3, así que **queda desbalanceada por culpa de la propia rotación**.

```
            5  (fe=-2)  <-- otro nodo desbalanceado, más arriba
        /       \
       3         8
      / \       / \
     2   4     7   10
              /   /  \
             6   9    11
                        \
                         12
```

**Paso 3: rotar a la izquierda en el 5** (caso RR). Ahora sí queda equilibrado, con altura 3.

```
            8
        /       \
       5         10
      / \       /  \
     3   7     9    11
    / \  /            \
   2  4 6              12
```

## Inserción: basta una

En ese mismo árbol, insertar el 13 desbalancea el 11. Una rotación deja el subárbol con raíz 12 e hijos 11 y 13, y los nodos de arriba no cambian: la raíz sigue con fe = −1 y altura 4.

### Por qué siempre es así

Sea z el nodo desbalanceado más profundo y h la altura de su subárbol **antes** de insertar. Para que z se desbalancee por la izquierda, tenía izquierda de altura h−1 y derecha de altura h−2, y la izquierda creció a h. Sea y el hijo izquierdo de z. El caso por la derecha es el espejo.

- **Caso LL:** y queda con izquierda de altura h−1 y derecha de altura h−2. Tras rotar, z tiene dos hijos de altura h−2, así que su altura es h−1. Como y tiene dos hijos de altura h−1, su altura es **h**.
- **Caso LR:** x, el hijo derecho de y, sube a altura h−1. Tras la rotación doble, y y z quedan con altura h−1, y x, que es la nueva raíz, con altura **h**.

En ambos casos, **el subárbol vuelve a la altura h que tenía antes de insertar**. Los ancestros estaban balanceados con esa altura y la siguen viendo igual, así que no puede aparecer otro desbalance. ∎

## Eliminación: por qué falla el mismo argumento

Sea z un nodo con izquierda de altura h−2 y derecha de altura h−1, y sea y su hijo derecho. Al eliminar en la izquierda, esta baja a h−3 y z queda con fe = −2. El resultado depende de y:

| Hijos de y (izquierdo, derecho) | Caso | Altura tras rebalancear | ¿Se propaga? |
|---|---|---|---|
| h−2, h−2 | RR | h | No |
| h−3, h−2 | RR | **h−1** | **Sí** |
| h−2, h−3 | RL | **h−1** | **Sí** |

En los dos últimos casos, el subárbol termina más bajo que antes. Si el ancestro ya estaba cargado hacia el otro lado, se desbalancea, y su rebalanceo puede volver a reducir la altura. Por eso una eliminación puede necesitar hasta un rebalanceo por nivel, es decir, O(log n), mientras que una inserción necesita como máximo uno.

La diferencia de fondo es esta: **al insertar, la rotación deshace el crecimiento que causó el problema; al eliminar, la rotación no puede devolver la altura perdida.**

## Verificación con código

`reto3.py` y `reto3.cpp` reproducen estos pasos y comprueban lo siguiente:

- **Inserción:** se probaron todas las permutaciones de 1 a 7 (5040) y 50 árboles aleatorios de 200 claves. Nunca hubo más de 1 rebalanceo por inserción, y cada rotación devolvió el subárbol a su altura anterior.
- **Eliminación:** en esos árboles aleatorios se necesitaron hasta 3 rebalanceos en una sola eliminación. Cerca del 2 % de las eliminaciones necesitaron 2 o más.
- **Integridad:** el árbol siguió siendo un AVL válido en cada paso de los árboles aleatorios y al final de cada permutación.
