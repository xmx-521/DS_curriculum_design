#ifndef _STACK_H_
#define _STACK_H_

#include "../Vector/Vecotr.h"
#include <iostream>

using std::cerr;
using std::endl;

template <class T>
class Stack
{
public:
    Stack() {}
    ~Stack() {}
    bool Empty() { return !elems_.Size(); }
    void Push(const T &elem) { elems_.PushBack(elem); }
    T Pop()
    {
        if (Empty())
        {
            cerr << "栈已为空，无法弹出" << endl;
            system("pause");
            exit(1);
        }
        T temp = elems_[elems_.Size() - 1];
        elems_.Erase(elems_.Size() - 1);
        return temp;
    }
    T &Top()
    {
        if (Empty())
        {
            cerr << "栈已为空,无法取得栈顶元素" << endl;
            system("pause");
            exit(1);
        }
        return elems_[elems_.Size() - 1];
    }
    const T &Top() const
    {
        if (Empty())
        {
            cerr << "栈已为空,无法取得栈顶元素" << endl;
            system("pause");
            exit(1);
        }
        return elems_[elems_.Size() - 1];
    }

private:
    Vector<T> elems_;
};

#endif //!_STACK_H_