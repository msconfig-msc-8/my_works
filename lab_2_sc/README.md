# Social Network (Lab 2) — Project Scaffold

Это стартовый каркас для ЛР-2 ("Социальная сеть").
Уже умеет:
- собираться из консоли (CMake)
- запускать CLI (`sn_cli`)
- запускать unit-тесты (`sn_tests`) без внешних библиотек

Дальше добавим `domain/`, `services/`, `storage/` и расширим тесты.

## Сборка
```bash
rm -rf build 2>nul || true
mkdir build
cd build
cmake ..
cmake --build .
