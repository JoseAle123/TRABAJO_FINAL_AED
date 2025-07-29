#ifndef VISUALIZER_H
#define VISUALIZER_H

#include "graph.h"
#include "search_algorithms.h"
#include <SFML/Graphics.hpp>
#include <string>

class Visualizer {
private:
    sf::RenderWindow window;
    const Graph* graph;
    SearchAlgorithms* search_algorithms;
    
    // Configuración de visualización
    static const int WINDOW_WIDTH = 800;
    static const int WINDOW_HEIGHT = 600;
    static const int NODE_RADIUS = 8;
    static const int SELECTED_NODE_RADIUS = 12;
    
    // Colores
    sf::Color NODE_COLOR = sf::Color::Blue;
    sf::Color EDGE_COLOR = sf::Color::Black;
    sf::Color PATH_COLOR = sf::Color::Red;
    sf::Color SELECTED_COLOR = sf::Color::Green;
    sf::Color BACKGROUND_COLOR = sf::Color::White;
    
    // Estado de la aplicación
    int selected_start = -1;
    int selected_goal = -1;
    SearchResult current_result;
    std::string current_algorithm = "Dijkstra";
    
    // Fuente para texto
    sf::Font font;
    bool font_loaded = false;
    
    // Funciones auxiliares
    sf::Vector2f nodeToScreen(const Node* node) const;
    int getNodeAtPosition(sf::Vector2f position) const;
    void drawNodes();
    void drawEdges();
    void drawPath();
    void drawUI();
    void drawNodeInfo(const Node* node, sf::Vector2f position);
    void handleMouseClick(sf::Vector2f position);
    void handleKeyPress(sf::Keyboard::Key key);
    void performSearch();
    
public:
    // Constructor
    Visualizer(const Graph* graph);
    
    // Destructor
    ~Visualizer();
    
    // Método principal para ejecutar la visualización
    void run();
    
    // Configurar algoritmo de búsqueda
    void setAlgorithm(const std::string& algorithm);
    
    // Obtener información del estado actual
    std::string getStatusText() const;
};

#endif // VISUALIZER_H

