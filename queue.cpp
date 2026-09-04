#include <iostream>
#include <stdexcept>

using namespace std;

template<class T>
class Queue {
    struct node {
        T data;
        node* next;
        node(T d, node* n = nullptr) : data(d), next(n) {}
    };
    
    node* head = nullptr; 
    node* tail = nullptr; 
    int current_size = 0;

public:
    Queue() = default;
    
    ~Queue() {
        clear();
    }

    void clear() {
        while (!empty()) {
            dequeue();
        }
    }

    bool empty() const {
        return head == nullptr;
    }

    int size() const {
        return current_size;
    }

    void enqueue(const T& x) {
        node* new_node = new node(x, nullptr);
        if (empty()) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
        current_size++;
    }

    void dequeue() {
        if (empty()) return;
        node* temp = head;
        head = head->next;
        delete temp;
        
        if (head == nullptr) {
            tail = nullptr;
        }
        current_size--;
    }

    T front() const {
        if (empty()) {
            throw runtime_error("La cola esta vacia");
        }
        return head->data;
    }

    T back() const {
        if (empty()) {
            throw runtime_error("La cola esta vacia");
        }
        return tail->data;
    }

    friend ostream& operator<<(ostream& os, const Queue<T>& q) {
        os << "Frente -> ";
        for (node* n = q.head; n != nullptr; n = n->next) {
            os << n->data << " -> ";
        }
        os << "Final";
        return os;
    }
};
