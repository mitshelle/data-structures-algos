/*
 *Name: Michelle McGowan, 2001813382, CS 302-1003, Assignment 7
 *Description: priority queue mario kart
 *Input: file, racer's distance
 *Output: racers 
 */

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>

template <class t1, class t2>
class priorityQ
{
public:
    priorityQ();
    void push_back(const t1 &, const t2 &);
    void pop_front();
    void decreaseKey(const t1 &, const t2 &);
    t2 get_front() const;
    t1 get_front_key() const;
    bool isEmpty() const;

private:
    struct priorityType
    {
        t1 key;
        t2 value;
    };

    void bubbleUp(std::size_t);
    void bubbleDown(std::size_t);

    std::vector<priorityType> heapArray;
    std::unordered_map<t1, std::size_t> itemToPQ;
};

template <class t1, class t2>
priorityQ<t1, t2>::priorityQ()
{
    // have root start at i=1
    heapArray.resize(1);
}

template <class t1, class t2>
void priorityQ<t1, t2>::push_back(const t1 &key, const t2 &value)
{
    // add pt obj to back
    heapArray.push_back(priorityType());
    // set 
    heapArray[heapArray.size() - 1].key = key;
    heapArray[heapArray.size() - 1].value = value;
    // MAP IT TO LAST INDEX OF HEAP ARR
    itemToPQ[key] = heapArray.size() - 1;
    bubbleUp(heapArray.size() - 1);
}

template <class t1, class t2>
void priorityQ<t1, t2>::pop_front()
{
    // remove from the index tracker
    itemToPQ.erase(heapArray[1].key);
    // assign last elemetn to root pos
    heapArray[1] = heapArray[heapArray.size() - 1];
    // remove last element from heap since being placed in 1st
    heapArray.pop_back();
    // UPDATE ITEMTOPQ
    itemToPQ[heapArray[1].key] = 1;
    bubbleDown(1);
}

template <class t1, class t2>
void priorityQ<t1, t2>::decreaseKey(const t1 &key, const t2 &value)
{
    // update the val
    heapArray[itemToPQ[key]].value = value;
    bubbleUp(itemToPQ[key]);
}

template <class t1, class t2>
t2 priorityQ<t1, t2>::get_front() const
{
    // return root val
    return heapArray[1].value;
}

template <class t1, class t2>
t1 priorityQ<t1, t2>::get_front_key() const
{
    // return root key
    return heapArray[1].key;
}

template <class t1, class t2>
bool priorityQ<t1, t2>::isEmpty() const
{
    // [0] is empty root is stored in [1]
    if (heapArray.size() == 1)
    {
        return true;
    }

    return false;
}

template <class t1, class t2>
void priorityQ<t1, t2>::bubbleDown(std::size_t index)
{
    // get children
    int leftChild = index * 2;
    int rightChild = index * 2 + 1;
    int swapKid = rightChild;

    // compare which kid is smaller
    if (heapArray[leftChild].value < heapArray[rightChild].value)
    {
        swapKid = leftChild;
    }

    // if out of bounds, leave
    if (rightChild > heapArray.size() - 1 && leftChild > heapArray.size() - 1)
    {
        return;
    }

    // loop while index is less than the size of heap && val is greater than
    while (index < heapArray.size() && heapArray[index].value > heapArray[swapKid].value)
    {
        // switch the index in unordered map
        itemToPQ[heapArray[swapKid].key] = index;
        // save into temp
        auto temp = heapArray[index];
        // swap index with the smallest kid
        heapArray[index] = heapArray[swapKid];
        // swap kid with index
        heapArray[swapKid] = temp;

        // update index since it is now where kid was
        index = swapKid;

        // switch the index in unordered map
        itemToPQ[heapArray[index].key] = swapKid;

        // find smallest child
        leftChild = index * 2;
        rightChild = index * 2 + 1;
        swapKid = rightChild;

        if (heapArray[leftChild].value < heapArray[rightChild].value)
        {
            swapKid = leftChild;
        }

        // if out of bonds, leave
        if (rightChild > heapArray.size() - 1 && leftChild > heapArray.size() - 1)
        {
            break;
        }
    }
}

template <class t1, class t2>
void priorityQ<t1, t2>::bubbleUp(std::size_t index)
{
    // parent must smaller
    int parent = index / 2;

    // loop while index is bigger than 0 and parent is greater than index
    while (index > 1 && heapArray[parent].value > heapArray[index].value)
    {
        // save into temp
        auto temp = heapArray[parent];
        // switch the index in unordered map
        itemToPQ[heapArray[parent].key] = index;
        // swap
        heapArray[parent] = heapArray[index];
        heapArray[index] = temp;
        // update index
        index = parent;
        // switch the index in unordered map
        itemToPQ[heapArray[index].key] = parent;
        // check the next parent
        parent = parent / 2;
    }
}
