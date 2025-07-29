#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "dynamic_array.h"

template<typename T>
class PriorityQueue {
private:
    DynamicArray<T> heap;
    
    // Funciones auxiliares para el heap
    int parent(int index) const;
    int leftChild(int index) const;
    int rightChild(int index) const;
    void heapifyUp(int index);
    void heapifyDown(int index);
    void swap(int i, int j);
    
public:
    // Constructor
    PriorityQueue();
    
    // Destructor
    ~PriorityQueue() = default;
    
    // Métodos principales
    void push(const T& element);
    void pop();
    T& top();
    const T& top() const;
    
    // Información de la cola de prioridad
    int getSize() const;
    bool isEmpty() const;
    void clear();
};

// Implementación de métodos template
template<typename T>
PriorityQueue<T>::PriorityQueue() {}

template<typename T>
int PriorityQueue<T>::parent(int index) const {
    return (index - 1) / 2;
}

template<typename T>
int PriorityQueue<T>::leftChild(int index) const {
    return 2 * index + 1;
}

template<typename T>
int PriorityQueue<T>::rightChild(int index) const {
    return 2 * index + 2;
}

template<typename T>
void PriorityQueue<T>::swap(int i, int j) {
    T temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
}

template<typename T>
void PriorityQueue<T>::heapifyUp(int index) {
    while (index > 0 && heap[parent(index)] > heap[index]) {
        swap(index, parent(index));
        index = parent(index);
    }
}

template<typename T>
void PriorityQueue<T>::heapifyDown(int index) {
    int minIndex = index;
    int left = leftChild(index);
    int right = rightChild(index);
    
    if (left < heap.getSize() && heap[left] < heap[minIndex]) {
        minIndex = left;
    }
    
    if (right < heap.getSize() && heap[right] < heap[minIndex]) {
        minIndex = right;
    }
    
    if (index != minIndex) {
        swap(index, minIndex);
        heapifyDown(minIndex);
    }
}

template<typename T>
void PriorityQueue<T>::push(const T& element) {
    heap.push_back(element);
    heapifyUp(heap.getSize() - 1);
}

template<typename T>
void PriorityQueue<T>::pop() {
    if (!isEmpty()) {
        heap[0] = heap[heap.getSize() - 1];
        heap.pop_back();
        if (!isEmpty()) {
            heapifyDown(0);
        }
    }
}

template<typename T>
T& PriorityQueue<T>::top() {
    if (isEmpty()) {
        throw "Priority queue is empty";
    }
    return heap[0];
}

template<typename T>
const T& PriorityQueue<T>::top() const {
    if (isEmpty()) {
        throw "Priority queue is empty";
    }
    return heap[0];
}

template<typename T>
int PriorityQueue<T>::getSize() const {
    return heap.getSize();
}

template<typename T>
bool PriorityQueue<T>::isEmpty() const {
    return heap.isEmpty();
}

template<typename T>
void PriorityQueue<T>::clear() {
    heap.clear();
}

#endif // PRIORITY_QUEUE_H

