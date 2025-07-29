#ifndef SEARCH_ALGORITHMS_H
#define SEARCH_ALGORITHMS_H

#include "graph.h"
#include "dynamic_array.h"
#include "queue.h"
#include "priority_queue.h"
#include <chrono>

// Estructura para representar el resultado de una búsqueda
struct SearchResult {
    DynamicArray<int> path;           // Camino encontrado (IDs de nodos)
    double total_distance;            // Distancia total del camino
    int nodes_explored;               // Número de nodos explorados
    std::chrono::milliseconds time_taken; // Tiempo tomado en la búsqueda
    bool path_found;                  // Si se encontró un camino
    
    SearchResult() : total_distance(0.0), nodes_explored(0), time_taken(0), path_found(false) {}
};

// Estructura para el algoritmo A*
struct AStarNode {
    int node_id;
    double g_cost;  // Costo desde el inicio
    double h_cost;  // Heurística (estimación al objetivo)
    double f_cost;  // g_cost + h_cost
    int parent;     // Nodo padre en el camino
    
    AStarNode() : node_id(-1), g_cost(0.0), h_cost(0.0), f_cost(0.0), parent(-1) {}
    
    AStarNode(int id, double g, double h, int p) 
        : node_id(id), g_cost(g), h_cost(h), f_cost(g + h), parent(p) {}
    
    // Operador para la cola de prioridad (menor f_cost tiene mayor prioridad)
    bool operator<(const AStarNode& other) const {
        return f_cost > other.f_cost; // Invertido para min-heap
    }
    
    bool operator>(const AStarNode& other) const {
        return f_cost < other.f_cost;
    }
};

class SearchAlgorithms {
private:
    const Graph* graph;
    
    // Funciones auxiliares
    double calculateDistance(const Node* node1, const Node* node2) const;
    DynamicArray<int> reconstructPath(const DynamicArray<int>& parent, int start, int goal) const;
    
public:
    // Constructor
    SearchAlgorithms(const Graph* graph);
    
    // Algoritmos de búsqueda
    SearchResult depthFirstSearch(int start, int goal);
    SearchResult breadthFirstSearch(int start, int goal);
    SearchResult dijkstra(int start, int goal);
    SearchResult bestFirstSearch(int start, int goal);
    SearchResult aStar(int start, int goal);
    
    // Método para comparar algoritmos
    void compareAlgorithms(int start, int goal);
};

#endif // SEARCH_ALGORITHMS_H

