#ifndef _STRING_H_
#define _STRING_H_

#include <cstring>
const int default_size = 10;
class String 
{
public:
	String(int size = default_size);
	String(const char* init);
	String(const String& init);	//copy constructor
	~String() { delete[]data_; };

	int GetLength()const { return cur_length_; };
	String GetSubString(int begin_pos, int length)const;
	int PatternMatching(const String& pattern,int start_pos = 0)const;
	//KMPģʽƥ��
	//����pattern�봮*this�е�ĳ���ִ�ƥ�䣬
	//�������ص�һ��ƥ��ʱ�ִ��ڴ�*this�е�λ�á�
	// 
	//����patternΪ�ջ��ڴ�*this��û��ƥ���ִ�,
	//��������-1

	int operator ==(const String& rhs)const { return strcmp(data_, rhs.data_) == 0; };
	//�ж����ַ����Ƿ���ȣ�������򷵻�1����������򷵻�0
	int operator !=(const String& rhs)const { return strcmp(data_, rhs.data_) != 0; };
	//�ж����ַ����Ƿ񲻵ȣ��������򷵻�1��������򷵻�0
	int operator!()const { return cur_length_ == 0; };
	//�ж��ַ����Ƿ�Ϊ�գ���Ϊ���򷵻�1�����򷵻�0
	String& operator=(const String& rhs);
	String& operator+=(const String& rhs);
	char& operator[](int index);
private:
	char* data_;		//�ַ����������
	int cur_length_;	//�ַ�����ʵ�ʳ���
	int max_size_;		//����������󳤶�

	void GetNext(int next[])const;
};
#endif // ! _STRING_H_

