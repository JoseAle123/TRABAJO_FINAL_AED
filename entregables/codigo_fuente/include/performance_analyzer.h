#ifndef PERFORMANCE_ANALYZER_H
#define PERFORMANCE_ANALYZER_H

#include "graph.h"
#include "search_algorithms.h"
#include <string>
#include <chrono>

struct PerformanceMetrics {
    std::string algorithm_name;
    int graph_size;
    int start_node;
    int goal_node;
    
    // Métricas de tiempo
    std::chrono::milliseconds construction_time;
    std::chrono::milliseconds search_time;
    
    // Métricas de memoria (aproximadas)
    size_t memory_used_mb;
    
    // Métricas de búsqueda
    bool path_found;
    double path_distance;
    int nodes_explored;
    int path_length;
    
    // Constructor
    PerformanceMetrics() : graph_size(0), start_node(-1), goal_node(-1),
                          construction_time(0), search_time(0), memory_used_mb(0),
                          path_found(false), path_distance(0.0), nodes_explored(0),
                          path_length(0) {}
};

class PerformanceAnalyzer {
private:
    DynamicArray<PerformanceMetrics> results;
    
public:
    // Constructor
    PerformanceAnalyzer();
    
    // Medir rendimiento de construcción de grafo
    PerformanceMetrics measureGraphConstruction(int num_nodes, const std::string& graph_type);
    
    // Medir rendimiento de algoritmo de búsqueda
    PerformanceMetrics measureSearchAlgorithm(const Graph& graph, const std::string& algorithm,
                                             int start, int goal);
    
    // Ejecutar suite completa de pruebas
    void runComprehensiveTest(const Graph& graph, int num_test_pairs = 10);
    
    // Comparar algoritmos en grafo grande
    void compareAlgorithmsLargeGraph(const Graph& graph, int start, int goal);
    
    // Generar reporte de rendimiento
    void generatePerformanceReport(const std::string& filename);
    
    // Medir uso de memoria (aproximado)
    size_t estimateMemoryUsage(const Graph& graph);
    
    // Limpiar resultados
    void clearResults();
    
    // Obtener resultados
    const DynamicArray<PerformanceMetrics>& getResults() const;
    
private:
    // Funciones auxiliares
    std::chrono::milliseconds getCurrentTime();
    void addResult(const PerformanceMetrics& metrics);
    std::string formatTime(std::chrono::milliseconds time);
    std::string formatMemory(size_t memory_mb);
};

#endif // PERFORMANCE_ANALYZER_H

