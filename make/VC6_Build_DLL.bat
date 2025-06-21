
call "C:\Program Files\Microsoft Visual Studio\VC98\Bin\VCVARS32.BAT"

CL /O2 -GX /FeSDL3.dll -LD -DSDL3LITE_SHARED ^
/I..\dependencies                 ^
/I..\include\                     ^
/I..\source\                      ^
..\source\SDL3Lite\OpenGL\*.cpp            ^
..\source\SDL3Lite\Platforms\Win32\*.cpp   ^
..\source\SDL3Lite\Renders\OpenGL1\*.cpp   ^
..\source\SDL3Lite\Renders\Software\*.cpp  ^
..\source\SDL3Lite\\*.cpp                  ^
gdi32.lib                         ^
opengl32.lib                      ^
winmm.lib                         ^
user32.lib

del *.obj

pause
