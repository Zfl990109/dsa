//
// Created by zfl on 2021/12/31.
//

#include "bin_node.h"
#include<iostream>

template<typename T> bin_psi(T) bin_node<T>::succ(){
    if (rc){
        bin_psi(T) x = rc;
        while (x->lc){
            x = x->lc;
        }
        return x;
    }
    bin_psi(T) x = *this;
    while (is_rc(*x)){
        x = x->parent;
    }
    return x->parent;
}

template<typename T>
template<typename VST>
void bin_node<T>::trav_level(VST &) {

}

template<typename T>
template<typename VST>
void bin_node<T>::trav_pre(VST &visit) {
    switch( rand() % 5){
        case 1: trav_in1(this, visit); break;
        case 2: trav_in2(this, visit); break;
        case 3: trav_in3(this, visit); break;
        case 4: trav_in4(this, visit); break;
        default: trav_prer(this, visit); break;  //递归版
    }
}

template<typename T>
template<typename VST>
void bin_node<T>::trav_in(VST &visit) {
    switch( rand() % 5){
        case 1: trav_in1(this, visit); break;
        case 2: trav_in2(this, visit); break;
        case 3: trav_in3(this, visit); break;
        case 4: trav_in4(this, visit); break;
        default: trav_inr(this, visit); break;  //递归版
    }
}

template<typename T>
template<typename VST>
void bin_node<T>::trav_post(VST &visit) {
    switch( rand() % 5){
        case 1: trav_in1(this, visit); break;
        case 2: trav_in2(this, visit); break;
        case 3: trav_in3(this, visit); break;
        case 4: trav_in4(this, visit); break;
        default: trav_postr(this, visit); break;  //递归版
    }
}

template<typename T, typename VST>
void trav_prer(bin_psi(T) x, VST& visit){
    if(!x) return;
    visit(x);
    trav_prer(x->lc, visit);
    trav_prer(x->rc, visit);
}