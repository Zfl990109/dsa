//
// Created by zfl on 2021/12/28.
//

#include "vector.h"
#include <iostream>
using namespace std;
//数组复制
template<typename T>
void vector<T>::copyFrom(const T *A, int lo, int hi) {
    _ele = new T[_capacity = 2 * (hi - lo)];
    _size = 0;
    while(lo < hi){
        _ele[_size++] = A[lo++];
    }
}
//扩容
template<typename T>
void vector<T>::expand() {
    if (_size < _capacity) return;
    if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
    T* oldEle = _ele;
    _ele = new T[_capacity <<= 1];
    for (int i = 0; i < _size; ++i) {
        _ele[i] = oldEle[i];
    }
    delete []oldEle;
}
//收缩
template<typename T>
void vector<T>::shrink() {
    if (_capacity < DEFAULT_CAPACITY << 1) return;
    if (_size << 2 > _capacity) return;
    T* oldEle = _ele;
    _ele = new T[_capacity >>= 1];
    for (int i = 0; i < _size; ++i) {
        _ele[i] = oldEle[i];
    }
    delete []oldEle;
}
//无序向量查找
template<typename T>
int vector<T>::find(const T &e, int lo, int hi) const {
    while((lo < hi--) && (e != _ele[hi]));
    return hi;
}
//有序向量查找
//TODO:实现binary_search和fib_search
template<typename T>
int vector<T>::search(const T &e, int lo, int hi) const {
    return 0;
}
//随机访问
template<typename T>
T &vector<T>::operator[](int r) const {
    return _ele[r];
}
//向量赋值
template<typename T>
vector<T> &vector<T>::operator=(const vector<T> &v) {
    if (_ele) delete []_ele;
    copyFrom(v._ele, 0, v.size());
    return *this;
}
//插入元素
template<typename T>
int vector<T>::insert(int r, const T &e) {
    expand();
    for (int i = _size; i > r ; i--) {
        _ele[i] = _ele[i - 1];
    }
    _ele[r] = e;
    _size++;
    return r;
}
//区间删除
template<typename T>
int vector<T>::remove(int lo, int hi) {
    if (lo == hi) return 0;
    while (hi < _size) _ele[lo++] = _ele[hi++];
    _size = lo;
    shrink();
    return hi - lo;
}
//单个删除
template<typename T>
T vector<T>::remove(int r) {
    T e = _ele[r];
    remove(r, r + 1);
    return e;
}
//置乱器
template<typename T> void permute(vector<T>& v){
    for (int i = v.size(); i > 0; i--) {
        swap(v[i - 1], v[rand() % i]);
    }
}
//向量整体置乱
template<typename T>
void vector<T>::unsort(int lo, int hi) {
    T* v = _ele + lo;
    for (int i = hi - lo; i > 0; i--) {
        swap(v[i - 1], v[rand() % i]);
    }
}
//无序向量去重
template<typename T>
int vector<T>::deduplicate() {
    int old_size = _size;
    int i = 1;
    while (i < _size){
        (find(_ele[i], 0, i) < 0) ? i++ : remove(i);
    }
    return old_size - _size;
}
//有序向量去重
template<typename T>
int vector<T>::uniqufy() {
    int i = 0, j = 0;
    while (++j <_size) {
        if (_ele[i] != _ele[j])
            _ele[++i] = _ele[j];
    }
    _size = ++i;
    shrink();
    return j - i;
}
//函数指针遍历
template<typename T>
void vector<T>::traverse(void (*visit)(T &)) {
    for (int i = 0; i < _size; ++i) {
        visit(_ele[i]);
    }
}
//函数对象遍历
template<typename T>
template<typename vst>
void vector<T>::traverse(vst & visit) {
    for (int i = 0; i < _size; ++i) {
        visit(_ele[i]);
    }
}

