/*
 *Name: Michelle McGowan, 2001813382, CS 302-1003, Assignment 1
 *Description: program for doubly linked lists, iterators, template classes
 *Input: text file
 *Output: ordered & unordered values in list form
 */
#include <fstream>
#include <iostream>
#include <vector>

// prototype
bool isSolved(char[10][10], std::vector<std::string>, int &, int, int);
bool isHorizontalCheck(char[10][10], int, int, std::string);
bool isVerticalCheck(char[10][10], int, int, std::string);
bool isHorizontalCheck(char[10][10], int, int, std::string);
void putWordVertical(char[10][10], int, int, std::string);
void putWordHorizontal(char[10][10], int, int, std::string);
void clearWordVertical(char[10][10], int, int, std::string);
void clearWordHorizontal(char[10][10], int, int, std::string);

int main()
{
    // declared vars
    std::ifstream iFile;
    std::string file;
    std::string word;
    char arr[10][10] = {};
    std::vector<std::string> words;
    int wordsIndex = 0;

    char c = 0;

    // prompt for file
    std::cout << "Enter filename: ";
    // get file
    std::cin >> file;

    // open file
    iFile.open(file);

    // loop until 9th row
    for (int i = 0; i < 10; i++)
    {
        // loop until 9th col
        for (int j = 0; j < 10; j++)
        {
            // read in data
            iFile >> c;
            // store data
            arr[i][j] = c;
        }
    }

    // get the words
    while (true)
    {
        // read in
        iFile >> word;
        // if at file end leave
        if (iFile.eof())
        {
            break;
        }

        // store in string vector
        words.push_back(word);
    }

    if (isSolved(arr, words, wordsIndex, 0, 0))
    {
        // loop until 9th row
        for (int i = 0; i < 10; i++)
        {
            // loop until 9th col
            for (int j = 0; j < 10; j++)
            {
                // print data
                std::cout << arr[i][j];
            }
            std::cout << std::endl;
        }
    }
}

bool isSolved(char grid[10][10], std::vector<std::string> words, int &wordsIndex, int posX, int posY)
{

    int row = 0, col = 0;
    std::string temp = words[wordsIndex]; // ANKARA
    // loop until 9th row
    for (int i = 0; i < 10; i++)
    {
        // loop until 9th col
        for (int j = 0; j < 10; j++)
        {
            if (grid[i][j] == '-')
            {
                row = i;
                col = j;
                break;
            }
        }
    }

    for (int i = 0; i < words.size() - 1; i++)
    {
        if (isVerticalCheck(grid, row, col, temp))
        {
            putWordVertical(grid, row, col, temp);

            if (isSolved(grid, words, wordsIndex, posX, posY))
            {
                return true;
            }

            clearWordVertical(grid, row, col, temp);
        }

        if (isHorizontalCheck(grid, row, col, temp))
        {
            putWordHorizontal(grid, row, col, temp);

            if (isSolved(grid, words, wordsIndex, posX, posY))
            {
                return true;
            }

            clearWordHorizontal(grid, row, col, temp);
        }
    }

    // if returns false then push back into list
    return false;
}

bool isVerticalCheck(char grid[10][10], int row, int col, std::string wordToTest)
{
    int i = 0;
    int j = 0;
    int length = wordToTest.length();

    if (row - 1 >= 0)
    {
        if (grid[row - 1][col] == '-')
        {
            if (grid[row - 1][col] == wordToTest[0])
            {
                i = 1;
                j = 1;
            }
            else if (grid[row - 1][col] != wordToTest[0])
            {
                return false;
            }
        }
    }

    while (row < 10 && i < length)
    {
        if (grid[row][col] == '-')
        {
            col += 1;
        }
        else if (grid[row][col] == wordToTest[i])
        {
            col += 1;
        }
        row++;
        i++;
    }

    if (col == length)
        return true;

    return false;
}

bool isHorizontalCheck(char grid[10][10], int row, int col, std::string wordToTest)
{
    int i = 0;
    int j = 0;
    int length = wordToTest.length();

    if (col - 1 >= 0)
    {
        if (grid[row][col - 1] == '-')
        {
            if (grid[row][col - 1] == wordToTest[0])
            {
                i = 1;
                j = 1;
            }
            else if (grid[row][col - 1] != wordToTest[0])
            {
                return false;
            }
        }
    }

    while (col < 10 && i < length)
    {
        if (grid[row][col] == '-')
        {
            j += 1;
        }
        else if (grid[row][col] == wordToTest[i])
        {
            j += 1;
        }
        col++;
        i++;
    }

    if (j == length)
        return true;

    return false;
}

void putWordVertical(char grid[10][10], int r, int c, std::string word)
{
    int i = 0;
    int length = word.length();

    if (r - 1 >= 0)
    {
        if (grid[r - 1][c] == word[0])
        {
            i = 1;
        }
    }

    while (i < length)
    {
        grid[r][c] = word[i];
        i++;
        r++;
    }
}

void putWordHorizontal(char grid[10][10], int r, int c, std::string word)
{
    int i = 0;
    int length = word.length();

    if (r - 1 >= 0)
    {
        if (grid[r][c - 1] == word[0])
        {
            i = 1;
        }
    }

    while (i < length)
    {
        grid[r][c] = word[i];
        i++;
        c++;
    }
}

void clearWordVertical(char grid[10][10], int r, int c, std::string word)
{
    int i = 0;
    int length = word.length();

    if (r - 1 >= 0)
    {
        if (grid[r - 1][c] == word[0])
        {
            i = 1;
        }
    }

    while (i < length)
    {
        grid[r][c] = '-';
        r++;
    }
}

void clearWordHorizontal(char grid[10][10], int r, int c, std::string word)
{
    int i = 0;
    int length = word.length();

    if (c - 1 >= 0)
    {
        if (grid[r][c - 1] == word[0])
        {
            i = 1;
        }
    }

    while (i < length)
    {
        grid[r][c] = '-';
        c++;
    }
}
