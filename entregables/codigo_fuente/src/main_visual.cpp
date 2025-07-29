#include "../include/graph.h"
#include "../include/map_loader.h"
#include "../include/visualizer.h"
#include <iostream>

int main() {
    std::cout << "=== Sistema de Navegación con Visualización ===" << std::endl;
    std::cout << "Cargando mapa de Arequipa..." << std::endl;
    
    // Crear y cargar el grafo
    Graph graph;
    MapLoader::createArequipaMap(graph);
    
    std::cout << "Mapa cargado exitosamente!" << std::endl;
    std::cout << "Nodos: " << graph.getNodeCount() << std::endl;
    std::cout << "Aristas: " << graph.getEdgeCount() << std::endl;
    
    // Mostrar lista de ubicaciones
    std::cout << "\nUbicaciones disponibles:" << std::endl;
    const DynamicArray<Node>& nodes = graph.getAllNodes();
    for (int i = 0; i < nodes.getSize(); i++) {
        const Node& node = nodes[i];
        std::cout << "ID " << node.getId() << ": " << node.getName() << std::endl;
    }
    
    std::cout << "\nIniciando visualizador..." << std::endl;
    
    // Crear y ejecutar el visualizador
    Visualizer visualizer(&graph);
    visualizer.run();
    
    std::cout << "Visualizador cerrado. ¡Gracias por usar el sistema!" << std::endl;
    
    return 0;
}

