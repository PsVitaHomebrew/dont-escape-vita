@echo off
rem Compile-checks one translated class on its own: check.bat ClassName
rem (uses its own output folder, so several checks can run at the same time)
call "C:\Program Files (x86)\Microsoft Visual Studio\18\BuildTools\VC\Auxiliary\Build\vcvars64.bat" >nul 2>nul
cd /d "%~dp0"
if not exist out\check\%1 mkdir out\check\%1
cl /nologo /c /std:c++17 /utf-8 /EHsc /Od /W3 /wd4244 /wd4267 /wd4305 /wd4996 /wd4018 /wd4146 /wd4065 /bigobj /Isrc /Fo"out\check\%1\\" src\game\cpp\%1.cpp
