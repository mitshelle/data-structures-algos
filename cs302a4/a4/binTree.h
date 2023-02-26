/*
 *Name: Michelle McGowan, 2001813382, CS 302-1003, Assignment 4
 *Description: binary trees
 *Input: text file
 *Output: deciphered message
 */

#ifndef BINTREE
#define BINTREE
#include <iostream>
#include <string.h>

class binTree
{
    struct binTreeNode
    {
        char letter;
        int frequency;
        binTreeNode *left, *right;
    };

public:
    binTree();
    binTree(char, int);
    binTree(binTree *, binTree *);
    ~binTree();
    int getFrequency() const;
    void postorder(binTreeNode *);
    std::string getPrefixCode(char);

private:
    std::string getPrefixCode(binTreeNode *, char);
    void destroyTree(binTreeNode *);
    binTreeNode *root;
};

#endif