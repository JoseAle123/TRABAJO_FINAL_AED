#include "../include/performance_analyzer.h"
#include "../include/large_graph_generator.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <cmath>

// Constructor
PerformanceAnalyzer::PerformanceAnalyzer() {}

// Medir rendimiento de construcción de grafo
PerformanceMetrics PerformanceAnalyzer::measureGraphConstruction(int num_nodes, const std::string& graph_type) {
    PerformanceMetrics metrics;
    metrics.algorithm_name = "Graph Construction (" + graph_type + ")";
    metrics.graph_size = num_nodes;
    
    auto start_time = std::chrono::high_resolution_clock::now();
    
    Graph test_graph;
    
    if (graph_type == "grid") {
        int side = static_cast<int>(std::sqrt(num_nodes));
        LargeGraphGenerator::generateGridGraph(test_graph, side, side);
    } else if (graph_type == "random") {
        LargeGraphGenerator::generateRandomGraph(test_graph, num_nodes, 0.01);
    } else if (graph_type == "city") {
        LargeGraphGenerator::generateCityLikeGraph(test_graph, num_nodes, 10);
    }
    
    auto end_time = std::chrono::high_resolution_clock::now();
    metrics.construction_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    metrics.memory_used_mb = estimateMemoryUsage(test_graph);
    
    std::cout << "Construcción de grafo " << graph_type << " (" << num_nodes << " nodos): " 
              << metrics.construction_time.count() << " ms, " 
              << metrics.memory_used_mb << " MB" << std::endl;
    
    return metrics;
}

// Medir rendimiento de algoritmo de búsqueda
PerformanceMetrics PerformanceAnalyzer::measureSearchAlgorithm(const Graph& graph, const std::string& algorithm,
                                                               int start, int goal) {
    PerformanceMetrics metrics;
    metrics.algorithm_name = algorithm;
    metrics.graph_size = graph.getNodeCount();
    metrics.start_node = start;
    metrics.goal_node = goal;
    
    SearchAlgorithms search(&graph);
    SearchResult result;
    
    auto start_time = std::chrono::high_resolution_clock::now();
    
    if (algorithm == "DFS") {
        result = search.depthFirstSearch(start, goal);
    } else if (algorithm == "BFS") {
        result = search.breadthFirstSearch(start, goal);
    } else if (algorithm == "Dijkstra") {
        result = search.dijkstra(start, goal);
    } else if (algorithm == "Best First") {
        result = search.bestFirstSearch(start, goal);
    } else if (algorithm == "A*") {
        result = search.aStar(start, goal);
    }
    
    auto end_time = std::chrono::high_resolution_clock::now();
    metrics.search_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    
    // Copiar resultados
    metrics.path_found = result.path_found;
    metrics.path_distance = result.total_distance;
    metrics.nodes_explored = result.nodes_explored;
    metrics.path_length = result.path.getSize();
    
    // Estimar uso de memoria durante la búsqueda
    metrics.memory_used_mb = estimateMemoryUsage(graph) + (metrics.nodes_explored * sizeof(int)) / (1024 * 1024);
    
    return metrics;
}

// Ejecutar suite completa de pruebas
void PerformanceAnalyzer::runComprehensiveTest(const Graph& graph, int num_test_pairs) {
    std::cout << "\n=== Suite Completa de Pruebas de Rendimiento ===" << std::endl;
    std::cout << "Grafo: " << graph.getNodeCount() << " nodos, " << graph.getEdgeCount() << " aristas" << std::endl;
    std::cout << "Pares de prueba: " << num_test_pairs << std::endl;
    
    std::srand(std::time(nullptr));
    DynamicArray<std::string> algorithms;
    algorithms.push_back("DFS");
    algorithms.push_back("BFS");
    algorithms.push_back("Dijkstra");
    algorithms.push_back("Best First");
    algorithms.push_back("A*");
    
    // Generar pares de nodos aleatorios para prueba
    for (int pair = 0; pair < num_test_pairs; pair++) {
        int start = std::rand() % graph.getNodeCount();
        int goal = std::rand() % graph.getNodeCount();
        
        if (start == goal) continue;
        
        std::cout << "\nPar de prueba " << (pair + 1) << ": " << start << " -> " << goal << std::endl;
        
        // Probar cada algoritmo
        for (int alg = 0; alg < algorithms.getSize(); alg++) {
            PerformanceMetrics metrics = measureSearchAlgorithm(graph, algorithms[alg], start, goal);
            addResult(metrics);
            
            std::cout << algorithms[alg] << ": ";
            if (metrics.path_found) {
                std::cout << "Camino encontrado, distancia=" << metrics.path_distance 
                         << ", nodos=" << metrics.nodes_explored 
                         << ", tiempo=" << metrics.search_time.count() << "ms";
            } else {
                std::cout << "Sin camino, nodos=" << metrics.nodes_explored 
                         << ", tiempo=" << metrics.search_time.count() << "ms";
            }
            std::cout << std::endl;
        }
    }
}

