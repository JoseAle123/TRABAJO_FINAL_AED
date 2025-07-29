#ifndef LINKED_LIST_H
#define LINKED_LIST_H

template<typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        
        Node(const T& data) : data(data), next(nullptr) {}
    };
    
    Node* head;
    Node* tail;
    int size;
    
public:
    // Constructor
    LinkedList();
    
    // Destructor
    ~LinkedList();
    
    // Constructor de copia
    LinkedList(const LinkedList& other);
    
    // Operador de asignación
    LinkedList& operator=(const LinkedList& other);
    
    // Métodos principales
    void push_front(const T& element);
    void push_back(const T& element);
    void pop_front();
    void pop_back();
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
    
    // Información de la lista
    int getSize() const;
    bool isEmpty() const;
    void clear();
    
    // Búsqueda
    bool contains(const T& element) const;
    int indexOf(const T& element) const;
    
    // Iterador básico
    class Iterator {
    private:
        Node* current;
        
    public:
        Iterator(Node* node) : current(node) {}
        
        T& operator*() { return current->data; }
        const T& operator*() const { return current->data; }
        
        Iterator& operator++() {
            if (current) current = current->next;
            return *this;
        }
        
        bool operator==(const Iterator& other) const {
            return current == other.current;
        }
        
        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };
    
    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }
    Iterator begin() const { return Iterator(head); }
    Iterator end() const { return Iterator(nullptr); }
};

// Implementación de métodos template
template<typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), size(0) {}

template<typename T>
LinkedList<T>::~LinkedList() {
    clear();
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList& other) : head(nullptr), tail(nullptr), size(0) {
    Node* current = other.head;
    while (current) {
        push_back(current->data);
        current = current->next;
    }
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& other) {
    if (this != &other) {
        clear();
        Node* current = other.head;
        while (current) {
            push_back(current->data);
            current = current->next;
        }
    }
    return *this;
}

template<typename T>
void LinkedList<T>::push_front(const T& element) {
    Node* new_node = new Node(element);
    if (isEmpty()) {
        head = tail = new_node;
    } else {
        new_node->next = head;
        head = new_node;
    }
    size++;
}

template<typename T>
void LinkedList<T>::push_back(const T& element) {
    Node* new_node = new Node(element);
    if (isEmpty()) {
        head = tail = new_node;
    } else {
        tail->next = new_node;
        tail = new_node;
    }
    size++;
}

template<typename T>
void LinkedList<T>::pop_front() {
    if (!isEmpty()) {
        Node* to_delete = head;
        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        }
        delete to_delete;
        size--;
    }
}

template<typename T>
void LinkedList<T>::pop_back() {
    if (!isEmpty()) {
        if (head == tail) {
            delete head;
            head = tail = nullptr;
        } else {
            Node* current = head;
            while (current->next != tail) {
                current = current->next;
            }
            delete tail;
            tail = current;
            tail->next = nullptr;
        }
        size--;
    }
}

template<typename T>
T& LinkedList<T>::front() {
    if (isEmpty()) {
        throw "List is empty";
    }
    return head->data;
}

template<typename T>
const T& LinkedList<T>::front() const {
    if (isEmpty()) {
        throw "List is empty";
    }
    return head->data;
}

template<typename T>
T& LinkedList<T>::back() {
    if (isEmpty()) {
        throw "List is empty";
    }
    return tail->data;
}

template<typename T>
const T& LinkedList<T>::back() const {
    if (isEmpty()) {
        throw "List is empty";
    }
    return tail->data;
}

template<typename T>
int LinkedList<T>::getSize() const {
    return size;
}

template<typename T>
bool LinkedList<T>::isEmpty() const {
    return size == 0;
}

template<typename T>
void LinkedList<T>::clear() {
    while (!isEmpty()) {
        pop_front();
    }
}

template<typename T>
bool LinkedList<T>::contains(const T& element) const {
    Node* current = head;
    while (current) {
        if (current->data == element) {
            return true;
        }
        current = current->next;
    }
    return false;
}

template<typename T>
int LinkedList<T>::indexOf(const T& element) const {
    Node* current = head;
    int index = 0;
    while (current) {
        if (current->data == element) {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1;
}

#endif // LINKED_LIST_H

