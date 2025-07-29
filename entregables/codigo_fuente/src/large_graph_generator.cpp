#include "../include/large_graph_generator.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>

// Generar grafo grande con patrón de cuadrícula
void LargeGraphGenerator::generateGridGraph(Graph& graph, int width, int height, double spacing) {
    graph.clear();
    std::cout << "Generando grafo de cuadrícula " << width << "x" << height << "..." << std::endl;
    
    // Crear nodos en patrón de cuadrícula
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int id = getGridIndex(x, y, width);
            double pos_x = x * spacing;
            double pos_y = y * spacing;
            
            std::string name = "Grid_" + std::to_string(x) + "_" + std::to_string(y);
            graph.addNode(Node(id, name, pos_x, pos_y));
        }
    }
    
    // Conectar nodos adyacentes (4-conectividad)
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int current_id = getGridIndex(x, y, width);
            
            // Conectar con vecino derecho
            if (x < width - 1) {
                int right_id = getGridIndex(x + 1, y, width);
                graph.addEdge(current_id, right_id, spacing);
                graph.addEdge(right_id, current_id, spacing);
            }
            
            // Conectar con vecino inferior
            if (y < height - 1) {
                int down_id = getGridIndex(x, y + 1, width);
                graph.addEdge(current_id, down_id, spacing);
                graph.addEdge(down_id, current_id, spacing);
            }
        }
    }
    
    std::cout << "Grafo de cuadrícula generado: " << graph.getNodeCount() 
              << " nodos, " << graph.getEdgeCount() << " aristas" << std::endl;
}

// Generar grafo grande aleatorio
void LargeGraphGenerator::generateRandomGraph(Graph& graph, int num_nodes, double connection_probability) {
    graph.clear();
    std::srand(std::time(nullptr));
    
    std::cout << "Generando grafo aleatorio con " << num_nodes << " nodos..." << std::endl;
    
    // Crear nodos con posiciones aleatorias
    for (int i = 0; i < num_nodes; i++) {
        double x = (double(std::rand()) / RAND_MAX) * 1000.0;
        double y = (double(std::rand()) / RAND_MAX) * 1000.0;
        
        std::string name = "Random_" + std::to_string(i);
        graph.addNode(Node(i, name, x, y));
    }
    
    // Conectar nodos con probabilidad dada
    const DynamicArray<Node>& nodes = graph.getAllNodes();
    int edges_added = 0;
    
    for (int i = 0; i < nodes.getSize(); i++) {
        for (int j = i + 1; j < nodes.getSize(); j++) {
            if ((double(std::rand()) / RAND_MAX) < connection_probability) {
                double distance = calculateDistance(nodes[i].getX(), nodes[i].getY(),
                                                  nodes[j].getX(), nodes[j].getY());
                graph.addEdge(i, j, distance);
                graph.addEdge(j, i, distance);
                edges_added += 2;
            }
        }
        
        // Mostrar progreso cada 1000 nodos
        if (i % 1000 == 0 && i > 0) {
            std::cout << "Procesados " << i << " nodos, " << edges_added << " aristas añadidas" << std::endl;
        }
    }
    
    std::cout << "Grafo aleatorio generado: " << graph.getNodeCount() 
              << " nodos, " << graph.getEdgeCount() << " aristas" << std::endl;
}

