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
    cout << left << setw(50) << "**               �����㷨�Ƚ�             \t**" << endl;
    cout << left << setw(50) << "==================================================" << endl;
    cout << left << setw(50) << "**               1 --- ð������           \t**" << endl;
    cout << left << setw(50) << "**               2 --- ѡ������           \t**" << endl;
    cout << left << setw(50) << "**               3 --- ֱ�Ӳ�������        \t**" << endl;
    cout << left << setw(50) << "**               4 --- ϣ������           \t**" << endl;
    cout << left << setw(50) << "**               5 --- ��������           \t**" << endl;
    cout << left << setw(50) << "**               6 --- ������             \t**" << endl;
    cout << left << setw(50) << "**               7 --- �鲢����           \t**" << endl;
    cout << left << setw(50) << "**               8 --- ��������           \t**" << endl;
    cout << left << setw(50) << "**               9 --- �˳�����           \t**" << endl;
    cout << left << setw(50) << "==================================================" << endl;

    cout << "\n����Ҫ������������ĸ�����";
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
        cout << "��ѡ�������㷨��\t";
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            Record record = BubbleSort(vec);
            cout << "ð����������ʱ�䣺\t" << record.time_.count() << 's' << endl;
            cout << "ð������洢������\t" << record.space_ << endl;
            cout << "ð������Ƚϴ�����\t" << record.comp_ << endl;
            cout << "ð�����򽻻�������\t" << record.swap_ << endl;
            break;
        }
        case 2:
        {
            Record record = SelectSort(vec);
            cout << "ѡ����������ʱ�䣺\t" << record.time_.count() << 's' << endl;
            cout << "ѡ������洢������\t" << record.space_ << endl;
            cout << "ѡ������Ƚϴ�����\t" << record.comp_ << endl;
            cout << "ѡ�����򽻻�������\t" << record.swap_ << endl;
            break;
        }
        case 3:
        {
            Record record = InsertSort(vec);
            cout << "ֱ�Ӳ�����������ʱ�䣺\t" << record.time_.count() << 's' << endl;
            cout << "ֱ�Ӳ�������洢������\t" << record.space_ << endl;
            cout << "ֱ�Ӳ�������Ƚϴ�����\t" << record.comp_ << endl;
            cout << "ֱ�Ӳ������򽻻�������\t" << record.swap_ << endl;
            break;
        }
        case 4:
        {
            Record record = ShellSort(vec);
            cout << "ϣ����������ʱ�䣺\t" << record.time_.count() << 's' << endl;
            cout << "ϣ������洢������\t" << record.space_ << endl;
            cout << "ϣ������Ƚϴ�����\t" << record.comp_ << endl;
            cout << "ϣ�����򽻻�������\t" << record.swap_ << endl;
            break;
        }
        case 5:
        {
            Record record = QuickSort(vec);
            cout << "������������ʱ�䣺\t" << record.time_.count() << 's' << endl;
            cout << "��������洢������\t" << record.space_ << endl;
            cout << "��������Ƚϴ�����\t" << record.comp_ << endl;
            cout << "�������򽻻�������\t" << record.swap_ << endl;
            break;
        }
        case 6:
        {
            Record record = HeapSort(vec);
            cout << "����������ʱ�䣺\t" << record.time_.count() << 's' << endl;
            cout << "������洢������\t" << record.space_ << endl;
            cout << "������Ƚϴ�����\t" << record.comp_ << endl;
            cout << "�����򽻻�������\t" << record.swap_ << endl;
            break;
        }
        case 7:
        {
            Record record = MergeSort(vec);
            cout << "�鲢��������ʱ�䣺\t" << record.time_.count() << 's' << endl;
            cout << "�鲢����洢������\t" << record.space_ << endl;
            cout << "�鲢����Ƚϴ�����\t" << record.comp_ << endl;
            cout << "�鲢���򽻻�������\t" << record.swap_ << endl;
            break;
        }
        case 8:
        {
            Record record = RadixSort(vec);
            cout << "������������ʱ�䣺\t" << record.time_.count() << 's' << endl;
            cout << "��������洢������\t" << record.space_ << endl;
            cout << "��������Ƚϴ�����\t" << record.comp_ << endl;
            cout << "�������򽻻�������\t" << record.swap_ << endl;
            break;
        }
        case 9:
            cout << "��л���ʹ��" << endl;
            system("pause");
            sign_in = false;
            break;
        default:
            cout << "��֧��ָ���������������������" << endl
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