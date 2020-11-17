#include <iostream>
#include "Problem1.h"

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::ostream;

int main()
{
    System system;
    system.Loop();
    return 0;
}

Student::Student(int number, const string &name, char sex, int age, const string &test_type)
    : number_(number),
      name_(name),
      sex_(sex),
      age_(age),
      test_type_(test_type)
{
}

ostream &operator<<(ostream &os, const Student &rhs)
{
    os << rhs.number_ << '\t' << rhs.name_ << '\t'
       << rhs.sex_ << '\t' << rhs.age_ << '\t'
       << rhs.test_type_ << endl;
    return os;
}

System::System()
{
    cout << "首先请建立考生信息系统！" << endl;
    cout << "请输入考生人数：";
    int students_num = 0;
    cin >> students_num;
    cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别！" << endl;
    for (int i = 0; i < students_num; ++i)
    {
        int number = 0;
        string name;
        char sex;
        int age = 0;
        string test_type;
        cin >> number >> name >> sex >> age >> test_type;
        if (IsNumberSame(number))
        {
            --i;
            continue;
        }
        Student student(number, name, sex, age, test_type);
        students_.Insert(students_.GetLength(), student);
    }
    Display();
}

void System::Loop()
{
    bool sign_in = true;
    while (sign_in)
    {
        cout << "请选择你要进行的操作(1为插入，2为删除，3为查找，4为修改，5为统计，6为取消操作，0为退出系统)" << endl;
        cout << "请选择你要进行的操作：";
        int op;
        cin >> op;
        switch (op)
        {
        case insert:
            Insert();
            break;
        case erase:
            Erase();
            break;
        case search:
            Search();
            break;
        case modify:
            Modify();
            break;
        case statistic:
            Statistic();
            break;
        // case cancel:
        //     Cancel();
        //     break;
        case sign_out:
            sign_in = false;
            cout << "系统退出" << endl;
            break;

        default:
            cout << "您输入的操作不在系统规定范围内，请重新输入" << endl
                 << endl;
            break;
        }
    }
}

void System::Insert()
{
    int insert_pos = 0;
    while (true)
    {
        cout << "请输入你要插入的考生的位置：";
        cin >> insert_pos;
        if (insert_pos <= 0 || insert_pos > students_.GetLength() + 1)
        {
            cerr << "插入位置" << insert_pos << "无效,请重新输入插入位置" << endl
                 << endl;
            continue;
        }
        else
        {
            break;
        }
    }
    while (true)
    {
        cout << "请依次输入要插入的考生的考号，姓名，性别，年龄及报考类别！" << endl;
        int number = 0;
        string name;
        char sex;
        int age = 0;
        string test_type;
        cin >> number >> name >> sex >> age >> test_type;
        if (IsNumberSame(number))
        {
            continue;
        }
        else
        {
            Student student(number, name, sex, age, test_type);
            students_.Insert(insert_pos - 1, student);
            break;
        }
    }
    Display();
    return;
}

void System::Erase()
{
    while (true)
    {
        cout << "请输入要删除的考生的考号：";
        int erase_number = 0;
        cin >> erase_number;
        for (int i = 1; i <= students_.GetLength(); ++i)
        {
            if (students_[i].number_ == erase_number)
            {
                cout << "你删除的学生为：" << students_[i];
                students_.Erase(i);
                Display();
                return;
            }
        }
        cerr << "系统中无考号为" << erase_number << "的考生，请核对后重新输入" << endl
             << endl;
    }
}

void System::Search()
{
    cout << "请输入你要查找的考生的考号：";
    int search_number = 0;
    cin >> search_number;
    for (int i = 1; i <= students_.GetLength(); ++i)
    {
        if (students_[i].number_ == search_number)
        {
            cout << "您查找的考生的信息为：" << endl;
            cout << "考号" << '\t'
                 << "姓名" << '\t'
                 << "性别" << '\t'
                 << "年龄" << '\t'
                 << "报考类别" << endl;
            cout << students_[i]
                 << endl;
            return;
        }
    }
    cout << "系统中无考号为" << search_number << "的考生" << endl
         << endl;
}

void System::Modify()
{
    int modify_number = 0;
    while (true)
    {
        cout << "请输入你要改变信息的考生的考号：";
        cin >> modify_number;
        for (int i = 1; i <= students_.GetLength(); ++i)
        {
            if (students_[i].number_ == modify_number)
            {
                while (true)
                {
                    cout << "请依次输入要改变的考生的考号，姓名，性别，年龄及报考类别！" << endl;
                    int number = 0;
                    string name;
                    char sex;
                    int age = 0;
                    string test_type;
                    cin >> number >> name >> sex >> age >> test_type;
                    if (IsNumberSame(number))
                    {
                        continue;
                    }
                    else
                    {
                        Student student(number, name, sex, age, test_type);
                        students_[i] = student;
                        Display();
                        return;
                    }
                }
            }
        }
        cout << "系统中不存在考号为" << modify_number << "的考生,请核对后重新输入" << endl
             << endl;
    }
}

void System::Statistic()
{
    cout << "统计结果为：" << endl;
    {
        cout << "系统中共有" << students_.GetLength() << "名考生" << endl;
        int male_num = 0;
        int sum_age = 0;
        for (int i = 1; i <= students_.GetLength(); ++i)
        {
            sum_age += students_[i].age_;
            if (students_[i].sex_ == 'm')
            {
                male_num++;
            }
        }
        int female_num = students_.GetLength() - male_num;
        cout << "男生人数为" << male_num << ",女生人数为" << female_num << endl;
        float average_age = (float)sum_age / (float)students_.GetLength();
        printf("平均年龄为:%.2f", average_age);
        cout << endl
             << endl;
    }
}

bool System::IsNumberSame(int number)
{
    for (int i = 1; i <= students_.GetLength(); i++)
    {
        if (number == students_[i].number_)
        {
            cerr << "错误！考号为" << number << "的考生已在系统中，请核对后重新输入" << endl
                 << endl;
            return true;
        }
    }
    return false;
}

void System::Display()
{
    cout << endl;
    cout << "考号" << '\t'
         << "姓名" << '\t'
         << "性别" << '\t'
         << "年龄" << '\t'
         << "报考类别" << endl;
    for (int i = 1; i <= students_.GetLength(); i++)
    {
        cout << students_[i];
    }
    cout << endl;
}