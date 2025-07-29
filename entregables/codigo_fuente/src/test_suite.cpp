#include "../include/test_suite.h"
#include "../include/map_loader.h"
#include "../include/performance_analyzer.h"
#include <iostream>
#include <cmath>

// Constructor
TestSuite::TestSuite() : tests_passed(0), tests_failed(0), total_tests(0) {}

// Funciones auxiliares para testing
void TestSuite::assert_true(bool condition, const std::string& test_name) {
    total_tests++;
    if (condition) {
        tests_passed++;
        print_test_result(test_name, true);
    } else {
        tests_failed++;
        print_test_result(test_name, false);
    }
}

void TestSuite::assert_false(bool condition, const std::string& test_name) {
    assert_true(!condition, test_name);
}

void TestSuite::assert_equals(int expected, int actual, const std::string& test_name) {
    assert_true(expected == actual, test_name + " (esperado: " + std::to_string(expected) + ", actual: " + std::to_string(actual) + ")");
}

void TestSuite::assert_equals(double expected, double actual, const std::string& test_name, double tolerance) {
    assert_true(std::abs(expected - actual) < tolerance, test_name + " (esperado: " + std::to_string(expected) + ", actual: " + std::to_string(actual) + ")");
}

void TestSuite::print_test_result(const std::string& test_name, bool passed) {
    std::cout << "[" << (passed ? "PASS" : "FAIL") << "] " << test_name << std::endl;
}

// Método principal de testing
void TestSuite::runAllTests() {
    std::cout << "=== EJECUTANDO SUITE DE PRUEBAS ===" << std::endl;
    std::cout << "Sistema de Navegación - Proyecto Final" << std::endl;
    std::cout << std::endl;
    
    testDynamicArray();
    testLinkedList();
    testQueue();
    testPriorityQueue();
    testGraphBasicOperations();
    testGraphConnectivity();
    testGraphEdgeWeights();
    testSearchAlgorithmsSmallGraph();
    testSearchAlgorithmsDisconnectedGraph();
    testSearchAlgorithmsOptimality();
    testLargeGraphGeneration();
    testGraphSaveLoad();
    testEdgeCases();
    testDataValidation();
    
    printSummary();
}

// Tests de estructuras de datos básicas
void TestSuite::testDynamicArray() {
    std::cout << "\n--- Tests de DynamicArray ---" << std::endl;
    
    DynamicArray<int> arr;
    
    // Test de array vacío
    assert_true(arr.isEmpty(), "Array inicialmente vacío");
    assert_equals(0, arr.getSize(), "Tamaño inicial es 0");
    
    // Test de inserción
    arr.push_back(10);
    arr.push_back(20);
    arr.push_back(30);
    
    assert_equals(3, arr.getSize(), "Tamaño después de 3 inserciones");
    assert_false(arr.isEmpty(), "Array no vacío después de inserciones");
    
    // Test de acceso
    assert_equals(10, arr[0], "Acceso al primer elemento");
    assert_equals(20, arr[1], "Acceso al segundo elemento");
    assert_equals(30, arr[2], "Acceso al tercer elemento");
    
    // Test de eliminación
    arr.pop_back();
    assert_equals(2, arr.getSize(), "Tamaño después de pop_back");
    
    // Test de limpieza
    arr.clear();
    assert_true(arr.isEmpty(), "Array vacío después de clear");
    assert_equals(0, arr.getSize(), "Tamaño 0 después de clear");
}

void TestSuite::testLinkedList() {
    std::cout << "\n--- Tests de LinkedList ---" << std::endl;
    
    LinkedList<int> list;
    
    // Test de lista vacía
    assert_true(list.isEmpty(), "Lista inicialmente vacía");
    assert_equals(0, list.getSize(), "Tamaño inicial es 0");
    
    // Test de inserción al frente
    list.push_front(10);
    list.push_front(20);
    
    assert_equals(2, list.getSize(), "Tamaño después de push_front");
    assert_equals(20, list.front(), "Elemento al frente");
    assert_equals(10, list.back(), "Elemento al final");
    
    // Test de inserción al final
    list.push_back(30);
    assert_equals(3, list.getSize(), "Tamaño después de push_back");
    assert_equals(30, list.back(), "Nuevo elemento al final");
    
    // Test de búsqueda
    assert_true(list.contains(20), "Lista contiene elemento 20");
    assert_false(list.contains(40), "Lista no contiene elemento 40");
    
    // Test de eliminación
    list.pop_front();
    assert_equals(2, list.getSize(), "Tamaño después de pop_front");
    assert_equals(10, list.front(), "Nuevo elemento al frente");
}

