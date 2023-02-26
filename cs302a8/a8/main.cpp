/*
 *Name: Michelle McGowan, 2001813382, CS 302-1003, Assignment 8
 *Description: dfs
 *Input: files for map and station info, starting station
 *Output: path
 */

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <stack>
#include <unordered_map>

struct edge
{
    // constructor
    edge() : station(), distance(0.0)
    {
        station = "";
        distance = 0.0;
    }
    edge(std::string s, double d) : station(s), distance(d)
    {
        station = s;
        distance = d;
    }

    // denotes the station name that an edge goes to
    std::string station;
    // distance of this edge
    double distance;
};

// func prototype
std::stack<std::string> _88MPH(std::unordered_map<std::string, std::list<edge>>,
                               std::unordered_map<std::string, double>, std::string, double &);

int main()
{
    std::ifstream iFile;
    std::string input, st1, st2;
    double dist = 0.0, battPower = 0.0;
    std::unordered_map<std::string, std::list<edge>> mapOfChargingStations;
    std::unordered_map<std::string, double> chargingStation;
    std::stack<std::string> reversedPath;

    // prompt for file
    std::cout << "Enter charging station map: ";
    std::cin >> input;

    iFile.open(input);

    // get the map
    while (true)
    {
        // read in
        iFile >> st1 >> st2 >> dist;
        if (iFile.eof())
        {
            break;
        }
        mapOfChargingStations[st1].push_back(edge(st2, dist));
    }

    iFile.close();

    // prompt for file
    std::cout << "Enter charging station info file: ";
    std::cin >> input;

    iFile.open(input);

    // get the info for charging stations
    while (true)
    {
        // read in
        iFile >> st1 >> dist;
        if (iFile.eof())
        {
            break;
        }
        chargingStation[st1] = dist;
    }

    iFile.close();

    // prompt for start loc & initial batt power
    std::cout << "Enter starting location and initial battery power: ";
    std::cin >> input >> battPower;

    // call to func to get path & return a stack
    auto path = _88MPH(mapOfChargingStations, chargingStation, input, battPower);

    // check if path is empty??? means no path found for criteria
    if (path.empty())
    {
        // output & exit
        std::cout << "We are stuck in the space time continuum, Marty!" << std::endl;
        return EXIT_SUCCESS;
    }

    // output
    std::cout << "Path: ";

    // output the path stack
    while (!path.empty())
    {
        std::cout << path.top();
        path.pop();

        // if not empty then print arrow
        if (!path.empty())
        {
            std::cout << " -> ";
        }
    }

    // output
    std::cout << "\n";
    std::cout << "Something needs to be done about your kids, Marty!" << std::endl;
}

/*
- from node starting from, see if can go to neighbors to get battpow needed
- do batt pow calculations, check if it is ok, push it onto stack
- if cannot gotta return back with empty stack and go to next neighbor to check
- if it is ok, go from that node to that node's neighbors to check
- return path once reached or if all nodes have been visited and cannot make path
*/

// adjList, charginstn for the watts, currently at station, battery power
std::stack<std::string> _88MPH(std::unordered_map<std::string, std::list<edge>> mapOfChargingStn,
                               std::unordered_map<std::string, double> chargingStn, std::string currStn, double &battPow)
{
    // declared vars
    std::stack<std::string> path;
    std::string station;

    // traverse map of neighbores for curr station
    for (auto neighbor = mapOfChargingStn[currStn].begin();
         neighbor != mapOfChargingStn[currStn].end(); neighbor++)
    {
        path.push(currStn);
        // lose some power traveling to the nxt stn
        battPow -= (*neighbor).distance * 0.346;
        // add to the power however much that stn has
        battPow += chargingStn[(*neighbor).station];

        // path.push((*neighbor).station);

        // if reached the amt needed
        if (battPow >= 62.5 && battPow <= 75.5)
        {
            path.push((*neighbor).station);
            return path;
        }

        // if path doesnt work then remove from stack
        if (battPow <= 0)
        {
            // reset
            battPow += (*neighbor).distance * 0.346;
            battPow -= chargingStn[(*neighbor).station];
            path.pop();
            // path.pop();
            return path;
        }

        // recursive call to function w/ neighbor to get their neighbors
        auto returningPath = _88MPH(mapOfChargingStn, chargingStn, (*neighbor).station, battPow);

        // if is empty go to next neigbor
        if (returningPath.empty())
        {
            // reset
            battPow += (*neighbor).distance * 0.346;
            battPow -= chargingStn[(*neighbor).station];
            path.pop();
            // path.pop();
            continue;
        }
        else
        {
            // not empty
            // for order of stack to be right
            int size = returningPath.size();
            if (returningPath.size() % 2 == 0)
            {
                station = path.top();
                path.pop();
            }

            // push to stack until the stack that was returned
            // is empty
            while (!returningPath.empty())
            {
                path.push(returningPath.top());
                returningPath.pop();
            }

            // for order of stack to be right
            if (size % 2 == 0)
            {
                path.push(station);
            }

            // leave
            break;
        }
    }

    return path;
}
