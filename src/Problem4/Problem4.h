#ifndef _PROBLEM_4_H
#define _PROBLEM_4_H
#include "../../include/Stack/Stack.h"
#include <string>
using std::string;

bool IsStringLegal(const string &s);                                        //�ж������Ƿ�Ϸ�
bool IsNumber(char c);                                                      //�ж��Ƿ�Ϊ����
bool IsOperator(char c);                                                    //�ж��Ƿ�Ϊ������
bool IsUnaryOperator(char pre, char cur);                                   //�ж��Ƿ�Ϊ��Ŀ�����
void InitString(string &s);                                                 //��ʼ���������ʽʹ�õ�Ŀ��˫Ŀ���������ͳһ
void Calculate(Stack<double> &data, Stack<char> &op);                       //����
void InfixToPostfix(const string &s, Stack<double> &data, Stack<char> &op); //����׺���ʽתΪ��׺���ʽ
double CalculatePostfix(Stack<double> &data, Stack<char> &op);              //�����׺���ʽ

#endif //!_PROBLEM_4_H