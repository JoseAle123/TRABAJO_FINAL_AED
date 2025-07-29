#ifndef QUEUE_H
#define QUEUE_H

template<typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        
        Node(const T& data) : data(data), next(nullptr) {}
    };
    
    Node* front_node;
    Node* rear_node;
    int size;
    
public:
    // Constructor
    Queue();
    
    // Destructor
    ~Queue();
    
    // Constructor de copia
    Queue(const Queue& other);
    
    // Operador de asignación
    Queue& operator=(const Queue& other);
    
    // Métodos principales
    void enqueue(const T& element);
    void dequeue();
    T& front();
    const T& front() const;
    T& rear();
    const T& rear() const;
    
    // Información de la cola
    int getSize() const;
    bool isEmpty() const;
    void clear();
};

// Implementación de métodos template
template<typename T>
Queue<T>::Queue() : front_node(nullptr), rear_node(nullptr), size(0) {}

template<typename T>
Queue<T>::~Queue() {
    clear();
}

template<typename T>
Queue<T>::Queue(const Queue& other) : front_node(nullptr), rear_node(nullptr), size(0) {
    Node* current = other.front_node;
    while (current) {
        enqueue(current->data);
        current = current->next;
    }
}

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue& other) {
    if (this != &other) {
        clear();
        Node* current = other.front_node;
        while (current) {
            enqueue(current->data);
            current = current->next;
        }
    }
    return *this;
}

template<typename T>
void Queue<T>::enqueue(const T& element) {
    Node* new_node = new Node(element);
    if (isEmpty()) {
        front_node = rear_node = new_node;
    } else {
        rear_node->next = new_node;
        rear_node = new_node;
    }
    size++;
}

template<typename T>
void Queue<T>::dequeue() {
    if (!isEmpty()) {
        Node* to_delete = front_node;
        front_node = front_node->next;
        if (front_node == nullptr) {
            rear_node = nullptr;
        }
        delete to_delete;
        size--;
    }
}

template<typename T>
T& Queue<T>::front() {
    if (isEmpty()) {
        throw "Queue is empty";
    }
    return front_node->data;
}

template<typename T>
const T& Queue<T>::front() const {
    if (isEmpty()) {
        throw "Queue is empty";
    }
    return front_node->data;
}

template<typename T>
T& Queue<T>::rear() {
    if (isEmpty()) {
        throw "Queue is empty";
    }
    return rear_node->data;
}

template<typename T>
const T& Queue<T>::rear() const {
    if (isEmpty()) {
        throw "Queue is empty";
    }
    return rear_node->data;
}

template<typename T>
int Queue<T>::getSize() const {
    return size;
}

template<typename T>
bool Queue<T>::isEmpty() const {
    return size == 0;
}

template<typename T>
void Queue<T>::clear() {
    while (!isEmpty()) {
        dequeue();
    }
}

#endif // QUEUE_H

