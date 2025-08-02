
call "C:\Program Files\Microsoft Visual Studio\VC98\Bin\VCVARS32.BAT"

CL /O2 -GX /FeSDL3.dll -LD -DSDL3LITE_SHARED ^
/I..\dependencies                   ^
/I..\include\                       ^
/I..\src\                           ^
..\src\SDL3\OpenGL\*.cpp            ^
..\src\SDL3\Win32\*.cpp             ^
..\src\SDL3\Renders\OpenGL1\*.cpp   ^
..\src\SDL3\*.cpp                   ^
gdi32.lib                           ^
opengl32.lib                        ^
winmm.lib                           ^
user32.lib

del *.obj

pause
