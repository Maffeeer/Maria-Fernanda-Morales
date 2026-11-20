@echo off
REM ============================================================
REM  Parcial final practico . un solo sistema integrado
REM  Ejecuta las dos partes en orden: primero C++, despues Python.
REM ============================================================
setlocal
cd /d "%~dp0"
where python >nul 2>&1 && (set PY=python) || (set PY=py)
echo.
where g++ >nul 2>&1 || echo   AVISO: no se encontro g++ en el PATH.
g++ -std=c++17 -g -o pruebas.exe sistema.cpp pruebas.cpp && pruebas.exe || echo   [FALLA] sistema.cpp no compila
echo.
%PY% pruebas.py
echo.
endlocal
