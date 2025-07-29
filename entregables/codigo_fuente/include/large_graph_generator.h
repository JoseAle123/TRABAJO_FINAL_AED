#ifndef LARGE_GRAPH_GENERATOR_H
#define LARGE_GRAPH_GENERATOR_H

#include "graph.h"
#include <string>

class LargeGraphGenerator {
public:
    // Generar grafo grande con patrón de cuadrícula
    static void generateGridGraph(Graph& graph, int width, int height, double spacing = 1.0);
    
    // Generar grafo grande aleatorio
    static void generateRandomGraph(Graph& graph, int num_nodes, double connection_probability = 0.1);
    
    // Generar grafo con distribución de ciudades (más realista)
    static void generateCityLikeGraph(Graph& graph, int num_nodes, int num_clusters = 10);
    
    // Generar obstáculos en el grafo (para simular calles bloqueadas)
    static void addObstacles(Graph& graph, double obstacle_percentage = 0.1);
    
    // Guardar grafo en archivo binario para carga rápida
    static bool saveGraphToBinary(const Graph& graph, const std::string& filename);
    
    // Cargar grafo desde archivo binario
    static bool loadGraphFromBinary(Graph& graph, const std::string& filename);
    
    // Generar datos de prueba específicos para 2M de nodos
    static void generate2MillionNodeGraph(Graph& graph);
    
private:
    // Funciones auxiliares
    static double calculateDistance(double x1, double y1, double x2, double y2);
    static void connectNearbyNodes(Graph& graph, int node_id, const DynamicArray<Node>& nodes, 
                                 double max_distance, int max_connections);
    static int getGridIndex(int x, int y, int width);
};

#endif // LARGE_GRAPH_GENERATOR_H