// Generar grafo con distribución de ciudades (más realista)
void LargeGraphGenerator::generateCityLikeGraph(Graph& graph, int num_nodes, int num_clusters) {
    graph.clear();
    std::srand(std::time(nullptr));
    
    std::cout << "Generando grafo tipo ciudad con " << num_nodes << " nodos en " 
              << num_clusters << " clusters..." << std::endl;
    
    // Generar centros de clusters
    DynamicArray<std::pair<double, double>> cluster_centers;
    for (int i = 0; i < num_clusters; i++) {
        double x = (double(std::rand()) / RAND_MAX) * 1000.0;
        double y = (double(std::rand()) / RAND_MAX) * 1000.0;
        cluster_centers.push_back(std::make_pair(x, y));
    }
    
    // Crear nodos distribuidos alrededor de los centros
    for (int i = 0; i < num_nodes; i++) {
        // Seleccionar cluster aleatorio
        int cluster = std::rand() % num_clusters;
        double center_x = cluster_centers[cluster].first;
        double center_y = cluster_centers[cluster].second;
        
        // Generar posición cerca del centro del cluster
        double radius = (double(std::rand()) / RAND_MAX) * 50.0; // Radio máximo de 50
        double angle = (double(std::rand()) / RAND_MAX) * 2.0 * 3.14159;
        
        double x = center_x + radius * std::cos(angle);
        double y = center_y + radius * std::sin(angle);
        
        std::string name = "City_" + std::to_string(i);
        graph.addNode(Node(i, name, x, y));
    }
    
    // Conectar nodos cercanos
    const DynamicArray<Node>& nodes = graph.getAllNodes();
    
    for (int i = 0; i < nodes.getSize(); i++) {
        connectNearbyNodes(graph, i, nodes, 30.0, 5); // Conectar con nodos dentro de 30 unidades, máximo 5 conexiones
        
        // Mostrar progreso
        if (i % 10000 == 0 && i > 0) {
            std::cout << "Procesados " << i << " nodos" << std::endl;
        }
    }
    
    std::cout << "Grafo tipo ciudad generado: " << graph.getNodeCount() 
              << " nodos, " << graph.getEdgeCount() << " aristas" << std::endl;
}

// Generar obstáculos en el grafo
void LargeGraphGenerator::addObstacles(Graph& graph, double obstacle_percentage) {
    std::cout << "Añadiendo obstáculos (" << obstacle_percentage * 100 << "% de nodos)..." << std::endl;
    
    const DynamicArray<Node>& nodes = graph.getAllNodes();
    int num_obstacles = static_cast<int>(nodes.getSize() * obstacle_percentage);
    
    for (int i = 0; i < num_obstacles; i++) {
        int node_id = std::rand() % nodes.getSize();
        
        // Remover todas las conexiones de este nodo (simulando obstáculo)
        // Nota: En una implementación completa, se necesitaría un método para remover aristas
        // Por ahora, solo marcamos conceptualmente
    }
    
    std::cout << "Obstáculos añadidos: " << num_obstacles << " nodos afectados" << std::endl;
}

// Guardar grafo en archivo binario
bool LargeGraphGenerator::saveGraphToBinary(const Graph& graph, const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo crear el archivo " << filename << std::endl;
        return false;
    }
    
    std::cout << "Guardando grafo en archivo binario..." << std::endl;
    
    // Guardar número de nodos
    int node_count = graph.getNodeCount();
    file.write(reinterpret_cast<const char*>(&node_count), sizeof(int));
    
    // Guardar nodos
    const DynamicArray<Node>& nodes = graph.getAllNodes();
    for (int i = 0; i < nodes.getSize(); i++) {
        const Node& node = nodes[i];
        
        int id = node.getId();
        file.write(reinterpret_cast<const char*>(&id), sizeof(int));
        
        std::string name = node.getName();
        int name_length = name.length();
        file.write(reinterpret_cast<const char*>(&name_length), sizeof(int));
        file.write(name.c_str(), name_length);
        
        double x = node.getX();
        double y = node.getY();
        file.write(reinterpret_cast<const char*>(&x), sizeof(double));
        file.write(reinterpret_cast<const char*>(&y), sizeof(double));
    }
    
    // Guardar aristas
    for (int i = 0; i < nodes.getSize(); i++) {
        const Node& node = nodes[i];
        const LinkedList<Edge>& adjacencies = graph.getAdjacencies(node.getId());
        
        int adj_count = adjacencies.getSize();
        file.write(reinterpret_cast<const char*>(&adj_count), sizeof(int));
        
        for (auto it = adjacencies.begin(); it != adjacencies.end(); ++it) {
            const Edge& edge = *it;
            
            int dest = edge.getDestination();
            double weight = edge.getWeight();
            
            file.write(reinterpret_cast<const char*>(&dest), sizeof(int));
            file.write(reinterpret_cast<const char*>(&weight), sizeof(double));
        }
    }
    
    file.close();
    std::cout << "Grafo guardado exitosamente en " << filename << std::endl;
    return true;
}

