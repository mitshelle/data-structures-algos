/*
 *Name: Michelle McGowan, 2001813382, CS 302-1003, Assignment 4
 *Description: binary trees
 *Input: text file
 *Output: deciphered message
 */

#include "binTree.h"

// default constructor - set root null
binTree::binTree()
{
    root = nullptr;
}

// constructor - allocate new obj & set params
binTree::binTree(char letter, int frequency)
{
    // allocate new obj
    root = new binTreeNode;

    // set from params
    root->letter = letter;
    root->frequency = frequency;

    // set to null
    root->left = nullptr;
    root->right = nullptr;
}

// constructor - combine two trees together
binTree::binTree(binTree *t1, binTree *t2)
{
    // allocate new obj
    root = new binTreeNode;

    // set to null char
    root->letter = '\0';

    // get freq of t1 & t2 add them together
    root->frequency = t1->getFrequency() + t2->getFrequency();

    // set to t1 root & t2 root
    root->left = t1->root;
    root->right = t2->root;
}

// destructor
binTree::~binTree()
{
    // call to recursive func to deallocate tree
    destroyTree(root);
}

// function to delete binary tree recursively
void binTree::destroyTree(binTreeNode *r)
{
    // base case nothing tree
    if (r == nullptr)
    {
        return;
    }

    // postorder deletion
    destroyTree(r->left);
    destroyTree(r->right);

    // starting node (root)
    delete r;
    r = nullptr;
}

// fucntion to return freq of root
int binTree::getFrequency() const
{
    return root->frequency;
}

// function to get binary str for prefix code
std::string binTree::getPrefixCode(char letter)
{
    // call to function to find leaf node & return str
    return getPrefixCode(root, letter);
}

// function to find leaf node w/ letter & return prefix string up tree
std::string binTree::getPrefixCode(binTreeNode *r, char letter)
{
    // declared vars
    std::string prefixCode = "";

    // check if leaf node && if not letter
    if (r->left == nullptr && r->right == nullptr && r->letter != letter)
    {
        return "";
    }

    // if is letter than return ; to know found letter
    if (r->letter == letter)
    {
        return ";";
    }

    // recursive call to go back up tree
    if (getPrefixCode(r->left, letter) != "")
    {
        // on the left so 0
        return getPrefixCode(r->left, letter) + "0";
    }

    if (getPrefixCode(r->right, letter) != "")
    {
        // on the right so 1
        return getPrefixCode(r->right, letter) + "1";
    }

    return prefixCode;
}

// void binTree::postorder(binTreeNode *r)
// {
//     if (r == nullptr)
//     {
//         return;
//     }

//     postorder(r->left);
//     postorder(r->right);

//     std::cout << r->letter << "|" << r->frequency << std::endl;

//     return;
// }
