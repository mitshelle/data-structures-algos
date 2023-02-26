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
#include "priorityQ.h"

// function to capitalize whole word
std::string capitalize(std::string str)
{
    for (int i = 0; i < str.size(); i++)
    {
        str[i] = toupper(str[i]);
    }
    return str;
}

int main()
{
    std::ifstream iFile;
    std::string input, racer;
    priorityQ<std::string, double> marioKart;
    // to see if racer has already been update each interval
    std::unordered_map<std::string, int> updates;
    std::vector<std::string> racers;
    std::unordered_map<std::string, std::string> rName;
    int count = 1, lead = 1;
    int racersUpdated = 0, amtOfRacers = 0;
    double updatedDist = 0.0, initial = 50.0;

    // prompt for file
    std::cout << "Enter racer file: ";
    std::cin >> input;

    // open file
    iFile.open(input);

    // get the letters
    while (true)
    {
        // read in
        iFile >> racer;
        if (iFile.eof())
            break;
        // map for name that is all regular
        rName[capitalize(racer)] = racer;
        // capitalize name
        racer = capitalize(racer);
        // for the actual race
        marioKart.push_back(racer, initial);
        racers.push_back(racer);
        amtOfRacers++;
    }

    do
    {
        std::cout << "\n\nInterval " << count << std::endl
                  << std::endl;

        // CHECK WHAT RACERS FINISHED THE RACE AND OUTPUT IN THE ORDER FINISHED
        while (marioKart.get_front() <= 0 && amtOfRacers > 0)
        {
            // not in the race anymore 
            updates[marioKart.get_front_key()] = -1;
            // find in list                     
            auto it = rName.find(marioKart.get_front_key());
            std::cout << lead << " " << it->second << std::endl;
            // remove from race 
            marioKart.pop_front();
            amtOfRacers--;
            lead++;

            if (marioKart.isEmpty())
                return EXIT_SUCCESS;
        }

        do
        {
            // output 
            std::cout << "\nEnter racer's name: ";
            std::cin >> input;

            // just make it not case sensitive
            input = capitalize(input);

            if (input == "DONE")
                break;

            // check if racer has been updated before
            if (updates[input] == 1)
            {
                std::cout << "\nAlready updated racer at this interval!\n";
                continue; // could be continue??
            }

            // check if racer has finished race
            // is in the list but val is -1
            if (updates[input] == -1)
            {
                std::cout << "\nRacer has already finished the race!\n";
                continue; // could be continue??
            }

            std::cout << "Enter updated distance: ";
            std::cin >> updatedDist;

            // update the distance for the specified racer
            marioKart.decreaseKey(input, updatedDist);
            // to keep track of which racers have been updated            
            updates[input] = 1;
            racersUpdated++;
        } while (input != "DONE" && racersUpdated != amtOfRacers);

        // update count for interval
        count++;
        // reset
        racersUpdated = 0;
        // no clear, just reset all the val if still in the race
        for (int i = 0; i < racers.size(); i++)
        {
            if (updates[racers[i]] != -1)
                updates[racers[i]] = 0;
        }

    // loop until all racers have finished
    } while (!marioKart.isEmpty());
}