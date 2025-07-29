#include "../include/map_loader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

// Cargar mapa desde archivo CSV
bool MapLoader::loadFromCSV(Graph& graph, const std::string& nodes_file, const std::string& edges_file) {
    // Limpiar el grafo existente
    graph.clear();
    
    // Cargar nodos
    std::ifstream nodes_stream(nodes_file);
    if (!nodes_stream.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo de nodos: " << nodes_file << std::endl;
        return false;
    }
    
    std::string line;
    // Saltar la primera línea si es un header
    std::getline(nodes_stream, line);
    
    while (std::getline(nodes_stream, line)) {
        std::stringstream ss(line);
        std::string item;
        
        // Formato esperado: id,name,x,y
        int id;
        std::string name;
        double x, y;
        
        if (std::getline(ss, item, ',')) {
            id = std::stoi(item);
        } else continue;
        
        if (std::getline(ss, item, ',')) {
            name = item;
        } else continue;
        
        if (std::getline(ss, item, ',')) {
            x = std::stod(item);
        } else continue;
        
        if (std::getline(ss, item, ',')) {
            y = std::stod(item);
        } else continue;
        
        graph.addNode(Node(id, name, x, y));
    }
    nodes_stream.close();
    
    // Cargar aristas
    std::ifstream edges_stream(edges_file);
    if (!edges_stream.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo de aristas: " << edges_file << std::endl;
        return false;
    }
    
    // Saltar la primera línea si es un header
    std::getline(edges_stream, line);
    
    while (std::getline(edges_stream, line)) {
        std::stringstream ss(line);
        std::string item;
        
        // Formato esperado: source,destination,weight
        int source, destination;
        double weight;
        
        if (std::getline(ss, item, ',')) {
            source = std::stoi(item);
        } else continue;
        
        if (std::getline(ss, item, ',')) {
            destination = std::stoi(item);
        } else continue;
        
        if (std::getline(ss, item, ',')) {
            weight = std::stod(item);
        } else continue;
        
        graph.addEdge(source, destination, weight);
    }
    edges_stream.close();
    
    std::cout << "Mapa cargado exitosamente: " << graph.getNodeCount() 
              << " nodos, " << graph.getEdgeCount() << " aristas" << std::endl;
    
    return true;
}

// Crear mapa de prueba de Arequipa
void MapLoader::createArequipaMap(Graph& graph) {
    graph.clear();
    
    // Agregar ubicaciones importantes de Arequipa con coordenadas aproximadas
    graph.addNode(Node(0, "Plaza de Armas", 100, 100));
    graph.addNode(Node(1, "Universidad Nacional San Agustín", 150, 80));
    graph.addNode(Node(2, "Mercado San Camilo", 80, 120));
    graph.addNode(Node(3, "Estadio Melgar", 200, 60));
    graph.addNode(Node(4, "Terminal Terrestre", 50, 50));
    graph.addNode(Node(5, "Aeropuerto Alfredo Rodríguez Ballón", 250, 100));
    graph.addNode(Node(6, "Monasterio de Santa Catalina", 90, 110));
    graph.addNode(Node(7, "Universidad Católica", 180, 90));
    graph.addNode(Node(8, "Hospital Nacional", 120, 140));
    graph.addNode(Node(9, "Cerro Colorado", 70, 180));
    graph.addNode(Node(10, "Paucarpata", 160, 150));
    graph.addNode(Node(11, "Cayma", 110, 40));
    graph.addNode(Node(12, "Yanahuara", 85, 85));
    graph.addNode(Node(13, "Sachaca", 130, 70));
    graph.addNode(Node(14, "Miraflores", 140, 130));
    
    // Agregar conexiones bidireccionales entre ubicaciones
    addBidirectionalEdge(graph, 0, 1, 2.2);   // Plaza -> UNSA
    addBidirectionalEdge(graph, 0, 2, 1.8);   // Plaza -> Mercado
    addBidirectionalEdge(graph, 0, 6, 1.0);   // Plaza -> Santa Catalina
    addBidirectionalEdge(graph, 0, 12, 1.5);  // Plaza -> Yanahuara
    addBidirectionalEdge(graph, 1, 3, 2.5);   // UNSA -> Estadio
    addBidirectionalEdge(graph, 1, 7, 1.8);   // UNSA -> Universidad Católica
    addBidirectionalEdge(graph, 1, 13, 1.2);  // UNSA -> Sachaca
    addBidirectionalEdge(graph, 2, 4, 2.0);   // Mercado -> Terminal
    addBidirectionalEdge(graph, 2, 8, 2.2);   // Mercado -> Hospital
    addBidirectionalEdge(graph, 3, 5, 2.8);   // Estadio -> Aeropuerto
    addBidirectionalEdge(graph, 3, 7, 1.5);   // Estadio -> Universidad Católica
    addBidirectionalEdge(graph, 4, 9, 3.5);   // Terminal -> Cerro Colorado
    addBidirectionalEdge(graph, 4, 11, 2.0);  // Terminal -> Cayma
    addBidirectionalEdge(graph, 5, 7, 3.0);   // Aeropuerto -> Universidad Católica
    addBidirectionalEdge(graph, 5, 10, 2.5);  // Aeropuerto -> Paucarpata
    addBidirectionalEdge(graph, 6, 12, 0.8);  // Santa Catalina -> Yanahuara
    addBidirectionalEdge(graph, 7, 10, 2.0);  // Universidad Católica -> Paucarpata
    addBidirectionalEdge(graph, 8, 9, 2.8);   // Hospital -> Cerro Colorado
    addBidirectionalEdge(graph, 8, 10, 1.8);  // Hospital -> Paucarpata
    addBidirectionalEdge(graph, 8, 14, 1.2);  // Hospital -> Miraflores
    addBidirectionalEdge(graph, 9, 10, 3.0);  // Cerro Colorado -> Paucarpata
    addBidirectionalEdge(graph, 10, 14, 1.5); // Paucarpata -> Miraflores
    addBidirectionalEdge(graph, 11, 12, 1.8); // Cayma -> Yanahuara
    addBidirectionalEdge(graph, 11, 13, 2.2); // Cayma -> Sachaca
    addBidirectionalEdge(graph, 12, 13, 1.5); // Yanahuara -> Sachaca
    addBidirectionalEdge(graph, 13, 14, 2.0); // Sachaca -> Miraflores
    
    std::cout << "Mapa de Arequipa creado: " << graph.getNodeCount() 
              << " nodos, " << graph.getEdgeCount() << " aristas" << std::endl;
}

