# ============================================================
#  Cívica Software  ·  TCK-5510  ·  Severidad P3
#  Sistema: RedAcopio  —  Mapa de cobertura de rutas
#  NO MODIFIQUE la matriz de datos ni el archivo de pruebas.
# ============================================================

# filas = rutas del camion, columnas = zonas del barrio
# cada celda = kilos recogidos por esa ruta en esa zona
cobertura = [
    [5, 0, 3, 0, 2, 4, 0],
    [0, 0, 7, 0, 1, 0, 6],
    [2, 0, 0, 0, 4, 3, 1],
    [0, 0, 5, 0, 0, 8, 2],
]

def total_por_ruta(m):
    """Devuelve una lista con el total recogido por cada ruta (fila)."""
    totales = []
    for fila in m:
        s = 0
        for v in fila:
            s += v
        totales.append(s)
    return totales


def cobertura_por_zona(m):
    """Devuelve una lista con el total recogido en cada zona (columna).
       BUG REPORTADO: la ultima zona nunca aparece en el informe."""
    totales = []
    for j in range(len(m[0])): # Quite el menos 1 para que recorra todas las columnas, incluyendo la ultima
        s = 0
        for i in range(len(m)):
            s += m[i][j]
        totales.append(s)
    return totales


def ruta_mas_productiva(m):
    """Devuelve el INDICE de la ruta que mas kilos recogio en total.
       PENDIENTE: implementar."""
    totales = total_por_ruta(m)
    return totales.index(max(totales))


def zonas_sin_cubrir(m):
    """Devuelve cuantas zonas (columnas) quedaron COMPLETAMENTE en cero,
       es decir, ninguna ruta recogio nada alli.
       PENDIENTE: implementar."""
    return sum(total == 0 for total in cobertura_por_zona(m)) # Se implemento la cantidad de zonas sin cubrir usando la funcion cobertura_por_zona y sumando los totales que sean 0


def main():
    print("Totales por ruta:", total_por_ruta(cobertura))
    print("Cobertura por zona:", cobertura_por_zona(cobertura))
    print("Ruta mas productiva (indice):", ruta_mas_productiva(cobertura))
    print("Zonas sin cubrir:", zonas_sin_cubrir(cobertura))


if __name__ == "__main__":
    main()
