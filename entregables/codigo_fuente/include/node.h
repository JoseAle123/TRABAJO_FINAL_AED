#ifndef NODE_H
#define NODE_H

#include <string>

class Node {
private:
    int id;
    std::string name;
    double x, y; // Coordenadas para visualización
    
public:
    // Constructor por defecto
    Node();
    
    // Constructor
    Node(int id, const std::string& name, double x = 0.0, double y = 0.0);
    
    // Getters
    int getId() const;
    std::string getName() const;
    double getX() const;
    double getY() const;
    
    // Setters
    void setName(const std::string& name);
    void setCoordinates(double x, double y);
    
    // Operadores de comparación
    bool operator==(const Node& other) const;
    bool operator!=(const Node& other) const;
};

#endif // NODE_H

