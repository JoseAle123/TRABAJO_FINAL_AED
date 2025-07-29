#include "../include/search_algorithms.h"
#include <iostream>
#include <cmath>
#include <limits>

// Constructor
SearchAlgorithms::SearchAlgorithms(const Graph* graph) : graph(graph) {}

// Función auxiliar para calcular distancia euclidiana
double SearchAlgorithms::calculateDistance(const Node* node1, const Node* node2) const {
    if (!node1 || !node2) return 0.0;
    
    double dx = node1->getX() - node2->getX();
    double dy = node1->getY() - node2->getY();
    return std::sqrt(dx * dx + dy * dy);
}

// Función auxiliar para reconstruir el camino
DynamicArray<int> SearchAlgorithms::reconstructPath(const DynamicArray<int>& parent, int start, int goal) const {
    DynamicArray<int> path;
    int current = goal;
    
    while (current != -1) {
        path.push_back(current);
        if (current == start) break;
        current = parent[current];
    }
    
    // Invertir el camino
    DynamicArray<int> reversed_path;
    for (int i = path.getSize() - 1; i >= 0; i--) {
        reversed_path.push_back(path[i]);
    }
    
    return reversed_path;
}

// Depth First Search
SearchResult SearchAlgorithms::depthFirstSearch(int start, int goal) {
    auto start_time = std::chrono::high_resolution_clock::now();
    SearchResult result;
    
    if (!graph->hasNode(start) || !graph->hasNode(goal)) {
        return result;
    }
    
    DynamicArray<bool> visited(graph->getNodeCount());
    DynamicArray<int> parent(graph->getNodeCount());
    DynamicArray<int> stack;
    
    // Inicializar arrays
    for (int i = 0; i < graph->getNodeCount(); i++) {
        visited.push_back(false);
        parent.push_back(-1);
    }
    
    stack.push_back(start);
    int nodes_explored = 0;
    
    while (!stack.isEmpty()) {
        int current = stack[stack.getSize() - 1];
        stack.pop_back();
        
        if (visited[current]) continue;
        
        visited[current] = true;
        nodes_explored++;
        
        if (current == goal) {
            result.path = reconstructPath(parent, start, goal);
            result.path_found = true;
            break;
        }
        
        const LinkedList<Edge>& adjacencies = graph->getAdjacencies(current);
        for (auto it = adjacencies.begin(); it != adjacencies.end(); ++it) {
            int neighbor = (*it).getDestination();
            if (!visited[neighbor]) {
                parent[neighbor] = current;
                stack.push_back(neighbor);
            }
        }
    }
    
    // Calcular distancia total si se encontró un camino
    if (result.path_found) {
        result.total_distance = 0.0;
        for (int i = 0; i < result.path.getSize() - 1; i++) {
            result.total_distance += graph->getEdgeWeight(result.path[i], result.path[i + 1]);
        }
    }
    
    result.nodes_explored = nodes_explored;
    auto end_time = std::chrono::high_resolution_clock::now();
    result.time_taken = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    
    return result;
}

// Breadth First Search
SearchResult SearchAlgorithms::breadthFirstSearch(int start, int goal) {
    auto start_time = std::chrono::high_resolution_clock::now();
    SearchResult result;
    
    if (!graph->hasNode(start) || !graph->hasNode(goal)) {
        return result;
    }
    
    DynamicArray<bool> visited(graph->getNodeCount());
    DynamicArray<int> parent(graph->getNodeCount());
    Queue<int> queue;
    
    // Inicializar arrays
    for (int i = 0; i < graph->getNodeCount(); i++) {
        visited.push_back(false);
        parent.push_back(-1);
    }
    
    queue.enqueue(start);
    visited[start] = true;
    int nodes_explored = 0;
    
    while (!queue.isEmpty()) {
        int current = queue.front();
        queue.dequeue();
        nodes_explored++;
        
        if (current == goal) {
            result.path = reconstructPath(parent, start, goal);
            result.path_found = true;
            break;
        }
        
        const LinkedList<Edge>& adjacencies = graph->getAdjacencies(current);
        for (auto it = adjacencies.begin(); it != adjacencies.end(); ++it) {
            int neighbor = (*it).getDestination();
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                parent[neighbor] = current;
                queue.enqueue(neighbor);
            }
        }
    }
    
    // Calcular distancia total si se encontró un camino
    if (result.path_found) {
        result.total_distance = 0.0;
        for (int i = 0; i < result.path.getSize() - 1; i++) {
            result.total_distance += graph->getEdgeWeight(result.path[i], result.path[i + 1]);
        }
    }
    
    result.nodes_explored = nodes_explored;
    auto end_time = std::chrono::high_resolution_clock::now();
    result.time_taken = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    
    return result;
}

