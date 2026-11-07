@echo off
rem Builds the PC test runner (detest.exe) with the MSVC Build Tools.
call "C:\Program Files (x86)\Microsoft Visual Studio\18\BuildTools\VC\Auxiliary\Build\vcvars64.bat" >nul 2>nul
cd /d "%~dp0"
if not exist out\pc mkdir out\pc
cl /nologo /std:c++17 /utf-8 /EHsc /O1 /Zi /Fd"out\pc\detest.pdb" /MP /W3 /wd4244 /wd4267 /wd4305 /wd4996 /wd4018 /wd4146 /wd4065 /bigobj /Isrc /Fo"out\pc\\" /Fe"out\pc\detest.exe" src\cs.cpp src\stacktrace.cpp src\engine.cpp src\audio.cpp src\main_pc.cpp src\game\registry.gen.cpp src\game\game_*.cpp
