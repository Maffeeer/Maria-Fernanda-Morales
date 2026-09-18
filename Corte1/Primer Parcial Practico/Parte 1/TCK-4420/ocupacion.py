# ============================================================
#  Cívica Software  ·  TCK-4420  ·  Severidad P3
#  Sistema: RedAcopio  —  Reporte de ocupación
#  NO MODIFIQUE la seccion de datos ni el archivo de pruebas.
# ============================================================

# filas = puntos de acopio, columnas = dias de la semana
ocupacion = [
    [4, 2, 6, 1, 3, 0],
    [0, 5, 5, 2, 7, 1],
    [8, 1, 0, 4, 2, 6],
    [3, 3, 3, 0, 0, 5],
]

def total_por_punto(m):
    """Devuelve una lista con el total recogido por cada punto (fila)."""
    totales = []
    for fila in m:
        s = 0
        for v in fila:
            s += v
        totales.append(s)
    return totales


def total_por_dia(m):
    """Devuelve una lista con el total recogido cada dia (columna).
       BUG REPORTADO: entrega totales incorrectos."""
    """ Se cambio el orden de los bucles para recorrer primero las columnas y luego las filas,"""
    totales = []
    for j in range(len(m[0])):           # <-- recorrer columnas (dias)
        s = 0
        for i in range(len(m)):
            s += m[i][j]
        totales.append(s)
    return totales


def dia_mas_flojo(m):
    """Devuelve el indice del dia con MENOR recoleccion total."""
    totales_dia = total_por_dia(m)
    return totales_dia.index(min(totales_dia))


def puntos_inactivos(m):
    """Devuelve cuantos registros estan en 0 (el punto no opero ese dia)."""
    contador = 0
    for fila in m:
        for valor in fila:
            if valor == 0:
                contador += 1
    return contador

def main():
    """Prueba de las funciones"""
    print("Total por punto:", total_por_punto(ocupacion))
    print("Total por día:", total_por_dia(ocupacion))
    print("Día más flojo (índice):", dia_mas_flojo(ocupacion))
    print("Puntos inactivos:", puntos_inactivos(ocupacion))


if __name__ == "__main__":
    main()