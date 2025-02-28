
call "C:\Program Files\Microsoft Visual Studio\VC98\Bin\VCVARS32.BAT"

cl /O2 -FeVC6_%1.exe -GX /I..\include /I..\dependencies %2%1 /link SDL3.lib opengl32.lib

del %1.obj
