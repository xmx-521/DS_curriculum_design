#include "Problem8.h"

using std::cin;
using std::string;

int main()
{
    ShowHelp();
    bool sign_in = true;
    Graph<string, int> graph;
    MinSpanTree<string, int> min_span_tree;
    while (sign_in)
    {
        cout << "��ѡ�������";
        char choice;
        cin >> choice;
        switch (choice)
        {
        case 'A':
            graph.SetEmpty();
            CreateVertices(graph);
            break;
        case 'B':
            AddEdges(graph);
            break;
        case 'C':
            min_span_tree = graph.KruscalMST();
            cout << "����Kruscal��С��������" << endl
                 << endl;
            break;
        case 'D':
            graph.DisplayMST(min_span_tree);
            break;
        case 'E':
            sign_in = false;
            cout << "ϵͳ�˳�";
            break;
        default:
            cout << "��֧��ָ���������������������" << endl
                 << endl;
            break;
        }
    }
    return 0;
}

void ShowHelp()
{
    cout << left << setw(50) << "**               �������ģ��ϵͳ             \t**" << endl;
    cout << left << setw(50) << "==================================================" << endl;
    cout << left << setw(50) << "**               A --- ������������           \t**" << endl;
    cout << left << setw(50) << "**               B --- ��ӵ����ı�           \t**" << endl;
    cout << left << setw(50) << "**               C --- ������С������         \t**" << endl;
    cout << left << setw(50) << "**               D --- ��ʾ��С������         \t**" << endl;
    cout << left << setw(50) << "**               E --- �˳�����              \t**" << endl;
    cout << left << setw(50) << "==================================================" << endl;
}

void CreateVertices(Graph<string, int> &graph)
{
    cout << "�����붥��ĸ�����";
    int vertex_num = 0;
    cin >> vertex_num;
    cout << "�������������������ƣ�" << endl;
    for (int i = 0; i < vertex_num; ++i)
    {
        string name;
        cin >> name;
        graph.InsertVertex(name);
    }
    cout << "�����������" << endl
         << endl;
}

void AddEdges(Graph<string, int> &graph)
{
    while (true)
    {
        cout << "�������������㼰�ߣ�";
        string head, tail;
        int key;
        cin >> head >> tail >> key;
        if (head == "?" && tail == "?" && key == 0)
        {
            break;
        }
        graph.InsertEdgeByData(head, tail, key);
    }
    cout << endl;
}