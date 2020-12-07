#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "../List/List.h"
#include <iostream>

using std::cerr;
using std::endl;

template <class T>
class Queue
{
public:
    Queue(){};
    ~Queue(){};

    bool Empty() { return elems_.IsEmpty(); }
    void Enqueue(const T &elem) { elems_.PushBack(elem); }
    T Dequeue()
    {
        if (Empty())
        {
            cerr << "������Ϊ�գ��޷�ɾ������Ԫ��" << endl;
            system("pause");
            exit(1);
        }
        T temp = elems_[1];
        elems_.Erase(1);
        return temp;
    }
    T &Front()
    {
        if (Empty())
        {
            cerr << "������Ϊ�գ��޷�ȡ�ö���Ԫ��" << endl;
            system("pause");
            exit(1);
        }
        return elems_[1];
    }
    const T &Front() const
    {
        if (Empty())
        {
            cerr << "������Ϊ�գ��޷�ȡ�ö���Ԫ��" << endl;
            system("pause");
            exit(1);
        }
        return elems_[1];
    }

private:
    List<T> elems_;
};

#endif //!_QUEUE_H_