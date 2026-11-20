# NO MODIFIQUE ESTE ARCHIVO. Alterarlo se considera fraude academico
# segun la seccion 13 de la guia de asignatura.
import os, sys

print("PARTE F · verificacion cruzada C++ / Python · caso H")
print("----------------------------------------------------------")

if not os.path.exists("cruce.txt"):
    print("  [FALLA] no se encontro cruce.txt")
    print("          La parte en C++ todavia no funciona. Ejecute primero:")
    print("            g++ -std=c++17 -fsanitize=address -g -o pruebas sistema.cpp pruebas.cpp")
    print("            ./pruebas")
    print("\n  PARCIAL ABIERTO.")
    sys.exit(0)

D = {}
for ln in open("cruce.txt"):
    if "=" in ln:
        a, _, b = ln.strip().partition("=")
        D[a] = b
nums = lambda s: [int(x) for x in s.split(",")] if s else []

codigos  = nums(D["codigos"])
pesos    = nums(D["pesos"])
valores  = nums(D["valores"])
cap      = int(D["capacidad"])
sel_cpp  = nums(D["seleccion"])
aporte   = int(D["aporte"])

try:
    from analisis import mejor_seleccion
except Exception as ex:
    print(f"  [FALLA] no se pudo importar analisis.py ({type(ex).__name__})")
    print("\n  PARCIAL ABIERTO.")
    sys.exit(0)

r = []
def chk(nombre, fn, esperado):
    try:
        obtenido = fn()
    except RecursionError:
        print(f"  [FALLA] {nombre}: RecursionError"); return False
    except Exception as ex:
        print(f"  [FALLA] {nombre}: lanzo {type(ex).__name__}"); return False
    ok = obtenido == esperado
    print(f"  [{'OK ' if ok else 'FALLA'}] {nombre}: obtuvo {obtenido}")
    if not ok: print(f"          esperaba {esperado}")
    return ok

r.append(chk("mejor_seleccion coincide con la version en C++",
             lambda: mejor_seleccion(codigos, pesos, valores, cap), sel_cpp))
r.append(chk("el aporte calculado en Python coincide",
             lambda: sum(valores[codigos.index(c)] for c in mejor_seleccion(codigos, pesos, valores, cap)),
             aporte))
r.append(chk("la seleccion cabe en la capacidad",
             lambda: sum(pesos[codigos.index(c)] for c in mejor_seleccion(codigos, pesos, valores, cap)) <= cap,
             True))
r.append(chk("capacidad 0 no selecciona nada",
             lambda: mejor_seleccion(codigos, pesos, valores, 0), []))
r.append(chk("capacidad enorme selecciona todo",
             lambda: mejor_seleccion(codigos, pesos, valores, 10**6), sorted(codigos)))
r.append(chk("lista vacia", lambda: mejor_seleccion([], [], [], cap), []))

print("----------------------------------------------------------")
if all(r):
    # el codigo se DERIVA de los resultados correctos: no esta escrito aqui
    cod = (f"PFH-{D['cuantos']}{D['suma']}{D['altura']}"
           f"{len(sel_cpp)}{aporte}")
    print(f"  PARCIAL CERRADO — codigo de cierre: {cod}")
    print("  Las dos partes del sistema funcionan y coinciden.")
else:
    print("  PARCIAL ABIERTO. La parte en C++ funciona, pero la version")
    print("  en Python no da el mismo resultado. Corrija analisis.py.")
