#ifndef GUARD_BST_H
#define GUARD_BST_H

#include <memory>

template <class T> class BST{
public:
    BST(): root{0}, size{0} {}


private:
    template <class T> class Node{
    public:
        Node() { create(); }
        Node(const T& t) { create(t); }
    private:
        Node<T>* left;
        Node<T>* right;
        Node<T>* parent;
        int key;
        T* data;
    };
    
    Node<T>* root;
    size_t size;

};


#endif
