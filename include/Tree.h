#ifndef _TREE_H_
#define _TREE_H_

#include <iostream>
using std::cout;
using std::endl;
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

    void SetData(const T &data) { data_ = data; }
    void AddChild(const T &data)
    {
        TreeNode *child = new TreeNode(data);
        TreeNode *current = first_child_;
        if (current == nullptr)
        {
            first_child_ = child;
        }
        else
        {
            while (current->next_sibling_ != nullptr)
            {
                current = current->next_sibling_;
            }
            current->next_sibling_ = child;
        }
    }
    void ShowChilds()
    {
        if (first_child_ == nullptr)
        {
            cout << data_ << "无第一代子孙" << endl;
        }
        else
        {
            cout << data_ << "的第一代子孙是：";
            TreeNode<T> *current = first_child_;
            while (current != nullptr)
            {
                cout << current->data_ << ' ';
                current = current->next_sibling_;
            }
            cout << endl;
        }
    }

private:
    T data_;
    TreeNode *first_child_, *next_sibling_;
};

//左长子右兄弟的树
template <class T>
class Tree
{
public:
    Tree(TreeNode<T> *root = nullptr) : root_(root) {}
    Tree(const T &data) { root_ = new TreeNode<T>(data); }
    ~Tree() { Destroy(root_); }
    void SetRoot(const T &data) { root_ = new TreeNode<T>(data); }
    bool Empty() { return root_ == nullptr ? true : false; }
    TreeNode<T> *GetRoot() { return root_; }
    TreeNode<T> *GetParent(TreeNode<T> *child)
    {
        TreeNode<T> *parent;
        parent = FindParent(root_, child);
        return parent;
    }
    void Destroy(TreeNode<T> *node)
    {
        if (node != nullptr)
        {
            Destroy(node->first_child_);
            Destroy(node->next_sibling_);
            delete node;
        }
    }
    void RemoveSubTree(TreeNode<T> *sub_tree)
    {
        TreeNode<T> *parent = GetParent(sub_tree);
        TreeNode<T> *first_child = sub_tree->first_child_;
        TreeNode<T> *current = parent->first_child_;
        if (current == sub_tree)
        {
            current->first_child_ = sub_tree->next_sibling_;
        }
        else
        {
            while (current->next_sibling_ != sub_tree)
            {
                current = current->next_sibling_;
            }
            current->next_sibling_ = sub_tree->next_sibling_;
        }
        delete sub_tree;
        Destroy(first_child);
    }
    TreeNode<T> *Find(const T &data)
    {
        if (Empty())
        {
            return nullptr;
        }
        else
        {
            return Find(root_, data);
        }
    }
    TreeNode<T> *Find(TreeNode<T> *root, const T &data)
    {
        if (root->data_ == data)
        {
            return root;
        }
        else
        {
            TreeNode<T> *current = root->first_child_;
            TreeNode<T> *answer = nullptr;
            while (current != nullptr)
            {
                if (answer = Find(current, data))
                {
                    return answer;
                }
                current = current->next_sibling_;
            }
            return nullptr;
        }
    }
    void DisplayTree()
    {
        if (Empty())
        {
            cout << "Empty" << endl;
        }
        else
        {
            DisplayTree(root_);
        }
    }

    void DisplayTree(TreeNode<T> *root)
    {
        if (root != nullptr)
        {
            cout << "root:" << root->data_ << endl;
            TreeNode<T> *current = root->first_child_;
            cout << "childs:";
            if (current == nullptr)
            {
                cout << "None";
            }
            else
            {
                while (current != nullptr)
                {
                    cout << current->data_ << ' ';
                    current = current->next_sibling_;
                }
            }
            cout << endl
                 << endl;
            current = root->first_child_;
            while (current != nullptr)
            {
                DisplayTree(current);
                current = current->next_sibling_;
            }
        }
    }

    void AddChild(TreeNode<T> *parent, const T &child_data)
    {
        parent->AddChild(child_data);
    }

private:
    TreeNode<T> *FindParent(TreeNode<T> *root, TreeNode<T> *child)
    {
        TreeNode<T> *current = root->first_child_;
        TreeNode<T> *parent = nullptr;
        while (current != nullptr && current != child)
        {
            if ((parent = FindParent(current, child)) != nullptr)
            {
                return parent;
            }
            current = current->next_sibling_;
        }
        if (current != nullptr && current == child)
        {
            return root;
        }
        else
        {
            return nullptr;
        }
    }
    TreeNode<T> *root_;
};

#endif //!_TREE_H_