#ifndef _PROBLEM_4_H
#define _PROBLEM_4_H
#include "../../include/Stack/Stack.h"
#include <string>
using std::string;

bool IsStringLegal(const string &s);                                        //判断输入是否合法
bool IsNumber(char c);                                                      //判断是否为数字
bool IsOperator(char c);                                                    //判断是否为操作符
bool IsUnaryOperator(char pre, char cur);                                   //判断是否为单目运算符
void InitString(string &s);                                                 //初始化算数表达式使得单目与双目运算符计算统一
void Calculate(Stack<double> &data, Stack<char> &op);                       //计算
void InfixToPostfix(const string &s, Stack<double> &data, Stack<char> &op); //将中缀表达式转为后缀表达式
double CalculatePostfix(Stack<double> &data, Stack<char> &op);              //计算后缀表达式

#endif //!_PROBLEM_4_H