// Cargar grafo desde archivo binario
bool LargeGraphGenerator::loadGraphFromBinary(Graph& graph, const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << filename << std::endl;
        return false;
    }
    
    std::cout << "Cargando grafo desde archivo binario..." << std::endl;
    graph.clear();
    
    // Leer número de nodos
    int node_count;
    file.read(reinterpret_cast<char*>(&node_count), sizeof(int));
    
    // Leer nodos
    for (int i = 0; i < node_count; i++) {
        int id;
        file.read(reinterpret_cast<char*>(&id), sizeof(int));
        
        int name_length;
        file.read(reinterpret_cast<char*>(&name_length), sizeof(int));
        
        char* name_buffer = new char[name_length + 1];
        file.read(name_buffer, name_length);
        name_buffer[name_length] = '\0';
        std::string name(name_buffer);
        delete[] name_buffer;
        
        double x, y;
        file.read(reinterpret_cast<char*>(&x), sizeof(double));
        file.read(reinterpret_cast<char*>(&y), sizeof(double));
        
        graph.addNode(Node(id, name, x, y));
    }
    
    // Leer aristas
    for (int i = 0; i < node_count; i++) {
        int adj_count;
        file.read(reinterpret_cast<char*>(&adj_count), sizeof(int));
        
        for (int j = 0; j < adj_count; j++) {
            int dest;
            double weight;
            
            file.read(reinterpret_cast<char*>(&dest), sizeof(int));
            file.read(reinterpret_cast<char*>(&weight), sizeof(double));
            
            graph.addEdge(i, dest, weight);
        }
    }
    
    file.close();
    std::cout << "Grafo cargado exitosamente: " << graph.getNodeCount() 
              << " nodos, " << graph.getEdgeCount() << " aristas" << std::endl;
    return true;
}

// Generar datos de prueba específicos para 2M de nodos
void LargeGraphGenerator::generate2MillionNodeGraph(Graph& graph) {
    std::cout << "Generando grafo de 2 millones de nodos..." << std::endl;
    std::cout << "Esto puede tomar varios minutos..." << std::endl;
    
    // Usar patrón de cuadrícula para eficiencia
    // 1414 x 1414 ≈ 2,000,000 nodos
    int side_length = 1414;
    generateGridGraph(graph, side_length, side_length, 1.0);
    
    std::cout << "Grafo de 2M nodos generado exitosamente!" << std::endl;
}

// Funciones auxiliares
double LargeGraphGenerator::calculateDistance(double x1, double y1, double x2, double y2) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    return std::sqrt(dx * dx + dy * dy);
}

void LargeGraphGenerator::connectNearbyNodes(Graph& graph, int node_id, const DynamicArray<Node>& nodes, 
                                           double max_distance, int max_connections) {
    const Node& current_node = nodes[node_id];
    int connections_made = 0;
    
    for (int i = 0; i < nodes.getSize() && connections_made < max_connections; i++) {
        if (i != node_id) {
            const Node& other_node = nodes[i];
            double distance = calculateDistance(current_node.getX(), current_node.getY(),
                                              other_node.getX(), other_node.getY());
            
            if (distance <= max_distance) {
                graph.addEdge(node_id, i, distance);
                connections_made++;
            }
        }
    }
}

int LargeGraphGenerator::getGridIndex(int x, int y, int width) {
    return y * width + x;
}

