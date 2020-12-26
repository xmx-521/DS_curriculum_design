#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "Vector.h"
#include "UFSets.h"
#include "PriorQueue.h"

template <class T>
struct GreaterThan
{
    bool operator()(const T &lhs, const T &rhs)
    {
        return lhs > rhs;
    }
};
template <class Tv>
class Vertex
{
public:
    Vertex() : in_degree_(0), out_degree_(0) {}
    Vertex(const Tv &data) : data_(data), in_degree_(0), out_degree_(0) {}
    ~Vertex() {}

    Tv data_;
    int in_degree_, out_degree_;
};

template <class Te>
class Edge
{
public:
    Edge() {}
    Edge(const Te &key) : key_(key) {}
    ~Edge() {}

    Te key_;
};

template <class Tv, class Te>
class MSTEdgeNode
{
public:
    MSTEdgeNode() {}
    MSTEdgeNode(int head, int tail, const Te &key)
        : head_(head), tail_(tail), key_(key) {}
    ~MSTEdgeNode() {}
    bool operator>(const MSTEdgeNode<Tv, Te> &rhs) const { return key_ > rhs.key_; }

    int head_, tail_;
    Te key_;
};

template <class Tv, class Te>
class MinSpanTree
{
public:
    MinSpanTree() {}
    ~MinSpanTree() {}
    void Push(const MSTEdgeNode<Tv, Te> &edge) { edges_.PushBack(edge); }
    Vector<MSTEdgeNode<Tv, Te>> edges_;
};
template <class Tv, class Te>
class Graph
{
public:
    Graph() : num_v_(0), num_e_(0) {}
    ~Graph() {}

    void InsertVertex(const Tv &vertex)
    {
        for (int i = 0; i < num_v_; ++i)
        {
            edges_[i].PushBack(nullptr);
        }
        num_v_++;
        edges_.PushBack(Vector<Edge<Te> *>(num_v_, nullptr));
        vertices_.PushBack(Vertex<Tv>(vertex));
    }
    int FindPos(Tv data)
    {
        for (int i = 0; i < vertices_.Size(); ++i)
        {
            if (vertices_[i].data_ == data)
            {
                return i;
            }
        }
        return -1;
    }
    void InsertEdgeByData(Tv data_head, Tv data_tail, const Te &edge)
    {
        int head = FindPos(data_head);
        int tail = FindPos(data_tail);
        InsertEdge(head, tail, edge);
    }
    void InsertEdge(int head, int tail, const Te &edge)
    {
        edges_[head][tail] = new Edge<Te>(edge);
        num_e_++;
        vertices_[head].out_degree_++;
        vertices_[tail].in_degree_++;
    }

    MinSpanTree<Tv, Te> KruscalMST()
    {
        MinSpanTree<Tv, Te> mst;
        PriorQueue<MSTEdgeNode<Tv, Te>, GreaterThan<MSTEdgeNode<Tv, Te>>> edges_left;
        UFSets sets(num_v_);
        for (int head = 0; head < num_v_; ++head)
        {
            for (int tail = head + 1; tail < num_v_; ++tail)
            {
                if (edges_[head][tail] != nullptr)
                {
                    MSTEdgeNode<Tv, Te> edge(head, tail, edges_[head][tail]->key_);
                    edges_left.Enqueue(edge);
                }
            }
        }
        int cnt = 1;
        while (cnt <= num_v_ - 1)
        {
            MSTEdgeNode<Tv, Te> edge = edges_left.Dequeue();
            if (!sets.IsSame(edge.head_, edge.tail_))
            {
                sets.Union(edge.head_, edge.tail_);
                mst.Push(edge);
                cnt++;
            }
        }
        return mst;
    }

    void DisplayMST(const MinSpanTree<Tv, Te> &min_span_tree)
    {
        cout << "最小生成树的顶点及边为：" << endl
             << endl;
        for (int i = 0; i < min_span_tree.edges_.Size(); i++)
        {
            cout << vertices_[min_span_tree.edges_[i].head_].data_ << '-' << '(' << min_span_tree.edges_[i].key_ << ')' << "->" << vertices_[min_span_tree.edges_[i].tail_].data_
                 << '\t';
        }
        cout << endl
             << endl;
    }

    void SetEmpty()
    {
        num_v_ = num_e_ = 0;
        vertices_ = Vector<Vertex<Tv>>();
        edges_ = Vector<Vector<Edge<Te> *>>();
    }

    Vector<Vector<Tv>> ToplogicalSort()
    {
        int *count_in = new int[num_v_];
        memset(count_in, 0, num_v_ * sizeof(int));
        for (int head = 0; head < num_v_; head++)
        {
            for (int out = 0; out < num_v_; out++)
            {
                if (edges_[head][out] != nullptr)
                {
                    count_in[out]++;
                }
            }
        }
        int top = -1;
        for (int i = 0; i < num_v_; i++)
        {
            if (count_in[i] == 0)
            {
                count_in[i] = top;
                top = i;
            }
        }
        Vector<Vector<Tv>> sorted_vertices;
        int s = 0;
        for (int i = 0; i < num_v_; i++)
        {
            int v = top;
            top = count_in[top];
            if (s > sorted_vertices.Size() - 1)
            {
                Vector<Tv> a;
                a.PushBack(vertices_[v].data_);
                sorted_vertices.PushBack(a);
            }
            else
            {
                sorted_vertices[s].PushBack(vertices_[v].data_);
            }
            bool change_sem = false;
            for (int j = 0; j < num_v_; j++)
            {
                if (edges_[v][j] != nullptr)
                {
                    if (--count_in[j] == 0)
                    {
                        change_sem = true;
                        count_in[j] = top;
                        top = j;
                    }
                }
            }
            if (change_sem)
            {
                s++;
            }
        }
        return sorted_vertices;
    }

    int GetIndex(const Tv &data)
    {
        for (int i = 0; i < num_v_; ++i)
        {
            if (vertices_[i].data_ == data)
            {
                return i;
            }
        }
        return -1;
    }

private:
    int num_v_, num_e_;
    Vector<Vertex<Tv>> vertices_;
    Vector<Vector<Edge<Te> *>> edges_;
};

#endif //!_GRAPH_H_