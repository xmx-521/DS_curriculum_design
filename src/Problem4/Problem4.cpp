#include "Problem4.h"
#include <iostream>
#include <iterator>
#include <cmath>

using std::cin;
using std::cout;
using std::endl;

int main()
{
    cout << "�����������ʽ��֧��С��Ϊ������" << endl;
    cout << "����ʹ��+��-��*��/��%��^��(��)��Ϊ�������֧�ֵ�Ŀ�����" << endl;
    cout << "ͬʱ��ע������Ӣ�������������������������������в�Ҫ���пո�" << endl;
    cout << "��ȷʾ��:+1-3*(-4.2^5.1)%2.5" << endl
         << endl;
    while (true)
    {
        cout << "�������������ʽ:" << endl;
        string s;
        cin >> s;
        if (!IsStringLegal(s))
        {
            cout << "�������ʽ���Ϸ��������������������ʽ" << endl;
            continue;
        }
        InitString(s);
        Stack<double> data;
        Stack<char> op;
        InfixToPostfix(s, data, op);
        double answer = CalculatePostfix(data, op);
        cout << "The answer is " << answer << endl
             << endl;
        cout << "�Ƿ�������㣿(y/n):";
        char choice;
        cin >> choice;
        cout << endl;
        if (choice == 'n')
        {
            break;
        }
        else
        {
            continue;
        }
    }

    return 0;
}

bool IsStringLegal(const string &s)
{
    int cnt_l_bracket = 0;
    int cnt_r_bracket = 0;
    for (string::const_iterator iter = s.begin(); iter != s.end(); ++iter)
    {
        if (!IsNumber(*iter) && !IsOperator(*iter) && *iter != '.')
        {
            return false;
        }
        switch (*iter)
        {
        case '(':
            ++cnt_l_bracket;
            break;
        case ')':
            ++cnt_r_bracket;
            break;
        default:
            break;
        }
    }
    if (cnt_l_bracket != cnt_r_bracket)
    {
        return false;
    }
    return true;
}

bool IsNumber(char c)
{
    return (c >= '0' && c <= '9');
}

bool IsOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^' || c == '(' || c == ')');
}

bool IsUnaryOperator(char pre, char cur)
{
    return ((cur == '+' || cur == '-') && (IsOperator(pre) && pre != ')'));
}

void InitString(string &s)
{
    string::iterator iter = s.begin();
    if (*iter == '+' || *iter == '-')
    {
        s.insert(iter, 1, '0');
    }
    while (iter != s.end())
    {
        iter++;
        if (IsUnaryOperator(*(iter - 1), *iter))
        {
            *iter = *iter == '+' ? '>' : '<';
            s.insert(iter, 1, '0');
        }
    }
}

void Calculate(Stack<double> &data, Stack<char> &op)
{
    double num1 = data.Pop();
    double num2 = data.Pop();
    switch (op.Pop())
    {
    case '+':
    case '>':
        data.Push(num2 + num1);
        break;
    case '-':
    case '<':
        data.Push(num2 - num1);
        break;
    case '*':
        data.Push(num2 * num1);
        break;
    case '/':
        data.Push(num2 / num1);
        break;
    case '%':
        data.Push(static_cast<int>(num2) % static_cast<int>(num1));
        break;
    case '^':
        data.Push(pow(num2, num1));
        break;
    default:
        break;
    }
}

void InfixToPostfix(const string &s, Stack<double> &data, Stack<char> &op)
{
    int level[128];
    level['('] = level[')'] = 0;
    level['+'] = level['-'] = 1;
    level['*'] = level['/'] = level['%'] = 2;
    level['^'] = 3;
    level['<'] = level['>'] = 4;
    for (string::const_iterator iter = s.begin(); iter != s.end(); ++iter)
    {
        if (IsNumber(*iter)) //��charתΪdouble����ջ
        {
            double temp_int = 0;
            double temp_real = 0;
            for (; iter != s.end() && IsNumber(*iter); ++iter)
            {
                temp_int = temp_int * 10 + (*iter - '0');
            }
            if (*iter == '.')
            {
                for (++iter; iter != s.end() && IsNumber(*iter); ++iter)
                {
                    temp_real = temp_real * 10 + (*iter - '0');
                }
                while (temp_real >= 1)
                {
                    temp_real /= 10;
                }
            }
            data.Push(temp_int + temp_real);
            --iter;
        }
        else //��Ϊ�����
        {
            if (*iter == ')')
            {
                while (op.Top() != '(')
                {
                    Calculate(data, op);
                }
                op.Pop(); //����������
            }
            else if (*iter == '(')
            {
                op.Push(*iter);
            }
            else
            {
                while (!op.Empty() && level[op.Top()] >= level[*iter])
                {
                    Calculate(data, op);
                }
                op.Push(*iter);
            }
        }
    }
}

double CalculatePostfix(Stack<double> &data, Stack<char> &op)
{
    while (!op.Empty())
    {
        Calculate(data, op);
    }
    return data.Top();
}
