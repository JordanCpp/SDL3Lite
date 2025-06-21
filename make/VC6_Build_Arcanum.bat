
call "C:\Program Files\Microsoft Visual Studio\VC98\Bin\VCVARS32.BAT"

cl /O2 -FeVC6_Arcanum.exe -GX /I..\include /I..\Arcanum ..\Arcanum\Arcanum\*.cpp /link SDL3.lib opengl32.lib

del *.obj

pause
