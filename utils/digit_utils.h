//
// Created by zfl on 2021/12/29.
//

#ifndef DSA_DIGIT_UTILS_H
#define DSA_DIGIT_UTILS_H
#include "../stack/stack.h"
//判断当前字符是否为数字
static bool isdigit(char s){
    return ('0' <= s) && (s <= '9');
}
//将字符串中的数字转换
static void readNum(char*& p, stack<float>& stk){
    stk.push((float )(*p - '0'));
    while (isdigit(*(++p)))
        stk.push(stk.pop() * 10 + (*p - '0'));
    if ('.' != *p) return;
    float fraction = 1;
    while (isdigit(*(++p)))
        stk.push(stk.pop() + (*p - '0') * (fraction /= 10));
}
#endif //DSA_DIGIT_UTILS_H
