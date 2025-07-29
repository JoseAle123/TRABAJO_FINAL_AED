#ifndef EDGE_H
#define EDGE_H

class Edge {
private:
    int source;      // ID del nodo origen
    int destination; // ID del nodo destino
    double weight;   // Peso de la arista (distancia, tiempo, etc.)
    
public:
    // Constructor por defecto
    Edge();
    
    // Constructor
    Edge(int source, int destination, double weight = 1.0);
    
    // Getters
    int getSource() const;
    int getDestination() const;
    double getWeight() const;
    
    // Setters
    void setWeight(double weight);
    
    // Operadores de comparación
    bool operator==(const Edge& other) const;
    bool operator!=(const Edge& other) const;
    bool operator<(const Edge& other) const; // Para ordenamiento por peso
};

#endif // EDGE_H

