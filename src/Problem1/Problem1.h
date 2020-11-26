#ifndef _PROBLEM_1_H_
#define _PROBLEM_1_H_

#include <string>
#include <iostream>
#include "../../lib/List/List.h"

using std::ostream;
using std::string;

enum operation
{
    sign_out = 0,
    insert,
    erase,
    search,
    modify,
    statistic,
    cancel,
};

class Student
{
    friend class System;
    friend ostream &operator<<(ostream &os, const Student &rhs);

public:
    Student(){};
    Student(int number, const string &name, const string &sex, int age, const string &test_type);
    ~Student() {}

private:
    int number_;
    string name_;
    string sex_;
    int age_;
    string test_type_;
};

class System
{
public:
    System();
    ~System() = default;
    void Loop();

private:
    bool IsNumberSame(int number);
    void Display();
    void Insert();
    void Erase();
    void Search();
    void Modify();
    void Statistic();
    void Cancel();
    List<Student> students_;
};

#endif // !_PROBLEM_1_H_