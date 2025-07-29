#include "../include/graph.h"
#include "../include/large_graph_generator.h"
#include "../include/performance_analyzer.h"
#include "../include/search_algorithms.h"
#include <iostream>
#include <string>

void showMenu() {
    std::cout << "\n=== Sistema de Navegación - Mapas Grandes ===" << std::endl;
    std::cout << "1. Generar grafo de cuadrícula (rápido)" << std::endl;
    std::cout << "2. Generar grafo tipo ciudad (medio)" << std::endl;
    std::cout << "3. Generar grafo aleatorio (lento)" << std::endl;
    std::cout << "4. Generar grafo de 2M nodos (muy lento)" << std::endl;
    std::cout << "5. Cargar grafo desde archivo" << std::endl;
    std::cout << "6. Probar algoritmos en grafo actual" << std::endl;
    std::cout << "7. Análisis de rendimiento completo" << std::endl;
    std::cout << "8. Guardar grafo actual" << std::endl;
    std::cout << "9. Salir" << std::endl;
    std::cout << "Seleccione una opción: ";
}

void generateGridGraph(Graph& graph) {
    int width, height;
    std::cout << "Ingrese ancho de la cuadrícula: ";
    std::cin >> width;
    std::cout << "Ingrese alto de la cuadrícula: ";
    std::cin >> height;
    
    if (width <= 0 || height <= 0 || width > 2000 || height > 2000) {
        std::cout << "Dimensiones inválidas. Usando 100x100." << std::endl;
        width = height = 100;
    }
    
    LargeGraphGenerator::generateGridGraph(graph, width, height);
}

void generateCityGraph(Graph& graph) {
    int num_nodes, num_clusters;
    std::cout << "Ingrese número de nodos (1000-100000): ";
    std::cin >> num_nodes;
    std::cout << "Ingrese número de clusters (5-50): ";
    std::cin >> num_clusters;
    
    if (num_nodes < 1000 || num_nodes > 100000) {
        std::cout << "Número de nodos inválido. Usando 10000." << std::endl;
        num_nodes = 10000;
    }
    
    if (num_clusters < 5 || num_clusters > 50) {
        std::cout << "Número de clusters inválido. Usando 10." << std::endl;
        num_clusters = 10;
    }
    
    LargeGraphGenerator::generateCityLikeGraph(graph, num_nodes, num_clusters);
}

void generateRandomGraph(Graph& graph) {
    int num_nodes;
    double probability;
    
    std::cout << "Ingrese número de nodos (100-10000): ";
    std::cin >> num_nodes;
    std::cout << "Ingrese probabilidad de conexión (0.001-0.1): ";
    std::cin >> probability;
    
    if (num_nodes < 100 || num_nodes > 10000) {
        std::cout << "Número de nodos inválido. Usando 1000." << std::endl;
        num_nodes = 1000;
    }
    
    if (probability < 0.001 || probability > 0.1) {
        std::cout << "Probabilidad inválida. Usando 0.01." << std::endl;
        probability = 0.01;
    }
    
    LargeGraphGenerator::generateRandomGraph(graph, num_nodes, probability);
}

void testAlgorithms(Graph& graph) {
    if (graph.getNodeCount() == 0) {
        std::cout << "Error: No hay grafo cargado." << std::endl;
        return;
    }
    
    std::cout << "\n=== Prueba de Algoritmos ===" << std::endl;
    std::cout << "Grafo actual: " << graph.getNodeCount() << " nodos, " 
              << graph.getEdgeCount() << " aristas" << std::endl;
    
    int start, goal;
    std::cout << "Ingrese nodo de inicio (0-" << (graph.getNodeCount()-1) << "): ";
    std::cin >> start;
    std::cout << "Ingrese nodo de destino (0-" << (graph.getNodeCount()-1) << "): ";
    std::cin >> goal;
    
    if (start < 0 || start >= graph.getNodeCount() || 
        goal < 0 || goal >= graph.getNodeCount()) {
        std::cout << "Nodos inválidos." << std::endl;
        return;
    }
    
    PerformanceAnalyzer analyzer;
    analyzer.compareAlgorithmsLargeGraph(graph, start, goal);
}

void performanceAnalysis(Graph& graph) {
    if (graph.getNodeCount() == 0) {
        std::cout << "Error: No hay grafo cargado." << std::endl;
        return;
    }
    
    std::cout << "\n=== Análisis de Rendimiento Completo ===" << std::endl;
    
    int num_tests;
    std::cout << "Ingrese número de pares de prueba (1-20): ";
    std::cin >> num_tests;
    
    if (num_tests < 1 || num_tests > 20) {
        num_tests = 5;
        std::cout << "Usando 5 pares de prueba por defecto." << std::endl;
    }
    
    PerformanceAnalyzer analyzer;
    analyzer.runComprehensiveTest(graph, num_tests);
    
    // Generar reporte
    std::string filename = "performance_report_" + std::to_string(graph.getNodeCount()) + "_nodes.txt";
    analyzer.generatePerformanceReport(filename);
}

int main() {
    std::cout << "=== Sistema de Navegación para Mapas Grandes ===" << std::endl;
    std::cout << "Proyecto Final - Algoritmos y Estructura de Datos" << std::endl;
    
    Graph graph;
    int choice;
    
    do {
        showMenu();
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                generateGridGraph(graph);
                break;
                
            case 2:
                generateCityGraph(graph);
                break;
                
            case 3:
                generateRandomGraph(graph);
                break;
                
            case 4: {
                std::cout << "ADVERTENCIA: Esto generará un grafo de 2M nodos." << std::endl;
                std::cout << "Puede tomar mucho tiempo y memoria. ¿Continuar? (s/n): ";
                char confirm;
                std::cin >> confirm;
                if (confirm == 's' || confirm == 'S') {
                    LargeGraphGenerator::generate2MillionNodeGraph(graph);
                }
                break;
            }
            
            case 5: {
                std::string filename;
                std::cout << "Ingrese nombre del archivo: ";
                std::cin >> filename;
                
                if (LargeGraphGenerator::loadGraphFromBinary(graph, filename)) {
                    std::cout << "Grafo cargado exitosamente." << std::endl;
                } else {
                    std::cout << "Error al cargar el grafo." << std::endl;
                }
                break;
            }
            
            case 6:
                testAlgorithms(graph);
                break;
                
            case 7:
                performanceAnalysis(graph);
                break;
                
            case 8: {
                if (graph.getNodeCount() == 0) {
                    std::cout << "Error: No hay grafo para guardar." << std::endl;
                } else {
                    std::string filename;
                    std::cout << "Ingrese nombre del archivo: ";
                    std::cin >> filename;
                    
                    if (LargeGraphGenerator::saveGraphToBinary(graph, filename)) {
                        std::cout << "Grafo guardado exitosamente." << std::endl;
                    } else {
                        std::cout << "Error al guardar el grafo." << std::endl;
                    }
                }
                break;
            }
            
            case 9:
                std::cout << "¡Gracias por usar el sistema!" << std::endl;
                break;
                
            default:
                std::cout << "Opción inválida. Intente nuevamente." << std::endl;
                break;
        }
        
        if (choice != 9) {
            std::cout << "\nPresione Enter para continuar...";
            std::cin.ignore();
            std::cin.get();
        }
        
    } while (choice != 9);
    
    return 0;
}

