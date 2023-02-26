/*
 *Name: Michelle McGowan, 2001813382, CS 302-1003, Assignment 6
 *Description: custom hashmap
 *Input: file, order food
 *Output: menu & total
 */

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <iomanip>
#include "hashMap.h"

// function to capitalize whole word
std::string capitalize(std::string str)
{
    for (int i = 0; i < str.size(); i++)
    {
        str[i] = toupper(str[i]);
    }
    return str;
}

struct menuType
{
    menuType() : price(0), quantity(0.0)
    {
        price = 0.0;
        quantity = 0;
    }
    menuType(double p, int q) : price(p), quantity(q)
    {
        price = p;
        quantity = q;
    }
    // operator used in the hashMap :: resize(int) function
    // that is used to determine if a node’s value is not
    // an empty entry
    bool operator!=(const menuType &m)
    {
        return quantity != m.quantity && price != m.price;
    }

    int quantity;
    double price;
};

int main()
{
    // declared vars
    std::ifstream iFile;
    std::string name, foodInput, input;
    int quanInput = 0, quant = 0, count = 0;
    double runningCost = 0;
    double price = 0.0;
    std::vector<std::string> itemNames;
    // HASHHHHHHHHHH
    hashMap<std::string, menuType> krustyKrabMenu;

    // prompt for file
    std::cout << "Enter krusty krab menu: ";
    std::cin >> input;

    // open file
    iFile.open(input);

    // get the letters
    while (!iFile.eof())
    {
        // read in
        iFile >> name >> price >> quant;
        itemNames.push_back(name);
        // call to func to uppercase str
        name = capitalize(name);
        krustyKrabMenu[name] = menuType(price, quant);
        // std::cout << "-----------------------------------------------------" << std::endl;
        // {
        //     for (auto i = (*it).begin(); i != (*it).end(); i++)
        //     {
        //         std::cout << (*i).key << " " << (*i).value.price << " - " << (*i).value.quantity << " ";
        //     }
        //     std::cout << std::endl;
        // }

        // std::cout << "-----------------------------------------------------" << std::endl
        //           << std::endl;
    }

    do
    {
        std::cout << "Item Name" << std::setw(28)
                  << "Price" << std::setw(10) << "Quantity" << std::endl;
        // output menu
        for (int i = 0; i < itemNames.size(); i++)
        {
            if (krustyKrabMenu[capitalize(itemNames[i])].quantity != 0)
            {
                std::cout << itemNames[i] << std::setw(38 - itemNames[i].length())
                          << std::fixed << std::setprecision(2) << krustyKrabMenu[capitalize(itemNames[i])].price
                          << std::setw(10) << krustyKrabMenu[capitalize(itemNames[i])].quantity << "\n";
            }
        }

        std::cout << "\n";
        // prompt user
        std::cout << "Are you going to order today, sir? ";
        std::cin >> foodInput;
        // call to func to uppercase str

        foodInput = capitalize(foodInput);
        // std::cout << krustyKrabMenu[foodInput].price << "|" << krustyKrabMenu[foodInput].quantity << std::endl;

        // if not in list or not in stock so quan is 0
        if (krustyKrabMenu[foodInput].quantity == 0 || krustyKrabMenu[foodInput].price == 0)
        {
            while (krustyKrabMenu[foodInput].quantity == 0 || krustyKrabMenu[foodInput].price == 0.0)
            {
                // error message
                std::cout << "We serve food here, sir" << std::endl;
                std::cin.clear();
                std::cin.ignore(40, '\n');
                std::cout << "\n";
                // prompt user
                std::cout << "Are you going to order today, sir? ";
                std::cin >> foodInput;
                foodInput = capitalize(foodInput);
            }
        }

        // prompt
        std::cout << "Great, excellent choice" << std::endl;
        std::cout << "How many? ";
        std::cin >> quanInput;

        // if quan wanted is bigger than quan have
        if (krustyKrabMenu[foodInput].quantity < quanInput)
        {
            // loop until quantity wanted is within quantity have
            while (krustyKrabMenu[foodInput].quantity < quanInput)
            {
                std::cout << "Try again: ";
                std::cin.clear();
                std::cin.ignore(40, '\n');
                std::cin >> quanInput;
            }
        }

        // output
        std::cout << "Well done, took you long enough\n";
        // subtract quan have from quan wants
        krustyKrabMenu[foodInput].quantity -= quanInput;
        // cost of quantity wants * price
        runningCost += krustyKrabMenu[foodInput].price * quanInput;
        count++;

        // if ordered everything on menu
        if (count == itemNames.size())
        { // maybe -1 or maybe just size ????
            std::cout << "Looks like you ordered everything on the menu, you know what that means\n";
            break;
        }
        else
        {
            std::cout << "Will this complete your order? ";
            std::cin >> input;
            std::cout << "\n";
        }

    } while (input == "n" || input == "N");

    // output total
    std::cout << "Your order comes out to $" << runningCost << "\n";
    std::cout << "Have a great day...barnacle head\n";
}