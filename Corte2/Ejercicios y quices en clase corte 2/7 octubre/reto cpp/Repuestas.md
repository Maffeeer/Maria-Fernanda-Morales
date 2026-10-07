# Integrantes: Daniel (py) y Mafe (cpp)

## 1. ¿Por qué la función mala pone a todos en la misma cubeta?

Todos los códigos comienzan con "EST-", así que cuando sumamos solo los primeros 4 caracteres, todos dan el mismo valor. E + S + T + - siempre es 281. Como el hash es 281 % capacidad, todos los códigos mapean al mismo índice sin importar cuáles sean los últimos dígitos. Por eso se amontonan todos en una sola cubeta.

## 2. La tabla con la función mala también se redimensionó. ¿Mejoró la distribución? ¿Por qué?

No mejoró. Aunque duplicamos la capacidad de 8 a 16, el problema sigue siendo el mismo. La función hash sigue siendo mala porque sigue ignorando lo que diferencia a los códigos. Si todos los primeros 4 caracteres son iguales, el hash siempre será idéntico. Redimensionar no arregla una función hash mala, solo hace la tabla más grande pero igual de ineficiente.

## 3. Con la función mala, ¿cuántas comparaciones hace buscar("EST-2026-0112") en el peor caso? ¿Y con la buena?

Con la función mala, todos los 12 estudiantes están en la misma cubeta, así que en el peor caso habría 12 comparaciones si el elemento está al final. Con la función buena, el hash distribuye bien los elementos, entonces cada cubeta tiene solo 1 o 2 elementos. La búsqueda es casi instantánea, máximo 1 comparación en promedio.

## 4. ¿Qué parte del código debería mirar una buena función hash para sus claves del proyecto?

Una buena función hash debe ver toda la clave, no solo una parte. En nuestro caso, los primeros 8 caracteres son iguales para todos, así que la diferencia está en los últimos 4 dígitos. La función multinomio que usamos es buena porque considera cada carácter con un peso diferente, lo que distribuye uniformente incluso cuando hay patrones repetidos al principio.
