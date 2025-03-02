#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>

// 노드 클래스
template <typename T>
class Linked_List_Node {
    friend class Linked_List<T>;
    friend class Linked_List_Iterator<T>;
private:
    T data;
    Linked_List_Node* prev;
    Linked_List_Node* next;
    Linked_List_Node(T d) : data(d), prev(nullptr), next(nullptr) {}
    ~Linked_List_Node() { std::cout << "Node " << data << " deleted" << std::endl; }
};

// 이터레이터 클래스 선언 (전방 선언)
template <typename T>
class Linked_List_Iterator;

// 링크드 리스트 클래스
template <typename T>
class Linked_List {
    friend class Linked_List_Iterator<T>;
private:
    int item_num;
    Linked_List_Node<T>* head;
    Linked_List_Node<T>* tail;
    void remove_all_items();
public:
    Linked_List() : item_num(0), head(nullptr), tail(nullptr) {}
    ~Linked_List() { remove_all_items(); }
    void add_at_front(T new_datum);
    void add_at_front(T new_datum, Linked_List_Iterator<T> & iter);
    void add_at_back(T new_datum);
    void add_at_back(T new_datum, Linked_List_Iterator<T> & iter);
    int get_list_length() const { return item_num; }
};

template <typename T>
void Linked_List<T>::add_at_front(T new_datum) {
    Linked_List_Node<T>* new_node = new Linked_List_Node<T>(new_datum);
    if (!head) {
        head = tail = new_node;
    } else {
        new_node->next = head;
        head->prev = new_node;
        head = new_node;
    }
    item_num++;
}

template <typename T>
void Linked_List<T>::add_at_front(T new_datum, Linked_List_Iterator<T> & iter) {
    add_at_front(new_datum);
    iter.current = head;
}

template <typename T>
void Linked_List<T>::add_at_back(T new_datum) {
    Linked_List_Node<T>* new_node = new Linked_List_Node<T>(new_datum);
    if (!tail) {
        head = tail = new_node;
    } else {
        new_node->prev = tail;
        tail->next = new_node;
        tail = new_node;
    }
    item_num++;
}

template <typename T>
void Linked_List<T>::add_at_back(T new_datum, Linked_List_Iterator<T> & iter) {
    add_at_back(new_datum);
    iter.current = tail;
}

template <typename T>
void Linked_List<T>::remove_all_items() {
    Linked_List_Node<T>* current = head;
    while (current) {
        Linked_List_Node<T>* to_delete = current;
        current = current->next;
        delete to_delete;
    }
    head = tail = nullptr;
    item_num = 0;
}

template <typename T>
class Linked_List_Iterator {
private:
    Linked_List_Node<T>* current;
    Linked_List<T>* list_p;
public:
    Linked_List_Iterator(Linked_List<T>& list) : list_p(&list), current(list.head) {}
    void advance() { if (current) current = current->next; }
    bool at_end() const { return current == nullptr; }
    T access_at_iterator() const { return current ? current->data : T(); }
    void remove_at_iterator();
    void insert_before_iterator(T new_datum);
    void reset_from_list(Linked_List<T> & list);
    void invalidate();
};

template <typename T>
void Linked_List_Iterator<T>::remove_at_iterator() {
    if (!current) return;
    Linked_List_Node<T>* to_delete = current;
    if (current->prev) current->prev->next = current->next;
    if (current->next) current->next->prev = current->prev;
    if (list_p->head == current) list_p->head = current->next;
    if (list_p->tail == current) list_p->tail = current->prev;
    current = current->next;
    delete to_delete;
    list_p->item_num--;
}

template <typename T>
void Linked_List_Iterator<T>::insert_before_iterator(T new_datum) {
    if (!current) return;
    Linked_List_Node<T>* new_node = new Linked_List_Node<T>(new_datum);
    new_node->next = current;
    new_node->prev = current->prev;
    if (current->prev) current->prev->next = new_node;
    current->prev = new_node;
    if (list_p->head == current) list_p->head = new_node;
    current = new_node;
    list_p->item_num++;
}

template <typename T>
void Linked_List_Iterator<T>::reset_from_list(Linked_List<T> & list) {
    list_p = &list;
    current = list.head;
}

template <typename T>
void Linked_List_Iterator<T>::invalidate() {
    list_p = nullptr;
    current = nullptr;
}

#endif // LINKED_LIST_H
