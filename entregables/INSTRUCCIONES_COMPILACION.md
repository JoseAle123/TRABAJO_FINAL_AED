# Instrucciones de Compilación - Sistema de Navegación

## Requisitos del Sistema

### Software Necesario
- **Compilador C++11 o superior**:
  - Windows: MinGW-w64, Visual Studio 2013+, o Clang
  - Linux: GCC 4.8+, Clang 3.3+
  - macOS: Xcode Command Line Tools

- **SFML 2.4+ (opcional, solo para interfaz gráfica)**:
  - Windows: Descargar desde https://www.sfml-dev.org/download.php
  - Linux: `sudo apt-get install libsfml-dev` (Ubuntu/Debian)
  - macOS: `brew install sfml`

### Hardware Recomendado
- **RAM**: Mínimo 4GB, recomendado 8GB para grafos grandes
- **Espacio en disco**: 100MB para código fuente y ejecutables
- **Procesador**: Cualquier CPU moderna (x86/x64)

## Compilación en Windows

### Opción 1: MinGW-w64
```cmd
# Navegar al directorio del proyecto
cd final_project

# Compilar interfaz de consola (sin SFML)
g++ -std=c++11 -I./include -o console_interface.exe src/node.cpp src/edge.cpp src/graph.cpp src/search_algorithms.cpp src/map_loader.cpp src/console_interface.cpp

# Compilar con SFML (interfaz gráfica)
g++ -std=c++11 -I./include -I/path/to/sfml/include -L/path/to/sfml/lib -o main_visual.exe src/node.cpp src/edge.cpp src/graph.cpp src/search_algorithms.cpp src/map_loader.cpp src/visualizer.cpp src/main_visual.cpp -lsfml-graphics -lsfml-window -lsfml-system

# Compilar sistema de mapas grandes
g++ -std=c++11 -I./include -o large_scale_test.exe src/node.cpp src/edge.cpp src/graph.cpp src/search_algorithms.cpp src/large_graph_generator.cpp src/performance_analyzer.cpp src/large_scale_test.cpp

# Compilar suite de pruebas
g++ -std=c++11 -I./include -o run_tests.exe src/node.cpp src/edge.cpp src/graph.cpp src/search_algorithms.cpp src/map_loader.cpp src/large_graph_generator.cpp src/test_suite.cpp src/run_tests.cpp
```

### Opción 2: Visual Studio
1. Crear nuevo proyecto de consola C++
2. Agregar todos los archivos .cpp y .h al proyecto
3. Configurar propiedades del proyecto:
   - C/C++ > General > Directorios de inclusión adicionales: `./include`
   - C/C++ > Lenguaje > Estándar del lenguaje C++: `C++11`
   - Para SFML: Agregar directorios de SFML en Vinculador > General
4. Compilar y ejecutar

## Compilación en Linux

```bash
# Instalar dependencias (Ubuntu/Debian)
sudo apt-get update
sudo apt-get install build-essential libsfml-dev

# Navegar al directorio del proyecto
cd final_project

# Compilar interfaz de consola
g++ -std=c++11 -I./include -o console_interface src/node.cpp src/edge.cpp src/graph.cpp src/search_algorithms.cpp src/map_loader.cpp src/console_interface.cpp

# Compilar con SFML
g++ -std=c++11 -I./include -o main_visual src/node.cpp src/edge.cpp src/graph.cpp src/search_algorithms.cpp src/map_loader.cpp src/visualizer.cpp src/main_visual.cpp -lsfml-graphics -lsfml-window -lsfml-system

# Compilar sistema de mapas grandes
g++ -std=c++11 -I./include -o large_scale_test src/node.cpp src/edge.cpp src/graph.cpp src/search_algorithms.cpp src/large_graph_generator.cpp src/performance_analyzer.cpp src/large_scale_test.cpp

# Compilar suite de pruebas
g++ -std=c++11 -I./include -o run_tests src/node.cpp src/edge.cpp src/graph.cpp src/search_algorithms.cpp src/map_loader.cpp src/large_graph_generator.cpp src/test_suite.cpp src/run_tests.cpp
```

## Compilación en macOS

```bash
# Instalar Xcode Command Line Tools
xcode-select --install

# Instalar SFML (opcional)
brew install sfml

# Compilar (similar a Linux)
g++ -std=c++11 -I./include -o console_interface src/node.cpp src/edge.cpp src/graph.cpp src/search_algorithms.cpp src/map_loader.cpp src/console_interface.cpp
```

## Verificación de Compilación

### Ejecutar Suite de Pruebas
```bash
# Linux/macOS
./run_tests

# Windows
run_tests.exe
```

**Resultado esperado**: 90+ pruebas exitosas (97.8% de éxito)

### Ejecutar Demostración
```bash
# Interfaz de consola
./console_interface

# Interfaz gráfica (si SFML está disponible)
./main_visual

# Sistema de mapas grandes
./large_scale_test
```

## Solución de Problemas

### Error: "SFML not found"
- **Solución**: Compilar únicamente la versión de consola sin SFML
- **Comando**: Usar únicamente `console_interface` y `large_scale_test`

### Error: "C++11 not supported"
- **Solución**: Actualizar compilador o usar flag `-std=c++0x`
- **MinGW**: Descargar versión más reciente
- **Visual Studio**: Usar VS 2013 o superior

### Error de memoria en grafos grandes
- **Solución**: Reducir tamaño de grafos generados
- **Recomendación**: Comenzar con grafos de 1,000 nodos

### Error de permisos en Linux
- **Solución**: Usar `chmod +x` para dar permisos de ejecución
```bash
chmod +x console_interface main_visual large_scale_test run_tests
```

## Archivos Generados

Después de la compilación exitosa, se generarán los siguientes ejecutables:

- `console_interface` - Interfaz de consola principal
- `main_visual` - Interfaz gráfica (requiere SFML)
- `large_scale_test` - Sistema de mapas grandes
- `run_tests` - Suite de pruebas automatizadas

## Notas Adicionales

- **Sin SFML**: El sistema funciona completamente con solo la interfaz de consola
- **Memoria**: Para grafos de 100K+ nodos, se requieren varios GB de RAM
- **Rendimiento**: Los tiempos de compilación pueden variar según el hardware
- **Compatibilidad**: Probado en Windows 10, Ubuntu 20.04, y macOS Big Sur

Para soporte adicional, consultar la documentación técnica completa en `documentacion_tecnica.pdf`.