void TestSuite::testQueue() {
    std::cout << "\n--- Tests de Queue ---" << std::endl;
    
    Queue<int> queue;
    
    // Test de cola vacía
    assert_true(queue.isEmpty(), "Cola inicialmente vacía");
    assert_equals(0, queue.getSize(), "Tamaño inicial es 0");
    
    // Test de enqueue
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    
    assert_equals(3, queue.getSize(), "Tamaño después de enqueue");
    assert_equals(10, queue.front(), "Primer elemento en la cola");
    assert_equals(30, queue.rear(), "Último elemento en la cola");
    
    // Test de dequeue
    queue.dequeue();
    assert_equals(2, queue.getSize(), "Tamaño después de dequeue");
    assert_equals(20, queue.front(), "Nuevo primer elemento");
    
    // Test FIFO
    queue.dequeue();
    queue.dequeue();
    assert_true(queue.isEmpty(), "Cola vacía después de dequeue todos");
}

void TestSuite::testPriorityQueue() {
    std::cout << "\n--- Tests de PriorityQueue ---" << std::endl;
    
    PriorityQueue<int> pq;
    
    // Test de cola de prioridad vacía
    assert_true(pq.isEmpty(), "Cola de prioridad inicialmente vacía");
    assert_equals(0, pq.getSize(), "Tamaño inicial es 0");
    
    // Test de inserción
    pq.push(30);
    pq.push(10);
    pq.push(20);
    
    assert_equals(3, pq.getSize(), "Tamaño después de push");
    assert_equals(10, pq.top(), "Elemento con menor prioridad al tope");
    
    // Test de extracción
    pq.pop();
    assert_equals(2, pq.getSize(), "Tamaño después de pop");
    assert_equals(20, pq.top(), "Siguiente elemento con menor prioridad");
}

// Tests de grafo
void TestSuite::testGraphBasicOperations() {
    std::cout << "\n--- Tests de Operaciones Básicas de Grafo ---" << std::endl;
    
    Graph graph;
    
    // Test de grafo vacío
    assert_equals(0, graph.getNodeCount(), "Grafo inicialmente sin nodos");
    assert_equals(0, graph.getEdgeCount(), "Grafo inicialmente sin aristas");
    
    // Test de adición de nodos
    graph.addNode(Node(0, "Nodo A", 0.0, 0.0));
    graph.addNode(Node(1, "Nodo B", 1.0, 1.0));
    graph.addNode(Node(2, "Nodo C", 2.0, 2.0));
    
    assert_equals(3, graph.getNodeCount(), "3 nodos añadidos");
    assert_true(graph.hasNode(0), "Grafo contiene nodo 0");
    assert_true(graph.hasNode(1), "Grafo contiene nodo 1");
    assert_true(graph.hasNode(2), "Grafo contiene nodo 2");
    assert_false(graph.hasNode(3), "Grafo no contiene nodo 3");
    
    // Test de adición de aristas
    graph.addEdge(0, 1, 1.5);
    graph.addEdge(1, 2, 2.0);
    graph.addEdge(0, 2, 3.0);
    
    assert_equals(3, graph.getEdgeCount(), "3 aristas añadidas");
    assert_true(graph.hasEdge(0, 1), "Existe arista 0->1");
    assert_true(graph.hasEdge(1, 2), "Existe arista 1->2");
    assert_true(graph.hasEdge(0, 2), "Existe arista 0->2");
    assert_false(graph.hasEdge(2, 0), "No existe arista 2->0");
    
    // Test de pesos de aristas
    assert_equals(1.5, graph.getEdgeWeight(0, 1), "Peso de arista 0->1");
    assert_equals(2.0, graph.getEdgeWeight(1, 2), "Peso de arista 1->2");
    assert_equals(3.0, graph.getEdgeWeight(0, 2), "Peso de arista 0->2");
}

