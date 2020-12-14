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
    cout << "���Ƚ���һ������!" << endl;
    cout << "���������ȵ�������";
    string ancestor_name;
    cin >> ancestor_name;
    FamilyTree familytree(ancestor_name);
    cout << "�˼��׵������ǣ�" << ancestor_name << endl
         << endl;
    bool sign_in = true;
    while (sign_in)
    {
        char choice;
        cout << "��ѡ��Ҫִ�еĲ���:";
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
            cout << "ϵͳ�˳�" << endl;
            sign_in = false;
            break;
        case 'F':
            familytree.Display();
            break;
        default:
            cout << "��֧��ָ���������������������" << endl
                 << endl;
        }
    }
    return 0;
}

void ShowHelp()
{
    cout << left << setw(50) << "**               ���׹���ϵͳ             \t**" << endl;
    cout << left << setw(50) << "==================================================" << endl;
    cout << left << setw(50) << "**            ��ѡ��Ҫִ�еĲ���:          \t**" << endl;
    cout << left << setw(50) << "**               A --- ���Ƽ���           \t**" << endl;
    cout << left << setw(50) << "**               B --- ��Ӽ�ͥ��Ա        \t**" << endl;
    cout << left << setw(50) << "**               C --- ��ɢ�ֲ���ͥ        \t**" << endl;
    cout << left << setw(50) << "**               D --- ���ļ�ͥ��Ա����    \t**" << endl;
    cout << left << setw(50) << "**               E --- �˳�����           \t**" << endl;
    cout << left << setw(50) << "**               F --- ��ӡ����           \t**" << endl;
    cout << left << setw(50) << "==================================================" << endl;
}

void FamilyTree::EstablishAFamily()
{
    cout << "������Ҫ������ͥ���˵�������";
    string parent_name;
    cin >> parent_name;
    TreeNode<string> *parent = names_.Find(parent_name);
    if (parent == nullptr)
    {
        cout << "���˲��ڼ����У�������ͥʧ��" << endl
             << endl;
    }
    else
    {
        int child_num = 0;
        cout << "������" << parent_name << "�Ķ�Ů������";
        cin >> child_num;
        cout << "����������" << parent_name << "�Ķ�Ů��������";
        Queue<string> child_names;
        bool build_fail = false;
        for (int i = 0; i < child_num; ++i)
        {
            string child_name;
            cin >> child_name;
            if (names_.Find(child_name))
            {
                cout << "����Ϊ" << child_name << "�������ڼ�����" << endl;
                build_fail = true;
            }
            child_names.Enqueue(child_name);
        }
        if (build_fail == true)
        {
            cout << "���׽���ʧ��" << endl
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
    cout << "������Ҫ��Ӷ��ӣ���Ů�������˵�������";
    string parent_name;
    cin >> parent_name;
    TreeNode<string> *parent = names_.Find(parent_name);
    if (parent == nullptr)
    {
        cout << "���˲��ڼ����У���Ӽ�ͥ��Աʧ��" << endl
             << endl;
    }
    else
    {
        cout << "������" << parent_name << "����ӵĵĶ��ӣ���Ů������������";
        string child_name;
        cin >> child_name;
        if (names_.Find(child_name))
        {
            cout << child_name << "���ڼ����У���Ӽ�ͥ��Աʧ��" << endl
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
    cout << "������Ҫ��ɢ�ļ�ͥ���˵�������";
    string parent_name;
    cin >> parent_name;
    TreeNode<string> *parent = names_.Find(parent_name);
    if (parent == nullptr)
    {
        cout << "���˲��ڼ����У���ɢ��ͥʧ��" << endl
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
    cout << "������Ҫ�����������˵�Ŀǰ������";
    string old_name;
    cin >> old_name;
    TreeNode<string> *current = names_.Find(old_name);
    if (current == nullptr)
    {
        cout << "���˲��ڼ����У���������ʧ��" << endl
             << endl;
    }
    else
    {
        cout << "��������ĺ��������";
        string new_name;
        cin >> new_name;
        if (names_.Find(new_name))
        {
            cout << new_name << "���ڼ����У���Ӽ�ͥ��Աʧ��";
        }
        else
        {
            current->SetData(new_name);
            cout << old_name << "�Ѹ���Ϊ" << new_name;
        }
        cout << endl
             << endl;
    }
}
void FamilyTree::Display()
{
    names_.DisplayTree();
}