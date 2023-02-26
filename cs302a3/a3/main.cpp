/*
 *Name: Michelle McGowan, 2001813382, CS 302-1003, Assignment 3
 *Description: program for solving crossword puzzle recursively
 *Input: text file
 *Output: solved crossword
 */
#include <fstream>
#include <iostream>
#include <vector>
#include <mutex>
#include <thread>

// global vars
std::vector<std::vector<int>> matA;
std::vector<std::vector<int>> matB;
std::vector<std::vector<int>> matC;
//std::mutex locks[4];
std::mutex lock;
// prototypes
void multiMat(int, int, int, int, int, int, int);

int main()
{
  // declared vars
  std::ifstream iFile;
  std::string file;
  int data = 0;
  int matDim = 0;
  int matDimHalf = 0;
  std::vector<std::thread> threadPool;

  // prompt for file
  std::cout << "Enter file: ";
  // get file
  std::cin >> file;

  // open file
  iFile.open(file);

  iFile >> matDim;

  // get matrix A
  matA.resize(matDim, std::vector<int>(matDim));

  // read in data to matrix A 
  for (int i = 0; i < matDim; i++)
  {
    for (int j = 0; j < matDim; j++)
    {
      iFile >> matA[i][j];
    }
  }

  // get matrix B
  matB.resize(matDim, std::vector<int>(matDim));

  // read in data to matrix B 
  for (int i = 0; i < matDim; i++)
  {
    for (int j = 0; j < matDim; j++)
    {
      iFile >> matB[i][j];
    }
  }

  // size matrix C
  matC.resize(matDim, std::vector<int>(matDim));

  // half the size 
  matDimHalf = matDim / 2;

  // for C11
  threadPool.push_back(std::thread(multiMat, matDimHalf, 0, 0, 0, 0, 0, 0));
  threadPool.push_back(std::thread(multiMat, matDimHalf, 0, 0, 0, matDimHalf, matDimHalf, 0)); 

  // for C12
  threadPool.push_back(std::thread(multiMat, matDimHalf, 0, matDimHalf, 0, 0, 0, matDimHalf));
  threadPool.push_back(std::thread(multiMat, matDimHalf, 0, matDimHalf, 0, matDimHalf, matDimHalf, matDimHalf));

  // for C21
  threadPool.push_back(std::thread(multiMat, matDimHalf, matDimHalf, 0, matDimHalf, 0, 0, 0));
  threadPool.push_back(std::thread(multiMat, matDimHalf, matDimHalf, 0, matDimHalf, matDimHalf, matDimHalf, 0));

  // for C22
  threadPool.push_back(std::thread(multiMat, matDimHalf, matDimHalf, matDimHalf, matDimHalf, 0, 0, matDimHalf));
  threadPool.push_back(std::thread(multiMat, matDimHalf, matDimHalf, matDimHalf, matDimHalf, matDimHalf, matDimHalf, matDimHalf)); 

  for (auto &t : threadPool)
    t.join();


  std::cout << "C Matrix" << std::endl;

  // output matrix
  for (int i = 0; i < matC.size(); i++)
  {
    for (int j = 0; j < matC[i].size(); j++)
      std::cout << matC[i][j] << " ";
    std::cout << std::endl;
  }
}

// func to multiply matrix f
void multiMat(int size, int rowC, int colC, int rowA, int colA, int rowB, int colB)
{

  // loop thru and save into matrix C
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      for (int m = 0; m < size; m++)
      {
        // row and col according to what submatrix on
        lock.lock(); // lock so thread writes one at a time
        matC[i + rowC][j + colC] += matA[i + rowA][m + colA] * matB[m + rowB][j + colB];
        lock.unlock(); // unlock so next thread can go 
      }
    }
  }
}