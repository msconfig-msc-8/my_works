# Полное руководство по проекту Network Resilience Analysis

## Оглавление

1. [Введение](#1-введение)
2. [Что такое OSTIS](#2-что-такое-ostis)
3. [Архитектура проекта](#3-архитектура-проекта)
4. [Модуль Network Resilience](#4-модуль-network-resilience)
5. [Ключевые узлы (Keynodes)](#5-ключевые-узлы-keynodes)
6. [Агент поиска точек сочленения](#6-агент-поиска-точек-сочленения)
7. [Агент поиска мостов](#7-агент-поиска-мостов)
8. [Агент определения связности](#8-агент-определения-связности)
9. [База знаний (SCS)](#9-база-знаний-scs)
10. [Тестирование](#10-тестирование)
11. [Сборка и запуск](#11-сборка-и-запуск)

---

# 1. Введение

Данный проект реализует анализ отказоустойчивости корпоративной сети на платформе OSTIS. Проект включает:

- **Модуль C++** с тремя агентами для анализа графа сети
- **Базу знаний SCS** с определением предметной области и тестовой сетью
- **Модульные тесты** для проверки корректности алгоритмов

Проект выполнен в рамках расчётной работы по дисциплине "Проектирование программного обеспечения интеллектуальных систем" (Вариант 6).

---

# 2. Что такое OSTIS

**OSTIS** (Open Semantic Technology for Intelligent Systems) — это технология создания интеллектуальных систем на основе семантических сетей.

## 2.1 Основные компоненты

| Компонент | Описание |
|-----------|----------|
| **SC-память** | Семантическая память для хранения знаний в виде графа |
| **SC-код** | Язык представления знаний (узлы и дуги) |
| **Агенты** | Программы, обрабатывающие знания в памяти |
| **SC-Web** | Веб-интерфейс для визуализации и взаимодействия |

## 2.2 Принцип работы

1. Знания хранятся в виде графа (узлы + связи)
2. Агенты "подписаны" на определённые события
3. При возникновении события агент активируется
4. Агент читает данные из памяти, обрабатывает их, записывает результат

---

# 3. Архитектура проекта

## 3.1 Структура каталогов

```
PpoisNetworkResilience/
├── problem-solver/
│   └── cxx/
│       └── network_resilience_module/      # Наш модуль
│           ├── agents/                      # Агенты
│           │   ├── articulation_points_agent.cpp
│           │   ├── articulation_points_agent.hpp
│           │   ├── bridges_agent.cpp
│           │   ├── bridges_agent.hpp
│           │   ├── vertex_connectivity_agent.cpp
│           │   └── vertex_connectivity_agent.hpp
│           ├── keynodes/                    # Ключевые узлы
│           │   └── resilience_keynodes.hpp
│           ├── test/                        # Тесты
│           │   └── test_resilience.cpp
│           ├── network_resilience_module.hpp
│           ├── network_resilience_module.cpp
│           └── CMakeLists.txt
├── knowledge-base/
│   └── network-domain/                      # База знаний
│       ├── network_domain.scs               # Онтология
│       └── test_network.scs                 # Тестовая сеть
└── docker-compose.yml
```

## 3.2 Связь компонентов

```
┌─────────────────────────────────────────────────────────────┐
│                         SC-ПАМЯТЬ                            │
│  ┌─────────────┐  ┌─────────────┐  ┌─────────────┐          │
│  │ Устройства  │  │   Связи     │  │  Действия   │          │
│  │  (nodes)    │──│  (arcs)     │──│  (actions)  │          │
│  └─────────────┘  └─────────────┘  └─────────────┘          │
└─────────────────────────────────────────────────────────────┘
         ▲                                    │
         │                                    ▼
┌─────────────────┐                 ┌─────────────────┐
│                 │                 │                 │
│  БАЗА ЗНАНИЙ    │                 │     АГЕНТЫ      │
│  (SCS файлы)    │                 │  (C++ классы)   │
│                 │                 │                 │
└─────────────────┘                 └─────────────────┘
```

---

# 4. Модуль Network Resilience

## 4.1 Заголовочный файл модуля

**Файл:** `network_resilience_module.hpp`

```cpp
#pragma once

#include <sc-memory/sc_module.hpp>

class NetworkResilienceModule : public ScModule
{
};
```

### Объяснение:

- `#pragma once` — защита от повторного включения заголовочного файла
- `#include <sc-memory/sc_module.hpp>` — подключение базового класса модуля OSTIS
- `class NetworkResilienceModule : public ScModule` — объявление класса модуля, наследующего от `ScModule`
- Класс пустой, так как вся логика регистрации агентов находится в `.cpp` файле

---

## 4.2 Реализация модуля

**Файл:** `network_resilience_module.cpp`

```cpp
#include "network_resilience_module.hpp"
#include "agents/vertex_connectivity_agent.hpp"
#include "agents/articulation_points_agent.hpp"
#include "agents/bridges_agent.hpp"
#include "keynodes/resilience_keynodes.hpp"

SC_MODULE_REGISTER(NetworkResilienceModule)
    ->Agent<VertexConnectivityAgent>()
    ->Agent<ArticulationPointsAgent>()
    ->Agent<BridgesAgent>();
```

### Объяснение по строкам:

| Строка | Код | Пояснение |
|--------|-----|-----------|
| 1 | `#include "network_resilience_module.hpp"` | Подключение заголовка модуля |
| 2-4 | `#include "agents/..."` | Подключение заголовков всех агентов |
| 5 | `#include "keynodes/resilience_keynodes.hpp"` | Подключение ключевых узлов |
| 7-10 | `SC_MODULE_REGISTER(...)` | Макрос регистрации модуля с указанием агентов |

### Как работает регистрация:

1. Макрос `SC_MODULE_REGISTER` создаёт точку входа для загрузки модуля
2. Метод `->Agent<T>()` регистрирует агент типа `T`
3. При загрузке модуля OSTIS автоматически подписывает агенты на события

---

# 5. Ключевые узлы (Keynodes)

**Файл:** `keynodes/resilience_keynodes.hpp`

```cpp
#pragma once

#include <sc-memory/sc_keynodes.hpp>

class ResilienceKeynodes : public ScKeynodes
{
public:
  static inline ScKeynode const action_find_vertex_connectivity{
      "action_find_vertex_connectivity",
      ScType::ConstNodeClass};

  static inline ScKeynode const action_find_articulation_points{
      "action_find_articulation_points",
      ScType::ConstNodeClass};

  static inline ScKeynode const action_find_bridges{
      "action_find_bridges", 
      ScType::ConstNodeClass};

  static inline ScKeynode const nrel_connected_to{
      "nrel_connected_to", 
      ScType::ConstNodeNonRole};

  static inline ScKeynode const concept_device{
      "concept_device", 
      ScType::ConstNodeClass};

  static inline ScKeynode const concept_server{
      "concept_server", 
      ScType::ConstNodeClass};

  static inline ScKeynode const concept_workstation{
      "concept_workstation", 
      ScType::ConstNodeClass};

  static inline ScKeynode const concept_switch{
      "concept_switch", 
      ScType::ConstNodeClass};

  static inline ScKeynode const concept_router{
      "concept_router", 
      ScType::ConstNodeClass};

  static inline ScKeynode const concept_gateway{
      "concept_gateway", 
      ScType::ConstNodeClass};
};
```

### Объяснение ключевых узлов:

| Keynode | Тип | Назначение |
|---------|-----|------------|
| `action_find_vertex_connectivity` | Class | Действие проверки связности |
| `action_find_articulation_points` | Class | Действие поиска точек сочленения |
| `action_find_bridges` | Class | Действие поиска мостов |
| `nrel_connected_to` | NonRole Relation | Отношение "соединён с" |
| `concept_device` | Class | Базовый класс устройств |
| `concept_server` | Class | Сервер |
| `concept_workstation` | Class | Рабочая станция |
| `concept_switch` | Class | Коммутатор |
| `concept_router` | Class | Маршрутизатор |
| `concept_gateway` | Class | Шлюз |

### Принцип работы ScKeynode:

```cpp
static inline ScKeynode const имя{"идентификатор", тип};
```

- `static inline` — переменная создаётся один раз для всего приложения
- `ScKeynode const` — константный ключевой узел
- `"идентификатор"` — системный идентификатор узла в SC-памяти
- `тип` — тип SC-элемента (класс, отношение и т.д.)

---

# 6. Агент поиска точек сочленения

## 6.1 Заголовочный файл

**Файл:** `agents/articulation_points_agent.hpp`

```cpp
#pragma once
#include <sc-memory/sc_agent.hpp>

class ArticulationPointsAgent : public ScActionInitiatedAgent
{
public:
  ScAddr GetActionClass() const override;
  ScResult DoProgram(ScAction & action) override;
};
```

### Объяснение:

- `ScActionInitiatedAgent` — базовый класс агента, реагирующего на действия
- `GetActionClass()` — возвращает класс действия, на который реагирует агент
- `DoProgram()` — основная логика агента

---

## 6.2 Реализация агента

**Файл:** `agents/articulation_points_agent.cpp`

```cpp
#include "articulation_points_agent.hpp"
#include "../keynodes/resilience_keynodes.hpp"
#include <sc-memory/sc_memory.hpp>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

ScAddr ArticulationPointsAgent::GetActionClass() const
{
  return ResilienceKeynodes::action_find_articulation_points;
}

ScResult ArticulationPointsAgent::DoProgram(ScAction & action)
{
  m_logger.Info("Starting Articulation Points Search");
  auto const & [argsAddr] = action.GetArguments<1>();
  ScAddr graphNode = argsAddr;

  if (!m_context.IsElement(graphNode))
  {
    return action.FinishWithError();
  }

  vector<ScAddr> nodes;
  map<size_t, vector<size_t>> adj;
  map<ScAddr, size_t, ScAddrLessFunc> addrToIndex;
  map<size_t, ScAddr> indexToAddr;

  ScIterator3Ptr itNodes =
      m_context.CreateIterator3(ResilienceKeynodes::concept_device, ScType::ConstPermPosArc, ScType::Unknown);

  size_t idx = 0;
  while (itNodes->Next())
  {
    ScAddr node = itNodes->Get(2);
    if (m_context.CheckConnector(graphNode, node, ScType::ConstPermPosArc))
    {
      nodes.push_back(node);
      addrToIndex[node] = idx;
      indexToAddr[idx] = node;
      idx++;
    }
  }

  for (auto const & node : nodes)
  {
    size_t u = addrToIndex[node];
    ScIterator5Ptr itEdges = m_context.CreateIterator5(
        node, ScType::ConstCommonArc, ScType::Unknown, ScType::ConstPermPosArc, ResilienceKeynodes::nrel_connected_to);
    while (itEdges->Next())
    {
      ScAddr neighbor = itEdges->Get(2);
      if (addrToIndex.count(neighbor))
      {
        size_t v = addrToIndex[neighbor];
        adj[u].push_back(v);
        adj[v].push_back(u);
      }
    }
  }

  size_t n = nodes.size();
  vector<bool> visited(n, false);
  vector<int> tin(n, -1), low(n, -1);
  int timer = 0;
  vector<ScAddr> articulationPoints;

  std::function<void(int, int)> dfs = [&](int u, int p = -1)
  {
    visited[u] = true;
    tin[u] = low[u] = timer++;
    int children = 0;
    for (int v : adj[u])
    {
      if (v == p)
        continue;
      if (visited[v])
      {
        low[u] = min(low[u], tin[v]);
      }
      else
      {
        dfs(v, u);
        low[u] = min(low[u], low[v]);
        if (low[v] >= tin[u] && p != -1)
          articulationPoints.push_back(indexToAddr[u]);
        children++;
      }
    }
    if (p == -1 && children > 1)
      articulationPoints.push_back(indexToAddr[u]);
  };

  for (size_t i = 0; i < n; ++i)
  {
    if (!visited[i])
      dfs(i, -1);
  }

  ScStructure result = m_context.GenerateStructure();
  for (auto const & ap : articulationPoints)
  {
    result << ap;
  }

  sort(articulationPoints.begin(), articulationPoints.end(), ScAddrLessFunc());
  articulationPoints.erase(unique(articulationPoints.begin(), articulationPoints.end()), articulationPoints.end());

  action.SetResult(result);
  return action.FinishSuccessfully();
}
```

### Подробное объяснение алгоритма:

#### Шаг 1: Получение аргументов (строки 17-24)

```cpp
auto const & [argsAddr] = action.GetArguments<1>();
ScAddr graphNode = argsAddr;

if (!m_context.IsElement(graphNode))
{
  return action.FinishWithError();
}
```

- Получаем первый аргумент действия — адрес графа сети
- Проверяем, что это корректный элемент SC-памяти
- Если нет — возвращаем ошибку

#### Шаг 2: Сбор вершин графа (строки 26-45)

```cpp
vector<ScAddr> nodes;
map<size_t, vector<size_t>> adj;
map<ScAddr, size_t, ScAddrLessFunc> addrToIndex;
map<size_t, ScAddr> indexToAddr;

ScIterator3Ptr itNodes =
    m_context.CreateIterator3(ResilienceKeynodes::concept_device, ScType::ConstPermPosArc, ScType::Unknown);

size_t idx = 0;
while (itNodes->Next())
{
  ScAddr node = itNodes->Get(2);
  if (m_context.CheckConnector(graphNode, node, ScType::ConstPermPosArc))
  {
    nodes.push_back(node);
    addrToIndex[node] = idx;
    indexToAddr[idx] = node;
    idx++;
  }
}
```

**Что происходит:**

1. Создаём структуры данных:
   - `nodes` — список всех вершин
   - `adj` — список смежности (граф)
   - `addrToIndex` — отображение SC-адрес → индекс
   - `indexToAddr` — отображение индекс → SC-адрес

2. Используем итератор из 3 элементов:
   - `concept_device` — начальный узел
   - `ConstPermPosArc` — тип дуги (принадлежность классу)
   - `Unknown` — ищем любой конечный узел

3. Для каждого устройства проверяем, принадлежит ли оно нашему графу

#### Шаг 3: Построение списка смежности (строки 47-62)

```cpp
for (auto const & node : nodes)
{
  size_t u = addrToIndex[node];
  ScIterator5Ptr itEdges = m_context.CreateIterator5(
      node, ScType::ConstCommonArc, ScType::Unknown, ScType::ConstPermPosArc, ResilienceKeynodes::nrel_connected_to);
  while (itEdges->Next())
  {
    ScAddr neighbor = itEdges->Get(2);
    if (addrToIndex.count(neighbor))
    {
      size_t v = addrToIndex[neighbor];
      adj[u].push_back(v);
      adj[v].push_back(u);
    }
  }
}
```

**Что происходит:**

1. Для каждой вершины ищем исходящие рёбра
2. Используем итератор из 5 элементов (для отношений):
   - `node` — начальная вершина
   - `ConstCommonArc` — общая дуга (связь)
   - `Unknown` — конечная вершина
   - `ConstPermPosArc` — дуга от отношения
   - `nrel_connected_to` — само отношение

3. Добавляем соседа в список смежности (в обе стороны — граф неориентированный)

#### Шаг 4: Алгоритм DFS для поиска точек сочленения (строки 64-100)

```cpp
size_t n = nodes.size();
vector<bool> visited(n, false);
vector<int> tin(n, -1), low(n, -1);
int timer = 0;
vector<ScAddr> articulationPoints;

std::function<void(int, int)> dfs = [&](int u, int p = -1)
{
  visited[u] = true;
  tin[u] = low[u] = timer++;
  int children = 0;
  for (int v : adj[u])
  {
    if (v == p)
      continue;
    if (visited[v])
    {
      low[u] = min(low[u], tin[v]);
    }
    else
    {
      dfs(v, u);
      low[u] = min(low[u], low[v]);
      if (low[v] >= tin[u] && p != -1)
        articulationPoints.push_back(indexToAddr[u]);
      children++;
    }
  }
  if (p == -1 && children > 1)
    articulationPoints.push_back(indexToAddr[u]);
};
```

**Алгоритм Тарьяна:**

| Переменная | Назначение |
|------------|------------|
| `visited[u]` | Посещена ли вершина u |
| `tin[u]` | Время входа в вершину u |
| `low[u]` | Минимальное время входа, достижимое из u |
| `timer` | Глобальный счётчик времени |
| `articulationPoints` | Найденные точки сочленения |

**Критерий точки сочленения:**

1. Для некорневой вершины `u`: если `low[v] >= tin[u]` для какого-то потомка `v`
2. Для корня: если у корня более одного ребёнка в DFS-дереве

#### Шаг 5: Формирование результата (строки 102-113)

```cpp
ScStructure result = m_context.GenerateStructure();
for (auto const & ap : articulationPoints)
{
  result << ap;
}

action.SetResult(result);
return action.FinishSuccessfully();
```

**Что происходит:**

1. Создаём SC-структуру для результата
2. Добавляем все найденные точки сочленения
3. Устанавливаем результат действия
4. Возвращаем успешное завершение

---

# 7. Агент поиска мостов

## 7.1 Заголовочный файл

**Файл:** `agents/bridges_agent.hpp`

```cpp
#pragma once
#include <sc-memory/sc_agent.hpp>

class BridgesAgent : public ScActionInitiatedAgent
{
public:
  ScAddr GetActionClass() const override;
  ScResult DoProgram(ScAction & action) override;
};
```

---

## 7.2 Реализация агента

**Файл:** `agents/bridges_agent.cpp`

```cpp
#include "bridges_agent.hpp"
#include "../keynodes/resilience_keynodes.hpp"
#include <sc-memory/sc_memory.hpp>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

ScAddr BridgesAgent::GetActionClass() const
{
  return ResilienceKeynodes::action_find_bridges;
}

ScResult BridgesAgent::DoProgram(ScAction & action)
{
  m_logger.Info("Starting Bridges Search");
  auto const & [argsAddr] = action.GetArguments<1>();
  ScAddr graphNode = argsAddr;

  if (!m_context.IsElement(graphNode))
  {
    return action.FinishWithError();
  }

  // 1. Collect graph
  vector<ScAddr> nodes;
  map<size_t, vector<size_t>> adj;
  map<ScAddr, size_t, ScAddrLessFunc> addrToIndex;
  map<size_t, ScAddr> indexToAddr;

  ScIterator3Ptr itNodes =
      m_context.CreateIterator3(ResilienceKeynodes::concept_device, ScType::ConstPermPosArc, ScType::Unknown);

  size_t idx = 0;
  while (itNodes->Next())
  {
    ScAddr node = itNodes->Get(2);
    if (m_context.CheckConnector(graphNode, node, ScType::ConstPermPosArc))
    {
      nodes.push_back(node);
      addrToIndex[node] = idx;
      indexToAddr[idx] = node;
      idx++;
    }
  }

  map<pair<size_t, size_t>, ScAddr> edgeToArc;

  for (auto const & node : nodes)
  {
    size_t u = addrToIndex[node];
    ScIterator5Ptr itEdges = m_context.CreateIterator5(
        node, ScType::ConstCommonArc, ScType::Unknown, ScType::ConstPermPosArc, ResilienceKeynodes::nrel_connected_to);
    while (itEdges->Next())
    {
      ScAddr neighbor = itEdges->Get(2);
      ScAddr commonArc = itEdges->Get(1);

      if (addrToIndex.count(neighbor))
      {
        size_t v = addrToIndex[neighbor];
        adj[u].push_back(v);
        adj[v].push_back(u);

        if (u < v)
          edgeToArc[{u, v}] = commonArc;
        else
          edgeToArc[{v, u}] = commonArc;
      }
    }
  }

  // 2. Find Bridges
  size_t n = nodes.size();
  vector<bool> visited(n, false);
  vector<int> tin(n, -1), low(n, -1);
  int timer = 0;
  ScStructure result = m_context.GenerateStructure();

  std::function<void(int, int)> dfs = [&](int u, int p = -1)
  {
    visited[u] = true;
    tin[u] = low[u] = timer++;
    for (int v : adj[u])
    {
      if (v == p)
        continue;
      if (visited[v])
      {
        low[u] = min(low[u], tin[v]);
      }
      else
      {
        dfs(v, u);
        low[u] = min(low[u], low[v]);
        if (low[v] > tin[u])
        {
          size_t a = min((size_t)u, (size_t)v);
          size_t b = max((size_t)u, (size_t)v);
          if (edgeToArc.count({a, b}))
          {
            result << edgeToArc[{a, b}];
          }
        }
      }
    }
  };

  for (size_t i = 0; i < n; ++i)
  {
    if (!visited[i])
      dfs(i, -1);
  }

  action.SetResult(result);
  return action.FinishSuccessfully();
}
```

### Отличия от агента точек сочленения:

| Аспект | Точки сочленения | Мосты |
|--------|------------------|-------|
| Что ищем | Вершины | Рёбра |
| Критерий | `low[v] >= tin[u]` | `low[v] > tin[u]` |
| Результат | SC-адреса вершин | SC-адреса дуг |
| Дополнительно | — | Храним `edgeToArc` |

### Ключевые отличия в коде:

```cpp
// Сохраняем соответствие ребра и SC-дуги
map<pair<size_t, size_t>, ScAddr> edgeToArc;

// При обходе сохраняем дугу
ScAddr commonArc = itEdges->Get(1);
if (u < v)
  edgeToArc[{u, v}] = commonArc;
else
  edgeToArc[{v, u}] = commonArc;

// Критерий моста (строгое неравенство)
if (low[v] > tin[u])
{
  result << edgeToArc[{a, b}];
}
```

---

# 8. Агент определения связности

## 8.1 Заголовочный файл

**Файл:** `agents/vertex_connectivity_agent.hpp`

```cpp
#pragma once
#include <sc-memory/sc_agent.hpp>

class VertexConnectivityAgent : public ScActionInitiatedAgent
{
public:
  ScAddr GetActionClass() const override;
  ScResult DoProgram(ScAction & action) override;
};
```

---

## 8.2 Реализация агента

**Файл:** `agents/vertex_connectivity_agent.cpp`

```cpp
#include "vertex_connectivity_agent.hpp"
#include "../keynodes/resilience_keynodes.hpp"
#include <sc-memory/sc_memory.hpp>
#include <sc-memory/sc_link.hpp>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

ScAddr VertexConnectivityAgent::GetActionClass() const
{
  return ResilienceKeynodes::action_find_vertex_connectivity;
}

ScResult VertexConnectivityAgent::DoProgram(ScAction & action)
{
  m_logger.Info("Starting Vertex Connectivity Calculation");
  auto const & [argsAddr] = action.GetArguments<1>();
  ScAddr graphNode = argsAddr;

  if (!m_context.IsElement(graphNode))
    return action.FinishWithError();

  vector<ScAddr> nodes;
  map<size_t, vector<size_t>> adj;
  map<ScAddr, size_t, ScAddrLessFunc> addrToIndex;

  ScIterator3Ptr itNodes =
      m_context.CreateIterator3(ResilienceKeynodes::concept_device, ScType::ConstPermPosArc, ScType::Unknown);

  size_t idx = 0;
  while (itNodes->Next())
  {
    ScAddr node = itNodes->Get(2);
    if (m_context.CheckConnector(graphNode, node, ScType::ConstPermPosArc))
    {
      nodes.push_back(node);
      addrToIndex[node] = idx++;
    }
  }

  if (nodes.empty())
    return action.FinishWithError();

  for (auto const & node : nodes)
  {
    size_t u = addrToIndex[node];
    ScIterator5Ptr itEdges = m_context.CreateIterator5(
        node, ScType::ConstCommonArc, ScType::Unknown, ScType::ConstPermPosArc, ResilienceKeynodes::nrel_connected_to);
    while (itEdges->Next())
    {
      ScAddr neighbor = itEdges->Get(2);
      if (addrToIndex.count(neighbor))
      {
        size_t v = addrToIndex[neighbor];
        adj[u].push_back(v);
      }
    }
  }

  vector<bool> visited(nodes.size(), false);
  vector<size_t> q;
  q.push_back(0);
  visited[0] = true;
  size_t head = 0;
  while (head < q.size())
  {
    size_t u = q[head++];
    for (size_t v : adj[u])
    {
      if (!visited[v])
      {
        visited[v] = true;
        q.push_back(v);
      }
    }
  }

  bool connected = (q.size() == nodes.size());

  ScAddr resultLink = m_context.GenerateLink();
  std::string resStr = connected ? "Connected (Connectivity >= 1)" : "Disconnected (Connectivity = 0)";
  m_context.SetLinkContent(resultLink, resStr);

  ScStructure result = m_context.GenerateStructure();
  result << resultLink;

  action.SetResult(result);
  return action.FinishSuccessfully();
}
```

### Объяснение алгоритма BFS:

```cpp
vector<bool> visited(nodes.size(), false);
vector<size_t> q;
q.push_back(0);
visited[0] = true;
size_t head = 0;
while (head < q.size())
{
  size_t u = q[head++];
  for (size_t v : adj[u])
  {
    if (!visited[v])
    {
      visited[v] = true;
      q.push_back(v);
    }
  }
}

bool connected = (q.size() == nodes.size());
```

**Принцип работы:**

1. Начинаем с вершины 0
2. Добавляем её в очередь
3. Для каждой вершины из очереди добавляем всех непосещённых соседей
4. Если размер очереди равен количеству вершин — граф связный

### Формирование текстового результата:

```cpp
ScAddr resultLink = m_context.GenerateLink();
std::string resStr = connected ? "Connected (Connectivity >= 1)" : "Disconnected (Connectivity = 0)";
m_context.SetLinkContent(resultLink, resStr);
```

- `GenerateLink()` — создаём SC-ссылку (узел с содержимым)
- `SetLinkContent()` — устанавливаем текстовое содержимое

---

# 9. База знаний (SCS)

## 9.1 Онтология предметной области

**Файл:** `knowledge-base/network-domain/network_domain.scs`

```scs
concept_device
=> nrel_main_idtf: [устройство] (* <- lang_ru;; *);
=> nrel_main_idtf: [device] (* <- lang_en;; *);;

concept_server
=> nrel_main_idtf: [сервер] (* <- lang_ru;; *);
=> nrel_main_idtf: [server] (* <- lang_en;; *);
<- concept_device;;

concept_workstation
=> nrel_main_idtf: [рабочая станция] (* <- lang_ru;; *);
=> nrel_main_idtf: [workstation] (* <- lang_en;; *);
<- concept_device;;

concept_switch
=> nrel_main_idtf: [коммутатор] (* <- lang_ru;; *);
=> nrel_main_idtf: [switch] (* <- lang_en;; *);
<- concept_device;;

concept_router
=> nrel_main_idtf: [маршрутизатор] (* <- lang_ru;; *);
=> nrel_main_idtf: [router] (* <- lang_en;; *);
<- concept_device;;

concept_gateway
=> nrel_main_idtf: [шлюз] (* <- lang_ru;; *);
=> nrel_main_idtf: [gateway] (* <- lang_en;; *);
<- concept_device;;

nrel_connected_to
=> nrel_main_idtf: [соединен с] (* <- lang_ru;; *);
=> nrel_main_idtf: [connected to] (* <- lang_en;; *);
<- sc_node_non_role_relation;
<- symmetric_relation;
<- binary_relation;;

action_find_articulation_points
=> nrel_main_idtf: [найти точки сочленения] (* <- lang_ru;; *);
=> nrel_main_idtf: [find articulation points] (* <- lang_en;; *);
<- sc_node_class;;

action_find_bridges
=> nrel_main_idtf: [найти мосты] (* <- lang_ru;; *);
=> nrel_main_idtf: [find bridges] (* <- lang_en;; *);
<- sc_node_class;;

action_find_vertex_connectivity
=> nrel_main_idtf: [найти вершинную связность] (* <- lang_ru;; *);
=> nrel_main_idtf: [find vertex connectivity] (* <- lang_en;; *);
<- sc_node_class;;
```

### Объяснение синтаксиса SCS:

#### Определение класса:

```scs
concept_device
=> nrel_main_idtf: [устройство] (* <- lang_ru;; *);
=> nrel_main_idtf: [device] (* <- lang_en;; *);;
```

| Элемент | Значение |
|---------|----------|
| `concept_device` | Системный идентификатор узла |
| `=>` | Направление отношения (от subject к object) |
| `nrel_main_idtf` | Отношение "основной идентификатор" |
| `[устройство]` | SC-ссылка с текстом |
| `(* <- lang_ru;; *)` | Вложенная конструкция: принадлежит классу `lang_ru` |
| `;;` | Конец предложения |

#### Наследование классов:

```scs
concept_server
<- concept_device;;
```

Читается: `concept_server` принадлежит классу `concept_device` (сервер — это устройство).

#### Определение отношения:

```scs
nrel_connected_to
<- sc_node_non_role_relation;
<- symmetric_relation;
<- binary_relation;;
```

- `sc_node_non_role_relation` — неролевое отношение
- `symmetric_relation` — симметричное (A связано с B = B связано с A)
- `binary_relation` — бинарное (связывает ровно 2 элемента)

---

## 9.2 Тестовая сеть

**Файл:** `knowledge-base/network-domain/test_network.scs`

```scs
network_infotech
=> nrel_main_idtf: [Сеть ООО "ИнфоТех"] (* <- lang_ru;; *);
<- sc_node_structure;;

ws_01 <- concept_workstation;;
ws_02 <- concept_workstation;;
ws_03 <- concept_workstation;;
server_01 <- concept_server;;
switch_01 <- concept_switch;;
router_01 <- concept_router;;

network_infotech -> ws_01; ws_02; ws_03; server_01; switch_01; router_01;;

// Connections
switch_01 => nrel_connected_to: ws_01;;
switch_01 => nrel_connected_to: ws_02;;
switch_01 => nrel_connected_to: ws_03;;
switch_01 => nrel_connected_to: server_01;;
switch_01 => nrel_connected_to: router_01;;
```

### Визуализация топологии:

```
                    router_01
                        |
                    switch_01
                   /  |  |  \
               ws_01 ws_02 ws_03 server_01
```

### Объяснение:

| Строка | Код | Пояснение |
|--------|-----|-----------|
| 1-3 | `network_infotech...` | Создание структуры (графа сети) |
| 5-10 | `ws_01 <- ...` | Создание устройств и указание их типов |
| 12 | `network_infotech -> ...` | Добавление устройств в структуру сети |
| 15-19 | `switch_01 => nrel_connected_to: ...` | Создание связей между устройствами |

### Результаты анализа этой сети:

| Анализ | Результат | Объяснение |
|--------|-----------|------------|
| Точки сочленения | `switch_01` | Удаление коммутатора разрывает связь всех устройств |
| Мосты | Все 5 рёбер | Каждое ребро — единственный путь |
| Связность | Connected | Все устройства достижимы друг от друга |

---

# 10. Тестирование

## 10.1 Файл тестов

**Файл:** `test/test_resilience.cpp`

```cpp
#include <sc-memory/test/sc_test.hpp>
#include <sc-memory/sc_memory.hpp>
#include <sc-memory/sc_addr.hpp>
#include <sc-memory/sc_type.hpp>
#include <sc-memory/sc_iterator.hpp>
#include <sc-memory/sc_link.hpp>
#include "../agents/articulation_points_agent.hpp"
#include "../agents/bridges_agent.hpp"
#include "../agents/vertex_connectivity_agent.hpp"
#include "../keynodes/resilience_keynodes.hpp"

using AgentTest = ScMemoryTest;

ScAddr create_device(ScMemoryContext * ctx)
{
  ScAddr node = ctx->GenerateNode(ScType::ConstNode);
  ctx->GenerateConnector(ScType::ConstPermPosArc, ResilienceKeynodes::concept_device, node);
  return node;
}

void connect_devices(ScMemoryContext * ctx, ScAddr d1, ScAddr d2)
{
  ScAddr arc = ctx->GenerateConnector(ScType::ConstCommonArc, d1, d2);
  ctx->GenerateConnector(ScType::ConstPermPosArc, ResilienceKeynodes::nrel_connected_to, arc);
}

TEST_F(AgentTest, ArticulationPointsLineGraph)
{
  ScAddr a = create_device(m_ctx.get());
  ScAddr b = create_device(m_ctx.get());
  ScAddr c = create_device(m_ctx.get());

  connect_devices(m_ctx.get(), a, b);
  connect_devices(m_ctx.get(), b, c);

  m_ctx->SubscribeAgent<ArticulationPointsAgent>();

  ScStructure structNode = m_ctx->GenerateStructure();
  structNode << a << b << c;

  ScAction action = m_ctx->GenerateAction(ResilienceKeynodes::action_find_articulation_points);
  action.SetArguments(structNode);

  EXPECT_TRUE(action.InitiateAndWait());
  EXPECT_TRUE(action.IsFinishedSuccessfully());

  ScAddr res = action.GetResult();
  EXPECT_TRUE(m_ctx->CheckConnector(res, b, ScType::ConstPermPosArc));
  EXPECT_FALSE(m_ctx->CheckConnector(res, a, ScType::ConstPermPosArc));
  EXPECT_FALSE(m_ctx->CheckConnector(res, c, ScType::ConstPermPosArc));

  m_ctx->UnsubscribeAgent<ArticulationPointsAgent>();
}

TEST_F(AgentTest, BridgesLineGraph)
{
  ScAddr a = create_device(m_ctx.get());
  ScAddr b = create_device(m_ctx.get());
  ScAddr c = create_device(m_ctx.get());

  connect_devices(m_ctx.get(), a, b);
  connect_devices(m_ctx.get(), b, c);

  m_ctx->SubscribeAgent<BridgesAgent>();

  ScStructure structNode = m_ctx->GenerateStructure();
  structNode << a << b << c;

  ScAction action = m_ctx->GenerateAction(ResilienceKeynodes::action_find_bridges);
  action.SetArguments(structNode);

  EXPECT_TRUE(action.InitiateAndWait());
  EXPECT_TRUE(action.IsFinishedSuccessfully());

  ScAddr res = action.GetResult();
  int count = 0;
  ScIterator3Ptr it = m_ctx->CreateIterator3(res, ScType::ConstPermPosArc, ScType::ConstCommonArc);
  while (it->Next())
    count++;
  EXPECT_EQ(count, 2);

  m_ctx->UnsubscribeAgent<BridgesAgent>();
}

TEST_F(AgentTest, VertexConnectivityCheck)
{
  ScAddr a = create_device(m_ctx.get());
  ScAddr b = create_device(m_ctx.get());
  connect_devices(m_ctx.get(), a, b);

  m_ctx->SubscribeAgent<VertexConnectivityAgent>();

  ScStructure structNode = m_ctx->GenerateStructure();
  structNode << a << b;

  ScAction action = m_ctx->GenerateAction(ResilienceKeynodes::action_find_vertex_connectivity);
  action.SetArguments(structNode);

  EXPECT_TRUE(action.InitiateAndWait());
  EXPECT_TRUE(action.IsFinishedSuccessfully());

  ScAddr res = action.GetResult();
  ScIterator3Ptr it = m_ctx->CreateIterator3(res, ScType::ConstPermPosArc, ScType::ConstNodeLink);
  EXPECT_TRUE(it->Next());

  m_ctx->UnsubscribeAgent<VertexConnectivityAgent>();
}
```

### Объяснение тестов:

#### Вспомогательные функции:

```cpp
ScAddr create_device(ScMemoryContext * ctx)
{
  ScAddr node = ctx->GenerateNode(ScType::ConstNode);
  ctx->GenerateConnector(ScType::ConstPermPosArc, ResilienceKeynodes::concept_device, node);
  return node;
}
```

Создаёт узел и добавляет его в класс `concept_device`.

```cpp
void connect_devices(ScMemoryContext * ctx, ScAddr d1, ScAddr d2)
{
  ScAddr arc = ctx->GenerateConnector(ScType::ConstCommonArc, d1, d2);
  ctx->GenerateConnector(ScType::ConstPermPosArc, ResilienceKeynodes::nrel_connected_to, arc);
}
```

Создаёт связь между двумя устройствами через отношение `nrel_connected_to`.

#### Тест 1: Точки сочленения

```
A --- B --- C
```

- Ожидаемый результат: B — точка сочленения
- Проверка: `EXPECT_TRUE(m_ctx->CheckConnector(res, b, ...))`

#### Тест 2: Мосты

```
A --- B --- C
```

- Ожидаемый результат: 2 моста (A-B и B-C)
- Проверка: подсчёт количества мостов в результате

#### Тест 3: Связность

```
A --- B
```

- Ожидаемый результат: граф связный
- Проверка: результат содержит SC-ссылку с текстом

---

## 10.2 Команда запуска тестов

```bash
docker compose exec machine env \
  LD_LIBRARY_PATH=/example-app/install/sc-machine/lib:/example-app/build/Release/extensions \
  /example-app/build/Release/extensions/network_resilience_tests
```

### Ожидаемый вывод:

```
[==========] Running 3 tests from 1 test suite.
[----------] 3 tests from AgentTest
[ RUN      ] AgentTest.ArticulationPointsLineGraph
[       OK ] AgentTest.ArticulationPointsLineGraph (14 ms)
[ RUN      ] AgentTest.BridgesLineGraph
[       OK ] AgentTest.BridgesLineGraph (10 ms)
[ RUN      ] AgentTest.VertexConnectivityCheck
[       OK ] AgentTest.VertexConnectivityCheck (6 ms)
[----------] 3 tests from AgentTest (31 ms total)

[==========] 3 tests from 1 test suite ran. (31 ms total)
[  PASSED  ] 3 tests.
```

---

# 11. Сборка и запуск

## 11.1 Требования

- Docker
- Docker Compose

## 11.2 Сборка

```bash
cd /home/shahzad/PPOIS/PP/PP/PpoisNetworkResilience
docker compose build
```

## 11.3 Запуск

```bash
docker compose up -d
```

## 11.4 Остановка

```bash
docker compose down
```

## 11.5 Доступ к системе

- **Web-интерфейс:** http://localhost:8000
- **SC-Server:** localhost:8090

---

# Заключение

В данном руководстве подробно рассмотрены все компоненты проекта анализа отказоустойчивости корпоративной сети:

1. **Архитектура модуля OSTIS** — структура файлов и их взаимосвязи
2. **Ключевые узлы** — определение семантических идентификаторов
3. **Три агента** — реализация алгоритмов поиска точек сочленения, мостов и проверки связности
4. **База знаний SCS** — онтология предметной области и тестовые данные
5. **Модульные тесты** — проверка корректности алгоритмов
6. **Инструкции по сборке и запуску** — команды Docker

Проект полностью функционален и готов к демонстрации.
