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
        cout << "请选择操作：";
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
            cout << "生成Kruscal最小生成树！" << endl
                 << endl;
            break;
        case 'D':
            graph.DisplayMST(min_span_tree);
            break;
        case 'E':
            sign_in = false;
            cout << "系统退出";
            break;
        default:
            cout << "不支持指定操作，请检查后重新输入" << endl
                 << endl;
            break;
        }
    }
    return 0;
}

void ShowHelp()
{
    cout << left << setw(50) << "**               电网造价模拟系统             \t**" << endl;
    cout << left << setw(50) << "==================================================" << endl;
    cout << left << setw(50) << "**               A --- 创建电网顶点           \t**" << endl;
    cout << left << setw(50) << "**               B --- 添加电网的边           \t**" << endl;
    cout << left << setw(50) << "**               C --- 构建最小生成树         \t**" << endl;
    cout << left << setw(50) << "**               D --- 显示最小生成树         \t**" << endl;
    cout << left << setw(50) << "**               E --- 退出程序              \t**" << endl;
    cout << left << setw(50) << "==================================================" << endl;
}

void CreateVertices(Graph<string, int> &graph)
{
    cout << "请输入顶点的个数：";
    int vertex_num = 0;
    cin >> vertex_num;
    cout << "请依次输入各顶点的名称：" << endl;
    for (int i = 0; i < vertex_num; ++i)
    {
        string name;
        cin >> name;
        graph.InsertVertex(name);
    }
    cout << "顶点输入完毕" << endl
         << endl;
}

void AddEdges(Graph<string, int> &graph)
{
    while (true)
    {
        cout << "请输入两个顶点及边：";
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