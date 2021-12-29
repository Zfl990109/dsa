//
// Created by zfl on 2021/12/28.
//

#ifndef DSA_LIST_H
#define DSA_LIST_H
#define list_psi(T) list_node<T>*

template<typename T> struct list_node{
    T data;     //数据域
    list_psi(T) pred;   //前驱
    list_psi(T) succ;   //后继
    list_node(){}
    list_node(T e, list_psi(T) p = nullptr, list_psi(T) s = nullptr)
        : data(e), pred(p), succ(s){}
    list_psi(T) insertAsPred(const T& e){   //作为前驱插入
        list_psi(T) x = new list_node(e, pred, this);
        pred->succ = x;
        pred = x;
        return x;
    }
    list_psi(T) insertAsSucc(const T& e){   //作为后继插入
        list_psi(T) x = new list_node(e, this, succ);
        succ->pred = x;
        succ = x;
        return x;
    }
};
template<typename T>
class list {
private:
    int _size;
    list_psi(T) header;
    list_psi(T) trailer;
protected:
    void init();
    int clear();
    void copyNodes(list_psi(T), int);   //复制节点p之后的n个节点
public:
    //构造函数
    list(){init();}
    list(const list<T>& l);     //列表整体复制
    list(const list<T>& l, int r, int n);     //复制列表中自r开始的n项
    list(list_psi(T) p, int n);     //复制从链表位置p开始的n项
    //析构函数
    ~list();
    /*************只读访问接口**************************************/
    int size() const { return _size; }
    bool empty() const { return _size <= 0; }
    T& operator[](int r) const;     //支持循秩访问
    list_psi(T) first() const { return header->succ; }      //首节点位置
    list_psi(T) last() const { return trailer->pred; }      //末节点位置
    bool valid(list_psi(T) p){      //验证位置p是否合法
        return p && (p != header) && (p != trailer);
    }
    list_psi(T) find(const T& e) const{     //无序链表查找
        return find(e, _size, trailer);
    }
    list_psi(T) find(const T& e, int n, list_psi(T) p) const;       //无序区间查找
    list_psi(T) search(const T& e, int n, list_psi(T) p) const;     //有序区间查找
    list_psi(T) selectMax(list_psi(T) p, int n);        //TODO:在位置p及其n-1个后继中选出最大者
    list_psi(T) selectMax(){        //选出整体最大者
        return selectMax(header->succ, _size);
    };
    /******************可写访问接口***************************************/
    list_psi(T) insertAsFirst(const T& e);      //讲元素e当做首节点插入
    list_psi(T) insertAsLast(const T& e);      //讲元素e当做末节点插入
    list_psi(T) insertA(list_psi(T) p, const T& e);      //讲元素e当做位置p的后继插入
    list_psi(T) insertB(list_psi(T) p, const T& e);      //讲元素e当做位置p的前驱插入
    T remove(list_psi(T) p);        //删除合法位置p的节点，并返回其元素值
    void sort(list_psi(T) p, int n);    //列表区间排序
    void sort(){    //列表整体排序
        sort(first(), _size);
    };
    int deduplicate();      //无序向量去重
    int uniqufy();      //有序向量去重
    void reverse();      //翻转
    void traverse(void (*)(T&));    //函数指针遍历
    template<typename VST> void traverse(VST&);     //函数对象遍历
};


#endif //DSA_LIST_H
