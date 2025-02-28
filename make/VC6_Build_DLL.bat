
call "C:\Program Files\Microsoft Visual Studio\VC98\Bin\VCVARS32.BAT"

CL /O2 -GX /FeSDL3.dll -LD -DSDL3LITE_SHARED ^
/I..\dependencies                 ^
/I..\include\                     ^
/I..\source\include\              ^
..\source\OpenGL\*.cpp            ^
..\source\Platforms\Win32\*.cpp   ^
..\source\Renders\OpenGL1\*.cpp   ^
..\source\Renders\Software\*.cpp  ^
..\source\SDL3\*.cpp              ^
..\source\Shared\*.cpp            ^
gdi32.lib                         ^
opengl32.lib                      ^
winmm.lib                         ^
user32.lib

del *.obj

pause
