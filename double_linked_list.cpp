#include <iostream>
#include <utility> // Para std::swap

using namespace std;

template<class T>
class double_linked_list {
public: 
    struct node {
        T data; 
        node* prev = nullptr; 
        node* next = nullptr; 
        node(T i, node* p = nullptr, node* n = nullptr) : data(i), prev(p), next(n) {}; 
    }; 

private:
    node* head = nullptr; 
    node* tail = nullptr; 
    int list_size = 0; 

public:
    double_linked_list() = default; 

    ~double_linked_list() {
        clear();
    }

    void clear() {
        while (head != nullptr) {
            pop_front();
        }
    }

    bool empty() const { return list_size == 0; }
    int size() const { return list_size; }
    node* begin() const { return head; }
    node* end() const { return tail; }

    void push_front(const T& d) {
        node* new_node = new node(d, nullptr, head);
        if (head != nullptr) {
            head->prev = new_node;
        }
        head = new_node; 
        ++list_size; 
        if (list_size == 1) {
            tail = head; 
        }
    }

    void push_back(const T& d) {
        node* new_node = new node(d, tail, nullptr);  
        if (tail != nullptr) {
            tail->next = new_node; 
        }
        tail = new_node; 
        ++list_size;
        if (list_size == 1) {
            head = tail; 
        }
    }

    void pop_front() {
        if (!head) return; 

        node* tmp = head; 
        head = head->next; 
        if (head != nullptr) { 
            head->prev = nullptr; 
        } else {
            tail = nullptr; 
        }
        delete tmp; 
        --list_size; 
    }

    void pop_back() {
        if (!tail) return; 

        node* tmp = tail; 
        tail = tail->prev; 
        if (tail != nullptr) {
            tail->next = nullptr; 
        } else {
            head = nullptr; 
        }
        delete tmp; 
        --list_size; 
    }
    
    node* search(const T& d) {
        node* n = head; 
        while (n && n->data != d) {
            n = n->next; 
        }
        return n; 
    }

    void remove(node* n) {
        if (n == nullptr) return;

        if (n == head) {
            pop_front(); 
        } else if (n == tail) {
            pop_back(); 
        } else {
            n->next->prev = n->prev; 
            n->prev->next = n->next; 
            delete n; 
            --list_size; 
        }
    }

    void insert(const T& d, node* n) { 
        if (n == nullptr) return; 

        if (n == head) {
            push_front(d); 
        } else {
            node* new_node = new node(d, n->prev, n); 
            n->prev->next = new_node; 
            n->prev = new_node; 
            ++list_size; 
        }
    }

    void reverse() {
        if (head == tail || head == nullptr) return; 
        node* current = head; 
        node* temp = nullptr; 
        while(current != nullptr) {
            temp = current; 
            swap(current->next, current->prev); 
            current = current->prev; 
        }
        tail = head; 
        head = temp; 
    }
 
    friend ostream& operator<< (ostream& os, const double_linked_list<T>& dll) {
        os << " head <-> " ; 
        for (node* n = dll.head; n; n = n->next) {
            os << n->data << " <-> ";  
        }
        os << " tail "; 
        return os; 
    }
};
