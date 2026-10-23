# Preguntas - Pilas y Colas

## 1. En una cola sobre lista enlazada, saco el último elemento. ¿Qué dos referencias tengo que actualizar y por qué?

Tengo que actualizar:
- El puntero `siguiente` del nodo anterior al último, poniéndolo en `None` (o `nullptr`)
- La referencia `cola` (el puntero al final), haciéndola apuntar al nuevo último nodo

Por qué: Cuando saco el último nodo, pierdo esa referencia. El nuevo último es el anterior, así que debo actualizar ambas referencias para mantener la integridad de la estructura.


## 2. En una cola circular de capacidad cinco, el frente está en tres y hay cuatro elementos. ¿En qué posición se guarda el siguiente que encole?

Hay cuatro elementos: posiciones 3, 4, 0, 1 (recuerda que es circular).
El siguiente se guarda en posición 2.

Cálculo: El final está en (3 + 4 - 1) % 5 = 1. El siguiente es (1 + 1) % 5 = 2.


## 3. Quiero deshacer las últimas tres operaciones. ¿Pila o cola? ¿Por qué?

Pila.

Por qué: Deshacer significa revertir el orden inverso. La última operación que hice es la primera que debo deshacer (LIFO). Una pila es exactamente eso.


## 4. Quiero atender por orden de llegada. ¿Pila o cola?

Cola.

Por qué: El primero que llega es el primero que se atiende (FIFO). Eso es una cola.
