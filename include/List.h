
#ifndef _LIST_H_
#define _LIST_H_

//链表节点

template <class T>
class List; //forward declaration

template <class T>
class LinkNode
{
	friend class List<T>;

public:
	LinkNode(LinkNode *l_link = nullptr, LinkNode *r_link = nullptr)
		: l_link_(l_link), r_link_(r_link) {}
	LinkNode(const T &data, LinkNode *l_link = nullptr, LinkNode *r_link = nullptr)
		: data_(data), l_link_(l_link), r_link_(r_link) {}
	void SetData(const T &data) { data_ = data; }
	T &GetData() { return data_; }
	LinkNode *Next() { return r_link_; }

private:
	T data_;
	LinkNode *l_link_, *r_link_;
};

//带附加头结点的双向循环链表，头结点下标为0，可访问下标从1开始
template <typename T>
class List
{
public:
	List();
	List(const List &rhs); //copy constructor
	~List() { Clear(); }
	void Clear();
	int GetLength() const;
	LinkNode<T> *GetHead() const { return first_; } //获得头指针
	LinkNode<T> *GetBegin() const { return first_->r_link_; }
	LinkNode<T> *GetEnd() const { return first_; }
	LinkNode<T> *Find(const T &data) const;	 //搜索含数据data的第一个节点并返回其地址，若找不到这样的节点则返回null
	LinkNode<T> *GetAdress(int index) const; //返回第index节点的地址，附加头结点index为0
	bool Insert(int index, T &data);		 //在第index节点后插入data,附加头结点index为0
	void PushBack(const T &data);
	bool Erase(int index); //删除第index节点,可删除节点index从1开始
	bool IsEmpty() const { return first_->r_link_ == first_ ? true : false; }

	T &operator[](int index);		  //重载subscript运算符，可访问起始位置为1
	List &operator=(const List &rhs); //重载“=”运算符

private:
	LinkNode<T> *CreateNode(LinkNode<T> *l_link = nullptr, LinkNode<T> *r_link = nullptr) const;
	LinkNode<T> *CreateNode(const T &data, LinkNode<T> *l_link = nullptr, LinkNode<T> *r_link = nullptr) const;
	void Init(const List &rhs);
	LinkNode<T> *first_;
};

#include <iostream>
using std::cerr;
using std::endl;

template <class T>
LinkNode<T> *List<T>::CreateNode(LinkNode<T> *l_link, LinkNode<T> *r_link) const
{
	try
	{
		LinkNode<T> *new_node = new LinkNode<T>(l_link, r_link);
		return new_node;
	}
	catch (std::bad_alloc ex)
	{
		cerr << ex.what() << endl;
		exit(1);
	}
}

template <class T>
LinkNode<T> *List<T>::CreateNode(const T &data, LinkNode<T> *l_link, LinkNode<T> *r_link) const
{
	try
	{
		LinkNode<T> *new_node = new LinkNode<T>(data, l_link, r_link);
		return new_node;
	}
	catch (std::bad_alloc ex)
	{
		cerr << ex.what() << endl;
		exit(1);
	}
}

template <class T>
void List<T>::Init(const List &rhs)
{
	first_ = CreateNode();
	first_->l_link_ = first_->r_link_ = first_;
	LinkNode<T> *ptr_lhs = first_->r_link_;
	LinkNode<T> *ptr_rhs = rhs.first_->r_link_;
	while (ptr_rhs != rhs.first_)
	{
		LinkNode<T> *new_node = CreateNode(ptr_rhs->data_, ptr_lhs, first_);
		ptr_lhs->r_link_ = new_node;
		first_->l_link_ = new_node;
		ptr_lhs = new_node;
		ptr_rhs = ptr_rhs->r_link_;
	}
}

template <class T>
List<T>::List()
{
	first_ = CreateNode();
	first_->l_link_ = first_->r_link_ = first_;
}

template <class T>
List<T>::List(const List &rhs)
{
	Init(rhs);
}

template <class T>
void List<T>::Clear()
{
	LinkNode<T> *ptr = first_->r_link_;
	while (ptr != first_)
	{
		LinkNode<T> *temp = ptr;
		ptr = ptr->r_link_;
		delete temp;
	}
	delete first_;
}

template <class T>
int List<T>::GetLength() const
{
	int cnt = 0;
	LinkNode<T> *ptr = first_->r_link_;
	while (ptr != first_)
	{
		cnt++;
		ptr = ptr->r_link_;
	}
	return cnt;
}

template <class T>
LinkNode<T> *List<T>::Find(const T &data) const
{
	LinkNode<T> *ptr = first_->r_link_;
	while (ptr != first_)
	{
		if (ptr->data_ == data)
		{
			return ptr;
		}
		else
		{
			ptr = ptr->r_link_;
		}
	}
	return nullptr;
}

template <class T>
LinkNode<T> *List<T>::GetAdress(int index) const
{
	if (index < 0)
	{
		return nullptr;
	}
	LinkNode<T> *ptr = first_;
	for (int i = 0; i < index; i++)
	{
		ptr = ptr->r_link_;
		if (ptr == first_)
		{
			return nullptr;
		}
	}
	return ptr;
}

template <class T>
bool List<T>::Insert(int index, T &data)
{
	LinkNode<T> *insert_address = GetAdress(index);
	if (!insert_address)
	{
		cerr << "插入位置" << index << "无效" << endl;
		return false;
	}
	else
	{
		LinkNode<T> *new_node = CreateNode(data, insert_address, insert_address->r_link_);
		insert_address->r_link_ = new_node;
		new_node->r_link_->l_link_ = new_node;
		return true;
	}
}

template <class T>
void List<T>::PushBack(const T &data)
{
	LinkNode<T> *new_node = CreateNode(data, first_->l_link_, first_);
	first_->l_link_->r_link_ = new_node;
	first_->l_link_ = new_node;
}

template <class T>
bool List<T>::Erase(int index)
{
	LinkNode<T> *erase_address = GetAdress(index);
	if (index == 0 || !erase_address)
	{
		cerr << "删除位置" << index << "无效" << endl;
		return false;
	}
	else
	{
		erase_address->l_link_->r_link_ = erase_address->r_link_;
		erase_address->r_link_->l_link_ = erase_address->l_link_;
		delete erase_address;
		return true;
	}
}

template <class T>
T &List<T>::operator[](int index)
{
	LinkNode<T> *address = GetAdress(index);
	if (index == 0 || !address)
	{
		cerr << "链表访问越界！访问位置为" << index << endl;
		exit(1);
	}
	return address->data_;
}

template <class T>
List<T> &List<T>::operator=(const List &rhs)
{
	Clear();
	Init(rhs);
	return *this;
}
#endif // !_LIST_H_