// Comparar algoritmos en grafo grande
void PerformanceAnalyzer::compareAlgorithmsLargeGraph(const Graph& graph, int start, int goal) {
    std::cout << "\n=== Comparación de Algoritmos en Grafo Grande ===" << std::endl;
    std::cout << "Grafo: " << graph.getNodeCount() << " nodos" << std::endl;
    std::cout << "Búsqueda: " << start << " -> " << goal << std::endl;
    
    DynamicArray<std::string> algorithms;
    algorithms.push_back("BFS");      // Más eficiente para grafos grandes
    algorithms.push_back("Dijkstra"); // Óptimo para caminos más cortos
    algorithms.push_back("A*");       // Más eficiente con heurística
    
    std::cout << "\nAlgoritmo\t\tTiempo(ms)\tNodos\t\tDistancia\tMemoria(MB)" << std::endl;
    std::cout << "------------------------------------------------------------------------" << std::endl;
    
    for (int i = 0; i < algorithms.getSize(); i++) {
        PerformanceMetrics metrics = measureSearchAlgorithm(graph, algorithms[i], start, goal);
        addResult(metrics);
        
        std::cout << algorithms[i] << "\t\t\t" << metrics.search_time.count() 
                  << "\t\t" << metrics.nodes_explored 
                  << "\t\t" << (metrics.path_found ? std::to_string(metrics.path_distance) : "N/A")
                  << "\t\t" << metrics.memory_used_mb << std::endl;
    }
}

// Generar reporte de rendimiento
void PerformanceAnalyzer::generatePerformanceReport(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo crear el archivo de reporte " << filename << std::endl;
        return;
    }
    
    file << "=== REPORTE DE RENDIMIENTO ===" << std::endl;
    file << "Generado: " << std::time(nullptr) << std::endl;
    file << "Total de pruebas: " << results.getSize() << std::endl;
    file << std::endl;
    
    file << "Algoritmo\t\tGrafo\tInicio\tDestino\tTiempo(ms)\tNodos\tDistancia\tMemoria(MB)\tCamino" << std::endl;
    file << "----------------------------------------------------------------------------------------" << std::endl;
    
    for (int i = 0; i < results.getSize(); i++) {
        const PerformanceMetrics& metrics = results[i];
        
        file << metrics.algorithm_name << "\t\t" 
             << metrics.graph_size << "\t"
             << metrics.start_node << "\t"
             << metrics.goal_node << "\t"
             << metrics.search_time.count() << "\t\t"
             << metrics.nodes_explored << "\t"
             << (metrics.path_found ? std::to_string(metrics.path_distance) : "N/A") << "\t\t"
             << metrics.memory_used_mb << "\t\t"
             << (metrics.path_found ? "Sí" : "No") << std::endl;
    }
    
    // Estadísticas resumidas
    file << std::endl << "=== ESTADÍSTICAS RESUMIDAS ===" << std::endl;
    
    DynamicArray<std::string> unique_algorithms;
    for (int i = 0; i < results.getSize(); i++) {
        bool found = false;
        for (int j = 0; j < unique_algorithms.getSize(); j++) {
            if (unique_algorithms[j] == results[i].algorithm_name) {
                found = true;
                break;
            }
        }
        if (!found) {
            unique_algorithms.push_back(results[i].algorithm_name);
        }
    }
    
    for (int alg = 0; alg < unique_algorithms.getSize(); alg++) {
        const std::string& algorithm = unique_algorithms[alg];
        
        long total_time = 0;
        int total_nodes = 0;
        int successful_searches = 0;
        int total_searches = 0;
        
        for (int i = 0; i < results.getSize(); i++) {
            if (results[i].algorithm_name == algorithm) {
                total_time += results[i].search_time.count();
                total_nodes += results[i].nodes_explored;
                if (results[i].path_found) successful_searches++;
                total_searches++;
            }
        }
        
        if (total_searches > 0) {
            file << algorithm << ":" << std::endl;
            file << "  Búsquedas totales: " << total_searches << std::endl;
            file << "  Búsquedas exitosas: " << successful_searches << " (" 
                 << (100.0 * successful_searches / total_searches) << "%)" << std::endl;
            file << "  Tiempo promedio: " << (total_time / total_searches) << " ms" << std::endl;
            file << "  Nodos promedio explorados: " << (total_nodes / total_searches) << std::endl;
            file << std::endl;
        }
    }
    
    file.close();
    std::cout << "Reporte de rendimiento guardado en: " << filename << std::endl;
}

// Medir uso de memoria (aproximado)
size_t PerformanceAnalyzer::estimateMemoryUsage(const Graph& graph) {
    size_t memory = 0;
    
    // Memoria de nodos
    memory += graph.getNodeCount() * sizeof(Node);
    
    // Memoria de aristas (aproximada)
    memory += graph.getEdgeCount() * sizeof(Edge);
    
    // Memoria de listas de adyacencia (aproximada)
    memory += graph.getNodeCount() * sizeof(LinkedList<Edge>);
    
    // Convertir a MB
    return memory / (1024 * 1024);
}

// Limpiar resultados
void PerformanceAnalyzer::clearResults() {
    results.clear();
}

// Obtener resultados
const DynamicArray<PerformanceMetrics>& PerformanceAnalyzer::getResults() const {
    return results;
}

// Funciones auxiliares
std::chrono::milliseconds PerformanceAnalyzer::getCurrentTime() {
    auto now = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
}

void PerformanceAnalyzer::addResult(const PerformanceMetrics& metrics) {
    results.push_back(metrics);
}

std::string PerformanceAnalyzer::formatTime(std::chrono::milliseconds time) {
    return std::to_string(time.count()) + " ms";
}

std::string PerformanceAnalyzer::formatMemory(size_t memory_mb) {
    return std::to_string(memory_mb) + " MB";
}

