/*
 *Name: Michelle McGowan, 2001813382, CS 302-1003, Assignment 1
 *Description: program for doubly linked lists, iterators, template classes
 *Input: text file
 *Output: ordered & unordered values in list form
 */
#include "LL.h"
#include <fstream>
#include <iostream>

int main()
{
  // declared vars
  std::ifstream iFile;
  std::string file;
  LL<int> numList;
  LL<int>::Iterator i;
  LL<int>::Iterator j;
  LL<int>::Iterator j2;
  LL<int>::Iterator endSorted;
  LL<int>::Iterator begSorted;
  int num = 0;
  bool isSorted = false;

  // prompt for file
  std::cout << "Enter filename: ";
  // get file
  std::cin >> file;

  // open file
  iFile.open(file);

  // loop to read in data
  while (true)
  {
    // read in data
    iFile >> num;
    // when reach end of file
    if (iFile.fail())
    {
      iFile.clear();
      iFile.ignore(40, '\n');
      break;
    }
    numList.headInsert(num);
    if (iFile.eof())
    {
      break;
    }
  }  
  
  begSorted = nullptr;
  endSorted = nullptr;

  do
  {
    // reset
    isSorted = false;

    // if null them make it point to front of list  
    if (begSorted == nullptr)
    {
      begSorted = numList.begin();
    }

    // set j to be front of list + 1 
    j = begSorted;
    j++;
    
    // loop until j = null or j = the last sorted element 
    for (i = begSorted; j != endSorted; i++)
    {
      // if greater swap
      if (*i > *j)
      {
        numList.swapNodes(i, j);

        // check if need front of list was was swapped
        if (numList.begin() != begSorted)
        {
          // set to new head 
          begSorted = numList.begin();
        }
        // set 
        isSorted = true;
      }     

      j++;
    }

    // if nothing swapped, leave 
    if(!isSorted){
      break;
    }

    // last sorted item since j is pointing null on first run
    endSorted = i; 
    // set 
    j = endSorted;
    // last sorted - 1 
    j--; 
    // last sorted - 1 
    i = j;
    // lasted sorted - 2
    i--; 

    // check if head of list 
    if (begSorted == numList.begin())
    { 
      // make null so it fully checks all nums in list 
      begSorted = nullptr;
    }

    // loop until first sorted element of list, is null on first run
    for (i; i != begSorted; i--)
    {
      // if greater swap
      if (*i > *j)
      {
        numList.swapNodes(i, j);
        isSorted = true;
      }

      j--;
    }

    // set to front sorted element 
    begSorted = j; 

  } while (isSorted);
  
  // print out
  i = numList.begin();
  while (i != nullptr)
  {
    std::cout << *i << " ";
    i++;
  }
}