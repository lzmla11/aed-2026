#include <iostream>
#include <stdexcept>

using namespace std;

template<class T>
class Stack {
    struct node {
        T data;
        node* next;
        node(T d, node* n = nullptr) : data(d), next(n) {}
    };
    
    node* head = nullptr;
    int current_size = 0;

public:
    Stack() = default;
    
    ~Stack() {
        clear();
    }

    void clear() {
        while (!empty()) {
            pop();
        }
    }

    bool empty() const {
        return head == nullptr; 
    }

    int size() const {
        return current_size;
    }

    void push(const T& x) {
        head = new node(x, head);
        current_size++;
    }

    void pop() {
        if (empty()) return; 
        node* temp = head;
        head = head->next;
        delete temp;
        current_size--;
    }

    T top() const {
        if (empty()) {
            throw runtime_error("La pila esta vacia");
        }
        return head->data;
    }

    friend ostream& operator<<(ostream& os, const Stack<T>& s) {
        os << "Tope -> ";
        for (node* n = s.head; n != nullptr; n = n->next) {
            os << n->data << " -> ";
        }
        os << "Base";
        return os;
    }
};
