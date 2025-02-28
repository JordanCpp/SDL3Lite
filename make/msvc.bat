
call "E:\Programs\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars32.bat"

CL /O2 -EHsc /FeSDL3.dll -LD      ^
/I..\include\                     ^
/I..\dependencies                 ^
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

pause
