/*
 *Name: Michelle McGowan, 2001813382, CS 302-1003, Assignment 4
 *Description: binary trees
 *Input: text file
 *Output: deciphered message
 */

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include "binTree.h"

int main()
{
    // declared vars
    std::ifstream iFile;
    std::string file;
    std::string nums;
    std::vector<char> letters;
    std::vector<std::string> prefixCodes;
    std::vector<int> freq;
    std::vector<binTree *> forest;
    binTree *t1, *t2, *temp, *t3;
    int l = 0;
    int fr = 0;
    int pos = 0;
    std::string str;
    std::string parse;

    // prompt for file
    std::cout << "Enter filename: ";
    // get file
    std::cin >> file;

    // open file
    iFile.open(file);

    // get the letters
    while (true)
    {
        // read in
        iFile >> l >> fr;
        // if at file end leave
        if (iFile.eof())
        {
            break;
        }

        // store in string vector
        letters.push_back(l);
        freq.push_back(fr);
    }

    // close file
    iFile.close();
    // prompt for 10101010 file
    std::cout << "Enter encrypted file: ";
    // get file
    std::cin >> file;

    // open file
    iFile.open(file);

    // get the letters
    getline(iFile, nums);

    // close file
    iFile.close();

    // create forest of binary trees,,, all just one node rn
    for (int i = 0; i < 30; i++)
    {
        forest.push_back(new binTree(letters[i], freq[i]));
    }

    // loop until there is only one element in the forest
    while (forest.size() != 1)
    {
        // set
        temp = forest[0];
        pos = 0;

        // loop until size of forest
        for (int i = 1; i < forest.size(); i++)
        {
            // get smallest
            if (temp->getFrequency() >= forest[i]->getFrequency())
            {
                // only set if they are not the same
                // keep whichever lett was found first w/ same freq
                if (temp->getFrequency() != forest[i]->getFrequency())
                {
                    temp = forest[i];
                    pos = i;
                }
            }
        }

        // set temp to binTree obj
        t1 = temp;

        // remove from vec
        forest.erase(forest.begin() + pos);

        // set
        temp = forest[0];
        pos = 0;

        // loop until size of forest
        for (int j = 0; j < forest.size(); j++)
        {
            // get second smallest
            if (temp->getFrequency() >= forest[j]->getFrequency())
            {
                // only set if they are not the same
                // keep whichever lett was found first w/ same freq
                if (temp->getFrequency() != forest[j]->getFrequency())
                {
                    temp = forest[j];
                    pos = j;
                }
            }
        }

        // set temp to binTree obj
        t2 = temp;

        // remove from vec
        forest.erase(forest.begin() + pos);

        // call to constructor to combine trees into one
        t3 = new binTree(t1, t2);

        // add back to vec
        forest.push_back(t3);
    }

    // get prefix codes for each letter
    for (int i = 0; i < 30; i++)
    {
        str = forest[0]->getPrefixCode(letters[i]);
        // reverse string
        str = std::string(str.rbegin(), str.rend() - 1);
        // add to vec
        prefixCodes.push_back(str);
    }

    // loop the size of the encoded input
    for (int i = 0; i < nums.size(); i++)
    {
        // get the next char of str[]
        parse += nums[i];
        // loop for each letter
        for (int j = 0; j < 30; j++)
        {
            // check if whats in parse
            // is = to any of codes
            if (parse == prefixCodes[j])
            {
                // output
                std::cout << letters[j];
                // reset
                parse = "";
                break;
            }
        }
    }
}