// Dijkstra
SearchResult SearchAlgorithms::dijkstra(int start, int goal) {
    auto start_time = std::chrono::high_resolution_clock::now();
    SearchResult result;
    
    if (!graph->hasNode(start) || !graph->hasNode(goal)) {
        return result;
    }
    
    const double INF = std::numeric_limits<double>::infinity();
    DynamicArray<double> distance(graph->getNodeCount());
    DynamicArray<int> parent(graph->getNodeCount());
    DynamicArray<bool> visited(graph->getNodeCount());
    
    // Inicializar arrays
    for (int i = 0; i < graph->getNodeCount(); i++) {
        distance.push_back(INF);
        parent.push_back(-1);
        visited.push_back(false);
    }
    
    distance[start] = 0.0;
    int nodes_explored = 0;
    
    for (int count = 0; count < graph->getNodeCount(); count++) {
        // Encontrar el nodo no visitado con menor distancia
        int u = -1;
        double min_dist = INF;
        
        for (int v = 0; v < graph->getNodeCount(); v++) {
            if (!visited[v] && distance[v] < min_dist) {
                min_dist = distance[v];
                u = v;
            }
        }
        
        if (u == -1) break; // No hay más nodos alcanzables
        
        visited[u] = true;
        nodes_explored++;
        
        if (u == goal) {
            result.path = reconstructPath(parent, start, goal);
            result.path_found = true;
            result.total_distance = distance[goal];
            break;
        }
        
        // Relajar aristas adyacentes
        const LinkedList<Edge>& adjacencies = graph->getAdjacencies(u);
        for (auto it = adjacencies.begin(); it != adjacencies.end(); ++it) {
            int v = (*it).getDestination();
            double weight = (*it).getWeight();
            
            if (!visited[v] && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                parent[v] = u;
            }
        }
    }
    
    result.nodes_explored = nodes_explored;
    auto end_time = std::chrono::high_resolution_clock::now();
    result.time_taken = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    
    return result;
}

// Best First Search (Greedy)
SearchResult SearchAlgorithms::bestFirstSearch(int start, int goal) {
    auto start_time = std::chrono::high_resolution_clock::now();
    SearchResult result;
    
    if (!graph->hasNode(start) || !graph->hasNode(goal)) {
        return result;
    }
    
    const Node* goal_node = graph->getNode(goal);
    DynamicArray<bool> visited(graph->getNodeCount());
    DynamicArray<int> parent(graph->getNodeCount());
    PriorityQueue<AStarNode> pq;
    
    // Inicializar arrays
    for (int i = 0; i < graph->getNodeCount(); i++) {
        visited.push_back(false);
        parent.push_back(-1);
    }
    
    const Node* start_node = graph->getNode(start);
    double h = calculateDistance(start_node, goal_node);
    pq.push(AStarNode(start, 0.0, h, -1));
    
    int nodes_explored = 0;
    
    while (!pq.isEmpty()) {
        AStarNode current = pq.top();
        pq.pop();
        
        if (visited[current.node_id]) continue;
        
        visited[current.node_id] = true;
        parent[current.node_id] = current.parent;
        nodes_explored++;
        
        if (current.node_id == goal) {
            result.path = reconstructPath(parent, start, goal);
            result.path_found = true;
            break;
        }
        
        const LinkedList<Edge>& adjacencies = graph->getAdjacencies(current.node_id);
        for (auto it = adjacencies.begin(); it != adjacencies.end(); ++it) {
            int neighbor = (*it).getDestination();
            if (!visited[neighbor]) {
                const Node* neighbor_node = graph->getNode(neighbor);
                double h_neighbor = calculateDistance(neighbor_node, goal_node);
                pq.push(AStarNode(neighbor, 0.0, h_neighbor, current.node_id));
            }
        }
    }
    
    // Calcular distancia total si se encontró un camino
    if (result.path_found) {
        result.total_distance = 0.0;
        for (int i = 0; i < result.path.getSize() - 1; i++) {
            result.total_distance += graph->getEdgeWeight(result.path[i], result.path[i + 1]);
        }
    }
    
    result.nodes_explored = nodes_explored;
    auto end_time = std::chrono::high_resolution_clock::now();
    result.time_taken = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    
    return result;
}

