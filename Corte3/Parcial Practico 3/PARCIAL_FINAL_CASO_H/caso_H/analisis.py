# ============================================================
#  analisis.py · CASO H · PARTE F del parcial  (10 puntos)
#  SaludBarrio — Puestos de salud y sus insumos
#
#  VERIFICACION CRUZADA
#  Esta es la MISMA logica de Sistema::mejorSeleccion, escrita en el otro
#  lenguaje. El verificador compara los dos resultados: si no coinciden,
#  uno de los dos esta mal y el parcial no cierra.
#
#  MODIFIQUE SOLO ESTE ARCHIVO.  NO TOQUE pruebas.py
# ============================================================


def mejor_seleccion(codigos, pesos, valores, capacidad):
 # Devuelve la mejor seleccion de codigos, pesos y valores que no exceda la capacidad, codigos[i], pesos[i] y valores[i] describen el mismo punto. cada punto se lleva o no se lleva. Si hay empate en valor, la seleccion con MENOS puntos. Debe dar exactamente el mismo resultado que la version en C++. PENDIENTE: implementar con recursion de tomar / no tomar y poda.
 # Recursion de tomar / no tomar y poda.

   n = len(codigos)
   best_value = 0
   best_selection = []

    # Función recursiva para explorar todas las combinaciones posibles
   def backtrack(index, current_weight, current_value, current_selection):
        nonlocal best_value, best_selection

        # Si hemos considerado todos los elementos
        if index == n:
            # Verificar si la selección actual es mejor que la mejor encontrada
            if current_value > best_value or (current_value == best_value and len(current_selection) < len(best_selection)):
                best_value = current_value
                best_selection = current_selection[:]
            return

        # Opción 1: No tomar el elemento actual
        backtrack(index + 1, current_weight, current_value, current_selection)

        # Opción 2: Tomar el elemento actual si no excede la capacidad
        if current_weight + pesos[index] <= capacidad:
            current_selection.append(codigos[index])
            backtrack(index + 1, current_weight + pesos[index], current_value + valores[index], current_selection)
            current_selection.pop()  # Backtrack

      # Iniciar la búsqueda recursiva
   backtrack(0, 0, 0, [])
      # Ordenar la mejor selección antes de devolverla 
   best_selection.sort()
   return best_selection
