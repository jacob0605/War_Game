
#ifndef __LL_H__
#define __LL_H__

#include <iostream>

class Linked_List_Node {
friend class Linked_List_Iterator;
friend class Linked_List;
private:
    int data;
    ~Linked_List_Node() { std::cout << "Linked_List_Node destructor: " << data << std::endl; }
    Linked_List_Node * prev;
    Linked_List_Node * next;
    Linked_List_Node(int d);
    Linked_List_Node(const Linked_List_Node &) = delete; // copy constructor
    Linked_List_Node & operator=(const Linked_List_Node &) = delete; // assignment operator
};

class Linked_List_Iterator; // forward declaration
class Linked_List {
public:
    Linked_List();
    Linked_List(const Linked_List & source);
    Linked_List & operator=(const Linked_List & source);
    ~Linked_List();
    void add_at_front(int & new_datum);
    void add_at_front(int & new_datum, Linked_List_Iterator & iter);
    void add_at_back(int &new_datum);
    void add_at_back(int & new_datum, Linked_List_Iterator & iter);
    int get_List_length();
friend class Linked_List_Iterator;
private:
    int item_num;
    Linked_List_Node * head;
    Linked_List_Node * tail;
    void remove_all_items();
};

class Linked_List_Iterator {
public:
    Linked_List_Iterator(Linked_List & list);
    void advance();
    bool at_end();
    void remove_at_iterator();
    void insert_before_iterator(int & new_datum);
    int access_at_iterator();
    void reset_from_list(Linked_List & list);
    void invalidate();
friend class Linked_List;
private:
    Linked_List_Node * current;
    Linked_List * list_p;
    // prohibit default constructor, copy constructor, assignment
    Linked_List_Iterator(Linked_List_Iterator & iter) {}
    Linked_List_Iterator & operator=(Linked_List_Iterator & iter) {}
};


#endif // __LL_H__