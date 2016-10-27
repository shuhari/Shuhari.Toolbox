@ECHO OFF

SET NEXT_STEP=
SET BUILD=%2
IF "%BUILD%" == "" (SET BUILD=debug)


ECHO Initialize...
if not exist build mkdir build
if not exist build\translations mkdir build\translations


if "%1" == "build" goto build
if "%1" == "clean" goto clean
if "%1" == "rebuild" goto rebuild
if "%1" == "lupdate" goto lupdate
if "%1" == "lrelease" goto lrelease
goto help

:clean
del /S /Q build\*.*
if exist build\debug rmdir /S /Q build\debug
if exist build\release rmdir /S /Q build\release
if "%NEXT_STEP%" == "build" goto build
goto end

:rebuild
set NEXT_STEP=build
goto clean

:build
cd build
del /Q Makefile*.*
del /Q uic_wrapper.bat
qmake ../src/toolbox.pro
mingw32-make %BUILD%
del /Q Makefile*.*
del /Q uic_wrapper.bat
cd ..
goto end

:lupdate
lupdate src/toolbox.pro
goto end

:lrelease
lrelease translations/toolbox.zh_CN.ts
copy /Y translations\toolbox.zh_CN.qm build\translations
copy /Y %QTDIR%\translations\qt_zh_CN.qm build\translations\qt.zh_CN.qm
goto end

:help
echo build.cmd build (debug or release) - Build projects incremental
echo build.cmd rebuild (debug or release) - Clean and rebuild projects
echo build.cmd lupdate - Run lupdate to output translation files
echo build.cmd lrelease (debug or release) - Run lrelease to generate .qm file and copy to dist directory
echo build.cmd clean - Clean directory
goto end

:end
