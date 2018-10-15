/*
 * Operations.hpp
 *
 *  Created on: Oct 14, 2018
 *      Author: erik
 */

#ifndef OPERATIONS_HPP_
#define OPERATIONS_HPP_

#include <vector>

#include "GraphAlgorithms.hpp"

class Environment;
class Graph;

enum Operation
{
    OP_CONNECTEDCOMPONENTS,
    OP_STRONGLYCONNECTEDCOMPONENTS,
    OP_STRONGLYCONNECTEDCOMPONENTSFAST,
    OP_SIZE
};

using GraphAlgorithm = std::vector<Graph> (*)(const Environment&);

struct {
    const char* const name;
    GraphAlgorithm function;
}
const operations[OP_SIZE] = {
        [OP_CONNECTEDCOMPONENTS] = { "concomp", findAllConnectedComponents },
        [OP_STRONGLYCONNECTEDCOMPONENTS] = { "strconcomp", findAllStronglyConnectedComponents },
        [OP_STRONGLYCONNECTEDCOMPONENTSFAST] = { "strconcompfast", findAllStronglyConnectedComponentsFast }
};



void printAvailableOperations();
void selectOperation(const char* str, const Environment& env);

#endif /* OPERATIONS_HPP_ */
