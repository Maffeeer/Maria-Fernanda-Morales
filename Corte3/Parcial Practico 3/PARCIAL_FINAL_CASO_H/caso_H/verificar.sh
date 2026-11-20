#!/usr/bin/env bash
# ============================================================
#  Parcial final practico · un solo sistema integrado
#  Ejecuta las dos partes en orden: primero C++, despues Python.
#  El codigo de cierre aparece al final, cuando las dos funcionen.
# ============================================================
cd "$(dirname "$0")" || exit 1
GXX=$(command -v g++); PY=$(command -v python3 || command -v python)
echo ""
if [ -z "$GXX" ]; then echo "  No se encontro g++."; else
  "$GXX" -std=c++17 -fsanitize=address -g -o pruebas sistema.cpp pruebas.cpp \
    && ./pruebas || echo "  [FALLA] sistema.cpp no compila"
fi
echo ""
if [ -z "$PY" ]; then echo "  No se encontro python3."; else "$PY" pruebas.py; fi
echo ""
