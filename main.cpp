#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

#include "Graph.hpp"
#include "GraphAlgorithms.hpp"
#include "Environment.hpp"
#include "Timer.hpp"

enum Operation
{
    OP_CONNECTEDCOMPONENTS, OP_STRONGLYCONNECTEDCOMPONENTS, OP_NOP
};

std::vector<Graph> nop(const Environment&)
{
    return std::vector<Graph>();
}

using GraphAlgorithm = std::vector<Graph> (*)(const Environment&);
const GraphAlgorithm operations[3] =
{
        [OP_CONNECTEDCOMPONENTS] = findAllConnectedComponents,
        [OP_STRONGLYCONNECTEDCOMPONENTS] = findAllStronglyConnectedComponents,
        [OP_NOP] = nop
};

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

Operation selectOperation(const char* str)
{
    if (!strcmp(str, "concomp"))
        return OP_CONNECTEDCOMPONENTS;
    if (!strcmp(str, "strconcomp"))
        return OP_STRONGLYCONNECTEDCOMPONENTS;
    return OP_NOP;
}

int main(int argc, char **argv)
{
    Timer tmr;
    if (argc != 3)
    {
        std::cout
                << "Program needs an operation and a graph file to operate on."
                << std::endl;
        return 0;
    }
    Environment env = Environment(argv[2]);

    std::cerr << "Elapsed time (load env): " << tmr.elapsed() << "s"
            << std::endl;

    env.printStats();

    doOperation(env, operations[selectOperation(argv[1])]);

    return 0;
}
