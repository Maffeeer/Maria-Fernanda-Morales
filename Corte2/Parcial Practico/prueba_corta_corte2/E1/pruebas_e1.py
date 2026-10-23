# NO MODIFIQUE ESTE ARCHIVO. Alterarlo se considera fraude academico
# segun la seccion 13 de la guia de asignatura.
from recursion import suma_impares, contar_caminos

def chk(nombre, fn, esperado):
    try:
        obtenido = fn()
    except RecursionError:
        print(f"  [FALLA] {nombre}: RecursionError (la recursion no termina)")
        return False
    except Exception as e:
        print(f"  [FALLA] {nombre}: lanzo {type(e).__name__}")
        return False
    ok = obtenido == esperado
    print(f"  [{'OK ' if ok else 'FALLA'}] {nombre}: obtuvo {obtenido}")
    if not ok:
        print(f"          esperaba {esperado}")
    return ok

print("EJERCICIO 1 · verificacion")
r = []
r.append(chk("suma_impares(5)",     lambda: suma_impares(5),     9))
r.append(chk("suma_impares(1)",     lambda: suma_impares(1),     1))
r.append(chk("suma_impares(0)",     lambda: suma_impares(0),     0))
r.append(chk("suma_impares(10)",    lambda: suma_impares(10),    25))
r.append(chk("contar_caminos(3,3)", lambda: contar_caminos(3, 3), 6))
r.append(chk("contar_caminos(2,4)", lambda: contar_caminos(2, 4), 4))
r.append(chk("contar_caminos(1,9)", lambda: contar_caminos(1, 9), 1))
r.append(chk("contar_caminos(4,4)", lambda: contar_caminos(4, 4), 20))

if all(r):
    # el codigo se DERIVA de los resultados correctos: no esta escrito aqui
    cod = f"2201-{suma_impares(10)}{contar_caminos(3,3)}{contar_caminos(4,4)}"
    print(f"\n  EJERCICIO 1 CERRADO — codigo de cierre: {cod}")
else:
    print("\n  Ejercicio ABIERTO. Corrija y vuelva a ejecutar.")
