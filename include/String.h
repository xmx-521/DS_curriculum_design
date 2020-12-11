#ifndef _STRING_H_
#define _STRING_H_

#include <cstring>
#include <exception>
#include <iostream>
const int default_size = 10;
class String
{
public:
	String(int size = default_size);
	String(const char *init);
	String(const String &init); //copy constructor
	~String() { delete[] data_; };

	int GetLength() const { return cur_length_; };
	String GetSubString(int begin_pos, int length) const;
	int PatternMatching(const String &pattern, int start_pos = 0) const;
	//KMP模式匹配
	//若串pattern与串*this中的某个字串匹配，
	//则函数返回第一次匹配时字串在串*this中的位置。
	//
	//若串pattern为空或在串*this中没有匹配字串,
	//则函数返回-1

	int operator==(const String &rhs) const { return strcmp(data_, rhs.data_) == 0; };
	//判断两字符串是否相等，若相等则返回1，若不相等则返回0
	int operator!=(const String &rhs) const { return strcmp(data_, rhs.data_) != 0; };
	//判断两字符串是否不等，若不等则返回1，若相等则返回0
	int operator!() const { return cur_length_ == 0; };
	//判断字符串是否为空，若为空则返回1，否则返回0
	String &operator=(const String &rhs);
	String &operator+=(const String &rhs);
	char &operator[](int index);

private:
	char *data_;	 //字符串存放数组
	int cur_length_; //字符串的实际长度
	int max_size_;	 //存放数组的最大长度

	void GetNext(int next[]) const;
};

String::String(int size)
	: max_size_(size)
{
	try
	{
		data_ = new char[max_size_ + 1];
	}
	catch (std::bad_alloc ex)
	{
		std::cerr << ex.what() << std::endl;
		exit(1);
	}
	cur_length_ = 0;
	data_[0] = '\0';
}

String::String(const char *init)
	: max_size_(strlen(init))
{
	try
	{
		data_ = new char[max_size_ + 1];
	}
	catch (std::bad_alloc ex)
	{
		std::cerr << ex.what() << std::endl;
		exit(1);
	}
	cur_length_ = strlen(init);
	strcpy(data_, init);
}

String::String(const String &init)
	: max_size_(init.max_size_)
{
	try
	{
		data_ = new char[max_size_ + 1];
	}
	catch (std::bad_alloc ex)
	{
		std::cerr << ex.what() << std::endl;
		exit(1);
	}
	cur_length_ = init.cur_length_;
	strcpy(data_, init.data_);
}

String String::GetSubString(int begin_pos, int length) const
{
	if (begin_pos < 0 || length < 0 || begin_pos + length > max_size_)
	{
		String sub_string(0);
		return sub_string;
	}
	else
	{
		if (begin_pos + length > cur_length_)
		{
			length = cur_length_ - begin_pos;
		}
		String sub_string(length);
		sub_string.cur_length_ = length;
		for (int i = 0, j = begin_pos; i < length; i++, j++)
		{
			sub_string.data_[i] = data_[j];
		}
		sub_string.data_[length] = '\0';
		return sub_string;
	}
}

int String::PatternMatching(const String &pattern, int start_pos) const
{
	int *next = nullptr;
	try
	{
		next = new int[cur_length_];
	}
	catch (std::bad_alloc ex)
	{
		std::cerr << ex.what() << std::endl;
		exit(1);
	}
	GetNext(next);
	int pos_p = 0, pos_t = start_pos;
	int length_p = pattern.cur_length_;
	int length_t = cur_length_;
	while (pos_p < length_p && pos_t < length_t) //????×?·????????¨?è
	{
		if (pos_p == -1 || pattern.data_[pos_p] == data_[pos_t]) //????×?·?????
		{
			pos_p++;
			pos_t++;
		}
		else
		{
			pos_p = next[pos_p];
		}
	}
	delete[] next;
	if (pos_p < length_p)
	{
		return -1;
	}
	else
	{
		return pos_t - length_p;
	}
}

void String::GetNext(int next[]) const
{
	next[0] = -1;
	int length_p = cur_length_;
	int j = 0, k = -1;
	while (j < length_p)
	{
		if (k == -1 || data_[j] == data_[k])
		{
			j++;
			k++;
			next[j] = k;
		}
		else
		{
			k = next[k];
		}
	}
}

String &String::operator=(const String &rhs)
{
	if (this != &rhs)
	{
		delete[] data_;
		try
		{
			data_ = new char[rhs.max_size_ + 1];
		}
		catch (std::bad_alloc ex)
		{
			std::cerr << ex.what() << std::endl;
			exit(1);
		}
		max_size_ = rhs.max_size_;
		cur_length_ = rhs.cur_length_;
		strcpy(data_, rhs.data_);
	}
	else
	{
		std::cerr << "×?·???×??í???????í??" << std::endl;
	}
	return *this;
}

String &String::operator+=(const String &rhs)
{
	char *original_data = data_;
	try
	{
		data_ = new char[cur_length_ + rhs.cur_length_];
	}
	catch (std::bad_alloc ex)
	{
		std::cerr << ex.what() << std::endl;
		exit(1);
	}
	cur_length_ += rhs.cur_length_;
	max_size_ = cur_length_;
	strcpy(data_, original_data);
	strcat(data_, rhs.data_);
	delete[] original_data;
	return *this;
}

char &String::operator[](int index)
{
	if (index < 0 || index >= cur_length_)
	{
		std::cerr << "×?·?????±ê??????" << std::endl;
		exit(1);
	}
	return data_[index];
}

#endif // ! _STRING_H_