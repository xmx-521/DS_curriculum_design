#ifndef _PROBLEM_1_H_
#define _PROBLEM_1_H_

#include <string>
#include "../lib/List.h"

using std::string;

enum Sex
{
    male,
    female
};

class Student
{
    friend class System;

public:
    Student(){};
    Student(int number, string name, Sex sex, int age, string test_type);
    ~Student() {}

private:
    int number_;
    string name_;
    Sex sex_;
    int age_;
    string test_type_;
};

class System
{
public:
    System();
    ~System() = default;

private:
    bool IsNumberSame(int number);
    List<Student> students_;
};

#endif // !_PROBLEM_1_H_