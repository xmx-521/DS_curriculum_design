#include "Problem2.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    cout << "输入分2行，分别在每行给出由若干个正整数构成的非降序序列，用-1表示序列的结尾（-1不属于这个序列）。数字用空格间隔" << endl;
    List<int> list1, list2, list3;
    cout << "请输入第一个链表" << endl;
    int temp_in = 0;
    while (temp_in != -1)
    {
        cin >> temp_in;
        list1.PushBack(temp_in);
    }
    list1.Erase(list1.GetLength());
    cout << "请输入第二个链表" << endl;
    temp_in = 0;
    while (temp_in != -1)
    {
        cin >> temp_in;
        list2.PushBack(temp_in);
    }
    list2.Erase(list2.GetLength());
    list3 = Intersect_list(list1, list2);
    if (!list3.GetLength())
    {
        cout << "NULL" << endl;
    }
    else
    {
        for (LinkNode<int> *p = list3.GetBegin(); p != list3.GetEnd(); p = p->Next())
        {
            cout << p->GetData() << ' ';
        }
        cout << endl;
    }
    return 0;
}