#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

template<typename T>
class DynamicArray {
private:
    T* data;
    int capacity;
    int size;
    
    void resize();
    
public:
    // Constructor
    DynamicArray(int initial_capacity = 10);
    
    // Destructor
    ~DynamicArray();
    
    // Constructor de copia
    DynamicArray(const DynamicArray& other);
    
    // Operador de asignación
    DynamicArray& operator=(const DynamicArray& other);
    
    // Métodos principales
    void push_back(const T& element);
    void pop_back();
    T& at(int index);
    const T& at(int index) const;
    T& operator[](int index);
    const T& operator[](int index) const;
    
    // Información del array
    int getSize() const;
    int getCapacity() const;
    bool isEmpty() const;
    void clear();
    
    // Iteradores básicos
    T* begin();
    T* end();
    const T* begin() const;
    const T* end() const;
};

// Implementación de métodos template
template<typename T>
DynamicArray<T>::DynamicArray(int initial_capacity) 
    : capacity(initial_capacity), size(0) {
    data = new T[capacity];
}

template<typename T>
DynamicArray<T>::~DynamicArray() {
    delete[] data;
}

template<typename T>
DynamicArray<T>::DynamicArray(const DynamicArray& other) 
    : capacity(other.capacity), size(other.size) {
    data = new T[capacity];
    for (int i = 0; i < size; i++) {
        data[i] = other.data[i];
    }
}

template<typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray& other) {
    if (this != &other) {
        delete[] data;
        capacity = other.capacity;
        size = other.size;
        data = new T[capacity];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }
    return *this;
}

template<typename T>
void DynamicArray<T>::resize() {
    capacity *= 2;
    T* new_data = new T[capacity];
    for (int i = 0; i < size; i++) {
        new_data[i] = data[i];
    }
    delete[] data;
    data = new_data;
}

template<typename T>
void DynamicArray<T>::push_back(const T& element) {
    if (size >= capacity) {
        resize();
    }
    data[size++] = element;
}

template<typename T>
void DynamicArray<T>::pop_back() {
    if (size > 0) {
        size--;
    }
}

template<typename T>
T& DynamicArray<T>::at(int index) {
    if (index < 0 || index >= size) {
        throw "Index out of bounds";
    }
    return data[index];
}

template<typename T>
const T& DynamicArray<T>::at(int index) const {
    if (index < 0 || index >= size) {
        throw "Index out of bounds";
    }
    return data[index];
}

template<typename T>
T& DynamicArray<T>::operator[](int index) {
    return data[index];
}

template<typename T>
const T& DynamicArray<T>::operator[](int index) const {
    return data[index];
}

template<typename T>
int DynamicArray<T>::getSize() const {
    return size;
}

template<typename T>
int DynamicArray<T>::getCapacity() const {
    return capacity;
}

template<typename T>
bool DynamicArray<T>::isEmpty() const {
    return size == 0;
}

template<typename T>
void DynamicArray<T>::clear() {
    size = 0;
}

template<typename T>
T* DynamicArray<T>::begin() {
    return data;
}

template<typename T>
T* DynamicArray<T>::end() {
    return data + size;
}

template<typename T>
const T* DynamicArray<T>::begin() const {
    return data;
}

template<typename T>
const T* DynamicArray<T>::end() const {
    return data + size;
}

#endif // DYNAMIC_ARRAY_H

