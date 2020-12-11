#ifndef _TREE_H_
#define _TREE_H_

template <class T>
class Tree;

//左长子右兄弟的树节点
template <class T>
class TreeNode
{
    friend class Tree<T>;

public:
    TreeNode()
        : first_child_(nullptr), next_sibling_(nullptr) {}
    TreeNode(const T &data, TreeNode *fc = nullptr, TreeNode *ns = nullptr)
        : data_(data), first_child_(fc), next_sibling_(ns) {}
    ~TreeNode() {}

private:
    T data_;
    TreeNode *first_child_, next_sibling_;
};

//左长子右兄弟的树
template <class T>
class Tree
{
public:
    Tree() : root_(nullptr) {}
    void Erase(Tree *subtree);

private:
    TreeNode<T> *root_;
};

#endif //!_TREE_H_