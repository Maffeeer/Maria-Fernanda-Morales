#!/usr/bin/env bash
# ============================================================
#  Prueba corta · Segundo corte · Algoritmos y Estructura de Datos
#  Ejecuta las pruebas de los cuatro ejercicios.
#  Uso:   bash verificar.sh          (los cuatro)
#         bash verificar.sh E2       (solo uno)
# ============================================================
cd "$(dirname "$0")" || exit 1
PY=$(command -v python3 || command -v python)
GXX=$(command -v g++)
LISTA=${1:-"E1 E2 E3 E4"}
FALTA=0

for E in $LISTA; do
  echo ""
  echo "============================================================"
  echo "  $E"
  echo "============================================================"
  case $E in
    E1) [ -z "$PY" ] && { echo "  No se encontro python3."; FALTA=1; continue; }
        ( cd E1 && "$PY" pruebas_e1.py ) ;;
    E3) [ -z "$PY" ] && { echo "  No se encontro python3."; FALTA=1; continue; }
        ( cd E3 && "$PY" pruebas_e3.py ) ;;
    E2) [ -z "$GXX" ] && { echo "  No se encontro g++."; FALTA=1; continue; }
        ( cd E2 && "$GXX" -std=c++17 -g -o pruebas_e2 busqueda.cpp pruebas_e2.cpp \
            && ./pruebas_e2 || echo "  [FALLA] el codigo no compila" ) ;;
    E4) [ -z "$GXX" ] && { echo "  No se encontro g++."; FALTA=1; continue; }
        ( cd E4 && "$GXX" -std=c++17 -g -o pruebas_e4 zonas.cpp pruebas_e4.cpp \
            && ./pruebas_e4 || echo "  [FALLA] el codigo no compila" ) ;;
    *)  echo "  Ejercicio desconocido: $E" ;;
  esac
done

echo ""
echo "============================================================"
echo "  Copie los codigos de cierre en su hoja de respuestas y"
echo "  suba la captura de esta salida al repositorio."
echo "============================================================"
exit $FALTA