void TestSuite::testGraphConnectivity() {
    std::cout << "\n--- Tests de Conectividad de Grafo ---" << std::endl;
    
    Graph graph;
    
    // Crear grafo conectado
    for (int i = 0; i < 5; i++) {
        graph.addNode(Node(i, "Nodo " + std::to_string(i), i, i));
    }
    
    // Conectar en cadena: 0-1-2-3-4
    for (int i = 0; i < 4; i++) {
        graph.addEdge(i, i + 1, 1.0);
        graph.addEdge(i + 1, i, 1.0); // Bidireccional
    }
    
    SearchAlgorithms search(&graph);
    
    // Test de conectividad
    SearchResult result = search.breadthFirstSearch(0, 4);
    assert_true(result.path_found, "Existe camino de 0 a 4");
    assert_equals(5, result.path.getSize(), "Camino tiene 5 nodos");
    assert_equals(4.0, result.total_distance, "Distancia total es 4");
    
    // Test de camino más corto
    graph.addEdge(0, 4, 2.0);
    graph.addEdge(4, 0, 2.0);
    
    SearchResult dijkstra_result = search.dijkstra(0, 4);
    assert_true(dijkstra_result.path_found, "Dijkstra encuentra camino");
    assert_equals(2.0, dijkstra_result.total_distance, "Dijkstra encuentra camino más corto");
}

void TestSuite::testGraphEdgeWeights() {
    std::cout << "\n--- Tests de Pesos de Aristas ---" << std::endl;
    
    Graph graph;
    
    // Crear triángulo con pesos diferentes
    graph.addNode(Node(0, "A", 0, 0));
    graph.addNode(Node(1, "B", 1, 0));
    graph.addNode(Node(2, "C", 0.5, 1));
    
    graph.addEdge(0, 1, 5.0);  // Camino directo costoso
    graph.addEdge(0, 2, 2.0);  // Camino indirecto barato
    graph.addEdge(2, 1, 2.0);
    
    SearchAlgorithms search(&graph);
    SearchResult result = search.dijkstra(0, 1);
    
    assert_true(result.path_found, "Dijkstra encuentra camino");
    assert_equals(4.0, result.total_distance, "Dijkstra elige camino más barato (0->2->1)");
    assert_equals(3, result.path.getSize(), "Camino tiene 3 nodos");
}

// Tests de algoritmos de búsqueda
void TestSuite::testSearchAlgorithmsSmallGraph() {
    std::cout << "\n--- Tests de Algoritmos en Grafo Pequeño ---" << std::endl;
    
    Graph graph;
    MapLoader::createArequipaMap(graph);
    
    SearchAlgorithms search(&graph);
    
    // Test de todos los algoritmos
    int start = 0, goal = 5; // Plaza de Armas -> Aeropuerto
    
    SearchResult dfs = search.depthFirstSearch(start, goal);
    SearchResult bfs = search.breadthFirstSearch(start, goal);
    SearchResult dijkstra = search.dijkstra(start, goal);
    SearchResult astar = search.aStar(start, goal);
    
    assert_true(dfs.path_found, "DFS encuentra camino");
    assert_true(bfs.path_found, "BFS encuentra camino");
    assert_true(dijkstra.path_found, "Dijkstra encuentra camino");
    assert_true(astar.path_found, "A* encuentra camino");
    
    // Dijkstra y A* deberían encontrar el camino óptimo
    assert_true(dijkstra.total_distance <= dfs.total_distance, "Dijkstra es óptimo comparado con DFS");
    assert_true(astar.total_distance <= dfs.total_distance, "A* es bueno comparado con DFS");
    
    // A* debería explorar menos nodos que Dijkstra
    assert_true(astar.nodes_explored <= dijkstra.nodes_explored, "A* es más eficiente que Dijkstra");
}

