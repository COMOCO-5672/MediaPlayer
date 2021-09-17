@echo off
title qmake and nmake build prompt
set VCINSTALLDIR=C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC
set QTDIR=C:\Qt\Qt5.12.5\5.12.5\msvc2015_64
set PATH=%VCINSTALLDIR%\bin;%QTDIR%\bin;%PATH%
call "%VCINSTALLDIR%\vcvarsall.bat" amd64
md bin
cd bin
qmake ../MediaPlayer.pro -spec win32-msvc "CONFIG+=qtquickcompiler"
nmake release
cd MediaPlayer/release
windeployqt MediaPlayer.exe