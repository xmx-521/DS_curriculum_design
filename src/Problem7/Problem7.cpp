#include "Problem7.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main()
{
    int wood_num;
    cout << "������Ҫ��ľͷ��ɵĿ���:";
    cin >> wood_num;
    cout << "������ÿ��ľͷ�ĳ���:" << endl;
    int cost_sum = 0;
    PriorQueue<int, GreaterThan<int>> prior_queue;
    for (int i = 0; i < wood_num; ++i)
    {
        int wood_length = 0;
        cin >> wood_length;
        prior_queue.Enqueue(wood_length);
    }
    while (prior_queue.Size() != 1)
    {
        int min_length1 = prior_queue.Dequeue();
        int min_length2 = prior_queue.Dequeue();
        int new_length = min_length1 + min_length2;
        cost_sum += new_length;
        prior_queue.Enqueue(new_length);
    }
    cout << "��ľͷ���" << wood_num << "�����С����Ϊ:" << cost_sum << endl;
    system("pause");
    return 0;
}