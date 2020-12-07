
#ifndef _LIST_H_
#define _LIST_H_

//����ڵ�

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

//������ͷ����˫��ѭ������ͷ����±�Ϊ0���ɷ����±��1��ʼ
template <typename T>
class List
{
public:
	List();
	List(const List &rhs); //copy constructor
	~List() { Clear(); }
	void Clear();
	int GetLength() const;
	LinkNode<T> *GetHead() const { return first_; } //���ͷָ��
	LinkNode<T> *GetBegin() const { return first_->r_link_; }
	LinkNode<T> *GetEnd() const { return first_; }
	LinkNode<T> *Find(const T &data) const;	 //����������data�ĵ�һ���ڵ㲢�������ַ�����Ҳ��������Ľڵ��򷵻�null
	LinkNode<T> *GetAdress(int index) const; //���ص�index�ڵ�ĵ�ַ������ͷ���indexΪ0
	bool Insert(int index, T &data);		 //�ڵ�index�ڵ�����data,����ͷ���indexΪ0
	void PushBack(const T &data);
	bool Erase(int index); //ɾ����index�ڵ�,��ɾ���ڵ�index��1��ʼ
	bool IsEmpty() const { return first_->r_link_ == first_ ? true : false; }

	T &operator[](int index);		  //����subscript��������ɷ�����ʼλ��Ϊ1
	List &operator=(const List &rhs); //���ء�=�������

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
		cerr << "����λ��" << index << "��Ч" << endl;
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
		cerr << "ɾ��λ��" << index << "��Ч" << endl;
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
		cerr << "�������Խ�磡����λ��Ϊ" << index << endl;
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
