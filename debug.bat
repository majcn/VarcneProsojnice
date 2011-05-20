qmake.exe vProsojnice.pro -r -spec win32-g++
mingw32-make.exe debug
mkdir "debug app"
move "debug\vProsojnice.exe" "debug app\vProsojnice.exe"
copy "needed dlls\*" "debug app"
rmdir "release" /S /Q
rmdir "debug" /S /Q
del "Make*"
del "ui_*"