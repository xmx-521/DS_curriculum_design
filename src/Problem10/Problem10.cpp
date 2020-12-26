#include "Problem10.h"
#include <iostream>
#include <ctime>

using std::cin;
using std::cout;
using std::default_random_engine;
using std::endl;
using std::left;
using std::setw;

int main()
{
    cout << left << setw(50) << "**               排序算法比较             \t**" << endl;
    cout << left << setw(50) << "==================================================" << endl;
    cout << left << setw(50) << "**               1 --- 冒泡排序           \t**" << endl;
    cout << left << setw(50) << "**               2 --- 选择排序           \t**" << endl;
    cout << left << setw(50) << "**               3 --- 直接插入排序        \t**" << endl;
    cout << left << setw(50) << "**               4 --- 希尔排序           \t**" << endl;
    cout << left << setw(50) << "**               5 --- 快速排序           \t**" << endl;
    cout << left << setw(50) << "**               6 --- 堆排序             \t**" << endl;
    cout << left << setw(50) << "**               7 --- 归并排序           \t**" << endl;
    cout << left << setw(50) << "**               8 --- 基数排序           \t**" << endl;
    cout << left << setw(50) << "**               9 --- 退出程序           \t**" << endl;
    cout << left << setw(50) << "==================================================" << endl;

    cout << "\n输入要产生的随机数的个数：";
    int num = 0;
    cin >> num;
    Vector<DATA> vec;
    default_random_engine e(time(0));
    for (int i = 0; i < num; ++i)
    {
        int temp = e();
        vec.PushBack(temp);
    }
    bool sign_in = true;
    while (sign_in)
    {
        cout << '\n';
        cout << "请选择排序算法：\t";
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            Record record = BubbleSort(vec);
            cout << "冒泡排序所用时间：\t" << record.time_.count() << 's' << endl;
            cout << "冒牌排序存储开销：\t" << record.space_ << endl;
            cout << "冒泡排序比较次数：\t" << record.comp_ << endl;
            cout << "冒泡排序交换次数：\t" << record.swap_ << endl;
            break;
        }
        case 2:
        {
            Record record = SelectSort(vec);
            cout << "选择排序所用时间：\t" << record.time_.count() << 's' << endl;
            cout << "选择排序存储开销：\t" << record.space_ << endl;
            cout << "选择排序比较次数：\t" << record.comp_ << endl;
            cout << "选择排序交换次数：\t" << record.swap_ << endl;
            break;
        }
        case 3:
        {
            Record record = InsertSort(vec);
            cout << "直接插入排序所用时间：\t" << record.time_.count() << 's' << endl;
            cout << "直接插入排序存储开销：\t" << record.space_ << endl;
            cout << "直接插入排序比较次数：\t" << record.comp_ << endl;
            cout << "直接插入排序交换次数：\t" << record.swap_ << endl;
            break;
        }
        case 4:
        {
            Record record = ShellSort(vec);
            cout << "希尔排序所用时间：\t" << record.time_.count() << 's' << endl;
            cout << "希尔排序存储开销：\t" << record.space_ << endl;
            cout << "希尔排序比较次数：\t" << record.comp_ << endl;
            cout << "希尔排序交换次数：\t" << record.swap_ << endl;
            break;
        }
        case 5:
        {
            Record record = QuickSort(vec);
            cout << "快速排序所用时间：\t" << record.time_.count() << 's' << endl;
            cout << "快速排序存储开销：\t" << record.space_ << endl;
            cout << "快速排序比较次数：\t" << record.comp_ << endl;
            cout << "快速排序交换次数：\t" << record.swap_ << endl;
            break;
        }
        case 6:
        {
            Record record = HeapSort(vec);
            cout << "堆排序所用时间：\t" << record.time_.count() << 's' << endl;
            cout << "堆排序存储开销：\t" << record.space_ << endl;
            cout << "堆排序比较次数：\t" << record.comp_ << endl;
            cout << "堆排序交换次数：\t" << record.swap_ << endl;
            break;
        }
        case 7:
        {
            Record record = MergeSort(vec);
            cout << "归并排序所用时间：\t" << record.time_.count() << 's' << endl;
            cout << "归并排序存储开销：\t" << record.space_ << endl;
            cout << "归并排序比较次数：\t" << record.comp_ << endl;
            cout << "归并排序交换次数：\t" << record.swap_ << endl;
            break;
        }
        case 8:
        {
            Record record = RadixSort(vec);
            cout << "基数排序所用时间：\t" << record.time_.count() << 's' << endl;
            cout << "基数排序存储开销：\t" << record.space_ << endl;
            cout << "基数排序比较次数：\t" << record.comp_ << endl;
            cout << "基数排序交换次数：\t" << record.swap_ << endl;
            break;
        }
        case 9:
            cout << "感谢你的使用" << endl;
            system("pause");
            sign_in = false;
            break;
        default:
            cout << "不支持指定操作，请检查后重新输入" << endl
                 << endl;
            break;
        }
        // for (int i = 0; i < vec.Size(); ++i)
        // {
        //     cout << vec[i] << '\n';
        // }
    }
    return 0;
}