#ifndef _PROBLEM6_H_
#define _PROBLEM6_H_

#include "../../include/Tree.h"
#include "../../include/Queue.h"
#include <string>
using std::string;

class FamilyTree
{
public:
    FamilyTree(TreeNode<string> *root = nullptr) : names_(root){};
    FamilyTree(const string &name) : names_(name){};
    ~FamilyTree(){};
    void EstablishAFamily();
    void AddFamilyMember();
    void DissolveAFamily();
    void ChangeName();
    void Display();

private:
    Tree<string> names_;
};

void ShowHelp();

#endif //!_PROBLEM6_H_