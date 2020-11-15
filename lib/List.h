#ifndef _LIST_H_
#define _LIST_H_

//单向链表节点

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

private:
	T data_;
	LinkNode *l_link_, r_link_;
};

//带附加头结点的双向循环链表，头结点下表为0，可访问下标从1开始
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
	LinkNode<T> *Find(const T &data) const;			//搜索含数据data的第一个节点并返回其地址，若找不到这样的节点则返回null
	LinkNode<T> *GetAdress(int index) const;		//返回第index节点的地址，附加头结点index为0
	bool Insert(int index, T &data);				//在第index节点后插入data,附加头结点index为0
	bool Erase(int index);							//删除第index节点,可删除节点index从1开始
	bool IsEmpty() const { return first_->r_link_ == nullptr ? true : false; }

	T &operator[](int index);		  //重载subscript运算符，可访问起始位置为1
	List &operator=(const List &rhs); //重载“=”运算符
private:
	LinkNode<T> *CreateNode(LinkNode<T> *l_link = nullptr, LinkNode<T> *r_link = nullptr) const;
	LinkNode<T> *CreateNode(const T &data, LinkNode<T> *l_link = nullptr, LinkNode<T> *r_link = nullptr) const;
	void Init(const List &rhs);
	LinkNode<T> *first_;
};
#endif // !_LIST_H_
