@echo off
REM ============================================================
REM  Prueba corta . Segundo corte . Algoritmos y Estructura de Datos
REM  Ejecuta las pruebas de los cuatro ejercicios.
REM  Uso:   verificar.bat          (los cuatro)
REM         verificar.bat E2       (solo uno)
REM ============================================================
setlocal
cd /d "%~dp0"
set LISTA=%1
if "%LISTA%"=="" set LISTA=E1 E2 E3 E4

where python >nul 2>&1 && (set PY=python) || (set PY=py)
where g++ >nul 2>&1 || echo   AVISO: no se encontro g++ en el PATH. Los ejercicios E2 y E4 no se podran compilar.

for %%E in (%LISTA%) do (
  echo.
  echo ============================================================
  echo   %%E
  echo ============================================================
  if /I "%%E"=="E1" ( pushd E1 & %PY% pruebas_e1.py & popd )
  if /I "%%E"=="E3" ( pushd E3 & %PY% pruebas_e3.py & popd )
  if /I "%%E"=="E2" ( pushd E2 & g++ -std=c++17 -g -o pruebas_e2.exe busqueda.cpp pruebas_e2.cpp && pruebas_e2.exe || echo   [FALLA] el codigo no compila & popd )
  if /I "%%E"=="E4" ( pushd E4 & g++ -std=c++17 -g -o pruebas_e4.exe zonas.cpp pruebas_e4.cpp && pruebas_e4.exe || echo   [FALLA] el codigo no compila & popd )
)

echo.
echo ============================================================
echo   Copie los codigos de cierre en su hoja de respuestas y
echo   suba la captura de esta salida al repositorio.
echo ============================================================
endlocal
