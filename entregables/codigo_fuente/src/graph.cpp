#include "../include/graph.h"
#include <iostream>

// Constructor
Graph::Graph() : node_count(0), edge_count(0) {}

// Función auxiliar para encontrar el índice de un nodo por ID
int Graph::findNodeIndex(int node_id) const {
    for (int i = 0; i < nodes.getSize(); i++) {
        if (nodes[i].getId() == node_id) {
            return i;
        }
    }
    return -1;
}

// Métodos para agregar nodos y aristas
void Graph::addNode(const Node& node) {
    if (!hasNode(node.getId())) {
        nodes.push_back(node);
        adjacency_list.push_back(LinkedList<Edge>());
        node_count++;
    }
}

void Graph::addEdge(const Edge& edge) {
    int source_index = findNodeIndex(edge.getSource());
    int dest_index = findNodeIndex(edge.getDestination());
    
    if (source_index != -1 && dest_index != -1) {
        adjacency_list[source_index].push_back(edge);
        edge_count++;
    }
}

void Graph::addEdge(int source, int destination, double weight) {
    Edge edge(source, destination, weight);
    addEdge(edge);
}

// Métodos para obtener información
int Graph::getNodeCount() const {
    return node_count;
}

int Graph::getEdgeCount() const {
    return edge_count;
}

Node* Graph::getNode(int node_id) {
    int index = findNodeIndex(node_id);
    if (index != -1) {
        return &nodes[index];
    }
    return nullptr;
}

const Node* Graph::getNode(int node_id) const {
    int index = findNodeIndex(node_id);
    if (index != -1) {
        return &nodes[index];
    }
    return nullptr;
}

Node* Graph::getNodeByName(const std::string& name) {
    for (int i = 0; i < nodes.getSize(); i++) {
        if (nodes[i].getName() == name) {
            return &nodes[i];
        }
    }
    return nullptr;
}

const Node* Graph::getNodeByName(const std::string& name) const {
    for (int i = 0; i < nodes.getSize(); i++) {
        if (nodes[i].getName() == name) {
            return &nodes[i];
        }
    }
    return nullptr;
}

// Métodos para obtener vecinos
const LinkedList<Edge>& Graph::getAdjacencies(int node_id) const {
    int index = findNodeIndex(node_id);
    if (index != -1) {
        return adjacency_list[index];
    }
    // Retornar una lista vacía si no se encuentra el nodo
    static LinkedList<Edge> empty_list;
    return empty_list;
}

DynamicArray<int> Graph::getNeighbors(int node_id) const {
    DynamicArray<int> neighbors;
    int index = findNodeIndex(node_id);
    
    if (index != -1) {
        const LinkedList<Edge>& edges = adjacency_list[index];
        for (auto it = edges.begin(); it != edges.end(); ++it) {
            neighbors.push_back((*it).getDestination());
        }
    }
    
    return neighbors;
}

// Métodos para verificar existencia
bool Graph::hasNode(int node_id) const {
    return findNodeIndex(node_id) != -1;
}

bool Graph::hasEdge(int source, int destination) const {
    int source_index = findNodeIndex(source);
    if (source_index != -1) {
        const LinkedList<Edge>& edges = adjacency_list[source_index];
        for (auto it = edges.begin(); it != edges.end(); ++it) {
            if ((*it).getDestination() == destination) {
                return true;
            }
        }
    }
    return false;
}

// Métodos para obtener peso de arista
double Graph::getEdgeWeight(int source, int destination) const {
    int source_index = findNodeIndex(source);
    if (source_index != -1) {
        const LinkedList<Edge>& edges = adjacency_list[source_index];
        for (auto it = edges.begin(); it != edges.end(); ++it) {
            if ((*it).getDestination() == destination) {
                return (*it).getWeight();
            }
        }
    }
    return -1.0; // Indica que no existe la arista
}

// Método para limpiar el grafo
void Graph::clear() {
    nodes.clear();
    adjacency_list.clear();
    node_count = 0;
    edge_count = 0;
}

// Método para obtener todos los nodos
const DynamicArray<Node>& Graph::getAllNodes() const {
    return nodes;
}

// Método para imprimir el grafo (para debugging)
void Graph::printGraph() const {
    std::cout << "Grafo con " << node_count << " nodos y " << edge_count << " aristas:" << std::endl;
    
    for (int i = 0; i < nodes.getSize(); i++) {
        const Node& node = nodes[i];
        std::cout << "Nodo " << node.getId() << " (" << node.getName() << "): ";
        
        const LinkedList<Edge>& edges = adjacency_list[i];
        for (auto it = edges.begin(); it != edges.end(); ++it) {
            std::cout << "-> " << (*it).getDestination() << " (peso: " << (*it).getWeight() << ") ";
        }
        std::cout << std::endl;
    }
}

