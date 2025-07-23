
set PATH=C:TC\BIN\

tcc -etests -P -O2 -IC:\SDL3\include\ -IC:\SDL3\src\ C:\SDL3\src\SDL3\Dos16\*.cpp C:\SDL3\src\SDL3\*.cpp C:\SDL3\tests.cpp
