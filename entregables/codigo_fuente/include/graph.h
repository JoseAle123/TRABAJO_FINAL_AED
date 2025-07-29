#ifndef GRAPH_H
#define GRAPH_H

#include "node.h"
#include "edge.h"
#include "dynamic_array.h"
#include "linked_list.h"
#include <string>

class Graph {
private:
    DynamicArray<Node> nodes;
    DynamicArray<LinkedList<Edge>> adjacency_list;
    int node_count;
    int edge_count;
    
    // Función auxiliar para encontrar el índice de un nodo por ID
    int findNodeIndex(int node_id) const;
    
public:
    // Constructor
    Graph();
    
    // Destructor
    ~Graph() = default;
    
    // Métodos para agregar nodos y aristas
    void addNode(const Node& node);
    void addEdge(const Edge& edge);
    void addEdge(int source, int destination, double weight = 1.0);
    
    // Métodos para obtener información
    int getNodeCount() const;
    int getEdgeCount() const;
    Node* getNode(int node_id);
    const Node* getNode(int node_id) const;
    Node* getNodeByName(const std::string& name);
    const Node* getNodeByName(const std::string& name) const;
    
    // Métodos para obtener vecinos
    const LinkedList<Edge>& getAdjacencies(int node_id) const;
    DynamicArray<int> getNeighbors(int node_id) const;
    
    // Métodos para verificar existencia
    bool hasNode(int node_id) const;
    bool hasEdge(int source, int destination) const;
    
    // Métodos para obtener peso de arista
    double getEdgeWeight(int source, int destination) const;
    
    // Método para limpiar el grafo
    void clear();
    
    // Método para obtener todos los nodos
    const DynamicArray<Node>& getAllNodes() const;
    
    // Método para imprimir el grafo (para debugging)
    void printGraph() const;
};

#endif // GRAPH_H

