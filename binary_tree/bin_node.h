//
// Created by zfl on 2021/12/31.
//

#ifndef DSA_BIN_NODE_H
#define DSA_BIN_NODE_H
#define bin_psi(T) bin_node<T>*
/*********************************************************************
 * bin_node 节点状态与性质的判断,此处的 x 表示 bin_node 节点这个对象
 **********************************************************************/
#define stature(p) ((p) ? (p)->height : -1)     //返回节点高度
#define is_root(x) (! ((x).parent) )
#define is_lc(x) ( ! is_root(x) && ( &(x) == (x).parent->lc) )
#define is_rc(x) ( ! is_root(x) && ( &(x) == (x).parent->rc) )
#define has_parent(x) ( ! is_root(x) )
#define has_lc(x) ( (x).lc )
#define has_rc(x) ( (x).rc )
#define has_child(x) ( has_lc(x) || has_rc(x) )
#define has_both_child(x) ( has_lc(x) && has_rc(x) )
#define is_leaf(x) ( !has_child(x) )
#define from_parent_to(x) /*来自父亲的引用*/ \
    ( is_root(x) ? _root : (is_lc(x) ? (x).parent->lc : (x).parent->rc ) )
/************************************************************************
 * 与 bin_node 具有特定关系的节点及指针,此处 x 表示指向 bin_node 对象的指针,需要解引用
 ***********************************************************************/
#define sibling(p) /*兄弟节点*/ \
    ( is_lc(*(p)) ? (p)->parent->rc : (p)->parent->lc )
#define uncle /*叔叔*/ \
    ( is_lc( *( (x)->parent ) ) ? (x)->parent->parent->rc : (x)->parent->parent->lc )
typedef enum{RE_RED, RE_BLACK} rb_color;

template<typename T> struct bin_node{
    T data;     //数据域
    bin_psi(T) parent;      //父节点
    bin_psi(T) lc;      //左孩子
    bin_psi(T) rc;      //右孩子
    int height;     //高度
    int npl;        //最右侧通路长度（左式堆）
    rb_color color;     //颜色（红黑树）
    //构造函数
    bin_node() :
            parent(nullptr), lc(nullptr), rc(nullptr), height(0), npl(1), color(RE_RED){}
    bin_node(T e, bin_psi(T) p = nullptr, bin_psi(T) lc = nullptr, bin_psi(T) rc = nullptr,
             int h = 0, int npl = 1, rb_color c = RE_RED):
            data(e), parent(p), lc(lc), rc(rc), height(h), npl(npl), color(c){}
    //操作接口
    int size();     //包括当前节点的子树的规模
    bin_psi(T) insertAsLc(const T& e){//作为当前节点的左孩子插入新节点
        return lc = new bin_node<T>(e, this);
    }
    bin_psi(T) insertAsRc(const T& e){//作为当前节点的右孩子插入新节点
        return rc = new bin_node<T>(e, this);
    }
    bin_psi(T) succ(); //取当前节点的后继
    template<typename VST> void trav_level(VST&);   //层序遍历
    template<typename VST> void trav_pre(VST&);   //先序遍历
    template<typename VST> void trav_in(VST&);   //中序遍历
    template<typename VST> void trav_post(VST&);   //后序遍历

    bool operator<(const bin_node<T>& bn){ return data < bn.data; }     //小于
    bool operator==(const bin_node<T>& bn){ return data == bn.data; }     //小于

};


#endif //DSA_BIN_NODE_H
