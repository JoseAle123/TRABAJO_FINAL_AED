#ifndef MAP_LOADER_H
#define MAP_LOADER_H

#include "graph.h"
#include <string>

class MapLoader {
public:
    // Cargar mapa desde archivo CSV
    static bool loadFromCSV(Graph& graph, const std::string& nodes_file, const std::string& edges_file);
    
    // Crear mapa de prueba de Arequipa
    static void createArequipaMap(Graph& graph);
    
    // Generar mapa sintético para pruebas
    static void generateSyntheticMap(Graph& graph, int num_nodes, double width, double height);
    
private:
    // Funciones auxiliares
    static double calculateDistance(double x1, double y1, double x2, double y2);
    static void addBidirectionalEdge(Graph& graph, int node1, int node2, double weight);
};

#endif // MAP_LOADER_H

