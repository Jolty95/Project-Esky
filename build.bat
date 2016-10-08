@echo off
cls
echo Script de compilacion de UmbJolt3D por Jolty95
echo =======================================
echo Version: 1.1
echo Proyecto: UmbJolt3D por Jolty95 ^& Esky73
echo =======================================
if "%1" == "clean" goto clean
echo Borrando el directorio romfs....
IF EXIST Builder\romfs rmdir /S /Q Builder\romfs
echo Copiando el script actualizado al directorio romfs...
::Copia el nuevo índice a romsfs
echo Creando directorio...
mkdir Builder\romfs
echo Creado.
echo Copiando index.lua...
copy index.lua Builder\romfs\index.lua
echo Copiado.
echo Compilando romfs en el directorio...
cd Builder
tools\3dstool -cvtf romfs romfs.bin --romfs-dir romfs
::Si no hay parametros, compila todo. Si hay compila cia o 3dsx.
if "%1" == "" goto all
if %1 == cia-b goto cia
if %1 == 3dsx-b goto 3dsx

goto %1

:all
echo =============================
echo Compilando en formato cia y 3dsx...
call :cia-b
call :3dsx-b
echo Compilacion terminada.
cd ..
exit /b

:3dsx
echo =============================
echo Compilando en formato 3dsx...
call :3dsx-b
echo Compilacion terminada.
cd ..
exit /b
:cia
echo =============================
echo Compilando en formato cia...
call :cia-b
echo Compilacion terminada.
cd ..
exit /b

:3dsx-b
echo Creando informacion SMDH...
tools\bannertool makesmdh -s "UmbJolt3D" -l "La creacion de Jolty y Esky" -p "Jolty95 & Esky73" -i UmbJolt3DLogo.png -o UmbJolt3D.smdh
echo Informacion SMDH creada.
echo Creando archivo 3DSX...
tools\3dsxtool bin/lpp-3ds.elf ../UmbJolt3D.3dsx --romfs=romfs.bin --smdh=UmbJolt3D.smdh 
echo Archivo 3DSX creado.
goto :EOF

:cia-b
echo Creando banner desde los archivos...
tools\bannertool makebanner -i banner.png -a sonido.wav -o banner.bin
echo Banner creado.
echo Creando icono desde archivo...
tools\bannertool makesmdh -s "UmbJolt3D" -l "La creacion de Jolty y Esky" -p "Jolty95 & Esky73" -i UmbJolt3DLogo.png -o icono.bin
echo Icono creado.
echo Creando archivo CIA ...
tools\makerom -f cia -o ../UmbJolt3D.cia -elf bin/lpp-3ds.elf -rsf UmbJolt3D.rsf -icon icono.bin -banner banner.bin -exefslogo -target t -romfs romfs.bin
echo Archivo CIA creado.
goto :EOF

:clean
echo Limpiando...
cd Builder
IF EXIST ..\*.3dsx del /F /Q ..\*.3dsx
IF EXIST ..\*.cia del /F /Q ..\*.cia
IF EXIST romfs rmdir /S /Q romfs
IF EXIST *.bin del /F /Q *.bin
IF EXIST *.smdh del /F /Q *.smdh
cd ..
echo Operacion terminada.
exit /b
