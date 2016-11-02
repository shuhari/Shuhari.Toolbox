@ECHO OFF
SET NEXT_STEP=
SET BUILD=%2
IF "%BUILD%" == "" (SET BUILD=debug)
SET PYQTDIR=C:\Lan\Python35\Lib\site-packages\PyQt5\Qt\bin

if "%1" == "codegen" goto codegen
if "%1" == "clean" goto clean
if "%1" == "build" goto build
if "%1" == "lupdate" goto lupdate
if "%1" == "lrelease" goto lrelease
if "%1" == "run" goto run
goto help

:codegen
pyrcc5 -o src/qrc_resources.py resources/resources.qrc
goto end

:clean
rmdir /S /Q build
rmdir /S /Q dist
if "%NEXT_STEP%" == "build" goto build
goto end

:rebuild
SET NEXT_STEP=build
goto clean

:build
REM --version-file FILE
REM -m MANIFEST.XML
REM --uac-admin
SET COMMON_ARGS=-y -i resources/toolbox.ico
IF "%BUILD%" == "debug" (
    SET EXENAME=toolboxd
    SET ARGS=%COMMON_ARGS% -n %EXENAME% -c
) ELSE (
    SET EXENAME=toolbox
    SET ARGS=%COMMON_ARGS% -n %EXENAME% -w
)
PyInstaller %ARGS% src/main.py
copy /Y %PYQTDIR%\Qt5Core.dll dist\%EXENAME%\
copy /Y %PYQTDIR%\Qt5Gui.dll dist\%EXENAME%\
copy /Y %PYQTDIR%\Qt5Widgets.dll dist\%EXENAME%\
copy /Y %PYQTDIR%\Qt5WinExtras.dll dist\%EXENAME%\
goto end

:lupdate
goto end

:lrelease
goto end

:run
python src/main.py
goto end

:help
ECHO build.cmd codegen - Generate code for .qrc
ECHO build.cmd clean - Clean build directory
ECHO build.cmd build (debug or release) - Build exe file
ECHO build.cmd rebuild (debug or release) - Reuild exe file
ECHO build.cmd lupdate - Create or update translation files
ECHO build.cmd lrelease - Generate .qm files
ECHO build.cmd run - Run application
goto end

:end

