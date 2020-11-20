#include "Problem3.h"
#include <iostream>
using std::cout;
using std::endl;
int main()
{
    //7*7的迷宫，入口为(1,1),出口为(1,5)
    char c_maze[MAX_SIZE][MAX_SIZE] = {
        {'#', '#', '#', '#', '#', '#', '#'},
        {'#', '0', '0', '0', '#', '0', '#'},
        {'#', '#', '0', '#', '#', '0', '#'},
        {'#', '0', '0', '0', '#', '0', '#'},
        {'#', '0', '#', '0', '0', '0', '#'},
        {'#', '#', '0', '0', '#', '0', '#'},
        {'#', '#', '#', '#', '#', '#', '#'}};
    Node maze[MAX_SIZE][MAX_SIZE];
    Construct_Maze(c_maze, 7, maze);
    Stack<Node *> route = FindRoute(maze, &maze[1][1], &maze[1][5]);
    UpdateMaze(c_maze, route);
    PrintMaze(c_maze, 7, maze[1][1], maze[1][5]);
    return 0;
}

Node *Node::Next()
{
    switch (out_)
    {
    case UP:
        return this - MAX_SIZE;
    case DOWN:
        return this + MAX_SIZE;
    case LEFT:
        return this - 1;
    case RIGHT:
        return this + 1;
    default:
        exit(1);
    }
}

Node *Node::Advance()
{
    Node *next;
    switch (out_)
    {
    case UP:
        next = this - MAX_SIZE;
        next->in_ = DOWN;
        break;
    case DOWN:
        next = this + MAX_SIZE;
        next->in_ = UP;
        break;
    case LEFT:
        next = this - 1;
        next->in_ = RIGHT;
        break;
    case RIGHT:
        next = this + 1;
        next->in_ = LEFT;
        break;
    default:
        exit(1);
    }
    return next;
}

void Construct_Maze(char c_maze[MAX_SIZE][MAX_SIZE], int maze_size, Node maze[MAX_SIZE][MAX_SIZE])
{
    for (int i = 0; i < maze_size; i++)
    {
        for (int j = 0; j < maze_size; j++)
        {
            maze[i][j].x_ = i;
            maze[i][j].y_ = j;
            switch (c_maze[i][j])
            {
            case '#':
                maze[i][j].status_ = WALL;
                break;
            case '0':
                maze[i][j].status_ = AVAILABLE;
                break;
            default:
                exit(1);
            }
        }
    }
}

Stack<Node *> FindRoute(Node[MAX_SIZE][MAX_SIZE], Node *entry, Node *exit)
{
    Node *current = entry;
    current->in_ = current->out_ = UNKNOWN;
    current->status_ = ROUTE;
    Stack<Node *> route;
    route.Push(current);
    while ((current = route.Top()) != exit)
    {
        while ((current->out_ = NextDir(current->out_)) < NOWAY)
        {
            if (current->Next()->status_ == AVAILABLE)
            {
                break;
            }
        }
        if (current->out_ == NOWAY)
        {
            current->status_ = RETURNED;
            route.Pop();
        }
        else
        {
            current = current->Advance();
            current->out_ = UNKNOWN;
            current->status_ = ROUTE;
            route.Push(current);
        }
    }
    return route;
}

void UpdateMaze(char c_maze[MAX_SIZE][MAX_SIZE], Stack<Node *> &route)
{
    Node *begin = route.Pop();
    c_maze[begin->x_][begin->y_] = 'E';
    Node *temp;
    while (!route.Empty())
    {
        temp = route.Pop();
        c_maze[temp->x_][temp->y_] = 'x';
    }
    c_maze[temp->x_][temp->y_] = 'B';
}

void PrintMaze(char c_maze[MAX_SIZE][MAX_SIZE], int maze_size, const Node &begin, const Node &end)
{
    cout << "起点为:(" << begin.x_ << "," << begin.y_ << ")" << endl;
    cout << "终点为:(" << end.x_ << "," << end.y_ << ")" << endl;
    cout << '\t';
    for (int i = 0; i < maze_size; i++)
    {
        cout << i << "列" << '\t';
    }
    cout << endl;
    for (int i = 0; i < maze_size; i++)
    {
        cout << i << "行" << '\t';
        for (int j = 0; j < maze_size; j++)
        {
            cout << c_maze[i][j] << '\t';
        }
        cout << endl;
    }
    return;
}