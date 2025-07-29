#ifndef TEST_SUITE_H
#define TEST_SUITE_H

#include "graph.h"
#include "search_algorithms.h"
#include "large_graph_generator.h"
#include <string>

class TestSuite {
private:
    int tests_passed;
    int tests_failed;
    int total_tests;
    
    // Funciones auxiliares para testing
    void assert_true(bool condition, const std::string& test_name);
    void assert_false(bool condition, const std::string& test_name);
    void assert_equals(int expected, int actual, const std::string& test_name);
    void assert_equals(double expected, double actual, const std::string& test_name, double tolerance = 0.001);
    void print_test_result(const std::string& test_name, bool passed);
    
public:
    // Constructor
    TestSuite();
    
    // Métodos principales de testing
    void runAllTests();
    
    // Tests de estructuras de datos básicas
    void testDynamicArray();
    void testLinkedList();
    void testQueue();
    void testPriorityQueue();
    
    // Tests de grafo
    void testGraphBasicOperations();
    void testGraphConnectivity();
    void testGraphEdgeWeights();
    
    // Tests de algoritmos de búsqueda
    void testSearchAlgorithmsSmallGraph();
    void testSearchAlgorithmsDisconnectedGraph();
    void testSearchAlgorithmsOptimality();
    void testSearchAlgorithmsPerformance();
    
    // Tests de generación de grafos grandes
    void testLargeGraphGeneration();
    void testGraphSaveLoad();
    
    // Tests de casos extremos
    void testEdgeCases();
    void testMemoryManagement();
    
    // Tests de validación de datos
    void testDataValidation();
    
    // Mostrar resumen de resultados
    void printSummary();
    
    // Obtener estadísticas
    int getTestsPassed() const;
    int getTestsFailed() const;
    int getTotalTests() const;
    double getSuccessRate() const;
};

#endif // TEST_SUITE_H

