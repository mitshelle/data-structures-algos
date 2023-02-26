/*
 *Name: Michelle McGowan, 2001813382, CS 302-1003, Assignment 2
 *Description: program for solving crossword puzzle recursively
 *Input: text file
 *Output: solved crossword
 */
#include <fstream>
#include <iostream>
#include <vector>

// prototypes
bool crosswordSolved(char[10][10], std::vector<std::string> &, int, int, int &);
bool isAcross(char[10][10], int, int, std::string &, std::vector<std::string> &, int &);
bool isDown(char[10][10], int, int, std::string &, std::vector<std::string> &, int &);
void clearWordAcross(char[10][10], int, int, std::string,
                     std::vector<std::string> &);
void clearWordDown(char[10][10], int, int, std::string,
                   std::vector<std::string> &);
void putWordAcross(char[10][10], int, int, std::string,
                   std::vector<std::string> &, int &);
void putWordDown(char[10][10], int, int, std::string,
                 std::vector<std::string> &, int &);

int main()
{
    // declared vars
    std::ifstream iFile;
    std::string file;
    std::string word;
    char arr[10][10] = {};
    std::vector<std::string> words;

    char c = 0;
    int index = 0;

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

    // loop until 9th row
    if (crosswordSolved(arr, words, 0, 0, index))
    {
        for (int i = 0; i < 10; i++)
        {
            // loop until 9th col
            for (int j = 0; j < 10; j++)
            {
                std::cout << arr[i][j];
            }
            std::cout << std::endl;
        }
    }
}

bool crosswordSolved(char grid[10][10], std::vector<std::string> &words, int row,
                     int col, int &wordsIndex)
{
    // declared vars
    bool placeForWord = false;
    int counter = 0;
    std::string word = "";

    // base case 1,,, no words in the words list = all used up
    if (words.size() == 0)
    {
        return true;
    }

    word = words[wordsIndex];

    // loop in 10x10grid
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            // check if it is - or first letter of word
            if (grid[i][j] == '-' || grid[i][j] == word[0] && grid[i][j + 1] == '-' || grid[i][j] == word[0] && grid[i + 1][j] == '-' 
                || grid[i][j] == 'L' && grid[i + 1][j] == '-' || grid[i][j] == 'G' && grid[i][j + 1] == '-')
            {
                // set row & col then break
                row = i;
                col = j;
                placeForWord = true;
                break;
            }
        }
        // if true then break from loop
        if (placeForWord)
            break;
    }

    // loop while index is less than word list size
    while (wordsIndex < words.size())
    {
        // set word at index
        word = words[wordsIndex];

        // check if can put word across
        if (isAcross(grid, row, col, word, words, wordsIndex))
        {
            // call function to put word across
            putWordAcross(grid, row, col, word, words, wordsIndex);
            // update counter
            counter++;
            // recursive call
            if (crosswordSolved(grid, words, row, col, wordsIndex))
            {
                return true;
            }

            // if recursive call returned false undo word placement
            clearWordAcross(grid, row, col, word, words);
            // update counter since removed it
            counter--;

            // check if there are 2 words left and counter = 0
            // to return false to call since it was infinite looping
            if (counter == 0 && words.size() == 2)
            {
                // set index
                wordsIndex = 0;
                return false;
            }

            // set index
            wordsIndex = 0;
        }
        // check if can put word down
        else if (isDown(grid, row, col, word, words, wordsIndex))
        {
            // call to func to put word down
            putWordDown(grid, row, col, word, words, wordsIndex);
            // update
            counter++;
            // recursive call
            if (crosswordSolved(grid, words, row, col, wordsIndex))
            {
                return true;
            }

            // if recursive call returned false undo word placement
            clearWordDown(grid, row, col, word, words);
            // update
            counter--;

            // check if counter = 0 and if 3 words left
            // was infite looping so make it return false
            if (counter == 0 && words.size() == 3)
            {
                // set
                wordsIndex = 0;
                return false;
            }

            // set
            wordsIndex = 0;
        }
        // if cant put anything down at all then go to next word
        else
        {
            wordsIndex++;
        }
    }

    return false;
}

