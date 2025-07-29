#include "../include/node.h"

// Constructor por defecto
Node::Node() : id(-1), name(""), x(0.0), y(0.0) {}

// Constructor
Node::Node(int id, const std::string& name, double x, double y) 
    : id(id), name(name), x(x), y(y) {}

// Getters
int Node::getId() const {
    return id;
}

std::string Node::getName() const {
    return name;
}

double Node::getX() const {
    return x;
}

double Node::getY() const {
    return y;
}

// Setters
void Node::setName(const std::string& name) {
    this->name = name;
}

void Node::setCoordinates(double x, double y) {
    this->x = x;
    this->y = y;
}

// Operadores de comparación
bool Node::operator==(const Node& other) const {
    return id == other.id;
}

bool Node::operator!=(const Node& other) const {
    return !(*this == other);
}

