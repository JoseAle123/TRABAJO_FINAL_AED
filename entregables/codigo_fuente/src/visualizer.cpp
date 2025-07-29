#include "../include/visualizer.h"
#include <iostream>
#include <sstream>
#include <cmath>

// Constructor
Visualizer::Visualizer(const Graph* graph) 
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Sistema de Navegación - Arequipa"),
      graph(graph), search_algorithms(new SearchAlgorithms(graph)) {
    
    // Intentar cargar una fuente del sistema
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        std::cout << "Advertencia: No se pudo cargar la fuente del sistema" << std::endl;
        font_loaded = false;
    } else {
        font_loaded = true;
    }
}

// Destructor
Visualizer::~Visualizer() {
    delete search_algorithms;
}

// Convertir coordenadas del nodo a coordenadas de pantalla
sf::Vector2f Visualizer::nodeToScreen(const Node* node) const {
    if (!node) return sf::Vector2f(0, 0);
    
    // Encontrar los límites del grafo
    double min_x = node->getX(), max_x = node->getX();
    double min_y = node->getY(), max_y = node->getY();
    
    const DynamicArray<Node>& nodes = graph->getAllNodes();
    for (int i = 0; i < nodes.getSize(); i++) {
        double x = nodes[i].getX();
        double y = nodes[i].getY();
        
        if (x < min_x) min_x = x;
        if (x > max_x) max_x = x;
        if (y < min_y) min_y = y;
        if (y > max_y) max_y = y;
    }
    
    // Agregar margen
    double margin = 50.0;
    double width = max_x - min_x;
    double height = max_y - min_y;
    
    if (width == 0) width = 1;
    if (height == 0) height = 1;
    
    // Escalar a la ventana
    double scale_x = (WINDOW_WIDTH - 2 * margin) / width;
    double scale_y = (WINDOW_HEIGHT - 2 * margin) / height;
    double scale = std::min(scale_x, scale_y);
    
    float screen_x = margin + (node->getX() - min_x) * scale;
    float screen_y = margin + (node->getY() - min_y) * scale;
    
    return sf::Vector2f(screen_x, screen_y);
}

// Obtener el nodo en una posición específica
int Visualizer::getNodeAtPosition(sf::Vector2f position) const {
    const DynamicArray<Node>& nodes = graph->getAllNodes();
    
    for (int i = 0; i < nodes.getSize(); i++) {
        sf::Vector2f node_pos = nodeToScreen(&nodes[i]);
        float dx = position.x - node_pos.x;
        float dy = position.y - node_pos.y;
        float distance = std::sqrt(dx * dx + dy * dy);
        
        if (distance <= NODE_RADIUS + 5) { // Un poco de tolerancia
            return nodes[i].getId();
        }
    }
    
    return -1;
}

// Dibujar nodos
void Visualizer::drawNodes() {
    const DynamicArray<Node>& nodes = graph->getAllNodes();
    
    for (int i = 0; i < nodes.getSize(); i++) {
        const Node& node = nodes[i];
        sf::Vector2f pos = nodeToScreen(&node);
        
        sf::CircleShape circle;
        
        // Determinar el color y tamaño del nodo
        if (node.getId() == selected_start) {
            circle.setRadius(SELECTED_NODE_RADIUS);
            circle.setFillColor(sf::Color::Green);
        } else if (node.getId() == selected_goal) {
            circle.setRadius(SELECTED_NODE_RADIUS);
            circle.setFillColor(sf::Color::Red);
        } else {
            circle.setRadius(NODE_RADIUS);
            circle.setFillColor(NODE_COLOR);
        }
        
        circle.setPosition(pos.x - circle.getRadius(), pos.y - circle.getRadius());
        circle.setOutlineThickness(2);
        circle.setOutlineColor(sf::Color::Black);
        
        window.draw(circle);
        
        // Dibujar etiqueta del nodo si la fuente está cargada
        if (font_loaded) {
            sf::Text text;
            text.setFont(font);
            text.setString(std::to_string(node.getId()));
            text.setCharacterSize(12);
            text.setFillColor(sf::Color::Black);
            
            sf::FloatRect textBounds = text.getLocalBounds();
            text.setPosition(pos.x - textBounds.width / 2, pos.y + circle.getRadius() + 2);
            
            window.draw(text);
        }
    }
}