// Generar mapa sintético para pruebas
void MapLoader::generateSyntheticMap(Graph& graph, int num_nodes, double width, double height) {
    graph.clear();
    std::srand(std::time(nullptr));
    
    // Generar nodos con posiciones aleatorias
    for (int i = 0; i < num_nodes; i++) {
        double x = (double(std::rand()) / RAND_MAX) * width;
        double y = (double(std::rand()) / RAND_MAX) * height;
        
        std::string name = "Nodo_" + std::to_string(i);
        graph.addNode(Node(i, name, x, y));
    }
    
    // Conectar cada nodo con sus vecinos más cercanos
    const DynamicArray<Node>& nodes = graph.getAllNodes();
    
    for (int i = 0; i < nodes.getSize(); i++) {
        // Encontrar los 3-5 vecinos más cercanos
        int max_connections = 3 + (std::rand() % 3); // 3-5 conexiones
        
        DynamicArray<std::pair<double, int>> distances;
        
        for (int j = 0; j < nodes.getSize(); j++) {
            if (i != j) {
                double dist = calculateDistance(nodes[i].getX(), nodes[i].getY(),
                                              nodes[j].getX(), nodes[j].getY());
                distances.push_back(std::make_pair(dist, j));
            }
        }
        
        // Ordenar por distancia (bubble sort simple)
        for (int k = 0; k < distances.getSize() - 1; k++) {
            for (int l = 0; l < distances.getSize() - k - 1; l++) {
                if (distances[l].first > distances[l + 1].first) {
                    auto temp = distances[l];
                    distances[l] = distances[l + 1];
                    distances[l + 1] = temp;
                }
            }
        }
        
        // Conectar con los vecinos más cercanos
        int connections = std::min(max_connections, distances.getSize());
        for (int k = 0; k < connections; k++) {
            int neighbor = distances[k].second;
            double weight = distances[k].first;
            
            // Solo agregar si no existe ya la conexión
            if (!graph.hasEdge(i, neighbor)) {
                addBidirectionalEdge(graph, i, neighbor, weight);
            }
        }
    }
    
    std::cout << "Mapa sintético generado: " << graph.getNodeCount() 
              << " nodos, " << graph.getEdgeCount() << " aristas" << std::endl;
}

// Funciones auxiliares
double MapLoader::calculateDistance(double x1, double y1, double x2, double y2) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    return std::sqrt(dx * dx + dy * dy);
}

void MapLoader::addBidirectionalEdge(Graph& graph, int node1, int node2, double weight) {
    graph.addEdge(node1, node2, weight);
    graph.addEdge(node2, node1, weight);
}

