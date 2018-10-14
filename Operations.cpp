/*
 * Operations.cpp
 *
 *  Created on: Oct 14, 2018
 *      Author: erik
 */

#include "Operations.hpp"

#include <algorithm>
#include <cstring>
#include <iostream>

#include "Environment.hpp"
#include "Graph.hpp"
#include "Timer.hpp"

template<class T>
void doOperation(const Environment& env, T func)
{
    Timer tmr;

    std::vector<Graph> conGraphs = func(env);

    std::cerr << "Elapsed time (operation): " << tmr.elapsed() << "s"
            << std::endl;

    std::for_each(conGraphs.begin(), conGraphs.end(), [] (const Graph& g)
    {   g.printNodes();});
}

void selectOperation(const char* str, const Environment& env)
{
    for (size_t i = 0; i < OP_SIZE; ++i)
    {
        if (!strcmp(str, operations[i].name))
        {
            doOperation(env, operations[i].function);
            return;
        }
    }
    std::cout << "No operation selected." << std::endl;
    printAvailableOperations();
}

void printAvailableOperations()
{
    for (size_t i = 0; i < OP_SIZE; ++i)
    {
        std::cout << operations[i].name << std::endl;
    }
}
