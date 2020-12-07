#ifndef _PROBLEM_3_H_
#define _PROBLEM_3_H_

#include "../../include/Stack/Stack.h"

enum Dir
{
    UNKNOWN,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NOWAY
};
enum Status
{
    AVAILABLE,
    RETURNED,
    ROUTE,
    WALL
};
const int MAX_SIZE = 50;
class Node
{
    friend void Construct_Maze(char c_maze[MAX_SIZE][MAX_SIZE], int maze_size, Node maze[MAX_SIZE][MAX_SIZE]);
    friend Stack<Node *> FindRoute(Node maze[MAX_SIZE][MAX_SIZE], Node *entry, Node *exit);
    friend void UpdateMaze(char c_maze[MAX_SIZE][MAX_SIZE], Stack<Node *> &route);
    friend void PrintMaze(char c_maze[MAX_SIZE][MAX_SIZE], int maze_size, const Node &begin, const Node &end);

public:
    Node(){};
    ~Node() {}
    Node *Next();
    Node *Advance();

private:
    int x_, y_;
    Dir in_, out_;
    Status status_;
};

Dir NextDir(Dir current)
{
    return Dir(current + 1);
}
void Construct_Maze(char c_maze[MAX_SIZE][MAX_SIZE], int maze_size, Node maze[MAX_SIZE][MAX_SIZE]);
Stack<Node *> FindRoute(Node **maze, Node *entry, Node *exit);
void UpdateMaze(char c_maze[MAX_SIZE][MAX_SIZE], Stack<Node *> &route);
void PrintMaze(char c_maze[MAX_SIZE][MAX_SIZE], int maze_size, const Node &begin, const Node &end);

#endif //!_PROBLEM_3_H_