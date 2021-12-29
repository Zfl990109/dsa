//
// Created by zfl on 2021/12/29.
//

#ifndef DSA_QUEUE_H
#define DSA_QUEUE_H
#include "../list/list.h"
template<typename T>
class queue : public list<T>{
public:
    void enqueue(const T& e) { insertAsLast(e); }

};


#endif //DSA_QUEUE_H
