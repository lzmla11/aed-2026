#include <iostream>

using namespace std;

template<class T>
class singly_linked_list {
public:
    struct node {
        T data; 
        node* next; 
        node(T d, node* n = nullptr) : data(d), next(n) {} 
    }; 

private: 
    node* head = nullptr; 
    node* tail = nullptr;
    int list_size = 0; 

public: 
    singly_linked_list() : head(nullptr), tail(nullptr), list_size(0) {}
    
    ~singly_linked_list() {
        clear();
    }

    node* begin() const {
        return head;
    }

    node* end() const {
        return tail;
    }
    
    void clear() {
        node* n; 
        while (head != nullptr) {
            n = head->next; 
            delete head; 
            head = n; 
        }
        tail = nullptr;
        list_size = 0;
    }

    bool empty() const {
        return head == nullptr; 
    }

    int size() const {
        return list_size;
    }
    
    void push_back(const T& d) {
        node* n = new node(d, nullptr); 
        if (empty()) {
            head = n; 
            tail = n; 
        } else {
            tail->next = n; 
            tail = n; 
        }
        list_size++;
    }
    
    void push_front(const T& d) {
        head = new node(d, head); 
        if (tail == nullptr) { 
            tail = head;
        }
        list_size++;
    }

    void pop_front() {
        if (empty()) return;
        node* tmp = head;
        head = head->next;
        delete tmp;
        if (head == nullptr) { 
            tail = nullptr;
        }
        list_size--;
    }

    bool remove(const T& d) {
        if (empty()) return false;

        if (head->data == d) {
            pop_front();
            return true;
        }

        node* current = head;
        while (current->next != nullptr && current->next->data != d) {
            current = current->next;
        }

        if (current->next != nullptr) {
            node* to_delete = current->next;
            current->next = to_delete->next;
            
            if (to_delete == tail) {
                tail = current;
            }
            
            delete to_delete;
            list_size--;
            return true;
        }
        return false;
    }

    void reverse() {
        if (empty() || head == tail) return; 
        
        node* prev = nullptr; 
        node* current = head;  
        node* next_node;  
        
        tail = head; 

        while (current != nullptr) {
            next_node = current->next;  
            current->next = prev; 
            prev = current; 
            current = next_node; 
        }
        head = prev; 
    }

    friend ostream& operator<< (ostream& os, const singly_linked_list<T>& sll) {
        for (node* n = sll.head; n; n = n->next) {
            os << n->data << " "; 
        }
        return os; 
    }
};


  
