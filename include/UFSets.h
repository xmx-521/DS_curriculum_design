#ifndef _UF_SETS_H_
#define _UF_SETS_H_

#include <cstring>
using std::memset;
const int DEFAULT_SIZE = 10;

class UFSets
{
public:
    UFSets(int size = DEFAULT_SIZE);
    ~UFSets() { delete[] parent_; }
    int FindRoot(int index);
    void Union(int elem1, int elem2);
    bool IsSame(int elem1, int elem2);

private:
    int *parent_;
    int size_;
};

UFSets::UFSets(int size)
{
    size_ = size;
    parent_ = new int[size];
    memset(parent_, -1, sizeof(int) * size);
}

int UFSets::FindRoot(int index)
{
    int root = index;
    while (parent_[root] >= 0)
    {
        root = parent_[root];
    }
    while (index != root)
    {
        int parent = parent_[index];
        parent_[index] = root;
        index = parent;
    }
    return root;
}

void UFSets::Union(int elem1, int elem2)
{
    int root1 = FindRoot(elem1);
    int root2 = FindRoot(elem2);
    if (root1 != root2)
    {
        int elem_num = parent_[root1] + parent_[root2];
        if (parent_[root1] > parent_[root2])
        {
            parent_[root1] = root2;
            parent_[root2] = elem_num;
        }
        else
        {
            parent_[root2] = root1;
            parent_[root1] = elem_num;
        }
    }
}

bool UFSets::IsSame(int elem1, int elem2)
{
    int root1 = FindRoot(elem1);
    int root2 = FindRoot(elem2);
    return root1 == root2;
}
#endif //!_UF_SETS_H_