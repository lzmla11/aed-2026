#include <iostream>
#include <stdexcept>

using namespace std;

template<class T>
class Deque {
    struct node {
        T data;
        node* prev;
        node* next;
        node(T d, node* p = nullptr, node* n = nullptr) : data(d), prev(p), next(n) {}
    };
    
    node* head = nullptr; 
    node* tail = nullptr; 
    int current_size = 0;

public:
    Deque() = default;
    
    ~Deque() {
        clear();
    }

    void clear() {
        while (!empty()) {
            pop_front();
        }
    }

    bool empty() const {
        return head == nullptr;
    }

    int size() const {
        return current_size;
    }

    void push_front(const T& x) {
        node* new_node = new node(x, nullptr, head);
        if (empty()) {
            tail = new_node;
        } else {
            head->prev = new_node;
        }
        head = new_node;
        current_size++;
    }

    void push_back(const T& x) {
        node* new_node = new node(x, tail, nullptr);
        if (empty()) {
            head = new_node;
        } else {
            tail->next = new_node;
        }
        tail = new_node;
        current_size++;
    }

    void pop_front() {
        if (empty()) return;
        node* temp = head;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete temp;
        current_size--;
    }

    void pop_back() {
        if (empty()) return;
        node* temp = tail;
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete temp;
        current_size--;
    }
    
    T front() const {
        if (empty()) throw runtime_error("El deque esta vacio");
        return head->data;
    }

    T back() const {
        if (empty()) throw runtime_error("El deque esta vacio");
        return tail->data;
    }

    friend ostream& operator<<(ostream& os, const Deque<T>& dq) {
        os << "Frente -> ";
        for (node* n = dq.head; n != nullptr; n = n->next) {
            os << n->data << " <-> ";
        }
        os << "Final";
        return os;
    }
};
