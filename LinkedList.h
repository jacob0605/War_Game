#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
#include <utility>

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
    ~Linked_List_Node() { std::cout << "Linked_List_Node destructor: " << data << std::endl; }

    Linked_List_Node(const Linked_List_Node&) = delete;
    Linked_List_Node& operator=(const Linked_List_Node&) = delete;
};

template <typename T>
class Linked_List {
    friend class Linked_List_Iterator<T>;

private:
    int item_num;
    Linked_List_Node<T>* head;
    Linked_List_Node<T>* tail;

    void remove_all_items();
    void copy_from(const Linked_List& other);

public:
    Linked_List();
    Linked_List(const Linked_List& other);
    Linked_List(Linked_List&& other) noexcept;
    ~Linked_List();

    Linked_List& operator=(const Linked_List& other);
    Linked_List& operator=(Linked_List&& other) noexcept;

    void swap(Linked_List& other) noexcept;

    void add_at_front(const T& new_datum);
    void add_at_front(const T& new_datum, Linked_List_Iterator<T>& iter);
    void add_at_back(const T& new_datum);
    void add_at_back(const T& new_datum, Linked_List_Iterator<T>& iter);

    int get_list_length() const { return item_num; }
    bool empty() const { return item_num == 0; }
    void clear() { remove_all_items(); }
};

template <typename T>
Linked_List<T>::Linked_List() : item_num(0), head(nullptr), tail(nullptr) {}

template <typename T>
Linked_List<T>::Linked_List(const Linked_List& other) : item_num(0), head(nullptr), tail(nullptr) {
    copy_from(other);
}

template <typename T>
Linked_List<T>::Linked_List(Linked_List&& other) noexcept : item_num(0), head(nullptr), tail(nullptr) {
    swap(other);
}

template <typename T>
Linked_List<T>::~Linked_List() {
    remove_all_items();
}

template <typename T>
Linked_List<T>& Linked_List<T>::operator=(const Linked_List& other) {
    if (this != &other) {
        remove_all_items();
        copy_from(other);
    }
    return *this;
}

template <typename T>
Linked_List<T>& Linked_List<T>::operator=(Linked_List&& other) noexcept {
    if (this != &other) {
        remove_all_items();
        swap(other);
    }
    return *this;
}

template <typename T>
void Linked_List<T>::swap(Linked_List& other) noexcept {
    std::swap(item_num, other.item_num);
    std::swap(head, other.head);
    std::swap(tail, other.tail);
}

template <typename T>
void Linked_List<T>::remove_all_items() {
    Linked_List_Node<T>* current = head;
    while (current) {
        Linked_List_Node<T>* to_delete = current;
        current = current->next;
        delete to_delete;
    }
    head = nullptr;
    tail = nullptr;
    item_num = 0;
}

template <typename T>
void Linked_List<T>::copy_from(const Linked_List& other) {
    Linked_List_Node<T>* node = other.head;
    while (node) {
        add_at_back(node->data);
        node = node->next;
    }
}

template <typename T>
void Linked_List<T>::add_at_front(const T& new_datum) {
    Linked_List_Node<T>* new_node = new Linked_List_Node<T>(new_datum);
    new_node->next = head;
    if (head) {
        head->prev = new_node;
    } else {
        tail = new_node;
    }
    head = new_node;
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
    new_node->prev = tail;
    if (tail) {
        tail->next = new_node;
    } else {
        head = new_node;
    }
    tail = new_node;
    ++item_num;
}

template <typename T>
void Linked_List<T>::add_at_back(const T& new_datum, Linked_List_Iterator<T>& iter) {
    add_at_back(new_datum);
    iter.list_p = this;
    iter.current = tail;
}

template <typename T>
class Linked_List_Iterator {
    friend class Linked_List<T>;

private:
    Linked_List_Node<T>* current;
    Linked_List<T>* list_p;

public:
    Linked_List_Iterator();
    explicit Linked_List_Iterator(Linked_List<T>& list);

    void advance();
    bool at_end() const;
    T access_at_iterator() const;
    void remove_at_iterator();
    void insert_before_iterator(const T& new_datum);
    void reset_from_list(Linked_List<T>& list);
    void invalidate();

private:
    Linked_List_Iterator(const Linked_List_Iterator&) = delete;
    Linked_List_Iterator& operator=(const Linked_List_Iterator&) = delete;
};

template <typename T>
Linked_List_Iterator<T>::Linked_List_Iterator() : current(nullptr), list_p(nullptr) {}

template <typename T>
Linked_List_Iterator<T>::Linked_List_Iterator(Linked_List<T>& list) : current(list.head), list_p(&list) {}

template <typename T>
void Linked_List_Iterator<T>::advance() {
    if (current) {
        current = current->next;
    }
}

template <typename T>
bool Linked_List_Iterator<T>::at_end() const {
    return current == nullptr;
}

template <typename T>
T Linked_List_Iterator<T>::access_at_iterator() const {
    return current ? current->data : T();
}

template <typename T>
void Linked_List_Iterator<T>::remove_at_iterator() {
    if (!list_p || !current) {
        return;
    }

    Linked_List_Node<T>* to_delete = current;
    Linked_List_Node<T>* prev_node = current->prev;
    Linked_List_Node<T>* next_node = current->next;

    if (prev_node) {
        prev_node->next = next_node;
    } else {
        list_p->head = next_node;
    }

    if (next_node) {
        next_node->prev = prev_node;
    } else {
        list_p->tail = prev_node;
    }

    current = next_node;
    delete to_delete;
    --list_p->item_num;
}

template <typename T>
void Linked_List_Iterator<T>::insert_before_iterator(const T& new_datum) {
    if (!list_p) {
        return;
    }

    if (!current) {
        list_p->add_at_back(new_datum);
        current = list_p->tail;
        return;
    }

    Linked_List_Node<T>* new_node = new Linked_List_Node<T>(new_datum);
    Linked_List_Node<T>* prev_node = current->prev;

    new_node->next = current;
    new_node->prev = prev_node;

    if (prev_node) {
        prev_node->next = new_node;
    } else {
        list_p->head = new_node;
    }

    current->prev = new_node;
    current = new_node;
    ++list_p->item_num;
}

template <typename T>
void Linked_List_Iterator<T>::reset_from_list(Linked_List<T>& list) {
    list_p = &list;
    current = list.head;
}

template <typename T>
void Linked_List_Iterator<T>::invalidate() {
    list_p = nullptr;
    current = nullptr;
}

#endif // LINKED_LIST_H
