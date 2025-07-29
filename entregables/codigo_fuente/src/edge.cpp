#include "../include/edge.h"

// Constructor por defecto
Edge::Edge() : source(-1), destination(-1), weight(0.0) {}

// Constructor
Edge::Edge(int source, int destination, double weight) 
    : source(source), destination(destination), weight(weight) {}

// Getters
int Edge::getSource() const {
    return source;
}

int Edge::getDestination() const {
    return destination;
}

double Edge::getWeight() const {
    return weight;
}

// Setters
void Edge::setWeight(double weight) {
    this->weight = weight;
}

// Operadores de comparación
bool Edge::operator==(const Edge& other) const {
    return source == other.source && destination == other.destination;
}

bool Edge::operator!=(const Edge& other) const {
    return !(*this == other);
}

bool Edge::operator<(const Edge& other) const {
    return weight < other.weight;
}

