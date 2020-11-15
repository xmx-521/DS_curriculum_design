#include "List.h"
#include <iostream>
using std::cerr;
using std::endl;

template <class T>
LinkNode<T> *List<T>::CreateNode(LinkNode<T> *l_link, LinkNode<T> *r_link) const
{
	try
	{
		first_ = new LinkNode<T>(l_link, r_link);
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
		first_ = new LinkNode<T>(data, l_link, r_link);
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
		ptr_rhs = ptr_rhs->r_link;
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
		temp = ptr;
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
	while (ptr != first)
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
	Init();
}
