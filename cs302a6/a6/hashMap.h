/*
 *Name: Michelle McGowan, 2001813382, CS 302-1003, Assignment 6
 *Description: custom hashmap
 *Input: file, order food
 *Output: menu & total
 */

#include <iostream>
#include <vector>
#include <list>
#include <string.h>

template <class t1, class t2>
class hashMap
{
public:
    hashMap();
    t2 &operator[](t1);

    // PUT THIS SHIT BACK
private:
    struct keyVal
    {
        t1 key;
        t2 value;
    };
    
    std::vector<std::list<keyVal>> table;
    void resize(int);
    int hashFunction(std::string);
    static const int MAX_COLLISIONS = 5;
    int filledEntries;
};

template <class t1, class t2>
hashMap<t1, t2>::hashMap()
{
    filledEntries = 0;
    // this is the vector resize function
    table.resize(5);
}

template <class t1, class t2>
int hashMap<t1, t2>::hashFunction(std::string key)
{
    std::hash<std::string> result;
    return result(key);
}

// FIX!!!!!!!!!!!!!!
template <class t1, class t2>
t2 &hashMap<t1, t2>::operator[](t1 key)
{
    int index = 0;
    double div = (double)filledEntries / table.size();
    // if load factor bigger than 20%
    if (div >= .20)
    {
        // this is created function
        resize(table.size());
    }

    // get place
    index = hashFunction(key) % table.size();

    while (true)
    {
        auto it = table[index].begin();

        // if nothing in the table yet then insert it
        if (table[index].size() == 0)
        {
            table[index].insert(it, keyVal());
            auto newEle = table[index].begin();
            (*newEle).key = key;
            (*newEle).value = t2();
        }

        // iterator to point to first node of linked list from place index
        for (it = table[index].begin(); it != table[index].end(); it++)
        {
            // if key found
            if ((*it).key == key)
            {
                return (*it).value;
            }

            // if current key is greater than
            // means it is not there
            if ((*it).key > key && table[index].size() < MAX_COLLISIONS)
            {
                // insert new at spot of it
                // set new w/ values
                auto newElement = table[index].insert(it, keyVal());
                (*newElement).key = key;
                (*newElement).value = t2();

                // if list size now full then inc
                if (table[index].size() == MAX_COLLISIONS)
                {
                    filledEntries++;
                }

                return (*newElement).value;
            }
        }

        // if not found and list is maxed out
        if (table[index].size() == MAX_COLLISIONS)
        {
            // inc
            index = (index + 1) % table.size();

            // iterator to point to first node of linked list from place index
            continue;
        }

        // add to back of list since the for loop ended
        table[index].push_back(keyVal());
        auto newEle = table[index].end();
        newEle--;
        (*newEle).key = key;
        (*newEle).value = t2();

        // if list size now full then inc
        if (table[index].size() == MAX_COLLISIONS)
        {
            filledEntries++;
        }

        return (*newEle).value;
    }
}

template <class t1, class t2>
void hashMap<t1, t2>::resize(int amount)
{
    // declared vars
    int index = 0;
    bool exit = false;
    int oldSize = table.size();
    // save everything in da table into a temp table
    std::vector<std::list<keyVal>> tempTable(table);
    table.clear();
    // resize table
    this->table.resize(oldSize + amount);
    // reset filled entries
    filledEntries = 0;

    // loop through old table
    for (int i = 0; i < tempTable.size(); i++)
    {
        for (auto it = tempTable[i].begin(); it != tempTable[i].end(); it++)
        {
            exit = false;
            if ((*it).value != t2(0, 0)) // if has default values then dont remap
            {
                index = hashFunction((*it).key) % table.size();

                while (true)
                {
                    auto it2 = table[index].begin();

                    // if nothing in the table yet then insert it
                    if (table[index].size() == 0)
                    {
                        table[index].insert(it2, keyVal());
                        auto newEle = table[index].begin();
                        (*newEle).key = (*it).key;
                        (*newEle).value = (*it).value;
                        break;
                    }

                    // iterator to point to first node of linked list from place index
                    for (it2 = table[index].begin(); it2 != table[index].end(); it2++)
                    {
                        // if current key is greater than
                        // means it is not there
                        if ((*it2).key > (*it).key && table[index].size() < MAX_COLLISIONS)
                        {
                            // set new w/ values
                            auto newElement = table[index].insert(it, keyVal());
                            (*newElement).key = (*it).key;
                            (*newElement).value = (*it).value;

                            if (table[index].size() == MAX_COLLISIONS)
                            {
                                filledEntries++;
                            }
                            // exit loop & dont add to back of list
                            exit = true;
                            break;
                        }
                    }

                    // if not found and list is maxed out
                    if (table[index].size() == MAX_COLLISIONS)
                    {
                        // inc
                        index = (index + 1) % table.size();

                        // iterator to point to first node of linked list from place index
                        continue;
                    }

                    if (!exit)
                    {
                        // add to back of list since for loop done
                        table[index].push_back(keyVal());
                        auto newEle = table[index].end();
                        newEle--;
                        (*newEle).key = (*it).key;
                        (*newEle).value = (*it).value;
                        // if list size now full then inc
                        if (table[index].size() == MAX_COLLISIONS)
                        {
                            filledEntries++;
                        }
                        break;
                    }
                }
            }
        }
    }
}