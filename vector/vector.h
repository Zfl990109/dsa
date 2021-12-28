//
// Created by zfl on 2021/12/28.
//

#ifndef DSA_VECTOR_H
#define DSA_VECTOR_H
#define DEFAULT_CAPACITY 5

template<typename T>
class vector {
protected:
    int _size{};
    int _capacity{};
    T* _ele;
    void copyFrom(const T* A, int lo, int hi);
    void expand();
    void shrink();

public:
    explicit vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0){   //构造函数
        _ele = new T[_capacity = c];
        for(_size = 0; _size < s; _size++){
            _ele[_size] = v;
        }
    }
    vector(const T* A, int n){ copyFrom(A, 0, n); }     //数组整体复制
    vector(const T* A, int lo, int hi){ copyFrom(A, lo, hi); }     //数组区间复制
    vector(vector<T> const& v){ copyFrom(v._ele, 0, v._size); }     //向量整体复制
    vector(vector<T> const& v, int lo, int hi){ copyFrom(v._ele, lo, hi); }     //向量区间复制
    ~vector(){ delete []_ele; }     //析构函数
    /***********************只读访问接口***********************************************/
    int size() const{ return _size; }
    bool empty() const{ return !_size; }
    int find(const T& e) const { return find(e, 0, _size); }    //无序向量整体查找
    int find(const T& e, int lo, int hi) const;     //无序向量区间查找
    int search(const T& e) const{   //有序向量整体查找
        return (_size <= 0) ? -1 : search(e, 0 , _size);
    }
    int search(const T& e, int lo, int hi) const;   //有序向量区间查找

    /*********************可写访问接口******************************************/
    T& operator[](int r) const;     //操作符重载,类似数组访问
    vector<T>& operator=(const vector<T>&);     //重载赋值操作符，以便直接克隆向量
    T remove(int r);    //删除单个元素,返回删除元素的值
    int remove(int lo, int hi);     //删除区间,返回删除元素的个数
    int insert(int r, const T& e);      //插入元素
    int insert(const T& e) { return insert(_size, e); }     //作为末尾元素插入
    void sort(int lo, int hi);      //排序
    void unsort(int lo, int hi);    //置乱
    int deduplicate();      //无序向量去重
    int uniqufy();      //有序向量去重

    /************遍历***********************************************************/
    void traverse( void(*) (T&) );      //使用函数指针遍历,只读或局部性修改
    template<typename vst> void traverse( vst& );      //使用函数对象遍历,可全局性修改

};

#endif //DSA_VECTOR_H
