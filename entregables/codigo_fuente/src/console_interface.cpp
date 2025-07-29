#include "../include/graph.h"
#include "../include/map_loader.h"
#include "../include/search_algorithms.h"
#include <iostream>
#include <string>

void showMenu() {
    std::cout << "\n=== Sistema de Navegación - Arequipa ===" << std::endl;
    std::cout << "1. Mostrar ubicaciones disponibles" << std::endl;
    std::cout << "2. Buscar ruta entre dos ubicaciones" << std::endl;
    std::cout << "3. Comparar todos los algoritmos" << std::endl;
    std::cout << "4. Generar mapa sintético y probar" << std::endl;
    std::cout << "5. Salir" << std::endl;
    std::cout << "Seleccione una opción: ";
}

void showLocations(const Graph& graph) {
    std::cout << "\n=== Ubicaciones Disponibles ===" << std::endl;
    const DynamicArray<Node>& nodes = graph.getAllNodes();
    for (int i = 0; i < nodes.getSize(); i++) {
        const Node& node = nodes[i];
        std::cout << "ID " << node.getId() << ": " << node.getName() 
                  << " (x=" << node.getX() << ", y=" << node.getY() << ")" << std::endl;
    }
}

void searchRoute(const Graph& graph) {
    SearchAlgorithms search(&graph);
    
    std::cout << "\n=== Búsqueda de Ruta ===" << std::endl;
    
    int start_id, goal_id;
    std::cout << "Ingrese ID del nodo de inicio: ";
    std::cin >> start_id;
    std::cout << "Ingrese ID del nodo de destino: ";
    std::cin >> goal_id;
    
    if (!graph.hasNode(start_id) || !graph.hasNode(goal_id)) {
        std::cout << "Error: Uno o ambos nodos no existen." << std::endl;
        return;
    }
    
    const Node* start_node = graph.getNode(start_id);
    const Node* goal_node = graph.getNode(goal_id);
    
    std::cout << "\nBuscando ruta desde '" << start_node->getName() 
              << "' hasta '" << goal_node->getName() << "'" << std::endl;
    
    std::cout << "\nSeleccione algoritmo:" << std::endl;
    std::cout << "1. Depth First Search (DFS)" << std::endl;
    std::cout << "2. Breadth First Search (BFS)" << std::endl;
    std::cout << "3. Dijkstra" << std::endl;
    std::cout << "4. Best First Search" << std::endl;
    std::cout << "5. A*" << std::endl;
    std::cout << "6. Comparar todos" << std::endl;
    
    int algorithm_choice;
    std::cout << "Opción: ";
    std::cin >> algorithm_choice;
    
    SearchResult result;
    std::string algorithm_name;
    
    switch (algorithm_choice) {
        case 1:
            result = search.depthFirstSearch(start_id, goal_id);
            algorithm_name = "DFS";
            break;
        case 2:
            result = search.breadthFirstSearch(start_id, goal_id);
            algorithm_name = "BFS";
            break;
        case 3:
            result = search.dijkstra(start_id, goal_id);
            algorithm_name = "Dijkstra";
            break;
        case 4:
            result = search.bestFirstSearch(start_id, goal_id);
            algorithm_name = "Best First Search";
            break;
        case 5:
            result = search.aStar(start_id, goal_id);
            algorithm_name = "A*";
            break;
        case 6:
            search.compareAlgorithms(start_id, goal_id);
            return;
        default:
            std::cout << "Opción inválida." << std::endl;
            return;
    }
    
    std::cout << "\n=== Resultado de " << algorithm_name << " ===" << std::endl;
    
    if (result.path_found) {
        std::cout << "¡Camino encontrado!" << std::endl;
        std::cout << "Ruta: ";
        for (int i = 0; i < result.path.getSize(); i++) {
            const Node* node = graph.getNode(result.path[i]);
            if (node) {
                std::cout << node->getName();
                if (i < result.path.getSize() - 1) {
                    std::cout << " -> ";
                }
            }
        }
        std::cout << std::endl;
        std::cout << "Distancia total: " << result.total_distance << " unidades" << std::endl;
        std::cout << "Nodos explorados: " << result.nodes_explored << std::endl;
        std::cout << "Tiempo de ejecución: " << result.time_taken.count() << " ms" << std::endl;
    } else {
        std::cout << "No se encontró un camino entre los nodos especificados." << std::endl;
    }
}

void testSyntheticMap() {
    std::cout << "\n=== Prueba con Mapa Sintético ===" << std::endl;
    
    int num_nodes;
    std::cout << "Ingrese número de nodos a generar (10-100): ";
    std::cin >> num_nodes;
    
    if (num_nodes < 10 || num_nodes > 100) {
        std::cout << "Número de nodos debe estar entre 10 y 100." << std::endl;
        return;
    }
    
    Graph synthetic_graph;
    MapLoader::generateSyntheticMap(synthetic_graph, num_nodes, 500.0, 500.0);
    
    std::cout << "Mapa sintético generado con " << synthetic_graph.getNodeCount() 
              << " nodos y " << synthetic_graph.getEdgeCount() << " aristas." << std::endl;
    
    // Probar con nodos aleatorios
    int start = 0;
    int goal = num_nodes / 2;
    
    std::cout << "\nProbando búsqueda desde nodo " << start << " hasta nodo " << goal << std::endl;
    
    SearchAlgorithms search(&synthetic_graph);
    search.compareAlgorithms(start, goal);
}

int main() {
    std::cout << "=== Sistema de Navegación Basado en Grafos ===" << std::endl;
    std::cout << "Proyecto Final - Algoritmos y Estructura de Datos" << std::endl;
    std::cout << "Cargando mapa de Arequipa..." << std::endl;
    
    // Crear y cargar el grafo principal
    Graph graph;
    MapLoader::createArequipaMap(graph);
    
    std::cout << "Mapa cargado exitosamente!" << std::endl;
    std::cout << "Nodos: " << graph.getNodeCount() << std::endl;
    std::cout << "Aristas: " << graph.getEdgeCount() << std::endl;
    
    int choice;
    do {
        showMenu();
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                showLocations(graph);
                break;
            case 2:
                searchRoute(graph);
                break;
            case 3: {
                std::cout << "\nIngrese ID del nodo de inicio: ";
                int start, goal;
                std::cin >> start;
                std::cout << "Ingrese ID del nodo de destino: ";
                std::cin >> goal;
                
                if (graph.hasNode(start) && graph.hasNode(goal)) {
                    SearchAlgorithms search(&graph);
                    search.compareAlgorithms(start, goal);
                } else {
                    std::cout << "Error: Uno o ambos nodos no existen." << std::endl;
                }
                break;
            }
            case 4:
                testSyntheticMap();
                break;
            case 5:
                std::cout << "¡Gracias por usar el sistema!" << std::endl;
                break;
            default:
                std::cout << "Opción inválida. Intente nuevamente." << std::endl;
                break;
        }
        
        if (choice != 5) {
            std::cout << "\nPresione Enter para continuar...";
            std::cin.ignore();
            std::cin.get();
        }
        
    } while (choice != 5);
    
    return 0;
}

