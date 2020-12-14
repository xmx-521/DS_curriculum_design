#ifndef _PROBLEM8_H_
#define _PROBLEM8_H_

#include <iostream>
#include <iomanip>
#include "../../include/Graph.h"

using std::left;
using std::setw;
using std::string;

void ShowHelp();
void CreateVertices(Graph<string, int> &graph);
void AddEdges(Graph<string, int> &graph);

#endif