// A* Search
SearchResult SearchAlgorithms::aStar(int start, int goal) {
    auto start_time = std::chrono::high_resolution_clock::now();
    SearchResult result;
    
    if (!graph->hasNode(start) || !graph->hasNode(goal)) {
        return result;
    }
    
    const Node* goal_node = graph->getNode(goal);
    const double INF = std::numeric_limits<double>::infinity();
    
    DynamicArray<double> g_score(graph->getNodeCount());
    DynamicArray<int> parent(graph->getNodeCount());
    DynamicArray<bool> in_open_set(graph->getNodeCount());
    PriorityQueue<AStarNode> open_set;
    
    // Inicializar arrays
    for (int i = 0; i < graph->getNodeCount(); i++) {
        g_score.push_back(INF);
        parent.push_back(-1);
        in_open_set.push_back(false);
    }
    
    g_score[start] = 0.0;
    const Node* start_node = graph->getNode(start);
    double h = calculateDistance(start_node, goal_node);
    open_set.push(AStarNode(start, 0.0, h, -1));
    in_open_set[start] = true;
    
    int nodes_explored = 0;
    
    while (!open_set.isEmpty()) {
        AStarNode current = open_set.top();
        open_set.pop();
        in_open_set[current.node_id] = false;
        
        nodes_explored++;
        
        if (current.node_id == goal) {
            parent[current.node_id] = current.parent;
            result.path = reconstructPath(parent, start, goal);
            result.path_found = true;
            result.total_distance = g_score[goal];
            break;
        }
        
        const LinkedList<Edge>& adjacencies = graph->getAdjacencies(current.node_id);
        for (auto it = adjacencies.begin(); it != adjacencies.end(); ++it) {
            int neighbor = (*it).getDestination();
            double weight = (*it).getWeight();
            double tentative_g = g_score[current.node_id] + weight;
            
            if (tentative_g < g_score[neighbor]) {
                parent[neighbor] = current.node_id;
                g_score[neighbor] = tentative_g;
                
                if (!in_open_set[neighbor]) {
                    const Node* neighbor_node = graph->getNode(neighbor);
                    double h_neighbor = calculateDistance(neighbor_node, goal_node);
                    open_set.push(AStarNode(neighbor, tentative_g, h_neighbor, current.node_id));
                    in_open_set[neighbor] = true;
                }
            }
        }
    }
    
    result.nodes_explored = nodes_explored;
    auto end_time = std::chrono::high_resolution_clock::now();
    result.time_taken = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    
    return result;
}

// Método para comparar algoritmos
void SearchAlgorithms::compareAlgorithms(int start, int goal) {
    std::cout << "\n=== Comparación de Algoritmos ===" << std::endl;
    std::cout << "Desde nodo " << start << " hasta nodo " << goal << std::endl;
    
    SearchResult dfs = depthFirstSearch(start, goal);
    SearchResult bfs = breadthFirstSearch(start, goal);
    SearchResult dijkstra_result = dijkstra(start, goal);
    SearchResult best_first = bestFirstSearch(start, goal);
    SearchResult a_star = aStar(start, goal);
    
    std::cout << "\nResultados:" << std::endl;
    std::cout << "Algoritmo\t\tCamino\t\tDistancia\tNodos\tTiempo(ms)" << std::endl;
    std::cout << "DFS\t\t\t" << (dfs.path_found ? "Sí" : "No") << "\t\t" 
              << dfs.total_distance << "\t\t" << dfs.nodes_explored << "\t" 
              << dfs.time_taken.count() << std::endl;
    std::cout << "BFS\t\t\t" << (bfs.path_found ? "Sí" : "No") << "\t\t" 
              << bfs.total_distance << "\t\t" << bfs.nodes_explored << "\t" 
              << bfs.time_taken.count() << std::endl;
    std::cout << "Dijkstra\t\t" << (dijkstra_result.path_found ? "Sí" : "No") << "\t\t" 
              << dijkstra_result.total_distance << "\t\t" << dijkstra_result.nodes_explored << "\t" 
              << dijkstra_result.time_taken.count() << std::endl;
    std::cout << "Best First\t\t" << (best_first.path_found ? "Sí" : "No") << "\t\t" 
              << best_first.total_distance << "\t\t" << best_first.nodes_explored << "\t" 
              << best_first.time_taken.count() << std::endl;
    std::cout << "A*\t\t\t" << (a_star.path_found ? "Sí" : "No") << "\t\t" 
              << a_star.total_distance << "\t\t" << a_star.nodes_explored << "\t" 
              << a_star.time_taken.count() << std::endl;
}

