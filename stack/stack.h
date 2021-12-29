//
// Created by zfl on 2021/12/29.
//

#ifndef DSA_STACK_H
#define DSA_STACK_H
#include "../vector/vector.h"

template<typename T>
class stack : public vector<T>{
public:
    void push(const T& e){ insert(size(), e); }     //入栈,等效于将新元素作为向量的末元素插入
    T pop(){ return remove(size() - 1); }       //出栈,等效于删除向量的末元素
    T& top(){ return (*this)[size() - 1]; }     //取得栈顶元素
};


#endif //DSA_STACK_H
