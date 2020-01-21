@echo off
REM "$Date: 2019-01-24 16:45:17 -0200 (qui, 24 jan 2019) $"
REM "$Author: chico $"
REM "$Revision: 125 $"
set OBJECT_=horloge
mingw32-make distclean
del /f /q /s release\*.*
del /f /q /s debug\*.*
del /f /q /s GeneratedFiles\*.*
del /f /q ui_*.h
del /f /q moc_*.cpp
del /f /q qrc_*.cpp
rmdir debug
rmdir release
rmdir GeneratedFiles\debug
rmdir GeneratedFiles\release
rmdir GeneratedFiles
Z: && cd Z:\ && rmdir /s /q %OBJECT_%
C: