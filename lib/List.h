#ifndef _LIST_H_
#define _LIST_H_

//��������ڵ�

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
	LinkNode<T> *Find(const T &data) const;			//����������data�ĵ�һ���ڵ㲢�������ַ�����Ҳ��������Ľڵ��򷵻�null
	LinkNode<T> *GetAdress(int index) const;		//���ص�index�ڵ�ĵ�ַ������ͷ���indexΪ0
	bool Insert(int index, T &data);				//�ڵ�index�ڵ�����data,����ͷ���indexΪ0
	bool Erase(int index);							//ɾ����index�ڵ�,��ɾ���ڵ�index��1��ʼ
	bool IsEmpty() const { return first_->r_link_ == nullptr ? true : false; }

	T &operator[](int index);		  //����subscript��������ɷ�����ʼλ��Ϊ1
	List &operator=(const List &rhs); //���ء�=�������
private:
	LinkNode<T> *CreateNode(LinkNode<T> *l_link = nullptr, LinkNode<T> *r_link = nullptr) const;
	LinkNode<T> *CreateNode(const T &data, LinkNode<T> *l_link = nullptr, LinkNode<T> *r_link = nullptr) const;
	void Init(const List &rhs);
	LinkNode<T> *first_;
};
#endif // !_LIST_H_
