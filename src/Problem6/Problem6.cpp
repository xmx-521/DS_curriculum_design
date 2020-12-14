#include "Problem6.h"
#include <iostream>
#include <iomanip>

using std::cin;
using std::cout;
using std::endl;
using std::left;
using std::setw;

int main()
{
    ShowHelp();
    cout << "首先建立一个家谱!" << endl;
    cout << "请输入祖先的姓名：";
    string ancestor_name;
    cin >> ancestor_name;
    FamilyTree familytree(ancestor_name);
    cout << "此家谱的祖先是：" << ancestor_name << endl
         << endl;
    bool sign_in = true;
    while (sign_in)
    {
        char choice;
        cout << "请选择要执行的操作:";
        cin >> choice;
        switch (choice)
        {
        case 'A':
            familytree.EstablishAFamily();
            break;
        case 'B':
            familytree.AddFamilyMember();
            break;
        case 'C':
            familytree.DissolveAFamily();
            break;
        case 'D':
            familytree.ChangeName();
            break;
        case 'E':
            cout << "系统退出" << endl;
            sign_in = false;
            break;
        case 'F':
            familytree.Display();
            break;
        default:
            cout << "不支持指定操作，请检查后重新输入" << endl
                 << endl;
        }
    }
    return 0;
}

void ShowHelp()
{
    cout << left << setw(50) << "**               家谱管理系统             \t**" << endl;
    cout << left << setw(50) << "==================================================" << endl;
    cout << left << setw(50) << "**            请选择要执行的操作:          \t**" << endl;
    cout << left << setw(50) << "**               A --- 完善家谱           \t**" << endl;
    cout << left << setw(50) << "**               B --- 添加家庭成员        \t**" << endl;
    cout << left << setw(50) << "**               C --- 解散局部家庭        \t**" << endl;
    cout << left << setw(50) << "**               D --- 更改家庭成员姓名    \t**" << endl;
    cout << left << setw(50) << "**               E --- 退出程序           \t**" << endl;
    cout << left << setw(50) << "**               F --- 打印家谱           \t**" << endl;
    cout << left << setw(50) << "==================================================" << endl;
}

void FamilyTree::EstablishAFamily()
{
    cout << "请输入要建立家庭的人的姓名：";
    string parent_name;
    cin >> parent_name;
    TreeNode<string> *parent = names_.Find(parent_name);
    if (parent == nullptr)
    {
        cout << "此人不在家谱中，建立家庭失败" << endl
             << endl;
    }
    else
    {
        int child_num = 0;
        cout << "请输入" << parent_name << "的儿女个数：";
        cin >> child_num;
        cout << "请依次输入" << parent_name << "的儿女的姓名：";
        Queue<string> child_names;
        bool build_fail = false;
        for (int i = 0; i < child_num; ++i)
        {
            string child_name;
            cin >> child_name;
            if (names_.Find(child_name))
            {
                cout << "名字为" << child_name << "的人已在家谱中" << endl;
                build_fail = true;
            }
            child_names.Enqueue(child_name);
        }
        if (build_fail == true)
        {
            cout << "家谱建立失败" << endl
                 << endl;
            return;
        }
        while (!child_names.Empty())
        {
            string child_name = child_names.Dequeue();
            parent->AddChild(child_name);
        }
        parent->ShowChilds();
        cout << endl;
    }
}

void FamilyTree::AddFamilyMember()
{
    cout << "请输入要添加儿子（或女儿）的人的姓名：";
    string parent_name;
    cin >> parent_name;
    TreeNode<string> *parent = names_.Find(parent_name);
    if (parent == nullptr)
    {
        cout << "此人不在家谱中，添加家庭成员失败" << endl
             << endl;
    }
    else
    {
        cout << "请输入" << parent_name << "新添加的的儿子（或女儿）的姓名：";
        string child_name;
        cin >> child_name;
        if (names_.Find(child_name))
        {
            cout << child_name << "已在家谱中，添加家庭成员失败" << endl
                 << endl;
        }
        else
        {
            parent->AddChild(child_name);
            parent->ShowChilds();
            cout << endl;
        }
    }
}
void FamilyTree::DissolveAFamily()
{
    cout << "请输入要解散的家庭的人的姓名：";
    string parent_name;
    cin >> parent_name;
    TreeNode<string> *parent = names_.Find(parent_name);
    if (parent == nullptr)
    {
        cout << "此人不在家谱中，解散家庭失败" << endl
             << endl;
    }
    else
    {
        parent->ShowChilds();
        names_.RemoveSubTree(parent);
        cout << endl;
    }
}
void FamilyTree::ChangeName()
{
    cout << "请输入要更改姓名的人的目前姓名：";
    string old_name;
    cin >> old_name;
    TreeNode<string> *current = names_.Find(old_name);
    if (current == nullptr)
    {
        cout << "此人不在家谱中，更改姓名失败" << endl
             << endl;
    }
    else
    {
        cout << "请输入更改后的姓名：";
        string new_name;
        cin >> new_name;
        if (names_.Find(new_name))
        {
            cout << new_name << "已在家谱中，添加家庭成员失败";
        }
        else
        {
            current->SetData(new_name);
            cout << old_name << "已改名为" << new_name;
        }
        cout << endl
             << endl;
    }
}
void FamilyTree::Display()
{
    names_.DisplayTree();
}