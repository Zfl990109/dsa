//
// Created by zfl on 2022/1/1.
//

#include "binary_tree.h"
#include "../vector/vector.h"
#include <iostream>

typedef binary_tree<char> pfc_tree;
typedef vector<pfc_tree*> pfc_forest;
#define N_CHAR (0x80 - 0x20)
//初始化pfc森林
pfc_forest* init(){
    pfc_forest* forest = new pfc_forest;
    for (int i = 0; i < N_CHAR; ++i) {
        forest->insert(i, new pfc_tree());
        (*forest)[i]->insertAsRoot(0x20 + i);
    }
    return forest;
}
//构造pfc编码树
//TODO：实现优先级队列,每次从 pfc 森林中挑选出最小的两棵树
pfc_tree* generate_tree(pfc_forest* forest){
    srand((unsigned int) time(NULL));
    while (forest->size() > 1){
        pfc_tree* s = new pfc_tree;
        s->insertAsRoot('^');
        int r1 = rand() % forest->size();
        s->attachAsLc(s->root(), (*forest)[r1]);
        forest->remove(r1);
        int r2 = rand() % forest->size();
        s->attachAsRc(s->root(), (*forest)[r2]);
        forest->remove(r2);
        forest->insert(forest->size(), s);
    }
    return (*forest)[0];
}
//生成 pfc 编码表
void generate_ct();

