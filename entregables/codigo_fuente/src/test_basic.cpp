#include "../include/graph.h"
#include "../include/search_algorithms.h"
#include <iostream>

int main() {
    std::cout << "=== Prueba Básica del Sistema de Navegación ===" << std::endl;
    
    // Crear un grafo de prueba
    Graph graph;
    
    // Agregar nodos (simulando algunas ubicaciones en Arequipa)
    graph.addNode(Node(0, "Plaza de Armas", 0.0, 0.0));
    graph.addNode(Node(1, "Universidad Nacional", 2.0, 1.0));
    graph.addNode(Node(2, "Mercado San Camilo", 1.0, -1.0));
    graph.addNode(Node(3, "Estadio Melgar", 3.0, 2.0));
    graph.addNode(Node(4, "Terminal Terrestre", -1.0, 2.0));
    graph.addNode(Node(5, "Aeropuerto", 4.0, 0.0));
    
    // Agregar aristas (conexiones entre ubicaciones)
    graph.addEdge(0, 1, 2.2);  // Plaza -> Universidad
    graph.addEdge(0, 2, 1.4);  // Plaza -> Mercado
    graph.addEdge(0, 4, 2.2);  // Plaza -> Terminal
    graph.addEdge(1, 3, 1.4);  // Universidad -> Estadio
    graph.addEdge(1, 5, 2.0);  // Universidad -> Aeropuerto
    graph.addEdge(2, 4, 2.2);  // Mercado -> Terminal
    graph.addEdge(3, 5, 2.2);  // Estadio -> Aeropuerto
    graph.addEdge(4, 3, 3.2);  // Terminal -> Estadio
    
    // Hacer el grafo bidireccional
    graph.addEdge(1, 0, 2.2);
    graph.addEdge(2, 0, 1.4);
    graph.addEdge(4, 0, 2.2);
    graph.addEdge(3, 1, 1.4);
    graph.addEdge(5, 1, 2.0);
    graph.addEdge(4, 2, 2.2);
    graph.addEdge(5, 3, 2.2);
    graph.addEdge(3, 4, 3.2);
    
    std::cout << "\nGrafo creado exitosamente!" << std::endl;
    graph.printGraph();
    
    // Probar algoritmos de búsqueda
    SearchAlgorithms search(&graph);
    
    std::cout << "\n=== Probando búsqueda desde Plaza de Armas (0) hasta Aeropuerto (5) ===" << std::endl;
    
    // Probar cada algoritmo
    SearchResult dfs = search.depthFirstSearch(0, 5);
    std::cout << "\nDFS - Camino encontrado: " << (dfs.path_found ? "Sí" : "No") << std::endl;
    if (dfs.path_found) {
        std::cout << "Camino: ";
        for (int i = 0; i < dfs.path.getSize(); i++) {
            std::cout << dfs.path[i];
            if (i < dfs.path.getSize() - 1) std::cout << " -> ";
        }
        std::cout << std::endl;
        std::cout << "Distancia total: " << dfs.total_distance << std::endl;
        std::cout << "Nodos explorados: " << dfs.nodes_explored << std::endl;
        std::cout << "Tiempo: " << dfs.time_taken.count() << " ms" << std::endl;
    }
    
    SearchResult bfs = search.breadthFirstSearch(0, 5);
    std::cout << "\nBFS - Camino encontrado: " << (bfs.path_found ? "Sí" : "No") << std::endl;
    if (bfs.path_found) {
        std::cout << "Camino: ";
        for (int i = 0; i < bfs.path.getSize(); i++) {
            std::cout << bfs.path[i];
            if (i < bfs.path.getSize() - 1) std::cout << " -> ";
        }
        std::cout << std::endl;
        std::cout << "Distancia total: " << bfs.total_distance << std::endl;
        std::cout << "Nodos explorados: " << bfs.nodes_explored << std::endl;
        std::cout << "Tiempo: " << bfs.time_taken.count() << " ms" << std::endl;
    }
    
    SearchResult dijkstra_result = search.dijkstra(0, 5);
    std::cout << "\nDijkstra - Camino encontrado: " << (dijkstra_result.path_found ? "Sí" : "No") << std::endl;
    if (dijkstra_result.path_found) {
        std::cout << "Camino: ";
        for (int i = 0; i < dijkstra_result.path.getSize(); i++) {
            std::cout << dijkstra_result.path[i];
            if (i < dijkstra_result.path.getSize() - 1) std::cout << " -> ";
        }
        std::cout << std::endl;
        std::cout << "Distancia total: " << dijkstra_result.total_distance << std::endl;
        std::cout << "Nodos explorados: " << dijkstra_result.nodes_explored << std::endl;
        std::cout << "Tiempo: " << dijkstra_result.time_taken.count() << " ms" << std::endl;
    }
    
    SearchResult a_star = search.aStar(0, 5);
    std::cout << "\nA* - Camino encontrado: " << (a_star.path_found ? "Sí" : "No") << std::endl;
    if (a_star.path_found) {
        std::cout << "Camino: ";
        for (int i = 0; i < a_star.path.getSize(); i++) {
            std::cout << a_star.path[i];
            if (i < a_star.path.getSize() - 1) std::cout << " -> ";
        }
        std::cout << std::endl;
        std::cout << "Distancia total: " << a_star.total_distance << std::endl;
        std::cout << "Nodos explorados: " << a_star.nodes_explored << std::endl;
        std::cout << "Tiempo: " << a_star.time_taken.count() << " ms" << std::endl;
    }
    
    // Comparar todos los algoritmos
    search.compareAlgorithms(0, 5);
    
    std::cout << "\n=== Prueba completada exitosamente ===" << std::endl;
    
    return 0;
}