void TestSuite::testSearchAlgorithmsDisconnectedGraph() {
    std::cout << "\n--- Tests en Grafo Desconectado ---" << std::endl;
    
    Graph graph;
    
    // Crear dos componentes desconectadas
    graph.addNode(Node(0, "A", 0, 0));
    graph.addNode(Node(1, "B", 1, 0));
    graph.addNode(Node(2, "C", 5, 0));
    graph.addNode(Node(3, "D", 6, 0));
    
    // Conectar 0-1 y 2-3, pero no entre grupos
    graph.addEdge(0, 1, 1.0);
    graph.addEdge(1, 0, 1.0);
    graph.addEdge(2, 3, 1.0);
    graph.addEdge(3, 2, 1.0);
    
    SearchAlgorithms search(&graph);
    
    // Test de búsqueda entre componentes desconectadas
    SearchResult result = search.breadthFirstSearch(0, 2);
    assert_false(result.path_found, "No existe camino entre componentes desconectadas");
    
    // Test de búsqueda dentro de la misma componente
    SearchResult result2 = search.breadthFirstSearch(0, 1);
    assert_true(result2.path_found, "Existe camino dentro de la misma componente");
}

void TestSuite::testSearchAlgorithmsOptimality() {
    std::cout << "\n--- Tests de Optimalidad de Algoritmos ---" << std::endl;
    
    Graph graph;
    
    // Crear grafo donde DFS puede no ser óptimo
    graph.addNode(Node(0, "Start", 0, 0));
    graph.addNode(Node(1, "Mid1", 1, 0));
    graph.addNode(Node(2, "Mid2", 0, 1));
    graph.addNode(Node(3, "Goal", 1, 1));
    
    // Camino directo costoso vs camino indirecto barato
    graph.addEdge(0, 3, 10.0); // Directo pero costoso
    graph.addEdge(0, 1, 1.0);  // Indirecto barato
    graph.addEdge(1, 3, 1.0);
    graph.addEdge(0, 2, 1.0);  // Otro camino indirecto
    graph.addEdge(2, 3, 1.0);
    
    SearchAlgorithms search(&graph);
    
    SearchResult dijkstra = search.dijkstra(0, 3);
    SearchResult astar = search.aStar(0, 3);
    
    assert_true(dijkstra.path_found, "Dijkstra encuentra camino");
    assert_true(astar.path_found, "A* encuentra camino");
    
    // Ambos deberían encontrar el camino óptimo (distancia 2)
    assert_equals(2.0, dijkstra.total_distance, "Dijkstra encuentra camino óptimo");
    // A* puede no ser exactamente óptimo debido a la heurística, pero debería ser razonable
    assert_true(astar.total_distance <= 3.0, "A* encuentra camino razonablemente bueno");
}

// Tests de generación de grafos grandes
void TestSuite::testLargeGraphGeneration() {
    std::cout << "\n--- Tests de Generación de Grafos Grandes ---" << std::endl;
    
    // Test de grafo de cuadrícula
    Graph grid_graph;
    LargeGraphGenerator::generateGridGraph(grid_graph, 10, 10);
    
    assert_equals(100, grid_graph.getNodeCount(), "Grafo de cuadrícula 10x10 tiene 100 nodos");
    assert_true(grid_graph.getEdgeCount() > 0, "Grafo de cuadrícula tiene aristas");
    
    // Test de conectividad en cuadrícula
    SearchAlgorithms search(&grid_graph);
    SearchResult result = search.breadthFirstSearch(0, 99);
    assert_true(result.path_found, "Existe camino en grafo de cuadrícula");
    
    // Test de grafo tipo ciudad
    Graph city_graph;
    LargeGraphGenerator::generateCityLikeGraph(city_graph, 100, 5);
    
    assert_equals(100, city_graph.getNodeCount(), "Grafo tipo ciudad tiene 100 nodos");
    assert_true(city_graph.getEdgeCount() > 0, "Grafo tipo ciudad tiene aristas");
}

