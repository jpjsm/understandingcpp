/*  **************************************************************************
 
    linkedlist.hpp

    This is a 'trick' to have implementation in a separate 
    

    Created by Juan Pablo Jofre on 2019-08-09.
    Copyright © 2019 Juan Pablo Jofre (juanpablo.jofre@live.com). All rights reserved.

    ***************************************************************************/
template<typename T>
linkedlist<T>::linkedlist(){
    list = nullptr;
};

template<typename T>
linkedlist<T>::linkedlist(T d){
    list = new node<T>(d);
};

template<typename T>
void linkedlist<T>::insert(T d){
    if (list == nullptr)
    {
        list = new node<T>(d);
        return;
    }
    
    node<T>* n = new node<T>(d);
    n->next = list;
    list = n;
};

template<typename T>
void linkedlist<T>::insert_last(T d){
    if (list == nullptr)
    {
        list = new node<T>(d);
        return;
    }
    
    node<T>* n = new node<T>(d);

    node<T>* l = list->next;
    while (l->next != nullptr){
        l = l->next;
    }

    l->next = n;
};

template<typename T>
void linkedlist<T>::insert_at(int p, T d){
    if (list == nullptr)
    {
        list = new node<T>(d);
        return;
    }
    
    node<T>* n = new node<T>(d);

    if (p <= 0){
        n->next = list;
        list = n;
        return;
    }

    p -= 1; // Since were traversing fwd, the search needs to land one position 
            // before

    int c = 0;
    node<T>* l = list;
    while (l->next != nullptr && c < p){
        l = l->next;
        c++;
    }

    if (l->next == nullptr)
    {
        l->next = n;
        return;
    }
    
    n->next = l->next;
    l->next = n;
};

template<typename T>
int linkedlist<T>::find(T d){
    if (list == nullptr)
    {
        return -1;
    }
    
    int c = 0;
    node<T>* l = list;
    while (l->next != nullptr ){
        if (l->data == d){
            return c;
        }

        l = l->next;
        c++;
    }

    if (l->data == d){
        return c;
    }

    return -1;
};

template<typename T>
T linkedlist<T>::remove(){
    if (list == nullptr)
    {
        throw "[linkedlist<T>::remove] Empty list; nothing to remove!";
    }
    
    node<T>* l = list;
    T v = list->data;
    list = l->next;
    delete l;
    return v;
};

template<typename T>
T linkedlist<T>::remove_last(){
    if (list == nullptr)
    {
        throw "[linkedlist<T>::remove_last] Empty list; nothing to remove!";
    }
    
    node<T>* n = list->next;
    node<T>* p = list;

    if (n == nullptr)
    {
        T v = list->data;
        delete list;
        list = nullptr;
        return v;
    }
    
    while (n->next != nullptr){
        p = n;
        n = n->next;
    }
    
    p->next = nullptr;
    T v = n->data;
    delete n;
    return v;
};

template<typename T>
bool linkedlist<T>::is_empty(){
    return list == nullptr;
}

template<typename T>
linkedlist<T>::~linkedlist(){
    if (list == nullptr){
        return;
    }
    
    while (list != nullptr)
    {
        remove();
    }      
};