// Dibujar aristas
void Visualizer::drawEdges() {
    const DynamicArray<Node>& nodes = graph->getAllNodes();
    
    for (int i = 0; i < nodes.getSize(); i++) {
        const Node& node = nodes[i];
        sf::Vector2f start_pos = nodeToScreen(&node);
        
        const LinkedList<Edge>& adjacencies = graph->getAdjacencies(node.getId());
        for (auto it = adjacencies.begin(); it != adjacencies.end(); ++it) {
            const Edge& edge = *it;
            const Node* dest_node = graph->getNode(edge.getDestination());
            
            if (dest_node) {
                sf::Vector2f end_pos = nodeToScreen(dest_node);
                
                sf::Vertex line[] = {
                    sf::Vertex(start_pos, EDGE_COLOR),
                    sf::Vertex(end_pos, EDGE_COLOR)
                };
                
                window.draw(line, 2, sf::Lines);
            }
        }
    }
}

// Dibujar el camino encontrado
void Visualizer::drawPath() {
    if (!current_result.path_found || current_result.path.getSize() < 2) {
        return;
    }
    
    for (int i = 0; i < current_result.path.getSize() - 1; i++) {
        const Node* node1 = graph->getNode(current_result.path[i]);
        const Node* node2 = graph->getNode(current_result.path[i + 1]);
        
        if (node1 && node2) {
            sf::Vector2f pos1 = nodeToScreen(node1);
            sf::Vector2f pos2 = nodeToScreen(node2);
            
            sf::Vertex line[] = {
                sf::Vertex(pos1, PATH_COLOR),
                sf::Vertex(pos2, PATH_COLOR)
            };
            
            window.draw(line, 2, sf::Lines);
        }
    }
}

// Dibujar interfaz de usuario
void Visualizer::drawUI() {
    if (!font_loaded) return;
    
    // Información de estado
    sf::Text status_text;
    status_text.setFont(font);
    status_text.setCharacterSize(14);
    status_text.setFillColor(sf::Color::Black);
    status_text.setPosition(10, 10);
    
    std::stringstream ss;
    ss << "Sistema de Navegación - Arequipa\n";
    ss << "Algoritmo: " << current_algorithm << "\n";
    ss << "Nodos: " << graph->getNodeCount() << ", Aristas: " << graph->getEdgeCount() << "\n";
    
    if (selected_start != -1) {
        const Node* start_node = graph->getNode(selected_start);
        if (start_node) {
            ss << "Inicio: " << start_node->getName() << " (ID: " << selected_start << ")\n";
        }
    } else {
        ss << "Inicio: No seleccionado (clic izquierdo)\n";
    }
    
    if (selected_goal != -1) {
        const Node* goal_node = graph->getNode(selected_goal);
        if (goal_node) {
            ss << "Destino: " << goal_node->getName() << " (ID: " << selected_goal << ")\n";
        }
    } else {
        ss << "Destino: No seleccionado (clic derecho)\n";
    }
    
    if (current_result.path_found) {
        ss << "Camino encontrado: Distancia = " << current_result.total_distance;
        ss << ", Nodos explorados = " << current_result.nodes_explored;
        ss << ", Tiempo = " << current_result.time_taken.count() << " ms\n";
    } else if (selected_start != -1 && selected_goal != -1) {
        ss << "No se encontró camino\n";
    }
    
    ss << "\nControles:\n";
    ss << "Clic izquierdo: Seleccionar inicio\n";
    ss << "Clic derecho: Seleccionar destino\n";
    ss << "ESPACIO: Buscar ruta\n";
    ss << "1-5: Cambiar algoritmo\n";
    ss << "ESC: Salir\n";
    
    status_text.setString(ss.str());
    
    // Fondo semi-transparente para el texto
    sf::FloatRect textBounds = status_text.getLocalBounds();
    sf::RectangleShape background(sf::Vector2f(textBounds.width + 20, textBounds.height + 20));
    background.setPosition(5, 5);
    background.setFillColor(sf::Color(255, 255, 255, 200));
    background.setOutlineThickness(1);
    background.setOutlineColor(sf::Color::Black);
    
    window.draw(background);
    window.draw(status_text);
}

