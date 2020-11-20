#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <iostream>
using std::cerr;
using std::endl;
const int default_capacity = 3;

template <class T>
class Vector
{
public:
    Vector() : size_(0), capacity_(default_capacity)
    {
        elems_ = new T[default_capacity];
    }
    Vector(const Vector &rhs) { Init(rhs); }
    ~Vector() { delete[] elems_; }
    int Size() { return size_; }
    Vector &operator=(const Vector &rhs)
    {
        T *old_elems_ = elems_;
        Init(rhs);
        delete[] old_elems_;
        return *this;
    }
    T &operator[](int rank);
    const T &operator[](int rank) const;

    bool Insert(int rank, const T &elem);
    void PushBack(const T &elem);
    bool Erase(int rank_low, int rank_high);
    bool Erase(int rank);

private:
    void Init(const Vector &rhs);
    void Expand();
    T *elems_;
    int size_;     //当前储存元素个数
    int capacity_; //Vector最大容量
};

template <class T>
const T &Vector<T>::operator[](int rank) const
{
    if (rank < 0 || rank >= size_)
    {
        cerr << "Vector下标访问越界！" << endl;
        exit(1);
    }
    return elems_[rank];
}

template <class T>
T &Vector<T>::operator[](int rank)
{
    return const_cast<T &>(static_cast<const Vector &>(*this)[rank]);
}

template <class T>
bool Vector<T>::Insert(int rank, const T &elem)
{
    if (rank < 0 || rank > size_)
    {
        return false;
    }
    Expand();
    for (int i = size_; i > rank; i--)
    {
        elems_[i] = elems_[i - 1];
    }
    elems_[rank] = elem;
    size_++;
    return true;
}

template <class T>
void Vector<T>::PushBack(const T &elem)
{
    Expand();
    elems_[size_++] = elem;
    return;
}

template <class T>
bool Vector<T>::Erase(int rank_low, int rank_high)
{
    if (rank_low >= rank_high || rank_low < 0 || rank_high > size_)
    {
        return false;
    }
    while (rank_high < size_)
    {
        elems_[rank_low++] = elems_[rank_high++];
    }
    size_ = rank_low;
    return true;
}

template <class T>
bool Vector<T>::Erase(int rank)
{
    if (rank < 0 || rank >= size_)
    {
        return false;
    }
    Erase(rank, rank + 1);
    return true;
}
template <class T>
void Vector<T>::Init(const Vector &rhs)
{
    size_ = rhs.size_;
    capacity_ = rhs.capacity_;
    elems_ = new T[capacity_];
    for (int i = 0; i < rhs.size_; i++)
    {
        elems_[i] = rhs[i];
    }
}

template <class T>
void Vector<T>::Expand()
{
    if (size_ < capacity_)
    {
        return;
    }
    T *old_elems = elems_;
    capacity_ *= 2;
    elems_ = new T[capacity_];
    for (int i = 0; i <= size_; i++)
    {
        elems_[i] = old_elems[i];
    }
    delete[] old_elems;
    return;
}
#endif //!_VECTOR_H_