#include <iostream>
#include <vector>
#include <cstring>

#include "Graph.hpp"
#include "GraphAlgorithms.hpp"
#include "Environment.hpp"
#include "Timer.hpp"

void printStats(const Environment& env)
{
    std::cout << "Number of vertices: " << env.getVertexSize() << std::endl;
    std::cout << "Number of edges: " << env.getEdgeSize() << std::endl;
}

template<class Iterator>
void printContainer(Iterator first, Iterator last, char delim)
{
    if (first != last)
    {
        std::cout << (*first)->getID();
    }

    for (Iterator iter = ++first; iter != last; ++iter)
    {
        std::cout << delim << (*iter)->getID();
    }
}

void getAllConnectedComponents(const Environment& env)
{
    Timer tmr;

    std::vector<Graph> conGraphs = findAllConnectedComponents(env);

    std::cerr << "Elapsed time (findAllConnectedComponents): " << tmr.elapsed() << "s" << std::endl;

    tmr.reset();

    for (const Graph& g: conGraphs)
    {
        printContainer(g.getVertices().cbegin(), g.getVertices().cend(), ' ');
        std::cout << std::endl;
    }

    std::cerr << "Elapsed time (printing): " << tmr.elapsed() << "s" << std::endl;
}

enum Operation
{
    OP_CONNECTEDCOMPONENTS,
    OP_STRONGLYCONNECTEDCOMPONENTS,
    OP_NOP
};

Operation selectOperation(const char* str)
{
    if (!strcmp(str, "concomp"))    return OP_CONNECTEDCOMPONENTS;
    if (!strcmp(str, "strconcomp")) return OP_STRONGLYCONNECTEDCOMPONENTS;
    return OP_NOP;
}

int main(int argc, char **argv)
{
    Timer tmr;
    if (argc != 3)
    {
        std::cout << "Program needs an operation and a graph file to operate on."
                << std::endl;
        return 0;
    }
    Environment env = Environment(argv[2]);

    std::cerr << "Elapsed time (load env): " << tmr.elapsed() << "s" << std::endl;

    printStats(env);

    switch (selectOperation(argv[1]))
    {
        case OP_CONNECTEDCOMPONENTS:
           getAllConnectedComponents(env);
        break;
        case OP_STRONGLYCONNECTEDCOMPONENTS:
        break;
    }

    return 0;
}
