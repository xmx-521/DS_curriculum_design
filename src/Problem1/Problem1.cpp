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

Student::Student(int number, const string &name, const string &sex, int age, const string &test_type)
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
    cout << "�����뽨��������Ϣϵͳ��" << endl;
    int students_num = 0;
    while (true)
    {
        cout << "�����뿼��������";
        cin >> students_num;
        if (students_num <= 0)
        {
            cout << "����������Ч������������";
        }
        else
        {
            break;
        }
    }
    cout << "���������뿼���Ŀ��ţ��������Ա����估�������" << endl;
    for (int i = 0; i < students_num; ++i)
    {
        int number = 0;
        string name;
        string sex;
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
        cout << "��ѡ����Ҫ���еĲ���(1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�6Ϊȡ��������0Ϊ�˳�ϵͳ)" << endl;
        cout << "��ѡ����Ҫ���еĲ�����";
        int operation;
        cin >> operation;
        switch (operation)
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
            cout << "ϵͳ�˳�" << endl;
            break;

        default:
            cout << "������Ĳ�������ϵͳ�涨��Χ�ڣ�����������" << endl
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
        cout << "��������Ҫ����Ŀ�����λ�ã�";
        cin >> insert_pos;
        if (insert_pos <= 0 || insert_pos > students_.GetLength() + 1)
        {
            cerr << "����λ��" << insert_pos << "��Ч,�������������λ��" << endl
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
        cout << "����������Ҫ����Ŀ����Ŀ��ţ��������Ա����估�������" << endl;
        int number = 0;
        string name;
        string sex;
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
        cout << "������Ҫɾ���Ŀ����Ŀ��ţ�";
        int erase_number = 0;
        cin >> erase_number;
        int index = 1;
        for (LinkNode<Student> *node = students_.GetBegin(); node != students_.GetEnd(); node = node->Next())
        {
            if (node->GetData().number_ == erase_number)
            {
                cout << "��ɾ����ѧ��Ϊ��" << node->GetData();
                students_.Erase(index);
                Display();
                return;
            }
            index++;
        }
        cerr << "ϵͳ���޿���Ϊ" << erase_number << "�Ŀ�������˶Ժ���������" << endl
             << endl;
    }
}

void System::Search()
{
    cout << "��������Ҫ���ҵĿ����Ŀ��ţ�";
    int search_number = 0;
    cin >> search_number;
    for (LinkNode<Student> *node = students_.GetBegin(); node != students_.GetEnd(); node = node->Next())
    {
        if (node->GetData().number_ == search_number)
        {
            cout << "�����ҵĿ�������ϢΪ��" << endl;
            cout << "����" << '\t'
                 << "����" << '\t'
                 << "�Ա�" << '\t'
                 << "����" << '\t'
                 << "�������" << endl;
            cout << node->GetData()
                 << endl;
            return;
        }
    }
    cout << "ϵͳ���޿���Ϊ" << search_number << "�Ŀ���" << endl
         << endl;
}

void System::Modify()
{
    int modify_number = 0;
    while (true)
    {
        cout << "��������Ҫ�ı���Ϣ�Ŀ����Ŀ��ţ�";
        cin >> modify_number;
        for (LinkNode<Student> *node = students_.GetBegin(); node != students_.GetEnd(); node = node->Next())
        {
            if (node->GetData().number_ == modify_number)
            {
                while (true)
                {
                    cout << "����������Ҫ�ı�Ŀ����Ŀ��ţ��������Ա����估�������" << endl;
                    int number = 0;
                    string name;
                    string sex;
                    int age = 0;
                    string test_type;
                    cin >> number >> name >> sex >> age >> test_type;
                    if (number != node->GetData().number_ && IsNumberSame(number))
                    {
                        continue;
                    }
                    else
                    {
                        Student student(number, name, sex, age, test_type);
                        node->SetData(student);
                        Display();
                        return;
                    }
                }
            }
        }
        cout << "ϵͳ�в����ڿ���Ϊ" << modify_number << "�Ŀ���,��˶Ժ���������" << endl
             << endl;
    }
}

void System::Statistic()
{
    cout << "ͳ�ƽ��Ϊ��" << endl;
    {
        cout << "ϵͳ�й���" << students_.GetLength() << "������" << endl;
        int male_num = 0;
        int sum_age = 0;
        for (LinkNode<Student> *node = students_.GetBegin(); node != students_.GetEnd(); node = node->Next())
        {
            sum_age += node->GetData().age_;
            if (node->GetData().sex_ == "��")
            {
                male_num++;
            }
        }
        int female_num = students_.GetLength() - male_num;
        cout << "��������Ϊ" << male_num << ",Ů������Ϊ" << female_num << endl;
        float average_age = (float)sum_age / (float)students_.GetLength();
        printf("ƽ������Ϊ:%.2f", average_age);
        cout << endl
             << endl;
    }
}

bool System::IsNumberSame(int number)
{
    for (LinkNode<Student> *node = students_.GetBegin(); node != students_.GetEnd(); node = node->Next())
    {
        if (number == node->GetData().number_)
        {
            cerr << "���󣡿���Ϊ" << number << "�Ŀ�������ϵͳ�У���˶Ժ���������" << endl
                 << endl;
            return true;
        }
    }
    return false;
}

void System::Display()
{
    cout << endl;
    cout << "����" << '\t'
         << "����" << '\t'
         << "�Ա�" << '\t'
         << "����" << '\t'
         << "�������" << endl;
    for (LinkNode<Student> *node = students_.GetBegin(); node != students_.GetEnd(); node = node->Next())
    {
        cout << node->GetData();
    }
    cout << endl;
}