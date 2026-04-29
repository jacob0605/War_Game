#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>

template <typename T>
class Linked_List;

template <typename T>
class Linked_List_Iterator;

template <typename T>
class Linked_List_Node {
    friend class Linked_List<T>;
    friend class Linked_List_Iterator<T>;

private:
    T data;
    Linked_List_Node* prev;
    Linked_List_Node* next;

    explicit Linked_List_Node(const T& d) : data(d), prev(nullptr), next(nullptr) {}
    ~Linked_List_Node() { std::cout << "Linked_List_Node deleted" << std::endl; }

    Linked_List_Node(const Linked_List_Node&) = delete;
    Linked_List_Node& operator=(const Linked_List_Node&) = delete;
};

template <typename T>
class Linked_List {
    friend class Linked_List_Iterator<T>;

public:
    Linked_List() : item_num(0), head(nullptr), tail(nullptr) {}

    Linked_List(const Linked_List& source) : item_num(0), head(nullptr), tail(nullptr) {
        copy_from(source);
    }

    Linked_List& operator=(const Linked_List& source) {
        if (this != &source) {
            remove_all_items();
            copy_from(source);
        }
        return *this;
    }

    ~Linked_List() { remove_all_items(); }

    void add_at_front(const T& new_datum);
    void add_at_front(const T& new_datum, Linked_List_Iterator<T>& iter);
    void add_at_back(const T& new_datum);
    void add_at_back(const T& new_datum, Linked_List_Iterator<T>& iter);
    int get_List_length() const { return item_num; }
    int get_list_length() const { return item_num; }
    void clear() { remove_all_items(); }

private:
    int item_num;
    Linked_List_Node<T>* head;
    Linked_List_Node<T>* tail;

    void remove_all_items();
    void copy_from(const Linked_List& source);
};

template <typename T>
class Linked_List_Iterator {
    friend class Linked_List<T>;

public:
    Linked_List_Iterator() : current(nullptr), list_p(nullptr) {}
    explicit Linked_List_Iterator(Linked_List<T>& list) : current(list.head), list_p(&list) {}

    void advance();
    bool at_end() const { return current == nullptr; }
    T access_at_iterator() const;
    void remove_at_iterator();
    void insert_before_iterator(const T& new_datum);
    void reset_from_list(Linked_List<T>& list) {
        list_p = &list;
        current = list.head;
    }
    void invalidate() {
        current = nullptr;
        list_p = nullptr;
    }

private:
    Linked_List_Node<T>* current;
    Linked_List<T>* list_p;
};

template <typename T>
void Linked_List<T>::copy_from(const Linked_List<T>& source) {
    for (Linked_List_Node<T>* node = source.head; node != nullptr; node = node->next) {
        add_at_back(node->data);
    }
}

template <typename T>
void Linked_List<T>::add_at_front(const T& new_datum) {
    Linked_List_Node<T>* new_node = new Linked_List_Node<T>(new_datum);

    if (head == nullptr) {
        head = tail = new_node;
    } else {
        new_node->next = head;
        head->prev = new_node;
        head = new_node;
    }

    ++item_num;
}

template <typename T>
void Linked_List<T>::add_at_front(const T& new_datum, Linked_List_Iterator<T>& iter) {
    add_at_front(new_datum);
    iter.list_p = this;
    iter.current = head;
}

template <typename T>
void Linked_List<T>::add_at_back(const T& new_datum) {
    Linked_List_Node<T>* new_node = new Linked_List_Node<T>(new_datum);

    if (tail == nullptr) {
        head = tail = new_node;
    } else {
        new_node->prev = tail;
        tail->next = new_node;
        tail = new_node;
    }

    ++item_num;
}

template <typename T>
void Linked_List<T>::add_at_back(const T& new_datum, Linked_List_Iterator<T>& iter) {
    add_at_back(new_datum);
    iter.list_p = this;
    iter.current = tail;
}

template <typename T>
void Linked_List<T>::remove_all_items() {
    Linked_List_Node<T>* node = head;

    while (node != nullptr) {
        Linked_List_Node<T>* doomed = node;
        node = node->next;
        delete doomed;
    }

    head = nullptr;
    tail = nullptr;
    item_num = 0;
}

template <typename T>
void Linked_List_Iterator<T>::advance() {
    if (list_p == nullptr) {
        return;
    }

    if (current == nullptr) {
        current = list_p->head;
    } else {
        current = current->next;
    }
}

template <typename T>
T Linked_List_Iterator<T>::access_at_iterator() const {
    return current != nullptr ? current->data : T();
}

template <typename T>
void Linked_List_Iterator<T>::remove_at_iterator() {
    if (list_p == nullptr || current == nullptr) {
        return;
    }

    Linked_List_Node<T>* doomed = current;
    Linked_List_Node<T>* next_node = current->next;

    if (doomed->prev != nullptr) {
        doomed->prev->next = doomed->next;
    } else {
        list_p->head = doomed->next;
    }

    if (doomed->next != nullptr) {
        doomed->next->prev = doomed->prev;
    } else {
        list_p->tail = doomed->prev;
    }

    delete doomed;
    --list_p->item_num;
    current = next_node;
}

template <typename T>
void Linked_List_Iterator<T>::insert_before_iterator(const T& new_datum) {
    if (list_p == nullptr) {
        return;
    }

    if (current == nullptr) {
        list_p->add_at_back(new_datum);
        current = list_p->tail;
        return;
    }

    Linked_List_Node<T>* new_node = new Linked_List_Node<T>(new_datum);
    new_node->next = current;
    new_node->prev = current->prev;

    if (current->prev != nullptr) {
        current->prev->next = new_node;
    } else {
        list_p->head = new_node;
    }

    current->prev = new_node;
    current = new_node;
    ++list_p->item_num;
}

#endif // LINKED_LIST_H
