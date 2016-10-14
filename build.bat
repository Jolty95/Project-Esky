@echo off
cls
echo Script de compilacion del Project: Esky por Jolty95
echo =======================================
echo Version: 2.1
echo Proyecto: Project: Esky por Jolty95 para Esky73
echo =======================================
if "%1" == "clean" goto clean
echo Borrando compilacion anterior...
IF EXIST *.cia del /F /Q *.cia
IF EXIST *.cxi del /F /Q *.cxi
echo Borrando el directorio romfs...
IF EXIST Builder\romfs rmdir /S /Q Builder\romfs
echo Copiando el script actualizado al directorio romfs...
::Copia el nuevo índice a romsfs
echo Creando directorio...
mkdir Builder\romfs
echo Creado.
echo Copiando index.lua...
copy sources\index.lua Builder\romfs\index.lua
echo Copiado.
echo Compilando romfs en el directorio...
cd Builder
tools\3dstool -cvtf romfs romfs.bin --romfs-dir romfs
::Compila el cia. Ademas crea un archivo CXI en la raiz para usarlo con citra
goto cia

:cia
echo =============================
echo Compilando en formato cia...
call :cia-b
echo Compilacion terminada.
cd ..
exit /b

:cia-b
echo Creando banner desde los archivos...
tools\bannertool makebanner -i banner.png -a sonido.wav -o banner.bin
echo Banner creado.
echo Creando icono desde archivo...
tools\bannertool makesmdh -s "Project:Esky" -l "Launcher Project: Esky" -p "Jolty95" -i icono.png -o icono.bin
echo Icono creado.
echo Creando CXI en la raiz...
tools\makerom -f cxi -o ../citra.cxi -elf bin/lpp-3ds.elf -rsf ProjectEsky.rsf -icon icono.bin -banner banner.bin -exefslogo -target t -romfs romfs.bin
echo Archivo CXI creado.
echo Creando archivo CIA ...
tools\makerom -f cia -o ../ProjectEsky.cia -elf bin/lpp-3ds.elf -rsf ProjectEsky.rsf -icon icono.bin -banner banner.bin -exefslogo -target t -romfs romfs.bin
echo Archivo CIA creado.
goto :EOF

:clean
echo Limpiando...
cd Builder
IF EXIST ..\*.cia del /F /Q ..\*.cia
IF EXIST romfs rmdir /S /Q romfs
IF EXIST *.bin del /F /Q *.bin
IF EXIST *.smdh del /F /Q *.smdh
cd ..
echo Operacion terminada.
exit /b
