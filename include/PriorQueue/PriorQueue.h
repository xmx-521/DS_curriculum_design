#ifndef _PRIOR_QUEUE_
#define _PRIOR_QUEUE_
#include "../Heap/heap.h"

template <class T, class Lt = less<T>>
class PriorQueue
{
public:
    PriorQueue() {}
    ~PriorQueue() {}

    bool Empty() { return elems_.Empty(); }
    int Size() { return elems_.Size(); }
    void Enqueue(const T &elem)
    {
        elems_.Insert(elem);
    }
    T &Front()
    {
        return elems_.GetMax();
    }
    const T &Front() const
    {
        return elems_.GetMax();
    }
    T Dequeue()
    {
        return elems_.DelMax();
    }
    void Display()
    {
        cout << "Priority queue elements:";
        if (!Empty())
        {
            elems_.Display();
        }
        else
        {
            cout << "Empty";
        }
        cout << '\n';
    }

private:
    Heap<T, Lt> elems_;
};
#endif