# Sistema de Navegación Basado en Grafos

**Proyecto Final - Algoritmos y Estructura de Datos**  
**Autor:** Manus AI  
**Fecha:** 29 de Julio, 2025

## Descripción

Sistema completo de navegación que implementa algoritmos de búsqueda en grafos desde cero, incluyendo estructuras de datos personalizadas, visualización gráfica, y análisis de rendimiento para mapas pequeños y grandes.

## Características Principales

- ✅ **Estructuras de datos desde cero**: DynamicArray, LinkedList, Queue, PriorityQueue
- ✅ **5 algoritmos de búsqueda**: DFS, BFS, Dijkstra, Best First Search, A*
- ✅ **Visualización gráfica**: Interfaz SFML para mapas interactivos
- ✅ **Interfaz de consola**: Alternativa completa sin dependencias gráficas
- ✅ **Mapas grandes**: Generación sintética hasta 2M nodos
- ✅ **Análisis de rendimiento**: Métricas detalladas y reportes comparativos
- ✅ **Suite de pruebas**: 92 pruebas automatizadas (97.8% éxito)

## Estructura del Proyecto

```
final_project/
├── include/           # Headers (.h)
├── src/              # Código fuente (.cpp)
├── build/            # Ejecutables compilados
├── data/             # Archivos de datos y mapas
├── docs/             # Documentación adicional
└── README.md         # Este archivo
```

## Compilación

### Requisitos
- Compilador C++11 o superior (GCC, Clang, MSVC)
- SFML 2.4+ (para interfaz gráfica)
- Make o herramientas de compilación equivalentes

### Compilar Todo el Sistema
```bash
# Compilar programa principal con interfaz gráfica
g++ -std=c++11 -I./include -o build/main_visual src/node.cpp src/edge.cpp src/graph.cpp src/search_algorithms.cpp src/map_loader.cpp src/visualizer.cpp src/main_visual.cpp -lsfml-graphics -lsfml-window -lsfml-system

# Compilar interfaz de consola (sin SFML)
g++ -std=c++11 -I./include -o build/console_interface src/node.cpp src/edge.cpp src/graph.cpp src/search_algorithms.cpp src/map_loader.cpp src/console_interface.cpp

# Compilar sistema de mapas grandes
g++ -std=c++11 -I./include -o build/large_scale_test src/node.cpp src/edge.cpp src/graph.cpp src/search_algorithms.cpp src/large_graph_generator.cpp src/performance_analyzer.cpp src/large_scale_test.cpp

# Compilar suite de pruebas
g++ -std=c++11 -I./include -o build/run_tests src/node.cpp src/edge.cpp src/graph.cpp src/search_algorithms.cpp src/map_loader.cpp src/large_graph_generator.cpp src/test_suite.cpp src/run_tests.cpp
```

### Solo Consola (sin SFML)
```bash
g++ -std=c++11 -I./include -o build/console_interface src/node.cpp src/edge.cpp src/graph.cpp src/search_algorithms.cpp src/map_loader.cpp src/console_interface.cpp
```

## Uso

### Interfaz Gráfica
```bash
./build/main_visual
```
- Clic en nodos para seleccionar origen y destino
- Seleccionar algoritmo del menú
- Visualizar rutas encontradas en tiempo real

### Interfaz de Consola
```bash
./build/console_interface
```
- Menú interactivo con opciones numeradas
- Comparación automática de algoritmos
- Métricas detalladas en formato tabular

### Mapas Grandes
```bash
./build/large_scale_test
```
- Generación de grafos sintéticos
- Análisis de rendimiento en grafos masivos
- Guardado/carga de grafos en formato binario

### Suite de Pruebas
```bash
./build/run_tests
```
- Validación automática de 92 pruebas
- Reporte detallado de resultados
- Verificación de correctitud del sistema

## Algoritmos Implementados

| Algoritmo | Optimalidad | Complejidad | Uso Recomendado |
|-----------|-------------|-------------|-----------------|
| **DFS** | No | O(V+E) | Exploración completa, memoria limitada |
| **BFS** | Sí (sin pesos) | O(V+E) | Camino más corto por aristas |
| **Dijkstra** | Sí | O((V+E)logV) | Camino más corto con pesos |
| **Best First** | No | O((V+E)logV) | Búsqueda rápida, no óptima |
| **A*** | Sí | O((V+E)logV) | Óptimo con heurística |

## Resultados de Rendimiento

**Grafo de cuadrícula 100x100 (10,000 nodos):**
- BFS: 281ms, 10,000 nodos explorados
- Dijkstra: 829ms, 10,000 nodos explorados  
- A*: 424ms, 5,101 nodos explorados

## Archivos Importantes

- `documentacion_tecnica.pdf` - Documentación técnica completa
- `validation_report.txt` - Reporte de validación del sistema
- `demo_performance_report.txt` - Análisis de rendimiento
- `grid_10k.dat` / `city_5k.dat` - Grafos grandes pre-generados

## Validación

- **92 pruebas automatizadas** con **97.8% de éxito**
- Cobertura completa de estructuras de datos y algoritmos
- Pruebas de casos extremos y manejo de errores
- Validación de métricas de rendimiento

## Compatibilidad

- ✅ **Windows**: MinGW, Visual Studio
- ✅ **Linux**: GCC, Clang
- ✅ **macOS**: Clang (con SFML instalado)

## Licencia

Proyecto académico desarrollado para fines educativos. Código disponible bajo licencia MIT para uso académico y de investigación.

## Contacto

Desarrollado por **Manus AI** como proyecto final para la materia de Algoritmos y Estructura de Datos.

---

*Para documentación técnica detallada, consultar `documentacion_tecnica.pdf`*

