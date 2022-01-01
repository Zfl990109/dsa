//
// Created by zfl on 2021/12/31.
//

#include "bin_node.h"
#include "../stack/stack.h"
#include<iostream>

template<typename T> bin_psi(T) bin_node<T>::succ(){
    bin_psi(T) x = this;
    if (rc){
        x = rc;
        while (has_lc(*x)) x = x->lc;
    }else{
        while (is_rc(*x)) x = x->parent;
        x = x->parent;
    }
    return x;
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
/************************************************************
 * 先序遍历
 ************************************************************/
template<typename T, typename VST>
void trav_prer(bin_psi(T) x, VST& visit){
    if(!x) return;
    visit(x);
    trav_prer(x->lc, visit);
    trav_prer(x->rc, visit);
}
template<typename T, typename VST>
void trav_pre1(bin_psi(T) x, VST& visit){
    stack<bin_psi(T)> stk;
    if(x) stk.push(x);
    while(!stk.empty()){
        x = stk.pop();
        visit(x);
        if(has_rc(*x)) stk.push(x->rc);
        if(has_lc(*x)) stk.push(x->lc);
    }
}
template<typename T, typename VST>
void trav_pre2(bin_psi(T) x, VST& visit){
    stack<bin_psi(T)> stk;
    while(true){
        while(x){
            visit(x);
            if(has_rc(*x)) stk.push(x->rc);
            x = x->lc;
        }
        if(stk.empty()) break;
        x = stk.pop();
    }
}
/***************************************************************
 * 中序遍历
 **************************************************************/
template<typename T, typename VST>
void trav_inr(bin_psi(T) x, VST& visit){
    if(!x) return;
    trav_prer(x->lc, visit);
    visit(x);
    trav_prer(x->rc, visit);
}
template<typename T, typename VST>
void trav_in1(bin_psi(T) x, VST& visit){
    stack<bin_psi(T)> stk;
    while(true){
        while(x){
            stk.push(x);
            x = x->lc;
        }
        if(stk.empty()) break;
        x = stk.pop();
        visit(x);
        x = x->rc;
    }
}
template<typename T, typename VST>
void trav_in2(bin_psi(T) x, VST& visit){
    stack<bin_psi(T)> stk;
    while(true){
        if(x){
            stk.push(x);
            x = x->lc;
        }else if(!stk.empty()){
            x = stk.pop();
            visit(x);
            x = x->rc;
        } else
            break;
    }
}
template<typename T, typename VST>
void trav_in3(bin_psi(T) x, VST& visit){
    bool goleft = true;
    while(true){
        if (has_lc(*x) && goleft){
            x = x->lc;
        }else{
            visit(x);
            if (has_rc(*x)){
                x = x->rc;
                goleft = true;
            } else{
                if (!(x = x->succ())) break;
                goleft = false;
            }
        }
    }
}
template<typename T, typename VST>
void trav_in4(bin_psi(T) x, VST& visit){
    while(true){
        if (has_lc(*x)){
            x = x->lc;
        }else{
            visit(x);
            while (!has_rc(*x))
                if (!(x = x->succ())) return;
                else visit(x);
            x = x->rc;
        }
    }
}
/***************************************************************
 * 后序遍历
 **************************************************************/
template<typename T, typename VST>
void trav_postr(bin_psi(T) x, VST& visit){
    if(!x) return;
    trav_prer(x->lc, visit);
    trav_prer(x->rc, visit);
    visit(x);
}
template<typename T, typename VST>
void trav_post1(bin_psi(T) x, VST& visit){
    stack<bin_psi(T)> stk;
    if (x) stk.push(x);
    while(!stk.empty()){
        if (stk.top() != x->parent){
            while ((x = stk.top())){
                if (has_lc(*x)){
                    if (has_rc(*x)) stk.push(x->rc);
                    stk.push(x->lc);
                } else
                    stk.push(x->rc);
            }
            stk.pop();
        }
        x = stk.pop();
        visit(x);
    }
}
template<typename T, typename VST>
void trav_post2(bin_psi(T) x, VST& visit){
    stack<bin_psi(T)> stk;
    bin_psi(T) pre = x;     //辅助判断标记,表示前一个访问的节点指针
    while(true){
        while (x){
            stk.push(x);
            x = x->lc;
        }
        if (stk.empty()) break;
        x = stk.top();
        if (has_rc(*x) && pre != x->rc){
            x = x->rc;
        } else{
            visit(x);
            pre = x;
            stk.pop();
            x = nullptr;
        }
    }
}
//TODO:通过对先序遍历进行翻转
template<typename T, typename VST>
void trav_post3(bin_psi(T) x, VST& visit){
}