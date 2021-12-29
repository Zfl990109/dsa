//
// Created by zfl on 2021/12/28.
//

#include "list.h"
#include "../utils/compare_utils.h"

template<typename T> void list<T>::init() {
    header = new list_node<T>;
    trailer = new list_node<T>;
    header->succ = trailer;
    header->pred = nullptr;
    trailer->pred = header;
    trailer->succ = nullptr;
    _size = 0;
}

template<typename T>
T &list<T>::operator[](int r) const {
    list_psi(T) p = first();
    while (0 < r--) p = p->succ;
    return p->data;
}

template<typename T>
list_node<T> *list<T>::find(const T &e, int n, list_node<T> *p) const {
    while(0 < n--){
        if (e == (p = p->pred)->data)
            return p;
    }
    return nullptr;
}

template<typename T>
list_node<T> *list<T>::insertAsFirst(const T &e) {
    _size++;
    return header->insertAsSucc(e);
}

template<typename T>
list_node<T> *list<T>::insertAsLast(const T &e) {
    _size++;
    return trailer->insertAsPred(e);
}

template<typename T>
list_node<T> *list<T>::insertA(list_node<T> *p, const T &e) {
    _size++;
    return p->insertAsSucc(e);
}

template<typename T>
list_node<T> *list<T>::insertB(list_node<T> *p, const T &e) {
    _size++;
    return p->insertAsPred(e);
}

template<typename T>
void list<T>::copyNodes(list_node<T> * p, int n) {
    init();
    while (n--){
        insertAsLast(p->data);
        p = p->succ;
    }
}

template<typename T>
list<T>::list(list_node<T> *p, int n) {
    copyNodes(p, n);
}

template<typename T>
list<T>::list(const list<T> &l, int r, int n) {
    copyNodes(l[r], n);
}

template<typename T>
list<T>::list(const list<T> &l) {
    copyNodes(l.first(), l.size());
}

template<typename T>
T list<T>::remove(list_node<T> *p) {
    T e = p->data;
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    delete p;
    _size--;
    return e;
}

template<typename T>
list<T>::~list() {
    clear();
    delete header;delete trailer;
}

template<typename T>
int list<T>::clear() {
    int old_size = _size;
    while (0 < _size) remove(header->succ);
    return old_size;
}

template<typename T>
int list<T>::deduplicate() {
    if (_size < 2) return 0;
    int old_size = _size;
    list_psi(T) p = header;
    int r = 0;
    while (trailer != (p = p->succ)){
        list_psi(T) q = find(p->data, r, p);
        q ? remove(q) : r++;
    }
    return old_size - _size;
}

template<typename T>
int list<T>::uniqufy() {
    if (_size < 2) return 0;
    int old_size = _size;
    list_psi(T) p = first();
    list_psi(T) q;
    while (trailer != (q = p->succ)){
        if (p->data != q->data) p = q;
        else remove(q);
    }
    return old_size - _size;
}

template<typename T>
void list<T>::traverse(void (*visit)(T &)) {
    for (list_psi(T) p = header->succ; p != trailer; p = p->succ) {
        visit(p->data);
    }
}

template<typename T>
template<typename VST>
void list<T>::traverse(VST &) {
    for (list_psi(T) p = header->succ; p != trailer; p = p->succ) {
        visit(p->data);
    }
}

template<typename T>
list_node<T> *list<T>::search(const T &e, int n, list_node<T> *p) const {
    while (0 <= n--){
        if (((p = p->pred)->data) <= e) break;
    }
    return p;
}
//TODO:实现插入排序,选择排序,归并排序
template<typename T>
void list<T>::sort(list_node<T> *p, int n) {

}

template<typename T>
list_node<T> *list<T>::selectMax(list_node<T> *p, int n) {
    list_psi(T) max = p;
    for (list_psi(T) cur = p; 1 < n; n--) {
        if ( !lt((cur = cur->succ)->data, max->data))
            max = cur;
    }
    return max;
}
