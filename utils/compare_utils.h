//
// Created by zfl on 2021/12/29.
//

#ifndef DSA_COMPARE_UTILS_H
#define DSA_COMPARE_UTILS_H

template<typename T> static bool lt(T* a, T* b){ return lt(*a, *b); }
template<typename T> static bool lt(T& a, T& b){ return a < b; }
template<typename T> static bool eq(T* a, T* b){ return eq(*a, *b); }
template<typename T> static bool eq(T& a, T& b){ return a == b; }


#endif //DSA_COMPARE_UTILS_H
