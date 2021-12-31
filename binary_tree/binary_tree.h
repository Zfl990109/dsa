//
// Created by zfl on 2021/12/31.
//

#ifndef DSA_BINARY_TREE_H
#define DSA_BINARY_TREE_H
#include "bin_node.h"

template<typename T>
class binary_tree {
protected:
    int _size;      //规模
    bin_psi(T) _root;   //根节点
    virtual int update_height( bin_psi(T) x);   //更新节点 x 的高度
    void update_height_above( bin_psi(T) x);   //更新节点 x 及其祖先的高度
public:
    binary_tree(): _size(0), _root(nullptr){}   //构造函数
    ~binary_tree(){     //析构函数
        if (0 < _size)
            remove(_root);
    }
    int size() const { return _size; }
    bool empty() const { return !_root; }
    bin_psi(T) root() const { return _root; }
    bin_psi(T) insertAsRoot(const T& e);    //将 e 作为根节点插入
    bin_psi(T) insertAsLc(bin_psi(T) x, const T& e);    //将 e 作为 x 的左孩子插入
    bin_psi(T) insertAsRc(bin_psi(T) x, const T& e);    //将 e 作为 x 的右孩子插入
    bin_psi(T) attachAsLc(bin_psi(T) x, binary_tree<T>* &tree);    //将 tree 作为 x 的左子树插入
    bin_psi(T) attachAsRc(bin_psi(T) x, binary_tree<T>* &tree);    //将 tree 作为 x 的右子树插入
    int remove(bin_psi(T) x);   //删除以位置 x 为根的子树,返回该子树的规模
    binary_tree<T>* secede(bin_psi(T) x);   //将子树 x 从当前树中摘除，并转化为一棵独立的树
    template<typename VST> void trav_level(VST& visit){ if (_root) _root->template trav_level(visit); } //层序遍历
    template<typename VST> void trav_pre(VST& visit){ if (_root) _root->template trav_pre(visit); } //先序遍历
    template<typename VST> void trav_in(VST& visit){ if (_root) _root->template trav_in(visit); } //中序遍历
    template<typename VST> void trav_post(VST& visit){ if (_root) _root->template trav_post(visit); } //后序遍历
    bool operator<(const binary_tree<T>& tree){
        return _root && tree._root && lt(_root, tree._root);
    }
    bool operator==(const binary_tree<T>& tree){
        return _root && tree._root && (_root == tree._root);
    }
};


#endif //DSA_BINARY_TREE_H
