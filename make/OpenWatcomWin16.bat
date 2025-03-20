
del *.err *.obj

wcl -xs -D_WIN16 -Ic:\WATCOM\h\ -Ic:\WATCOM\h\win\ -I..\LDL\include ..\LDL_Pal.cpp ..\LDL\source\*.cpp ..\LDL\source\Renders\*.cpp ..\LDL\source\Win16\*.cpp /link windows.lib

pause
