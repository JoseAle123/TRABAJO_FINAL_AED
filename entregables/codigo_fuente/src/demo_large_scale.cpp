#include "../include/graph.h"
#include "../include/large_graph_generator.h"
#include "../include/performance_analyzer.h"
#include "../include/search_algorithms.h"
#include <iostream>

int main() {
    std::cout << "=== Demostración de Mapas Grandes ===" << std::endl;
    
    // Prueba 1: Grafo de cuadrícula mediano
    std::cout << "\n1. Generando grafo de cuadrícula 100x100 (10,000 nodos)..." << std::endl;
    Graph grid_graph;
    LargeGraphGenerator::generateGridGraph(grid_graph, 100, 100);
    
    std::cout << "Grafo generado: " << grid_graph.getNodeCount() 
              << " nodos, " << grid_graph.getEdgeCount() << " aristas" << std::endl;
    
    // Probar algoritmos en el grafo de cuadrícula
    std::cout << "\n2. Probando algoritmos de búsqueda..." << std::endl;
    SearchAlgorithms search(&grid_graph);
    
    int start = 0;        // Esquina superior izquierda
    int goal = 9999;      // Esquina inferior derecha
    
    std::cout << "Búsqueda desde nodo " << start << " hasta nodo " << goal << std::endl;
    
    // Probar BFS (más eficiente para grafos grandes)
    SearchResult bfs_result = search.breadthFirstSearch(start, goal);
    std::cout << "BFS: ";
    if (bfs_result.path_found) {
        std::cout << "Camino encontrado, distancia=" << bfs_result.total_distance 
                  << ", nodos explorados=" << bfs_result.nodes_explored 
                  << ", tiempo=" << bfs_result.time_taken.count() << "ms" << std::endl;
    } else {
        std::cout << "Sin camino" << std::endl;
    }
    
    // Probar Dijkstra
    SearchResult dijkstra_result = search.dijkstra(start, goal);
    std::cout << "Dijkstra: ";
    if (dijkstra_result.path_found) {
        std::cout << "Camino encontrado, distancia=" << dijkstra_result.total_distance 
                  << ", nodos explorados=" << dijkstra_result.nodes_explored 
                  << ", tiempo=" << dijkstra_result.time_taken.count() << "ms" << std::endl;
    } else {
        std::cout << "Sin camino" << std::endl;
    }
    
    // Probar A*
    SearchResult astar_result = search.aStar(start, goal);
    std::cout << "A*: ";
    if (astar_result.path_found) {
        std::cout << "Camino encontrado, distancia=" << astar_result.total_distance 
                  << ", nodos explorados=" << astar_result.nodes_explored 
                  << ", tiempo=" << astar_result.time_taken.count() << "ms" << std::endl;
    } else {
        std::cout << "Sin camino" << std::endl;
    }
    
    // Prueba 2: Grafo tipo ciudad
    std::cout << "\n3. Generando grafo tipo ciudad (5,000 nodos)..." << std::endl;
    Graph city_graph;
    LargeGraphGenerator::generateCityLikeGraph(city_graph, 5000, 10);
    
    std::cout << "Grafo tipo ciudad generado: " << city_graph.getNodeCount() 
              << " nodos, " << city_graph.getEdgeCount() << " aristas" << std::endl;
    
    // Análisis de rendimiento
    std::cout << "\n4. Análisis de rendimiento..." << std::endl;
    PerformanceAnalyzer analyzer;
    
    // Comparar algoritmos en el grafo de ciudad
    analyzer.compareAlgorithmsLargeGraph(city_graph, 0, 2500);
    
    // Guardar grafo para pruebas futuras
    std::cout << "\n5. Guardando grafos para uso futuro..." << std::endl;
    LargeGraphGenerator::saveGraphToBinary(grid_graph, "grid_10k.dat");
    LargeGraphGenerator::saveGraphToBinary(city_graph, "city_5k.dat");
    
    // Generar reporte
    analyzer.generatePerformanceReport("demo_performance_report.txt");
    
    std::cout << "\n=== Demostración completada ===" << std::endl;
    std::cout << "Archivos generados:" << std::endl;
    std::cout << "- grid_10k.dat: Grafo de cuadrícula de 10,000 nodos" << std::endl;
    std::cout << "- city_5k.dat: Grafo tipo ciudad de 5,000 nodos" << std::endl;
    std::cout << "- demo_performance_report.txt: Reporte de rendimiento" << std::endl;
    
    return 0;
}