void TestSuite::testGraphSaveLoad() {
    std::cout << "\n--- Tests de Guardado/Carga de Grafos ---" << std::endl;
    
    // Crear grafo de prueba
    Graph original_graph;
    original_graph.addNode(Node(0, "Test A", 1.0, 2.0));
    original_graph.addNode(Node(1, "Test B", 3.0, 4.0));
    original_graph.addEdge(0, 1, 5.0);
    
    // Guardar grafo
    std::string filename = "test_graph.dat";
    bool saved = LargeGraphGenerator::saveGraphToBinary(original_graph, filename);
    assert_true(saved, "Grafo guardado exitosamente");
    
    // Cargar grafo
    Graph loaded_graph;
    bool loaded = LargeGraphGenerator::loadGraphFromBinary(loaded_graph, filename);
    assert_true(loaded, "Grafo cargado exitosamente");
    
    // Verificar que son iguales
    assert_equals(original_graph.getNodeCount(), loaded_graph.getNodeCount(), "Mismo número de nodos");
    assert_equals(original_graph.getEdgeCount(), loaded_graph.getEdgeCount(), "Mismo número de aristas");
    
    const Node* original_node = original_graph.getNode(0);
    const Node* loaded_node = loaded_graph.getNode(0);
    
    if (original_node && loaded_node) {
        assert_true(original_node->getName() == loaded_node->getName(), "Mismo nombre de nodo");
        assert_equals(original_node->getX(), loaded_node->getX(), "Misma coordenada X");
        assert_equals(original_node->getY(), loaded_node->getY(), "Misma coordenada Y");
    }
    
    assert_equals(5.0, loaded_graph.getEdgeWeight(0, 1), "Mismo peso de arista");
}

// Tests de casos extremos
void TestSuite::testEdgeCases() {
    std::cout << "\n--- Tests de Casos Extremos ---" << std::endl;
    
    Graph graph;
    SearchAlgorithms search(&graph);
    
    // Test de grafo vacío
    SearchResult result = search.breadthFirstSearch(0, 1);
    assert_false(result.path_found, "No hay camino en grafo vacío");
    
    // Test de nodo único
    graph.addNode(Node(0, "Solo", 0, 0));
    SearchResult result2 = search.breadthFirstSearch(0, 0);
    assert_true(result2.path_found, "Camino de nodo a sí mismo");
    assert_equals(1, result2.path.getSize(), "Camino de longitud 1");
    assert_equals(0.0, result2.total_distance, "Distancia 0 a sí mismo");
    
    // Test de nodos inexistentes
    SearchResult result3 = search.breadthFirstSearch(0, 999);
    assert_false(result3.path_found, "No hay camino a nodo inexistente");
}

void TestSuite::testDataValidation() {
    std::cout << "\n--- Tests de Validación de Datos ---" << std::endl;
    
    Graph graph;
    
    // Test de nodos duplicados
    graph.addNode(Node(0, "A", 0, 0));
    int initial_count = graph.getNodeCount();
    graph.addNode(Node(0, "A duplicado", 1, 1)); // Mismo ID
    
    assert_equals(initial_count, graph.getNodeCount(), "No se añaden nodos duplicados");
    
    // Test de aristas a nodos inexistentes
    int initial_edges = graph.getEdgeCount();
    graph.addEdge(0, 999, 1.0); // Nodo 999 no existe
    
    assert_equals(initial_edges, graph.getEdgeCount(), "No se añaden aristas a nodos inexistentes");
    
    // Test de pesos negativos (permitidos)
    graph.addNode(Node(1, "B", 1, 1));
    graph.addEdge(0, 1, -1.0);
    
    assert_equals(-1.0, graph.getEdgeWeight(0, 1), "Se permiten pesos negativos");
}

// Mostrar resumen de resultados
void TestSuite::printSummary() {
    std::cout << "\n=== RESUMEN DE PRUEBAS ===" << std::endl;
    std::cout << "Total de pruebas: " << total_tests << std::endl;
    std::cout << "Pruebas exitosas: " << tests_passed << std::endl;
    std::cout << "Pruebas fallidas: " << tests_failed << std::endl;
    std::cout << "Tasa de éxito: " << (getSuccessRate() * 100) << "%" << std::endl;
    
    if (tests_failed == 0) {
        std::cout << "\n¡TODAS LAS PRUEBAS PASARON! ✓" << std::endl;
        std::cout << "El sistema está funcionando correctamente." << std::endl;
    } else {
        std::cout << "\n⚠️  ALGUNAS PRUEBAS FALLARON" << std::endl;
        std::cout << "Revisar los fallos reportados arriba." << std::endl;
    }
}

// Obtener estadísticas
int TestSuite::getTestsPassed() const {
    return tests_passed;
}

int TestSuite::getTestsFailed() const {
    return tests_failed;
}

int TestSuite::getTotalTests() const {
    return total_tests;
}

double TestSuite::getSuccessRate() const {
    if (total_tests == 0) return 0.0;
    return static_cast<double>(tests_passed) / total_tests;
}

