//
// Created by zfl on 2021/12/31.
//

#include "binary_tree.h"
#include<iostream>
template<typename T> int binary_tree<T>::update_height(bin_node<T> *x) {
    return x->height = 1 + max(stature(x->lc), stature(x->rc));
}

template<typename T>
void binary_tree<T>::update_height_above(bin_node<T> *x) {
    while (x){
        update_height(x);
        x = x->parent;
    }
}

template<typename T>
bin_node<T> *binary_tree<T>::insertAsRoot(const T &e) {
    _size = 1;
    return _root = new bin_node<T>(e);
}

template<typename T>
bin_node<T> *binary_tree<T>::insertAsLc(bin_node<T> *x, const T &e) {
    _size++;
    x->insertAsLc(e);
    update_height_above(x);
    return x->lc;
}

template<typename T>
bin_node<T> *binary_tree<T>::insertAsRc(bin_node<T> *x, const T &e) {
    _size++;
    x->insertAsRc(e);
    update_height_above(x);
    return x->rc;
}

template<typename T>
bin_node<T> *binary_tree<T>::attachAsLc(bin_node<T> *x, binary_tree<T> *&tree) {
    if (x->lc = tree->_root) x->lc->parent = x;
    _size += tree->_size;
    update_height_above(x);
    tree->_size = 0;
    tree->_root = nullptr;
    delete tree;
    return x;
}

template<typename T>
bin_node<T> *binary_tree<T>::attachAsRc(bin_node<T> *x, binary_tree<T> *&tree) {
    if (x->rc = tree->_root) x->rc->parent = x;
    _size += tree->_size;
    update_height_above(x);
    removeAt(tree->_root);
    tree->_size = 0;
    tree->_root = nullptr;
    delete tree;
    return x;
}

template<typename T>
int binary_tree<T>::remove(bin_node<T> *x) {
    from_parent_to(*x) = nullptr;
    update_height_above(x->parent);
    int n = removeAt(x);
    _size -= n;
    return n;
}

template<typename T>
binary_tree<T> *binary_tree<T>::secede(bin_node<T> *x) {
    from_parent_to(*x) = nullptr;
    update_height_above(x->parent);
    binary_tree<T>* tree = new binary_tree<T>;
    tree->_root = x;
    x->parent = nullptr;
    tree->_size = x->size();
    _size -= x->size();
    return tree;
}

template<typename T>
static int removeAt(bin_psi(T) x){
    if (!x) return 0;
    int n = 1 + removeAt(x->lc) + removeAt(x->rc);
    x->data = NULL;
    delete x;
    return n;
}