bool isAcross(char grid[10][10], int row, int col, std::string &word, std::vector<std::string> &words, int &wordsIndex)
{
    // get length of word passed
    int len = word.length();

    // loop until lenght of word for each char
    for (int i = 0; i < len; i++)
    {
        //  check if it can have word and then if char is in right place & right letter
        if (grid[row][col + i] == '-' || grid[row][col + i] == word[i])
        {
            // check if right length
            if (i == len - 1 && grid[row][col + len + 1] != '-')
            {
                return true;
            }
        }
        else
        {
            return false;
        }
    }

    return false;
}

bool isDown(char grid[10][10], int row, int col, std::string &word, std::vector<std::string> &words, int &wordsIndex)
{
    // get length of word passed
    int len = word.length();

    // loop until lenght of word for each char
    for (int i = 0; i < len; i++)
    {
        //  check if it can have word and then if char is in right place & right letter
        if (grid[row + i][col] == '-' || grid[row + i][col] == word[i])
        {
            // check if right length
            if (i == len - 1 && grid[row + len + 1][col] != '-')
            {
                return true;
            }
        }
        else
        {
            return false;
        }
    }

    return false;
}

void putWordAcross(char grid[10][10], int row, int col, std::string word,
                   std::vector<std::string> &words, int &wordsIndex)
{
    // get length of word passed
    int len = word.length();

    // put word into specified spot
    for (int i = 0; i < len; i++)
    {
        grid[row][col + i] = word[i];
    }

    // remove word from list
    for (int i = 0; i < words.size(); i++)
    {
        // check if it is word
        if (words[i] == word)
        {
            words.erase(words.begin() + i);
        }
    }

    // check if word list only has 1 word and index isnt 0
    if (words.size() == 1 && wordsIndex != 0)
    {
        // then reset index back to 0
        wordsIndex--;
    }

    // check if index is at end of list/last word
    if (wordsIndex == words.size())
        wordsIndex = 0;
}

void putWordDown(char grid[10][10], int row, int col, std::string word,
                 std::vector<std::string> &words, int &wordsIndex)
{
    // get length of word passed
    int len = word.length();

    // put word into specified spot
    for (int i = 0; i < len; i++)
    {
        grid[row + i][col] = word[i];
    }

    // remove word from list
    for (int i = 0; i < words.size(); i++)
    {
        // check if it is word in list
        if (words[i] == word)
        {
            words.erase(words.begin() + i);
        }
    }

    // check if word list only has 1 word and index isnt 0
    if (words.size() == 1 && wordsIndex != 0)
    {
        // then reset index back to 0
        wordsIndex--;
    }

    // check if index is at end of list/last word
    if (wordsIndex == words.size())
    {
        wordsIndex = 0;
    }

    // check if index is 1 then reset it back to 0
    if (wordsIndex == 1)
    {
        wordsIndex = 0;
    }
}

void clearWordAcross(char grid[10][10], int row, int col, std::string word,
                     std::vector<std::string> &words)
{

    // get length of word passed
    int len = word.length();

    // remove word from specified spot
    for (int i = 0; i < len; i++)
    {
        // check if letter is a part of another word, then dont remove if
        // will have + if not a part of another word
        if (grid[row + 1][col + i] == '+' || grid[row - 1][col + i] == '+')
            grid[row][col + i] = '-';
    }

    // add word back to list
    words.push_back(word);
}

void clearWordDown(char grid[10][10], int row, int col, std::string word,
                   std::vector<std::string> &words)
{
    // get length of word passed
    int len = word.length();

    // remove word from specified spot
    for (int i = 0; i < len; i++)
    {
        // check if letter is a part of another word, then dont remove if
        // will have + if not a part of another word
        if (grid[row + i][col + 1] == '+' || grid[row + i][col - 1] == '+')
        {
            grid[row + i][col] = '-';
        }
    }

    // add word back to list
    words.push_back(word);
}