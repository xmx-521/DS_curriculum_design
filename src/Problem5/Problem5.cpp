#include "Problem5.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main()
{
    cout << "请输入一行正整数，其中第一数字为顾客总数，后面跟着N位顾客的编号" << endl;
    cout << "请输入:";
    int customer_num = 0;
    cin >> customer_num;
    Queue<int> window_A;
    Queue<int> window_B;
    for (int i = 0; i < customer_num; ++i)
    {
        int SerialNumber;
        cin >> SerialNumber;
        if (SerialNumber % 2)
        {
            window_A.Enqueue(SerialNumber);
        }
        else
        {
            window_B.Enqueue(SerialNumber);
        }
    }
    cout << "业务处理完成的顺序为:" << endl;
    while (!window_A.Empty() || !window_B.Empty())
    {
        for (int i = 0; i < 2; ++i)
        {
            if (!window_A.Empty())
            {
                cout << window_A.Dequeue() << ' ';
            }
        }
        if (!window_B.Empty())
        {
            cout << window_B.Dequeue() << ' ';
        }
    }
    cout << endl;
    system("pause");
    return 0;
}