#include "Problem7.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main()
{
    int wood_num;
    cout << "请输入要将木头锯成的块数:";
    cin >> wood_num;
    cout << "请输入每块木头的长度:" << endl;
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
    cout << "将木头锯成" << wood_num << "块的最小花费为:" << cost_sum << endl;
    system("pause");
    return 0;
}