// Manejar clic del mouse
void Visualizer::handleMouseClick(sf::Vector2f position) {
    int node_id = getNodeAtPosition(position);
    
    if (node_id != -1) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            selected_start = node_id;
            std::cout << "Nodo de inicio seleccionado: " << node_id << std::endl;
        } else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            selected_goal = node_id;
            std::cout << "Nodo de destino seleccionado: " << node_id << std::endl;
        }
        
        // Limpiar resultado anterior
        current_result = SearchResult();
    }
}

// Manejar presión de teclas
void Visualizer::handleKeyPress(sf::Keyboard::Key key) {
    switch (key) {
        case sf::Keyboard::Space:
            if (selected_start != -1 && selected_goal != -1) {
                performSearch();
            }
            break;
        case sf::Keyboard::Num1:
            current_algorithm = "DFS";
            current_result = SearchResult();
            break;
        case sf::Keyboard::Num2:
            current_algorithm = "BFS";
            current_result = SearchResult();
            break;
        case sf::Keyboard::Num3:
            current_algorithm = "Dijkstra";
            current_result = SearchResult();
            break;
        case sf::Keyboard::Num4:
            current_algorithm = "Best First";
            current_result = SearchResult();
            break;
        case sf::Keyboard::Num5:
            current_algorithm = "A*";
            current_result = SearchResult();
            break;
        case sf::Keyboard::Escape:
            window.close();
            break;
        default:
            break;
    }
}

// Realizar búsqueda
void Visualizer::performSearch() {
    if (selected_start == -1 || selected_goal == -1) {
        return;
    }
    
    std::cout << "Buscando ruta desde " << selected_start << " hasta " << selected_goal 
              << " usando " << current_algorithm << std::endl;
    
    if (current_algorithm == "DFS") {
        current_result = search_algorithms->depthFirstSearch(selected_start, selected_goal);
    } else if (current_algorithm == "BFS") {
        current_result = search_algorithms->breadthFirstSearch(selected_start, selected_goal);
    } else if (current_algorithm == "Dijkstra") {
        current_result = search_algorithms->dijkstra(selected_start, selected_goal);
    } else if (current_algorithm == "Best First") {
        current_result = search_algorithms->bestFirstSearch(selected_start, selected_goal);
    } else if (current_algorithm == "A*") {
        current_result = search_algorithms->aStar(selected_start, selected_goal);
    }
    
    if (current_result.path_found) {
        std::cout << "Camino encontrado! Distancia: " << current_result.total_distance 
                  << ", Nodos explorados: " << current_result.nodes_explored 
                  << ", Tiempo: " << current_result.time_taken.count() << " ms" << std::endl;
    } else {
        std::cout << "No se encontró camino" << std::endl;
    }
}

// Método principal para ejecutar la visualización
void Visualizer::run() {
    std::cout << "Iniciando visualizador..." << std::endl;
    std::cout << "Controles:" << std::endl;
    std::cout << "- Clic izquierdo: Seleccionar nodo de inicio" << std::endl;
    std::cout << "- Clic derecho: Seleccionar nodo de destino" << std::endl;
    std::cout << "- ESPACIO: Buscar ruta" << std::endl;
    std::cout << "- 1-5: Cambiar algoritmo (DFS, BFS, Dijkstra, Best First, A*)" << std::endl;
    std::cout << "- ESC: Salir" << std::endl;
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    handleMouseClick(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
                    break;
                case sf::Event::KeyPressed:
                    handleKeyPress(event.key.code);
                    break;
                default:
                    break;
            }
        }
        
        // Limpiar ventana
        window.clear(BACKGROUND_COLOR);
        
        // Dibujar elementos
        drawEdges();
        drawPath();
        drawNodes();
        drawUI();
        
        // Mostrar ventana
        window.display();
    }
}

// Configurar algoritmo de búsqueda
void Visualizer::setAlgorithm(const std::string& algorithm) {
    current_algorithm = algorithm;
    current_result = SearchResult();
}

// Obtener información del estado actual
std::string Visualizer::getStatusText() const {
    std::stringstream ss;
    ss << "Algoritmo: " << current_algorithm;
    ss << ", Inicio: " << selected_start;
    ss << ", Destino: " << selected_goal;
    if (current_result.path_found) {
        ss << ", Distancia: " << current_result.total_distance;
    }
    return ss.str();
}

