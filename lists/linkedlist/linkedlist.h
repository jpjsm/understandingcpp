/*  **************************************************************************
 
    linkedlist.h
    

    Created by Juan Pablo Jofre on 2019-08-09.
    Copyright © 2019 Juan Pablo Jofre (juanpablo.jofre@live.com). All rights reserved.

    ***************************************************************************/

#ifndef LINKED_LIST
#define LINKED_LIST

template<typename V>
struct node {
    node<V>* next;
    V data;

    node(V d):node(nullptr, d){}
    node(node* n, V d): next(n), data(d){}
};

template<typename T>
struct linkedlist {
    node<T>* list;

    linkedlist();
    linkedlist(T d);
    void insert(T d);
    void insert_last(T d);
    void insert_at(int p, T d);
    int find(T d);
    T remove();
    T remove_last();
    bool is_empty();
    ~linkedlist();
  /*
  T remove_at(int p);
  void add_linkedlist(linkedlist<T> l);
  void append_linkedlist(linkedlist<T> ;);
  */
};

#include "linkedlist.hpp"
#endif


