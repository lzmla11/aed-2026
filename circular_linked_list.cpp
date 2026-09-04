#include <iostream>

using namespace std;

template<class T>
class circular_linked_list {
public: 
    struct node {
        T data; 
        node* prev; 
        node* next;
        node(T d, node* p = nullptr, node* n = nullptr) : data(d), prev(p), next(n) {}
    };

private:
    node* head = nullptr; 
    int list_size = 0; 

public: 
    circular_linked_list() = default; 
    
    ~circular_linked_list() {
        clear();
    }

    void clear() {
        if (head == nullptr) return;

        node* tail = head->prev;
        tail->next = nullptr; 

        node* temp; 
        while(head != nullptr) {
            temp = head; 
            head = head->next; 
            delete temp; 
        }
        list_size = 0;
    }

    bool empty() const { return list_size == 0; }
    int size() const { return list_size; }
    node* begin() const { return head; }

    void push_front(const T& d) {
        if (head == nullptr) {
            head = new node(d); 
            head->next = head; 
            head->prev = head; 
        } else {
            node* tail = head->prev; 
            node* new_node = new node(d, tail, head); 
            
            head->prev = new_node; 
            tail->next = new_node; 
            head = new_node; 
        }
        list_size++;
    }

    void push_back(const T& d) {
        if (head == nullptr) {
            push_front(d);
            return;
        }
        node* tail = head->prev;
        node* new_node = new node(d, tail, head);
        
        tail->next = new_node;
        head->prev = new_node;
        list_size++;
    }

    void pop_front() {
        if (empty()) return;
        remove(head);
    }

    void pop_back() {
        if (empty()) return;
        remove(head->prev); 
    }

    node* search(const T& d) {
        if (head == nullptr) {
            return nullptr; 
        }
        node* n = head;  
        do {
            if (n->data == d) {
                return n; 
            }
            n = n->next; 
        } while(n != head);

        return nullptr; 
    }

    void insert(node* n, const T& d) { 
        if (n == nullptr || head == nullptr) return; 
        
        node* p = n->prev;
        node* curr = new node(d, p, n); 

        p->next = curr; 
        n->prev = curr; 
        
        if (n == head) {
            head = curr; 
        }
        list_size++;
    }

    void remove(node* n) {
        if (n == nullptr || head == nullptr) return; 
        
        if (list_size == 1) { 
            if (n == head) {
                delete n; 
                head = nullptr; 
                list_size--;
            }
            return; 
        }

        node* p = n->prev; 
        node* s = n->next; 
        p->next = s; 
        s->prev = p;
        
        if (n == head) {
            head = s; 
        }

        delete n; 
        list_size--;
    }

    friend ostream& operator<< (ostream& os, const circular_linked_list<T>& cll) {
        if (cll.empty()) return os << "Lista vacía";
        
        node* current = cll.head;
        do {
            os << current->data;
            current = current->next;
            if (current != cll.head) os << " <-> ";
        } while (current != cll.head);
        
        os << " <-> (vuelve al head)";
        return os;
    }
};
