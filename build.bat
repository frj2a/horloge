@echo off
REM "$Date: 2019-01-24 16:35:14 -0200 (qui, 24 jan 2019) $"
REM "$Author: chico $"
REM "$Revision: 124 $"
set OBJECT=horloge
del /q %OBJECT%.exe
del /q %OBJECT%.upx
svn up
\Qt\Qt-5.12.0\bin\lrelease *.pro
qmake -r -spec win32-g++ "CONFIG-=debug_and_release release debug" "CONFIG+=release"  && mingw32-make qmake_all && mingw32-make -s -j4 && strip -psx %OBJECT%.exe && "C:\Program Files\upx-3.95-win64\upx.exe" --ultra-brute --best %OBJECT%.exe && move %OBJECT%.exe ..\ && call distclean.bat && move ..\%OBJECT%.exe .\