#include <iostream>
#include <vector>

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

int main(int argc, char **argv)
{
    Timer tmr;
    if (argc != 2)
    {
        std::cout << "Program needs a file with graph to operate on."
                << std::endl;
        return 0;
    }
    Environment env = Environment(argv[1]);

    std::cout << "Elapsed time: " << tmr.elapsed() << "s" << std::endl;

    printStats(env);

    tmr.reset();

    std::vector<Graph> conGraphs = findAllConnectedComponents(env);

    std::cout << "Elapsed time: " << tmr.elapsed() << "s" << std::endl;
    tmr.reset();

    for (const Graph& g: conGraphs)
    {
        printContainer(g.getVertices().cbegin(), g.getVertices().cend(), ' ');
        std::cout << std::endl;
    }

    std::cout << "Elapsed time: " << tmr.elapsed() << "s" << std::endl;

    return 0;
}
