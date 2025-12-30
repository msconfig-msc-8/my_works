@echo off
setlocal

REM Удаляем build, только если он есть
if exist build (
  rmdir /s /q build
)

mkdir build
cd build

cmake ..
cmake --build .
ctest --output-on-failure
.\tests\sn_tests.exe

endlocal
