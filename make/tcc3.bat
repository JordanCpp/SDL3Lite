
set PATH=TC\BIN\

tcc -emain -ml -P -O2 -IC:\SDL3\include\ -IC:\SDL3\src\ C:\SDL3\src\SDL3\*.cpp C:\SDL3\src\SDL3\DOS16\*.cpp C:\SDL3\main.c
