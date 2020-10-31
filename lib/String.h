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
	//KMP模式匹配
	//若串pattern与串*this中的某个字串匹配，
	//则函数返回第一次匹配时字串在串*this中的位置。
	// 
	//若串pattern为空或在串*this中没有匹配字串,
	//则函数返回-1

	int operator ==(const String& rhs)const { return strcmp(data_, rhs.data_) == 0; };
	//判断两字符串是否相等，若相等则返回1，若不相等则返回0
	int operator !=(const String& rhs)const { return strcmp(data_, rhs.data_) != 0; };
	//判断两字符串是否不等，若不等则返回1，若相等则返回0
	int operator!()const { return cur_length_ == 0; };
	//判断字符串是否为空，若为空则返回1，否则返回0
	String& operator=(const String& rhs);
	String& operator+=(const String& rhs);
	char& operator[](int index);
private:
	char* data_;		//字符串存放数组
	int cur_length_;	//字符串的实际长度
	int max_size_;		//存放数组的最大长度

	void GetNext(int next[])const;
};
#endif // ! _STRING_H_

