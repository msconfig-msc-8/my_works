# Быстрый старт

## Остановить систему
```bash
cd /home/shahzad/PPOIS/PP/PP/PpoisNetworkResilience
docker compose down
```

## Запустить систему
```bash
cd /home/shahzad/PPOIS/PP/PP/PpoisNetworkResilience
docker compose up -d
```

## Запустить тесты
```bash
docker compose exec machine env LD_LIBRARY_PATH=/example-app/install/sc-machine/lib:/example-app/build/Release/extensions /example-app/build/Release/extensions/network_resilience_tests
```

## Открыть в браузере
http://localhost:8000
