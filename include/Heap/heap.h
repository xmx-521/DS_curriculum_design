#ifndef _HEAP_H_
#define _HEAP_H_

#include <functional>
#include <algorithm>
#include <iostream>
#include "../Vector/Vecotr.h"

using std::cout;
using std::less;
using std::swap;

template <class T, class Lt = less<T>> //默认为最大堆
class Heap
{
public:
    Heap() {}
    ~Heap() {}
    int Size() { return nodes_.Size(); }
    bool Empty() { return Size() ? false : true; }
    void Insert(const T &elem)
    {
        nodes_.PushBack(elem);
        AjustUp();
    }
    const T &GetMax() const
    {
        return nodes_[0];
    }
    T &GetMax()
    {
        return nodes_[0];
    }
    T DelMax()
    {
        T max_elem = nodes_[0];
        nodes_[0] = nodes_[Size() - 1];
        nodes_.Erase(Size() - 1);
        AjustDown();
        return max_elem;
    }
    void PrintHeap()
    {
        cout << "Heap elements:";
        if (!Empty())
        {
            Display();
        }
        else
        {
            cout << "Empty";
        }
        cout << '\n';
    }
    void Display()
    {
        for (int i = 0; i < Size(); ++i)
        {
            cout << nodes_[i] << ' ';
        }
    }

private:
    int Lc(int pr)
    {
        int ans = 0;
        return ((ans = 1 + pr * 2) <= Size() - 1) ? ans : -1;
    }
    int Rc(int pr)
    {
        int ans = 0;
        return ((ans = (1 + pr) * 2) <= Size() - 1) ? ans : -1;
    }
    int Pr(int c)
    {
        return (c > 0) ? (c - 1) / 2 : -1;
    }
    int FirstPriority(int pr)
    {
        int lc = Lc(pr);
        int rc = Rc(pr);
        int first_priority = pr;
        if (lc != -1 && lt_(nodes_[first_priority], nodes_[lc]))
        {
            first_priority = lc;
        }
        if (rc != -1 && lt_(nodes_[first_priority], nodes_[rc]))
        {
            first_priority = rc;
        }
        return first_priority;
    }
    void AjustUp() //入堆后上调整
    {
        int low = Size() - 1;
        int high = 0;
        while ((high = Pr(low)) != -1)
        {
            if (lt_(nodes_[low], nodes_[high]))
            {
                break;
            }
            swap(nodes_[low], nodes_[high]);
            low = high;
        }
    }
    void AjustDown() //出堆后下调整
    {
        int low = 0;
        int high = 0;
        while ((low = FirstPriority(high)) != high)
        {
            swap(nodes_[low], nodes_[high]);
            high = low;
        }
    }
    Lt lt_;
    Vector<T> nodes_;
};

#endif