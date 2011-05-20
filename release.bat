qmake.exe vProsojnice.pro -r -spec win32-g++ CONFIG+=release
mingw32-make.exe release
mkdir "release app"
move "release\vProsojnice.exe" "release app\vProsojnice.exe"
copy "needed dlls\*" "release app"
rmdir "release" /S /Q
rmdir "debug" /S /Q
del "Make*"
del "ui_*"