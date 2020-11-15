#include <iostream>
#include "Problem1.h"

using std::cerr;
using std::cin;
using std::cout;
using std::endl;

int main()
{
    System system;
    return 0;
}

Student::Student(int number, string name, Sex sex, int age, string test_type)
    : number_(number),
      name_(name),
      sex_(sex),
      age_(age),
      test_type_(test_type)
{
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
        string str_sex;
        Sex sex;
        int age = 0;
        string test_type;
        cin >> number >> name >> str_sex >> age >> test_type;
        sex = (str_sex == "男") ? male : female;
        if (IsNumberSame(number))
        {
            --i;
            continue;
        }
        Student student(number, name, sex, age, test_type);
        students_.Insert(students_.GetLength(), student);
    }
}

bool System::IsNumberSame(int number)
{
    for (int i = 1; i <= students_.GetLength(); i++)
    {
        if (number == students_[i].number_)
        {
            cerr << "考号为" << number << "的考生已存在，请核对信息后重新输入" << endl;
            return true;
        }
    }
    return false;
}