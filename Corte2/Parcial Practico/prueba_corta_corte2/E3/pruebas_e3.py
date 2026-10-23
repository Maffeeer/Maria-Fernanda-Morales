# NO MODIFIQUE ESTE ARCHIVO. Alterarlo se considera fraude academico
# segun la seccion 13 de la guia de asignatura.
from historial import historial_final, profundidad_maxima

C1 = ["abrir", "editar", "guardar", "DESHACER", "imprimir", "DESHACER", "DESHACER", "cerrar"]
C2 = ["DESHACER", "DESHACER", "abrir"]
C3 = []
C4 = ["a", "b", "DESHACER", "DESHACER", "DESHACER"]
C5 = ["a", "b", "DESHACER", "c"]

def chk(nombre, fn, esperado):
    try:
        obtenido = fn()
    except Exception as e:
        print(f"  [FALLA] {nombre}: lanzo {type(e).__name__}")
        return False
    ok = obtenido == esperado
    print(f"  [{'OK ' if ok else 'FALLA'}] {nombre}: obtuvo {obtenido}")
    if not ok:
        print(f"          esperaba {esperado}")
    return ok

print("EJERCICIO 3 · verificacion")
r = []
r.append(chk("historial_final caso 1", lambda: historial_final(C1), ["abrir", "cerrar"]))
r.append(chk("historial_final pila vacia", lambda: historial_final(C2), ["abrir"]))
r.append(chk("historial_final lista vacia", lambda: historial_final(C3), []))
r.append(chk("historial_final todo deshecho", lambda: historial_final(C4), []))
r.append(chk("profundidad_maxima caso 1", lambda: profundidad_maxima(C1), 3))
r.append(chk("profundidad_maxima caso 5", lambda: profundidad_maxima(C5), 2))
r.append(chk("profundidad_maxima lista vacia", lambda: profundidad_maxima(C3), 0))
r.append(chk("profundidad_maxima pila vacia", lambda: profundidad_maxima(C2), 1))

if all(r):
    # el codigo se DERIVA de los resultados correctos: no esta escrito aqui
    cod = (f"2203-{len(historial_final(C1))}{profundidad_maxima(C1)}"
           f"{profundidad_maxima(C5)}{profundidad_maxima(C2)}")
    print(f"\n  EJERCICIO 3 CERRADO — codigo de cierre: {cod}")
else:
    print("\n  Ejercicio ABIERTO. Corrija y vuelva a ejecutar.")
